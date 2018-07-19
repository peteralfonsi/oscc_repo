// based on Publisher.cpp

#include <iostream>
#include <PolySyncNode.hpp>
#include <PolySyncDataModel.hpp>

using namespace std;

#ifndef NODE_FLAGS_VALUE
#define NODE_FLAGS_VALUE (0)
#endif

class OsccCheckPublisherNode : public polysync::Node {

private:
    const string node_name = "oscc-check-publish-cpp"; // i dont know if this is important or not?
    const string enable_disable_msg_name = "oscc_enable_disable_msg";
    const string steering_command_msg_name = "oscc_steering_command_msg";
    const bool debug = true;
    int message_number = 0;

    //ps_msg_type _messageType;

public:
    OsccCheckPublisherNode() { //directly copied from Publisher.cpp, unsure if we want to change things
        setNodeType( PSYNC_NODE_TYPE_API_USER );
        setDomainID( PSYNC_DEFAULT_DOMAIN );
        setSDFID( PSYNC_SDF_ID_INVALID );
        setFlags( NODE_FLAGS_VALUE | PSYNC_INIT_FLAG_STDOUT_LOGGING );
        setNodeName( node_name );
    }
    void initStateEvent() override {
        polysync::datamodel::OsccEnableDisableMsg enable_message( *this);
        enable_message.setHeaderTimestamp(polysync::getTimestamp());
        std::cout << "enable status:" << enable_message.getEnableControl() << std::endl;
        enable_message.print();
        enable_message.setEnableControl(1); //??
        enable_message.publish();

        //std::cout << "Message Type:" << getMessageTypeByName(steering_command_msg_name);
        //_messageType = getMessageTypeByName(steering_command_msg_name);
    }
    void okStateEvent() override {
        polysync::datamodel::OsccSteeringCommandMsg message(*this); //unsure about message(*this)
        //list of messages: http://docs.polysync.io/releases/2.1.1/api-docs/cpp-data-model/control/platformsteeringcommandmessage/
        message.setHeaderTimestamp(polysync::getTimestamp());
        /*(if (!message.getEnabled()) {
            message.setEnabled(1); //enables steering
        }*/
        //message.setSteeringCommandKind(STEERING_COMMAND_ANGLE); //unsure? torque is not an option http://docs.polysync.io/releases/2.1.1/api-docs/c-data-model/control/enumerations/#ps-steering-command-kind
        //float angle = message_number*30 - 90 * (6.28/360);
        float torque = message_number * 0.1 - 0.3;
            message.setSteeringTorque(torque);

        //message.setSteeringWheelAngle()


        if (debug) {
            message.print(); //should this be ::?
            std::cout << "Attempted torque: " << torque << std::endl;
            std::cout << "Actual torque: " << message.getSteeringTorque() << std::endl;
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
    void releaseStateEvent() override {
        polysync::datamodel::OsccEnableDisableMsg disable_message;
        disable_message.setEnableControl(0);
        std::cout << "Steering control is: " << disable_message.getEnableControl() << std::endl;

    }

};

int main(){
    OsccCheckPublisherNode oscccheckpublishernode;

    oscccheckpublishernode.connectPolySync();

    return 0;
}
