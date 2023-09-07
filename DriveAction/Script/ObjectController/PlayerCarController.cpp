#include "PlayerCarController.h"
#include "PlayerCar.h"
#include "SphereHitChecker.h"
#include "SoundPlayer.h"
#include "SoundListener.h"
#include "Utility.h"
#include "FirstPositionGetter.h"
#include "PlayerDrawModel.h"
#include "PlayerObserver.h"
/// <summary>
/// �v���C���[�̎Ԃ̏�����
/// </summary>
PlayerCarController::PlayerCarController()
    :ActorController(ObjectInit::player)
{
    //�����ʒu
    std::vector<PlacementData> editData = FirstPositionGetter::GetPlaceData(Object::player);
    //�Ԃ̊J��
    car = new PlayerCar(editData[0]);
    playerObserver = std::make_shared<PlayerObserver>(car);
    //�v���C���[�̈ʒu���特���W�߂郊�X�i�[�̐ݒ�
    listener = new SoundListener(CreatePlayerObserver());
    //�v���C���[�`���
    playerDrawer = new PlayerDrawModel();
}
/// <summary>
/// �Ԃ�Lisner��Delete
/// </summary>
PlayerCarController::~PlayerCarController()
{
    SAFE_DELETE(car);
    SAFE_DELETE(listener);
}
/// <summary>
/// �Ԃ̈ʒu�Ƃ���n��
/// </summary>
/// <returns></returns>
std::shared_ptr<PlayerObserver> PlayerCarController::CreatePlayerObserver() const
{
    return playerObserver;
}
/// <summary>
/// ���𕷂����߂ɏꏊ���X�V
/// </summary>
void PlayerCarController::Update()
{
    car->Update();
    listener->Update();
}
/// <summary>
/// �`��
/// </summary>
void PlayerCarController::Draw() const
{
    playerDrawer->Draw(car);
}
