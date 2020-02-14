#include <omp.h>
#include <maya/MFnPlugin.h>
#include <maya/MFnMesh.h>
#include <maya/MItMeshVertex.h>
#include <maya/MFloatPointArray.h>
#include <maya/MMatrix.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MTime.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MMeshIntersector.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnNumericData.h>

#include "wrapDeformer.hpp"


MTypeId WrapDeformer::id(0x00001);
MObject WrapDeformer::aTargetMesh;


WrapDeformer::WrapDeformer()
{
    mInitialized = false;
    mBarycentricData = std::vector<BarycentricData>();
    mMatrices = MatrixVector();
}


WrapDeformer::WrapDeformer(
    bool initialized,
    std::vector<BarycentricData> barycentricData,
    MatrixVector matrices,
    f3Vector relativePositions) :

    mInitialized(initialized),
    mBarycentricData(std::move(barycentricData)),
    mMatrices(std::move(matrices)),
    mRelativePositions(std::move(relativePositions))
{

}


WrapDeformer::~WrapDeformer() = default;


void* WrapDeformer::creator()
{
    return new WrapDeformer;
}


MStatus WrapDeformer::initialize()
{
    MStatus rStatus;
    MFnUnitAttribute unitAttr;
    MFnTypedAttribute typedAttr;
    MFnNumericAttribute numericAttr;

    // Target mesh plug
    aTargetMesh = typedAttr.create("targetMesh", "target", MFnData::kMesh);
    typedAttr.setHidden(true);
    addAttribute(aTargetMesh);

    // Attribute affects
    attributeAffects(aTargetMesh, outputGeom);

    return rStatus;
}


MStatus WrapDeformer::deform(
        MDataBlock& block,
        MItGeometry& iter,
        const MMatrix& localToWorldMatrix,
        unsigned int multiIndex)
{
    MStatus rStatus;
    // Get node plugs
    float envelopeValue = block.inputValue(envelope).asFloat();
    MObject targetMeshObj = block.inputValue(WrapDeformer::aTargetMesh).asMesh();

    // Quick exit: no targetMesh or envelope is zero
    if (targetMeshObj.isNull() || envelopeValue <= 0.0f)
    {
        return rStatus;
    }

    // Get input geometry data
    MObject inMeshObj = getInputGeometry(block, multiIndex);
    MFnMesh inMeshFn(inMeshObj);
    MFloatPointArray points;
    inMeshFn.getPoints(points, MSpace::kWorld);
    //  Get target geometry data
    MFnMesh targetMeshFn(targetMeshObj);
    MFloatPointArray targetPoints;
    targetMeshFn.getPoints(targetPoints, MSpace::kWorld);

    // Initialize rest distance for each vertex at start time
    if (!mInitialized)
    {
        // Clear barycentric data
        mBarycentricData.clear();
        mBarycentricData.resize(points.length());
        // Clear matrices
        mMatrices.clear();
        mMatrices.resize(points.length());
        // Clear matrices
        mRelativePositions.clear();
        mRelativePositions.resize(points.length());

        // Prepare geometry data of the target mesh
        MMeshIntersector targetMeshIntersector;
        targetMeshIntersector.create(targetMeshObj);

        // Iterate over the mesh to initialize the system
        MItMeshVertex vIter(inMeshObj);
        vIter.reset();
        while(!vIter.isDone())
        {
            // Get point and normal of this vertex
            MPoint thisPoint = vIter.position(MSpace::kWorld);
            MVector thisNormal;
            vIter.getNormal(thisNormal);

            // Find closest point on mesh and its normal
            MPointOnMesh pointOnMesh = getClosestPoint(thisPoint, targetMeshIntersector);
            MPoint closestPoint = pointOnMesh.getPoint();
            MFloatVector closestPointNormal = pointOnMesh.getNormal();

            // Build BarycentricData instance
            // Get values of u, v coordinates, polygon id and triangle in polygon id
            float u = 0.0f;
            float v = 0.0f;
            pointOnMesh.getBarycentricCoords(u, v);
            int closestTriangleIndex = pointOnMesh.triangleIndex();
            int closestPolygonIndex = pointOnMesh.faceIndex();
            // Get vertex indices of the closestTriangleIndex of the closestPolygonIndex
            int closestIndices[3];
            targetMeshFn.getPolygonTriangleVertices(closestPolygonIndex, closestTriangleIndex, closestIndices);
            IntVector vertexIndices({closestIndices[0], closestIndices[1], closestIndices[2]});
            // Create and store a BarycentricData target object for this point
            BarycentricData barycentricData;
            barycentricData.setPolygonIndex(closestPolygonIndex);
            barycentricData.setTriangleIndex(closestTriangleIndex);
            barycentricData.setVertexIndices(vertexIndices);
            barycentricData.setU(u);
            barycentricData.setV(v);
            barycentricData.setW();
            mBarycentricData[vIter.index()] = barycentricData;

            // Compute transformation matrix from the barycentric projection
            MFloatPoint aTargetPoint = targetPoints[vertexIndices[0]];
            f3 a = f3{aTargetPoint.x, aTargetPoint.y, aTargetPoint.z};
            MFloatPoint bTargetPoint = targetPoints[vertexIndices[1]];
            f3 b = f3{bTargetPoint.x, bTargetPoint.y, bTargetPoint.z};
            MFloatPoint cTargetPoint = targetPoints[vertexIndices[2]];
            f3 c = f3{cTargetPoint.x, cTargetPoint.y, cTargetPoint.z};
            f3 barycentricProjection = barycentricData.getBarycentricProjection(a, b, c);
            // Normal
            f3 normal = f3{closestPointNormal.x, closestPointNormal.y, closestPointNormal.z};
            // Tangent (ensure that tangent vector length is not zero)
            f3 pointToTangent = a;
            f3 tangentVector = pointToTangent - barycentricProjection;
            if (tangentVector.norm() < 1e-3)
            {
                pointToTangent = b;
            }
            f3 tangent = (pointToTangent - barycentricProjection).normalized();
            // Binormal
            f3 binormal = (tangent.cross(normal)).normalized();
            // Matrix
            Matrix matrix;
            matrix <<   binormal[0], normal[0], tangent[0],
                        binormal[1], normal[1], tangent[1],
                        binormal[2], normal[2], tangent[2];
            mMatrices[vIter.index()] = matrix;

            // Compute relative position of this point to the barycentric projection at rest
            Matrix inverseMatrix = matrix.inverse();
            f3 parsedPoint = f3{(float)thisPoint.x, (float)thisPoint.y, (float)thisPoint.z};
            f3 vectorInWorldSpace = parsedPoint - barycentricProjection;
            mRelativePositions[vIter.index()] = inverseMatrix * vectorInWorldSpace;

            vIter.next();
        }

        // Mark as initialized
        if (!mBarycentricData.empty() && !mMatrices.empty() && !mRelativePositions.empty())
        {
            mInitialized = true;
        }
    }

    // Compute and apply the deformation at every single Node Graph evaluation
#pragma omp parallel for schedule(static)
    for (int idx = 0; idx < points.length(); ++ idx)
    {
        // Compute goal position of this point using barycentric coordinates
        BarycentricData barycentricData = mBarycentricData[idx];
        IntVector vertexIndices = barycentricData.getVertexIndices();
        MFloatPoint aTargetPoint = targetPoints[vertexIndices[0]];
        f3 a = f3{aTargetPoint.x, aTargetPoint.y, aTargetPoint.z};
        MFloatPoint bTargetPoint = targetPoints[vertexIndices[1]];
        f3 b = f3{bTargetPoint.x, bTargetPoint.y, bTargetPoint.z};
        MFloatPoint cTargetPoint = targetPoints[vertexIndices[2]];
        f3 c = f3{cTargetPoint.x, cTargetPoint.y, cTargetPoint.z};
        f3 barycentricProjection = barycentricData.getBarycentricProjection(a, b, c);
        f3 goalPoint = (mMatrices[idx] * mRelativePositions[idx]) + barycentricProjection;
        MPoint goalPointWorldSpace = MPoint(goalPoint[0], goalPoint[1], goalPoint[2]) * localToWorldMatrix;
        MVector weightedDistanceVector = goalPointWorldSpace - MVector(points[idx]);
        points[idx] += weightedDistanceVector * envelopeValue;
    }

    // Update geometry and return
    inMeshFn.setPoints(points, MSpace::kWorld);
    return rStatus;
}


MObject WrapDeformer::getInputGeometry(MDataBlock& block, unsigned int geoIdx)
{
    MArrayDataHandle inputArray = block.outputArrayValue(input);
    inputArray.jumpToElement(geoIdx);
    MObject inputObj = inputArray.outputValue().child(inputGeom).asMesh();
    return inputObj;
}


MPointOnMesh WrapDeformer::getClosestPoint(const MPoint &sourcePoint, const MMeshIntersector &meshIntersector) const
{
    MPointOnMesh pointOnMesh;
    meshIntersector.getClosestPoint(sourcePoint, pointOnMesh, 100.0f);
    return pointOnMesh;
}


MStatus initializePlugin(MObject obj)
{
    MStatus result;
    MFnPlugin plugin(
            obj,
            "Carlos Monteagudo",
            "1.0",
            "Any");
    result = plugin.registerNode(
            "wrapDeformer",
            WrapDeformer::id,
            WrapDeformer::creator,
            WrapDeformer::initialize,
            MPxNode::kDeformerNode);
    return result;
}


MStatus uninitializePlugin(MObject obj)
{
    MStatus result;
    MFnPlugin plugin(obj);
    result = plugin.deregisterNode(WrapDeformer::id);
    return result;
}