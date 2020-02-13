#ifndef WRAPDEFORMER_BARYCENTRICDATA_HPP
#define WRAPDEFORMER_BARYCENTRICDATA_HPP

#include <vector>

#include "alias.hpp"


class BarycentricData
{

public:

    BarycentricData();
    BarycentricData(int polygonIndex, int triangleIndex, IntVector &vertexIndexList, float u, float v, float w);
    ~BarycentricData();

    /** Set mPolygonIndex member
     *
     * @param polygonIndex  index to set
     */
    void setPolygonIndex(int polygonIndex);

    /** Set mTriangleIndex member
     *
     * @param triangleIndex  index to set
     */
    void setTriangleIndex(int triangleIndex);
    
    /** Set mVertexIndices member
     *
     * @param vertexIndexList   list of indexes to set
     */
    void setVertexIndices(IntVector &vertexIndexList);
    
    /** Set mU member
     *
     * @param u     float value to set
     */
    void setU(float u);
    
    /** Set mV member
     *
     * @param v     float value to set
     */
    void setV(float v);
    
    /** Set mW member using mU and mV values
     *
     */
    void setW();

    /** Get mPolygonIndex member value
     *
     * @return  the polygon index
     */
    int getPolygonIndex() const;
    
    /** Get mTriangleIndex member value
     *
     * @return  the triangle index
     */
    int getTriangleIndex() const;
    
    /** Get mVertexIndices member value
     *
     * @return  the list of vertex indices
     */
    IntVector getVertexIndices() const;
    
    /** Get mU member value
     *
     * @return  the value of coordinate mU
     */
    float getU() const;
    
    /** Get mV member value
     *
     * @return  the value of coordinate mV
     */
    float getV() const;
    
    /** Get mW member value
     *
     * @return  the value of coordinate mW
     */
    float getW() const;

    /** Calculate the position of the (u, v, w) barycentric point in a triangle with the given points as vertices
     *
     * @param a     first vertex of the triangle
     * @param b     second vertex of the triangle
     * @param c     third vertex of the triangle
     * @return      the point projected on the barycentric coordinates
     */
    f3 getBarycentricProjection(f3 &a, f3 &b, f3 &c) const;

private:

    /** Class members
     * 
     */
    int mPolygonIndex;
    int mTriangleIndex;
    float mU;
    float mV;
    float mW;
    IntVector mVertexIndices;
};

#endif // WRAPDEFORMER_BARYCENTRICDATA_HPP