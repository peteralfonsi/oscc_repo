#include <iostream>
#include <PolySyncNode.hpp>
#include <PolySyncDataModel.hpp>

using namespace std;

#ifndef NODE_FLAGS_VALUE
#define NODE_FLAGS_VALUE (0)
#endif

class OsccEnableNode : public polysync::Node
{
private:
    const string node_name = "oscc-enable-cpp";
    const string subscribe_message_name = "oscc_enable_disable_msg";

    ps_msg_type _messageType;

public:
    OsccEnableNode()
    {
        setNodeType( PSYNC_NODE_TYPE_API_USER );
        setDomainID(PSYNC_DEFAULT_DOMAIN);
        setSDFID(10);
        setFlags(NODE_FLAGS_VALUE | PSYNC_INIT_FLAG_STDOUT_LOGGING);
        setNodeName( node_name );
    }
    ~OsccEnableNode(){}

    void initStateEvent() override
    {
        _messageType = getMessageTypeByName(subscribe_message_name);
        polysync::datamodel::OsccEnableDisableMsg message(*this);
        message.setHeaderTimestamp(polysync::getTimestamp());
        message.setEnableControl(1);
        std::cout << "enable status" << message.getEnableControl() << std::endl;
        message.print();
        message.publish();

    }

    void okStateEvent() override
    {
        polysync::sleepMicro(10000);
    }

    void errorStateEvent() override
    {
        polysync::sleepMicro(10000);
    }

    void releaseStateEvent() override
    {
        polysync::datamodel::OsccEnableDisableMsg disableMsg;
        disableMsg.setEnableControl(0);
        std::cout << "enable status" << disableMsg.getEnableControl() << std::endl;

    }

};

int main()
{
    OsccEnableNode enablenode;
    enablenode.connectPolySync();
    return 0;
}