#include "PlayerObserver.h"
#include "PlayerCar.h"
/// <summary>
/// �v���C���[�̏���n�����
/// </summary>
/// <param name="playerCar">�v���C���[</param>
PlayerObserver::PlayerObserver(PlayerCar* const playerCar)
    :ObjectObserver(playerCar)
{
    subject = playerCar;
}
/// <summary>
/// ���W�A�C�e��������������
/// </summary>
/// <returns></returns>
int PlayerObserver::GetCollectCount()
{
    return subject->GetCollectCount();
}