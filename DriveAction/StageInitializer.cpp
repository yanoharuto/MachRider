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
/// ステージの初期化をする
/// </summary>
/// <param name="cotrollerManager"></param>
void StageInitializer::Init(ActorControllerManager* cotrollerManager)
{
    auto firstPositionGeneratetor = new FirstPositionGetter();
    //ステージに配置してあるオブジェクトを置いていく
    cotrollerManager->AddActorController(new StageObjectController(firstPositionGeneratetor));
    //プレイヤーを配置
    auto firstPosList = firstPositionGeneratetor->GetFirstPositionLoad(FirstPositionDataKind::playerPosition);
    VECTOR dir = firstPositionGeneratetor->GetChallengeData()[0].collectPos[0][0];
    dir = VNorm(VSub(dir, firstPosList[0][0]));
    Player* player = new Player(firstPosList[0][0], dir);
    
    cotrollerManager->AddActorController(player);
    playerObserver = player->CreatePlayerObserver();
}
/// <summary>
/// ステージの制限時間
/// </summary>
/// <returns></returns>
float StageInitializer::GetGameTime() const
{
    //データを読み取り
    return atof(LoadStageData(gameTime).c_str());
}

std::weak_ptr<ObjectObserver> StageInitializer::GetPlayerObserver() const
{
    return  playerObserver;
}
