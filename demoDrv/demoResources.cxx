// Our resource class.
// This class will interpret the command line and read the config file

#include "demoResources.hxx"
#include <ErrHdl.hxx>

// TODO you likely have different things in the config file
unsigned short int demoResources::tcpPort = 12401;

//-------------------------------------------------------------------------------
// init is a wrapper around begin, readSection and end

void demoResources::init(int &argc, char *argv[])
{
  // Prepass of commandline arguments, e.g. get the arguments needed to
  // find the config file.
  begin(argc, argv);

  // Read the config file
  while ( readSection() || generalSection() ) ;

  // Postpass of the commandline arguments, e.g. get the arguments that
  // will override entries in the config file
  end(argc, argv);
}

//-------------------------------------------------------------------------------

PVSSboolean demoResources::readSection()
{
  // Are we in our section ?
  if ( !isSection("demo") ) return PVSS_FALSE;

  // skip "[demo]"
  getNextEntry();

  // Now read the section until new section or end of file
  while ( (getCfgState() != CFG_SECT_START) && (getCfgState() != CFG_EOF) )
  {
    // TODO whatever you have to read from the config file
    if      ( getKeyWord().icmp("tcpPort") == 0 ) getCfgStream() >> tcpPort;

    else if ( !commonKeyWord() )
    {
      unknownKeyWordError();
    }

    // get next entry
    getNextEntry();
  }

  // So the loop will stop at the end of the file
  return getCfgState() != CFG_EOF;
}

//-------------------------------------------------------------------------------
