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

void StageInitializer::Init(ActorControllerManager* cotrollerManager)
{
    auto firstPositionGeneratetor = new FirstPositionGetter();
    cotrollerManager->AddActorController(new StageObjectController(firstPositionGeneratetor));

    auto firstPosList = firstPositionGeneratetor->GetFirstPositionLoad(FirstPositionDataKind::playerPosition);

    VECTOR dir = firstPositionGeneratetor->GetChallengeData()[0].collectPos[0][0];
    dir = VNorm(VSub(dir, firstPosList[0][0]));
    Player* player = new Player(firstPosList[0][0],dir);
    cotrollerManager->AddActorController(player);
    playerObserver = player->CreatePlayerObserver();
}

float StageInitializer::GetGameTime() const
{
    //ƒf[ƒ^‚ð“Ç‚ÝŽæ‚è
    auto fileLoader = new CSVFileLoader(StageSelect::GetLoadeStageName());
    auto setStageInitDataVec = fileLoader->GetLoadStringData();
    SAFE_DELETE(fileLoader);
    return atof(setStageInitDataVec[gameTime].c_str());
}

std::shared_ptr<ObjectObserver> StageInitializer::GetPlayerObserver() const
{
    return  playerObserver;
}
