#include "deformTransfer.h"
#include <maya/MTypeId.h>
#include <maya/MFnPlugin.h>
#include <iostream>


MTypeId DeformTransfer::id(0x8000c);


DeformTransfer::DeformTransfer() = default;


DeformTransfer::~DeformTransfer() = default;


void* DeformTransfer::creator()
{
    return new DeformTransfer;
}


MStatus DeformTransfer::initialize()
{
    // TODO: initialize attributes and plugs
    return MStatus::kSuccess;
}


MStatus DeformTransfer::deform(
        MDataBlock& block,
        MItGeometry& iter,
        const MMatrix& mat,
        unsigned int multiIndex)
{
    MStatus returnStatus;
    // TODO: implement the deformer itself
    return returnStatus;
}


MStatus DeformTransfer::accessoryNodeSetup(MDagModifier& cmd)
{
    MStatus result;
    // TODO (optional): implement creation of dependent and additional nodes of this deformer
    return result;
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
            "deformTransfer",
            DeformTransfer::id,
            DeformTransfer::creator,
            DeformTransfer::initialize,
            MPxNode::kDeformerNode);
    return result;
}


MStatus uninitializePlugin(MObject obj)
{
    MStatus result;
    MFnPlugin plugin(obj);
    result = plugin.deregisterNode(DeformTransfer::id);
    return result;
}