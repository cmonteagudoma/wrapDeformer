#ifndef HELLOWORLD_H
#define HELLOWORLD_H

#include <maya/MArgList.h>
#include <maya/MObject.h>
#include <maya/MGlobal.h>
#include <maya/MPxCommand.h>

class DeformTransfer : public MPxCommand {
public:
    DeformTransfer() {};
    virtual MStatus doIt(const MArgList& argList);
    static void* creator();
};
#endif