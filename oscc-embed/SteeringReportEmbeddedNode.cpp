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

    void initStateEvent() override { //stackoverflow.com/questions/12142174/run-a-python-script-with-arguments
        FILE* file;
        int argc;
        char* argv[];

        argc = 3;
        argv[0] = "oscc-check.py";
        argv[1] = "-V"; 
        argv[2] = "kia_soul_ev";
        Py_SetProgramName(argv[0]);
        Py_Initialize();
        PySys_SetArgv(argc, argv);
        file = fopen("oscc-check.py", "r");

        //fp = _Py_fopen(filename, "r");
        PyRun_SimpleFile(file, "oscc-check.py");
        Py_Finalize();

    }

    int runPythonFunction(int c, char *v[]) { //v[] is argv[] when run from command line. v[1] is python script 

    }

    void okStateEvent() override { 

    }

    void releaseStateEvent() override { 

    }
}