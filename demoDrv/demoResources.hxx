#ifndef demoRESOURCES_H_
#define demoRESOURCES_H_

// Our resources class
// This class has two tasks:
//  - Interpret commandline and read config file
//  - Be an interface to internal datapoints

#include <DrvResources.hxx>

class demoResources : public DrvResources
{
  public:
    static void init(int &argc, char *argv[]); // Initialize statics
    static PVSSboolean readSection();          // read config file

    // Get our static Variables
    // TODO you likely have different things in the config file
    static unsigned short int getTCPPort() { return tcpPort; }

  private:
    // TODO you likely have different things in the config file
    static unsigned short int tcpPort;
};

#endif
