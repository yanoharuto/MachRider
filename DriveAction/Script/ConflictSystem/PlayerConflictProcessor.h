#pragma once
#include "ConflictProcessor.h"
class PlayerCar;
/// <summary>
/// �v���C���[�̏Փˏ������s��
/// </summary>
class PlayerConflictProcessor : public ConflictProcessor
{
public:

    /// <summary>
    /// �v���C���[�̏Փˏ������s��
    /// </summary>
    PlayerConflictProcessor(PlayerCar* const car);
    ~PlayerConflictProcessor() {};
    /// <summary>
    /// �Փˌ��ʎ��s��
    /// </summary>
    /// <param name="resultInfo">�Փˌ���</param>
    void OnConflict(CollisionResultInfo resultInfo)override;
    /// <summary>
    /// ���W�A�C�e���ɂԂ�������
    /// </summary>
    /// <returns></returns>
    int GetCollectNum()const { return getCollectNum; };
private:
    //���W�A�C�e���ɂԂ�������
    int getCollectNum = 0;
};

