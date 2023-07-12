#include <math.h>
#include "DxLib.h"
#include "StageObjectController.h"
#include "AssetManager.h"
#include "Utility.h"
#include "FirstPositionGetter.h"
#include "InitActor.h"
#include "Rock.h"
#include "StageWall.h"

/// <summary>
/// ������
/// </summary>
/// <returns></returns>
StageObjectController::StageObjectController(FirstPositionGetter* firstPosGetter)
{   
    //���̐ݒ�
    auto param = InitActor::GetActorParamator(stageFloor);
    floorModelHandle = param.modelHandle;
    MV1SetScale(floorModelHandle, VGet(param.setModelSize, param.setModelSize, param.setModelSize));
    MV1SetPosition(floorModelHandle, VGet(0, param.firstPosY, 0));
    //skyDome�̐ݒ�
    param = InitActor::GetActorParamator(skyDome);
    skyDomeModelHandle = param.modelHandle;
    MV1SetScale(skyDomeModelHandle, VGet(param.setModelSize, param.setModelSize, param.setModelSize));
    ////���z�u����
    //auto rocksFirstPos = firstPosGetter->GetFirstPositionLoad(FirstPositionDataKind::rockPosition);
    //for (int i = 0; i < rocksFirstPos.size(); i++)
    //{
    //    for (int j = 0; j < rocksFirstPos[i].size(); j++)
    //    {
    //        actorList .push_back(new Rock(rocksFirstPos[i][j], i));
    //    }
    //}
    actorList.push_back(new StageWall());
}

/// <summary>
/// ��폜
/// </summary>
/// <returns></returns>
StageObjectController::~StageObjectController()
{
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        SAFE_DELETE((*ite));
    }
    
}


/// <summary>
/// �R�[�X�̃��f����`��
/// </summary>
void StageObjectController::Draw() const
{
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        (*ite)->Draw();
    }
    
    MV1DrawModel(floorModelHandle);
    //���C�g�̉e���Ȃ��ŋ��`��
    SetUseLighting(false);
    MV1DrawModel(skyDomeModelHandle);
    
    SetUseLighting(true);
}