#include "barycentricData.hpp"


BarycentricData::BarycentricData() = default;;


BarycentricData::BarycentricData(
        int polygonIndex,
        int triangleIndex,
        IntVector &vertexIndexList,
        float u,
        float v,
        float w) :
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


void BarycentricData::setVertexIndices(IntVector &vertexIndexList)
{
    mVertexIndices = vertexIndexList;
}


void BarycentricData::setU(float u)
{
    mU = u;
}


void BarycentricData::setV(float v)
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


float BarycentricData::getU() const
{
    return mU;
}


float BarycentricData::getV() const
{
    return mV;
}


float BarycentricData::getW() const
{
    return mW;
}


f3 BarycentricData::getBarycentricProjection(f3 &a, f3 &b, f3 &c) const
{
    f3 projection = a*mU + b*mV + c*mW;
    return projection;
}