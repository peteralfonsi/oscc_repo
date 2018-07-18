// based on Publisher.cpp

#include <iostream>
#include <PolySyncNode.hpp>
#include <PolySyncDataModel.hpp>

using namespace std;

class OsccCheckPublisherNode : public polysync::Node { 

private: 
    const string node_name = "oscc-check-publish-cpp"; // i dont know if this is important or not?
    const string steering_command_msg_name = "ps_platform_steering_command_msg";
    const bool debug = true;
    int message_number = 0;

    ps_msg_type _messageType;

public: 
    OsccCheckPublisherNode() { //directly copied from Publisher.cpp, unsure if we want to change things
        setNodeType( PSYNC_NODE_TYPE_API_USER );
        setDomainID( PSYNC_DEFAULT_DOMAIN );
        setSDFID( PSYNC_SDF_ID_INVALID );
        setFlags( NODE_FLAGS_VALUE | PSYNC_INIT_FLAG_STDOUT_LOGGING );
        setNodeName( node_name );
    }
    void initStateEvent() override {
        _messageType = getMessageTypeByName(steering_command_msg_name);
    }
    void okStateEvent() override {
        polysync::datamodel::PlatformSteeringCommandMessage message(*this); //unsure about message(*this)
        //list of messages: http://docs.polysync.io/releases/2.1.1/api-docs/cpp-data-model/control/platformsteeringcommandmessage/
        message.setHeaderTimestamp(polysync::getTimestamp());
        if (!message.getEnabled()) {
            message.setEnabled(1); //enables steering
        }
        message.setSteeringCommandKind(STEERING_COMMAND_ANGLE); //unsure? torque is not an option http://docs.polysync.io/releases/2.1.1/api-docs/c-data-model/control/enumerations/#ps-steering-command-kind
        int angle = message_number*30 - 90;
            message.setSteeringWheelAngle(angle);
        
        //message.setSteeringWheelAngle()


        if (debug) {
            message.print(); //should this be ::?
            std::cout << "Attempted angle: " << angle << std::endl;
        }
        message.publish();
        polysync::sleepMicro(3000000); //wait 3s so wheel can be adjusted before next message? idk
        message_number++;
        if (message_number >= 7) {
            message_number = 0;
        }

    }
    void errorStateEvent() override { // these three copied directly
        polysync::sleepMicro(10000);
    }

    void fatalStateEvent() override
    {
        // do nothing, sleep for 10 milliseconds
        polysync::sleepMicro( 10000 );
    }
    
    void warnStateEvent() override
    {
        // do nothing, sleep for 10 milliseconds
        polysync::sleepMicro( 10000 );
    }

};