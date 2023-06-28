#include "DemoCarController.h"
#include "DemoCar.h"
#include "Utility.h"
#include "Timer.h"
#include "ObjectObserver.h"
#include "ObjectSubject.h"
#include "Object.h"
DemoCarController::DemoCarController(VECTOR setPos, VECTOR setDir)
{
    demoCar = new DemoCar(setPos, setDir);
    subject = new ObjectSubject(demoCar);
}

DemoCarController::~DemoCarController()
{
    SAFE_DELETE(demoCar);
}

void DemoCarController::Update()
{
    demoCar->Update();
}

bool DemoCarController::IsAlive() const
{
    return demoCar->GetObjectState() != Object::dead;
}

void DemoCarController::Draw() const
{
    demoCar->Draw();
}

void DemoCarController::InitPosition()
{
    demoCar->InitPosition();
}

std::shared_ptr<ObjectObserver> DemoCarController::CreateCarObserver()
{
    return std::make_shared<ObjectObserver>(subject);
}
