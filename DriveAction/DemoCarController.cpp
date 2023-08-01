#include "DemoCarController.h"
#include "DemoCar.h"
#include "Utility.h"
#include "Timer.h"
#include "ObjectObserver.h"
#include "Object.h"
#include "ModelViewer.h"
/// <summary>
/// �^�C�g���ő��点��
/// </summary>
DemoCarController::DemoCarController(VECTOR setPos, VECTOR setDir)
    :ActorController(ObjectInit::player)
{
    demoCar = new DemoCar(setPos, setDir);
    observer = std::make_shared<ObjectObserver>(demoCar);
    viewer = new ModelViewer(ObjectInit::player);
}

DemoCarController::~DemoCarController()
{
    SAFE_DELETE(demoCar);
    observer.reset();
    SAFE_DELETE(viewer);
}
/// <summary>
/// �Ԃ̈ړ�
/// </summary>
void DemoCarController::Update()
{
    demoCar->Update();
}
/// <summary>
/// �������Ă��邩�ǂ���
/// </summary>
/// <returns></returns>
bool DemoCarController::IsAlive() const
{
    return demoCar->GetObjectState() != Object::dead;
}

/// <summary>
/// �`��
/// </summary>
void DemoCarController::Draw() const
{
    viewer->Draw(demoCar);
}
/// <summary>
/// �ʒu�̏�����
/// </summary>
void DemoCarController::InitPosition()
{
    demoCar->InitPosition();
}
/// <summary>
/// �Ԃ̈ʒu�Ȃǂ��J�����Ȃǂɓn����悤�ɂ���
/// </summary>
/// <returns></returns>
std::shared_ptr<ObjectObserver> DemoCarController::CreateCarObserver()
{
    return observer;
}
