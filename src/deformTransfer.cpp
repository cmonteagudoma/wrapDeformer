#include "deformTransfer.h"
#include <maya/MFnPlugin.h>
#include <iostream>
#include <omp.h>

void* DeformTransfer::creator() { return new DeformTransfer; }

MStatus DeformTransfer::doIt(const MArgList& argList) {

#pragma omp parallel
    for (unsigned i=0; i<1000; i++) {
        MGlobal::displayInfo("Deform Transfer is here! It's fine");
    }

    return MS::kSuccess;
}

MStatus initializePlugin(MObject obj) {
    MFnPlugin plugin(obj, "Carlos Monteagudo", "1.0", "Any");
    MStatus status = plugin.registerCommand("deformTransfer", DeformTransfer::creator);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    return status;
}

MStatus uninitializePlugin(MObject obj) {
    MFnPlugin plugin(obj);
    MStatus status = plugin.deregisterCommand("DeformTransfer");
    CHECK_MSTATUS_AND_RETURN_IT(status);
    return status;
}