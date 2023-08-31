#include <math.h>
#include "DxLib.h"
#include "StageObjectController.h"
#include "AssetManager.h"
#include "Utility.h"
#include "FirstPositionGetter.h"
#include "InitActor.h"
#include "StageWall.h"
#include "DrawModel.h"
/// <summary>
/// ������
/// </summary>
/// <returns></returns>
StageObjectController::StageObjectController()
    :ActorController(ObjectInit::wall)
{   
    //���̐ݒ�
    floorModelHandle = InitActor::GetModelHandle(stageFloor);
    auto param = InitActor::GetActorParamator(stageFloor);
    MV1SetPosition(floorModelHandle, VGet(0, param.firstPosY, 0));
    //skyDome�̐ݒ�
    skyDomeModelHandle = InitActor::GetModelHandle(skyDome);
    stageWall = new StageWall();
    drawModel = new DrawModel(wall);
}

/// <summary>
/// ��폜
/// </summary>
/// <returns></returns>
StageObjectController::~StageObjectController()
{
    SAFE_DELETE(stageWall);
    SAFE_DELETE(drawModel);
}

/// <summary>
/// �R�[�X�̃��f����`��
/// </summary>
void StageObjectController::Draw() const
{
    //�ǂƏ�
    drawModel->Draw(stageWall);
    MV1DrawModel(floorModelHandle);
    //���C�g�̉e���Ȃ��ŋ��`��
    SetUseLighting(false);
    MV1DrawModel(skyDomeModelHandle);
    SetUseLighting(true);
}