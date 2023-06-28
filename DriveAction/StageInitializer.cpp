#include "StageInitializer.h"
#include "Utility.h"
#include "StageObjectController.h"
#include "FirstPositionGetter.h"
#include "ActorControllerManager.h"
#include "Player.h"
#include "CSVFileLoader.h"
#include "StageSelect.h"
StageInitializer::StageInitializer()
{
    
}

StageInitializer::~StageInitializer()
{
}

/// <summary>
/// �X�e�[�W�̏�����������
/// </summary>
/// <param name="cotrollerManager"></param>
void StageInitializer::Init(ActorControllerManager* cotrollerManager)
{
    auto firstPositionGeneratetor = new FirstPositionGetter();
    //�X�e�[�W�ɔz�u���Ă���I�u�W�F�N�g��u���Ă���
    cotrollerManager->AddActorController(new StageObjectController(firstPositionGeneratetor));
    //�v���C���[��z�u
    auto firstPosList = firstPositionGeneratetor->GetFirstPositionLoad(FirstPositionDataKind::playerPosition);
    VECTOR dir = firstPositionGeneratetor->GetChallengeData()[0].collectPos[0][0];
    dir = VNorm(VSub(dir, firstPosList[0][0]));
    Player* player = new Player(firstPosList[0][0], dir);
    
    cotrollerManager->AddActorController(player);
    playerObserver = player->CreatePlayerObserver();
}
/// <summary>
/// �X�e�[�W�̐�������
/// </summary>
/// <returns></returns>
float StageInitializer::GetGameTime() const
{
    //�f�[�^��ǂݎ��
    return atof(LoadStageData(gameTime).c_str());
}

std::weak_ptr<ObjectObserver> StageInitializer::GetPlayerObserver() const
{
    return  playerObserver;
}
