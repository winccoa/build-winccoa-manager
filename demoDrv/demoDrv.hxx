#ifndef demoDRV_H_
#define demoDRV_H_

#include <DrvManager.hxx>

class demoDrv : public DrvManager
{
  public:
    virtual void install_HWMapper();
    virtual void install_HWService();
    virtual void install_AlertService();

    virtual HWObject *getHWObject() const; 
};

#endif
