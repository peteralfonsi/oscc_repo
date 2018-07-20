#ifndef STEERINGCOMMANDGENERATOR_HPP
#define STEERINGCOMMANDGENERATOR_HPP

#include <PolySyncNode.hpp>
#include <PolySyncDataModel.hpp>



class SteeringCommandGenerator { 

public: 
    SteeringCommandGenerator(polysync::Node &);
    void generateCommand();
    void publishCommand();

private: 
    polysync::datmodel::OsccSteeringCommandMsg _message;
    int _messageNumber;
    float _defaultTorque;

};

#endif