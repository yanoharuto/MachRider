#include "StageWall.h"
#include "AssetManager.h"
#include "ConflictManager.h"
//�X�e�[�W�̏c��
float StageWall::stageLength;
//�X�e�[�W�̉���
float StageWall::stageWidth;
/// <summary>
/// �s���͈͂����߂��
/// </summary>
StageWall::StageWall()
    :Actor(ObjectInit::wall)
{
    tag = ObjectTag::obstacle;
    position = setFirstPos;
    //�����蔻��
    wallCollider = new WallCollider(this, stageSmallestSize, stageBiggestSize);
    ConflictManager::AddHitChecker(wallCollider);

    stageLength = fabsf(stageSmallestSize.z) + fabsf(stageBiggestSize.z);
    stageWidth = fabsf(stageSmallestSize.x) + fabsf(stageBiggestSize.x);
}

StageWall::~StageWall()
{
    ConflictManager::EraceHitChecker(wallCollider);
}

/// <summary>
/// �X�e�[�W�̉���
/// </summary>
/// <returns></returns>
float StageWall::GetStageWidth()
{
    return stageWidth;
}
/// <summary>
/// �X�e�[�W�̏c��
/// </summary>
/// <returns></returns>
float StageWall::GetStageLength()
{
    return stageLength;
}