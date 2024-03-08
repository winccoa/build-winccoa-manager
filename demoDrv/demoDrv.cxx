#include <demoDrv.hxx>
#include <demoHWMapper.hxx>
#include <demoHWService.hxx>

#include <HWObject.hxx>

//------------------------------------------------------------------------------------

void demoDrv::install_HWMapper()
{
  hwMapper = new demoHWMapper;
}

//--------------------------------------------------------------------------------

void demoDrv::install_HWService()
{
  hwService = new demoHWService;
}

//--------------------------------------------------------------------------------

HWObject * demoDrv::getHWObject() const
{
  return new HWObject();
}

//--------------------------------------------------------------------------------

void demoDrv::install_AlertService()
{
  DrvManager::install_AlertService();
}
