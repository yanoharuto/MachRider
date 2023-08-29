#include "PlayerConflictProcessor.h"
#include "PlayerCar.h"

PlayerConflictProcessor::PlayerConflictProcessor(PlayerCar* const car)
    :ConflictProcessor(car)
{
}

PlayerConflictProcessor::~PlayerConflictProcessor()
{
}
/// <summary>
/// �Փˌ��ʎ��s��
/// </summary>
/// <param name="resultInfo">�Փˌ���</param>
void PlayerConflictProcessor::OnConflict(CollisionResultInfo resultInfo)
{
    //�Փˌ�̏������s���K�v���Ȃ��Ȃ�I��
    if (object == nullptr)return;
    if (resultInfo.hit != HitSituation::NotHit)
    {
        //�����������̏������s��
        object->OnConflict(resultInfo);
        //�R���N�g�A�C�e���Ȃ�J�E���g
        if (resultInfo.tag == Object::collect)
        {
            getCollectNum++;
        }
    }
}