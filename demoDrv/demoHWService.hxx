#ifndef demoHWSERVICE_H_
#define demoHWSERVICE_H_

#include <HWService.hxx>
#include <demoHWMapper.hxx>

class demoHWService : public HWService
{
  public:
    virtual PVSSboolean initialize(int argc, char *argv[]);
    virtual PVSSboolean start();
    virtual void stop();
    virtual void workProc();
    virtual PVSSboolean writeData(HWObject *objPtr);
};

#endif
