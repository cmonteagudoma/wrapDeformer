#ifndef WRAPDEFORMER_BARYCENTRICDATA_HPP
#define WRAPDEFORMER_BARYCENTRICDATA_HPP

#include <vector>

#include "types.hpp"


class BarycentricData
{

public:

    BarycentricData();
    BarycentricData(int polygonIndex, int triangleIndex, IntVector& vertexIndexList, f32 u, f32 v, f32 w);
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
    void setVertexIndices(IntVector& vertexIndexList);
    
    /** Set mU member
     *
     * @param u     f32 value to set
     */
    void setU(f32 u);
    
    /** Set mV member
     *
     * @param v     f32 value to set
     */
    void setV(f32 v);
    
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
    f32 getU() const;
    
    /** Get mV member value
     *
     * @return  the value of coordinate mV
     */
    f32 getV() const;
    
    /** Get mW member value
     *
     * @return  the value of coordinate mW
     */
    f32 getW() const;

    /** Calculate the position of the (u, v, w) barycentric point in a triangle with the given points as vertices
     *
     * @param a     first vertex of the triangle
     * @param b     second vertex of the triangle
     * @param c     third vertex of the triangle
     * @return      the point projected on the barycentric coordinates
     */
    f3 getBarycentricProjection(f3& a, f3& b, f3& c) const;

private:

    /** Class members
     * 
     */
    int mPolygonIndex;
    int mTriangleIndex;
    f32 mU;
    f32 mV;
    f32 mW;
    IntVector mVertexIndices;
};

#endif // WRAPDEFORMER_BARYCENTRICDATA_HPP