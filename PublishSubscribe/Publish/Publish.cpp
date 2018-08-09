#include <iostream>
#include <PolySyncNode.hpp>
#include <PolySyncDataModel.hpp>

using namespace std;

/**
 * Node flags to be OR'd with node flags during the build.
 *
 */
#ifndef NODE_FLAGS_VALUE
#define NODE_FLAGS_VALUE (0)
#endif

/**
 * @brief PublisherSubscriberNode class
 *
 * 
 */
class PublisherSubscriberNode : public polysync::Node
{

private:
    const string node_name = "polysync-publish-fakelidar";
    const string msg_ID = "ps_lidar_points_msg";
    float _relativeTime{ 0.0 };
    const float _gridScale{ 10.0 };
    const ulong _gridSideLength{ 100 };
    const ulong _numberOfPoints{ 10000 };
    const float _sineFrequency{ 4.0 };


    ps_msg_type _messageType;
    
public:
    
    PublisherSubscriberNode()
    {
        setNodeType( PSYNC_NODE_TYPE_API_USER );
        setDomainID( PSYNC_DEFAULT_DOMAIN );
        setSDFID( PSYNC_SDF_ID_INVALID );
        setFlags( NODE_FLAGS_VALUE | PSYNC_INIT_FLAG_STDOUT_LOGGING );
        setNodeName( node_name );
    }
    
    ~PublisherSubscriberNode()
    {
        
    }

    void initStateEvent() override
    {
        _messageType = getMessageTypeByName( msg_ID );
        polysync::datamodel::SensorDescriptor descriptor;

        descriptor.setTransformParentId( PSYNC_COORDINATE_FRAME_LOCAL );
        descriptor.setType( PSYNC_SENSOR_KIND_NOT_AVAILABLE );
        _message.setSensorDescriptor( descriptor );

        auto time = polysync::getTimestamp();
        _message.setHeaderTimestamp( time );
        _message.setStartTimestamp( time );
        _message.setEndTimestamp( time );
    }
    
    void releaseStateEvent() override
    {
        // do nothing, sleep for 10 milliseconds
    }
    
    void errorStateEvent() override
    {
        // do nothing, sleep for 10 milliseconds
        polysync::sleepMicro( 10000 );
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
    
    /**
     * Override the base class functionality to send messages when the node
     * reaches the "ok" state. This is the state where the node is in its
     * normal operating mode.
     */
    void okStateEvent() override
    {
        auto time = polysync::getTimestamp();
        auto timeDelta = time - _message.getStartTimestamp();
        auto timeDeltaSeconds = static_cast< float >( timeDelta ) / 1000000.0;

        _relativeTime += timeDeltaSeconds;
        _message.setStartTimestamp( time );
        _message.setEndTimestamp( time );

        std::vector< LidarPoint > outputPoints;
        outputPoints.reserve( _numberOfPoints );
        for( auto pointNum = 0U; pointNum < _numberOfPoints; ++pointNum )
        {
            polysync::datamodel::LidarPoint point;
            point.setIntensity( 255 );
            auto x = pointNum % 100;
            auto y = pointNum / 100;

            float u = static_cast< float >( x )/ 100.0;
            float v = static_cast< float >( y ) / 100.0;

            // center u/v at origin
            u = ( u * 2.0 ) - 1.0;
            v = ( v * 2.0 ) - 1.0;

            float w = sin( ( u * _sineFrequency ) + _relativeTime )
                    * cos( ( v * _sineFrequency ) + _relativeTime )
                    * 0.5;

            point.setPosition( { u * 10, v * 10, w * 10 } );
            outputPoints.emplace_back( point );
        }
        _message.setPoints(outputPoints);
    
        // Create a message
        polysync::datamodel::LidarPointsMessage message( *this );    
        // Set message data
        message.setHeaderTimestamp( polysync::getTimestamp() );
        message.publish();
        // The ok state is called periodically by the system, sleep to reduce
        // the number of messages sent
        polysync::sleepMicro( 1000000 );
    }
};


/**
 * Entry point for this node
 * The "connectToPolySync" is a blocking call, users must use Ctrl-C to quit
 * the execution loop.
 */
int main()
{
    // Create an instance of the PublisherSubscriberNode and connect it to 
    // PolySync
    PublisherSubscriberNode publisherSubscriberNode;

    // When the node has been created, it will cause an initStateEvent to be
    // sent and then proceed into the okState.  connectToPolySync does not
    // return, use Ctrl-C to exit
    publisherSubscriberNode.connectPolySync();

    return 0;
}
