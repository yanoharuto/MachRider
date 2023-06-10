#include "GamePlayUI.h"
#include "Utility.h"
#include "MiniMap.h"
#include "TimerUI.h"
#include "Timer.h"
#include "NumUI.h"
#include "ObjectSubject.h"
#include "ObjectObserver.h"
#include "CoinManager.h"
#include "RacerManager.h"
#include "CountDown.h"
/// <summary>
/// プレイヤーに関するUI　コインの所得数とか
/// </summary>
/// <param name="setTimer"></param>
/// <param name="setFirstCoinNum"></param>
GamePlayUI::GamePlayUI(Timer* setTimer, int setFirstCoinNum,RacerManager* racerManager)
{
    timerUI = new TimerUI(setTimer);
    minimapUI = new MiniMap(racerManager);
    manualData = UIManager::CreateUIData(manual);
    firstCoinNum = setFirstCoinNum;
    firstNumUI = new NumUI(allCollectItemNum);
    getNumUI = new NumUI(getCollectItemNum);
    slashHandle = UIManager::CreateUIData(collectItemUI);
    playerObserver = new ObjectObserver(racerManager->GetPlayerSubject(0));
    countDown = new CountDown(setTimer);
}


GamePlayUI::~GamePlayUI()
{
    SAFE_DELETE(timerUI);
    SAFE_DELETE(minimapUI);
    SAFE_DELETE(getNumUI);
    SAFE_DELETE(firstNumUI);
    SAFE_DELETE(playerObserver);
    SAFE_DELETE(countDown);
}

void GamePlayUI::Update(CoinManager* coinManager)
{
    nowGetCoinNum = playerObserver->GetSubjectHitCount(Object::ObjectTag::coin);
    countDown->Update();
    minimapUI->Update(coinManager->GetCoinPosList());
}

void GamePlayUI::Draw()const
{
    DrawRotaGraph(manualData.x, manualData.y, manualData.size, 0, manualData.dataHandle[0], true);
    DrawRotaGraph( slashHandle.x,slashHandle.y, slashHandle.size, 0, slashHandle.dataHandle[0], true);
    firstNumUI->Draw(firstCoinNum);
    getNumUI->Draw(nowGetCoinNum); 
    timerUI->Draw();
    minimapUI->Draw();
    countDown->DrawUI();
}

