#ifndef demoHWMAPPER_H_
#define demoHWMAPPER_H_

#include <TreeHWMapper.hxx>

class demoHWMapper : public TreeHWMapper
{
  public:
    virtual PVSSboolean addDpPa(DpIdentifier &dpId, PeriphAddr *confPtr);
    virtual PVSSboolean clrDpPa(DpIdentifier &dpId, PeriphAddr *confPtr);
};

#endif
