#include "DemoCarController.h"
#include "DemoCar.h"
#include "Utility.h"
#include "Timer.h"
#include "ObjectObserver.h"
#include "Object.h"
#include "DrawModel.h"
/// <summary>
/// �^�C�g���ő��点��
/// </summary>
DemoCarController::DemoCarController(VECTOR setPos, VECTOR setDir)
    :ActorController(ObjectInit::player)
{
    demoCar = new DemoCar(setPos, setDir);
    observer = std::make_shared<ObjectObserver>(demoCar);
    drawModel = new DrawModel(ObjectInit::player);
}
/// <summary>
/// �����Ă���Ԃƕ`����̊J��
/// </summary>
DemoCarController::~DemoCarController()
{
    SAFE_DELETE(demoCar);
    observer.reset();
    SAFE_DELETE(drawModel);
}
/// <summary>
/// �Ԃ̈ړ�
/// </summary>
void DemoCarController::Update()
{
    demoCar->Update();
}
/// <summary>
/// �`��
/// </summary>
void DemoCarController::Draw() const
{
    drawModel->Draw(demoCar);
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
