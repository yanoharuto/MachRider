#include "BigRadiusLaserController.h"
#include "BigRadiusLaser.h"
#include "ObjectObserver.h"
#include "ObjectSubject.h"
BigRadiusLaserController::BigRadiusLaserController(ObjectSubject* sub)
{
    observer = new ObjectObserver(sub);
    actorList.push_back(new BigRadiusLaser(observer));
}
