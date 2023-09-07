#include "TitleCarController.h"
#include "TitleCar.h"
#include "Utility.h"
#include "Timer.h"
#include "ObjectObserver.h"
#include "Object.h"
#include "DrawModel.h"
/// <summary>
/// �^�C�g���ő��点��
/// </summary>
TitlteCarController::TitlteCarController(VECTOR setPos, VECTOR setDir)
    :ActorController(ObjectInit::player)
{
    titleCar = new TitleCar(setPos, setDir);
    observer = std::make_shared<ObjectObserver>(titleCar);
    drawModel = new DrawModel(ObjectInit::player);
}
/// <summary>
/// �����Ă���Ԃƕ`����̊J��
/// </summary>
TitlteCarController::~TitlteCarController()
{
    SAFE_DELETE(titleCar);
    observer.reset();
    SAFE_DELETE(drawModel);
}
/// <summary>
/// �Ԃ̈ړ�
/// </summary>
void TitlteCarController::Update()
{
    titleCar->Update();
}
/// <summary>
/// �`��
/// </summary>
void TitlteCarController::Draw() const
{
    drawModel->Draw(titleCar);
}
/// <summary>
/// �ʒu�̏�����
/// </summary>
void TitlteCarController::InitPosition()
{
    titleCar->InitPosition();
}
/// <summary>
/// �Ԃ̈ʒu�Ȃǂ��J�����Ȃǂɓn����悤�ɂ���
/// </summary>
/// <returns></returns>
std::shared_ptr<ObjectObserver> TitlteCarController::CreateCarObserver()
{
    return observer;
}
