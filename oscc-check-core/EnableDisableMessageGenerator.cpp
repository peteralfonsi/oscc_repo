#include <PolySyncNode.hpp>
#include <PolySyncDataModel.hpp>

#include "EnableDisableMessageGenerator.hpp"

using namespace std;
using namespace polysync::datamodel;

EnableDisableMessageGenerator::EnableDisableMessageGenerator(polysync::Node & node )
    : 
    _message(node)
{ 
    initializeMessage();
    _enableKey = 1;
    _disableKey = 0;
    _defaultKey = _disableKey;
}

void EnableDisableMessageGenerator::initializeMessage() { 
    polysync::datamodel::SensorDescriptor descriptor; 
    descriptor.setId(4); //may not be correct
    descriptor.setTransformParentId(PSYNC_COORDINATE_FRAME_LOCAL); //unneeded? 
    descriptor.setType(PSYNC_SENSOR_KIND_NOT_AVAIABLE); //maybe also wrong
    _message.setSensorDescriptor(descriptor);
    _message.setHeaderTimestamp(polysync::getTimestamp());
    _message.setEnableControl(_defaultKey);
}

void EnableDisableMessageGenerator::generateEnableCommand() {
    _message.setEnableControl(_enableKey);
}
void EnableDisableMessageGenerator::generateDisableCommand() {
    _message.setEnableControl(_disableKey);
}
void publishCommand() {
    _message.publish()
}
