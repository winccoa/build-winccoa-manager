#include <demoAlertService.hxx>
#include <AlertObject.hxx>
#include <HWObject.hxx>
#include <demoResources.hxx>

//----------------------------------------------------------------------------------
demoAlertService::demoAlertService()
{
}

//----------------------------------------------------------------------------------
demoAlertService::~demoAlertService()
{
}

//---------------------------------------------------------------------------------------------
PVSSboolean demoAlertService::ackAlertInHW(AlertObject *alertPtr, HWObject *objPtr)
{
  if (Resources::isDbgFlag(DrvResources::DBG_DRV_ALERT))
  {
      std::cerr << "got alert ack request for HW " << objPtr->getAddress() << std::endl;
      alertPtr->debugPrint();
      std::cerr << "----------------------------------------------" << std::endl;
  }

  alertPtr->setEvent(AlertObject::EA_ACK);
  alertPtr->setComment("simulated ACK from PLC");
  setAlert(alertPtr, objPtr);

  return PVSS_TRUE;
}


void demoAlertService::ackConfirmCB(const AlertObject *alertPtr, const HWObject *adrPtr)
{
  if (Resources::isDbgFlag(DrvResources::DBG_DRV_ALERT))
  {
      std::cerr << "got ack confirm CB for HW " << adrPtr->getAddress() << std::endl;
      alertPtr->debugPrint();
      std::cerr << "----------------------------------------------" << std::endl;
  }
}

void demoAlertService::changeNotificationCB(const AlertObject *alertPtr, const HWObject *adrPtr)
{
  if (Resources::isDbgFlag(DrvResources::DBG_DRV_ALERT))
  {
      std::cerr << "got change notification CB for HW " << adrPtr->getAddress() << std::endl;
      alertPtr->debugPrint();
      std::cerr << "----------------------------------------------" << std::endl;
  }
}

void demoAlertService::invisibleConfirmCB(const AlertObject *alertPtr, const HWObject *adrPtr)
{
  if (Resources::isDbgFlag(DrvResources::DBG_DRV_ALERT))
  {
      std::cerr << "got invisible confirm CB for HW " << adrPtr->getAddress() << std::endl;
      alertPtr->debugPrint();
      std::cerr << "----------------------------------------------" << std::endl;
  }
}
