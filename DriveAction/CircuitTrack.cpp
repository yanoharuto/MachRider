#include <math.h>
#include "CircuitTrack.h"
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
CircuitTrack::CircuitTrack(FirstPositionGetter* firstPosGetter)
{
    //�n�ʂ̏�����
    auto initParam= InitActor::GetActorParamator(stageFloor);
    
    floorModelHandle = initParam.modelHandle;
    auto rocksFirstPos = firstPosGetter->GetFirstPositionLoad(FirstPositionDataKind::rockPosition);
    //���z�u����
    for (int i = 0; i < rocksFirstPos.size(); i++)
    {
        for (int j = 0; j < rocksFirstPos[i].size(); j++)
        {
            Rock* rock = new Rock(rocksFirstPos[i][j], i);
            rocks.push_back(rock);
        }

    }
    stageWall = new StageWall();
}

/// <summary>
/// ��폜
/// </summary>
/// <returns></returns>
CircuitTrack::~CircuitTrack()
{
    for (auto ite = rocks.begin(); ite != rocks.end(); ite++)
    {
        SAFE_DELETE((*ite));
    }
    SAFE_DELETE(stageWall);
}


/// <summary>
/// �R�[�X�̃��f����`��
/// </summary>
void CircuitTrack::Draw()
{
    for (auto ite = rocks.begin(); ite != rocks.end(); ite++)
    {
        (*ite)->Draw();
    }
    stageWall->Draw();
    MV1DrawModel(floorModelHandle);
}