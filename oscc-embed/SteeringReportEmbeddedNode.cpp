#include <iostream>
#include <PolySyncNode.hpp>
#include <PolySyncDataModel.hpp>
#include <Python.h>
#include <conio.h>

using namespace std;

#ifndef NODE_FLAGS_VALUE
#define NODE_FLAGS_VALUE (0)
#endif

class SteeringReportEmbeddedNode : public polysync::Node 
{ 

private: 
    const string node_name = "ed-msg-embedded-node-cpp";

public: 
    SteeringReportEmbeddedNode() { 
        setNodeType(PSYNC_NODE_TYPE_API_USER);
        setDomainID(PSYNC_DEFAULT_DOMAIN);
        setSDFID(PSYNC_SDF_ID_INVALID);
        setFlags(NODE_FLAGS_VALUE | PSYNC_INIT_FLAG_STDOUT_LOGGING);
        setNodeName(node_name);
    }

    void initStateEvent() override { //https://www.codeproject.com/Articles/820116/Embedding-Python-program-in-a-C-Cplusplus-code
        char filename[] = "oscc-check.py";
        FILE* fp;
        Py_Initialize();
        fp = _Py_fopen(filename, "r");
        PyRun_SimpleFile(fp, filename)

    }

    int runPythonFunction(int c, char *v[]) { //v[] is argv[] when run from command line. v[1] is python script 

    }

    void okStateEvent() override { 

    }

    void releaseStateEvent() override { 

    }
}