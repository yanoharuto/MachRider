#include "LittleRadiusLaserController.h"
#include "LittleRadiusLaser.h"
#include "ObjectObserver.h"
LittleRadiusLaserController::LittleRadiusLaserController(ObjectSubject* sub)
{
    observer = new ObjectObserver(sub);
    actorList.push_back(new LittleRadiusLaser(observer));
}

