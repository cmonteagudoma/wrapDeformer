#ifndef DEFORMTRANSFER_H
#define DEFORMTRANSFER_H

#include <maya/MTypeId.h>
#include <maya/MArgList.h>
#include <maya/MObject.h>
#include <maya/MGlobal.h>
#include <maya/MPxDeformerNode.h>


class DeformTransfer : public MPxDeformerNode
{

public:

    DeformTransfer();
    ~DeformTransfer() override;

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

    /** Deform the point with a squash algorithm
     *
     * @param block         the data block of the node
     * @param iter          an iterator for the geometry to be deformed
     * @param mat           matrix to transform the point into world space
     * @param multiIndex    the index of the geometry that we are deforming
     * @return              succeed status
     */
    MStatus deform(
            MDataBlock& block,
            MItGeometry& iter,
            const MMatrix& mat,
            unsigned int multiIndex) override;

    /** This method is called when the deformer is created by the "deformer" command.
     * You can add to the cmds in the MDagModifier cmd in order to hook up any additional nodes that your node needs
     * to operate.
     *
     * @param cmd
     * @return      succeed status
     */
    MStatus accessoryNodeSetup(MDagModifier& cmd) override;


public:

    static MTypeId id;

};

#endif  // DEFORMTRANSFER_H