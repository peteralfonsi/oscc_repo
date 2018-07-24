#include <iostream>
#include <PolySyncNode.hpp>
#include <PolySyncDataModel.hpp>

using namespace std;

#ifndef NODE_FLAGS_VALUE
#define NODE_FLAGS_VALUE (0)
#endif

class YourNode : public polysync::Node
{
private:
    const string node_name = "your-node"; //edit when actually creating code w this
    const string subscribe_msg_name = "your-subscribe"; //edit when actually creating code w this

    ps_msg_type _messageType;

public:

    YourNode()
    {
        //edit when actually creating code w this
        setNodeType(YOUR_PSYNC_CONSTANTS);
        setDomainID(YOUR_PSYNC_CONSTANTS);
        setSFID(YOUR_PSYNC_CONSTANTS);
        setFlags(YOUR_PSYNC_CONSTANTS);
        
        //this one is actually correct
        setNodeName(node_name);
    }
    ~YourNode() //apparently this is a deconstructor, 
    //not sure if it requires arguments in some cases

    void initStateEvent() override
    {

    }
    void errorStateEvent() override
    {

    }
    void fatalStateEvent() override
    {

    }
    void warnStateEvent() override
    {

    }
    void okStateEvent() override
    {
        //your main code here
    }
    void releaseStateEvent() override
    {
        disconnectPolysync();
    } //release state should be triggered by error and fatal? not sure tho


}

int main(){
    YourNode your_node; //calls an instance of the node class
    your_node.connectPolySync();
    return 0;
}