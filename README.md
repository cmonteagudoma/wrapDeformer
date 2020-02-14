# WrapDeformer

WrapDeformer is a deformer node implemented as a Plugin for Maya in C++. It allows you to transfer deformations 
between polygonal objects of different resolutions, ideally from meshes of low detail to meshes of high detail 
in terms of vertex density.

The deformer implements an algorithm based on transform matrices and barycentric coordinates. Each vertex `v` 
of the mesh to deform (`dMesh`) calculates its closest point `cPoint` on the target mesh (`tMesh`), the 
barycentric coordinates of `cPoint` in the closest polygon, the inverse transform matrix `tMat` of that 
polygon and also the relative position of `v` respect to `cPoint`, i.e. `v*`. In order to calculate the 
deformation, each vertex `v` uses the barycentric coordinates and `tMat` to obtain the position  of `cPoint` 
in world space at every single time step, `cPoint*`. Then, applying `v*` over `cPoint*`, we obtain the new
goal position of `v`.
