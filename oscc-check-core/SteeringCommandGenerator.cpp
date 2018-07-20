#include "SteeringCommandGenerator.hpp"

using namespace std;

SteeringCommandGenerator::SteeringCommandGenerator(polysync::Node & node) : 
    _message(node)
    {
        _defaultTorque = 0.0;
        initializeMessage();
        _messageNumber = 0;
    }

void SteeringCommandGenerator::initializeMessage() {
    polysync::datamodel::SensorDescriptor descriptor; 
    descriptor.setId(4); //may not be correct
    descriptor.setTransformParentId(PSYNC_COORDINATE_FRAME_LOCAL); //unneeded? 
    descriptor.setType(PSYNC_SENSOR_KIND_NOT_AVAIABLE); //maybe also wrong
    _message.setSensorDescriptor(descriptor);
    _message.setHeaderTimestamp(polysync::getTimestamp());
    _message.setSteeringTorque(_defaultTorque);
}

void SteeringCommandGenerator::generateCommand() {
    _initializeMessage();
    float torque = _messageNumber * 0.1 - 0.3;
    _message.setSteeringTorque(torque);

}

void SteeringCommandGenerator::publishCommand() {
    _message.publish();
    _messageNumber++;
    if (_messageNumber) >= 7 {
        _messageNumber = 0;
    }
}