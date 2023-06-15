#include "BomberController.h"
#include "Rocket.h"
#include "ObjectObserver.h"
#include "ObjectSubject.h"

BomberController::BomberController(ObjectSubject* sub)
{
    observer = new ObjectObserver(sub);
    actorList.push_back(new Rocket(observer));
}
