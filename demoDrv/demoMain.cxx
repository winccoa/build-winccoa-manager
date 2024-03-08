#include <demoDrv.hxx>
#include <demoResources.hxx>

#include <signal.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  // an instance of our own resources class is needed
  demoResources resources;

  resources.init(argc, argv);

  // the user wants to know std. commandline options
  if ( resources.getHelpFlag() )
  {
    resources.printHelp();
    return 0;
  }

  // the user wants to know std. debug flags
  if ( resources.getHelpDbgFlag() )
  {
    resources.printHelpDbg();
    return 0;
  }

  // the user wants to know std. report flags
  if ( resources.getHelpReportFlag() )
  {
    resources.printHelpReport();
    return 0;
  }

  // handle std. signals
  signal(SIGINT, Manager::sigHdl);
  signal(SIGTERM, Manager::sigHdl);

  // a pointer is needed, since the Manager dtor does a delete
  demoDrv *driver = new demoDrv;

  driver->mainProcedure(argc, argv);

  return 0;
}
