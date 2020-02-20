#include "barycentricData.hpp"


BarycentricData::BarycentricData() = default;;


BarycentricData::BarycentricData(
        int polygonIndex,
        int triangleIndex,
        IntVector& vertexIndexList,
        f32 u,
        f32 v,
        f32 w) :
        mPolygonIndex(polygonIndex),
        mTriangleIndex(triangleIndex),
        mVertexIndices(vertexIndexList),
        mU(u),
        mV(v),
        mW(w)
{

};


BarycentricData::~BarycentricData() = default;;


void BarycentricData::setPolygonIndex(int polygonIndex)
{
    mPolygonIndex = polygonIndex;
}


void BarycentricData::setTriangleIndex(int triangleIndex)
{
    mTriangleIndex = triangleIndex;
}


void BarycentricData::setVertexIndices(IntVector& vertexIndexList)
{
    mVertexIndices = vertexIndexList;
}


void BarycentricData::setU(f32 u)
{
    mU = u;
}


void BarycentricData::setV(f32 v)
{
    mV = v;
}


void BarycentricData::setW()
{
    mW = 1.0f - mU - mV;
}


int BarycentricData::getPolygonIndex() const
{
    return mPolygonIndex;
}


int BarycentricData::getTriangleIndex() const
{
    return mTriangleIndex;
}


IntVector BarycentricData::getVertexIndices() const
{
    return mVertexIndices;
}


f32 BarycentricData::getU() const
{
    return mU;
}


f32 BarycentricData::getV() const
{
    return mV;
}


f32 BarycentricData::getW() const
{
    return mW;
}


f3 BarycentricData::getBarycentricProjection(f3& a, f3& b, f3& c) const
{
    f3 projection = a*mU + b*mV + c*mW;
    return projection;
}