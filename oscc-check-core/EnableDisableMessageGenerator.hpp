#ifndef ENABLEDISABLEMESSAGEGENERATOR_HPP
#define ENABLEDISABLEMESSAGEGENERATOR_HPP

#include <PolySyncNode.hpp>
#include <PolySyncDataModel.hpp>

class EnableDisableMessageGenerator {

public: 
    EnableDisableMessageGenerator(polysync::Node &);
    void generateEnableCommand();
    void generateDisableCommand();
    void initializeMessage();
    void publishCommand();
private: 
    const int _enableKey;
    const int _disableKey;
    const int _defaultKey;

};

#endif