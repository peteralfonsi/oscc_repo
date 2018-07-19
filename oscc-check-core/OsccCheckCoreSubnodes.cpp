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
    ps_timestamp _updateInterval{50000}; //idk if this is a reasonable amount
    std::unique_ptr<EnableDisableMessageGenerator> _enableDisableCommandGenerator;
    std::unique_ptr<SteeringCommandGenerator> _steeringCommandGenerator;
    

public:
    OsccCheckPublisherNode() { //directly copied from Publisher.cpp, unsure if we want to change things
        setNodeType( PSYNC_NODE_TYPE_API_USER );
        setDomainID( PSYNC_DEFAULT_DOMAIN );
        setSDFID( PSYNC_SDF_ID_INVALID );
        setFlags( NODE_FLAGS_VALUE | PSYNC_INIT_FLAG_STDOUT_LOGGING );
        setNodeName( node_name );
    }
    void initStateEvent() override {

        _steeringCommandGenerator = 
            std::unique_ptr< SteeringCommandGenerator >{ //we dont know what goes in the template brackets
                new SteeringCommandGenerator(*this);
            }
        _enableDisableCommandGenerator = 
            std:unique_ptr< EnableDisableMessageGenerator>{
                new EnableDisableMessageGenerator(*this);
            }

        _enableDisableCommandGenerator.generateEnableCommand();
        _enableDisableCommandGenerator.publishCommand();

    }
    void okStateEvent() override {

        _steeringCommandGenerator->generateCommand();
        _steeringCommandGenerator->publishCommand();
        polysync::sleepMicro(_updateInterval);
        

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
