#ifndef WRAPDEFORMER_HPP
#define WRAPDEFORMER_HPP

#include <vector>
#include <maya/MTypeId.h>
#include <maya/MArgList.h>
#include <maya/MObject.h>
#include <maya/MGlobal.h>
#include <maya/MPxDeformerNode.h>
#include <maya/MFloatArray.h>

#include "barycentricData.hpp"
#include "types.hpp"


class WrapDeformer : public MPxDeformerNode
{

public:

    WrapDeformer();
    WrapDeformer(
            bool initialized,
            std::vector<BarycentricData> barycentricData,
            MatrixVector matrices,
            f3Vector relativePositions);
    ~WrapDeformer() override;

    /** Create new instance of the deformer
     *
     * @return  created instance
     */
    static void* creator();

    /** Initialize the node in terms of attributes and plugs
     *
     * @return  succeed status
     */
    static MStatus initialize();

    /** Deform the mesh applying a wrap algorithm based on barycentric coordinates
     *
     * @param block                 the data block of the node
     * @param iter                  an iterator for the geometry to be deformed
     * @param localToWorldMatrix    matrix to transform the point into world space
     * @param multiIndex            the index of the geometry that we are deforming
     * @return                      succeed status
     */
    MStatus deform(
            MDataBlock& block,
            MItGeometry& iter,
            const MMatrix& localToWorldMatrix,
            unsigned int multiIndex) override;

    /** Attributes of the deformer node in Maya
     *
     */
    static MTypeId id;
    static MObject aTargetMesh;

    /** Class members in plain cpp
     *
     */
    bool mInitialized;
    std::vector<BarycentricData> mBarycentricData;
    MatrixVector mMatrices;
    f3Vector mRelativePositions;

private:

    /** Return the MObject instance of the geometry connected at the given index of the input data block
     *
     * @param block     the data block of the node
     * @param geoIdx    index in the data block array
     * @return          geometry object
     */
    static MObject getInputGeometry(MDataBlock& block, unsigned int geoIdx);

    /** Return the closest point on the given mesh from the given source point
     *
     * @param sourcePoint       the point from the ray will be traced
     * @param meshIntersector   the mesh intersector instance
     * @return                  the point on the given mesh closest to the given source
     */
    MPointOnMesh getClosestPoint(const MPoint& sourcePoint, const MMeshIntersector& meshIntersector) const;

    /** Resolve the projection of a BarycentricData instance using the given point positions
     *
     * @param points                array of point positions
     * @param barycentricData       object with barycentric data, coordinates and vertex indices
     * @return                      the projected point
     */
    inline f3 getBarycentricProjection(const MFloatPointArray& points, const BarycentricData& barycentricData) const;

};

#endif  // WRAPDEFORMER_HPP