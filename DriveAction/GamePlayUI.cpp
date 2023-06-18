#include "GamePlayUI.h"
#include "Utility.h"
#include "MiniMap.h"
#include "TimerUI.h"
#include "Timer.h"
#include "NumUI.h"
#include "ChallengeFlow.h"
#include "ObjectObserver.h"
#include "CountDown.h"
#include "CollectSign.h"

/// <summary>
/// プレイヤーに関するUI　コインの所得数とか
/// </summary>
/// <param name="setTimer"></param>
/// <param name="setFirstCoinNum"></param>
GamePlayUI::GamePlayUI(Timer* setTimer,ChallengeFlow* challengeFlow, std::shared_ptr<ObjectObserver> player)
{
    timerUI = new TimerUI(setTimer);
    minimapUI = new MiniMap(player);
    manualData = UIManager::CreateUIData(manual);
    firstCoinNum = challengeFlow->GetTotalCollectNum();
    firstNumUI = new NumUI(allCollectItemNum);
    getNumUI = new NumUI(getCollectItemNum);
    collectSignData = UIManager::CreateUIData(collectSign);
    cSign = new CollectSign(player);
    slashData = UIManager::CreateUIData(collectItemUI);
    playerObserver = player;
    countDown = new CountDown(setTimer);
}


GamePlayUI::~GamePlayUI()
{
    SAFE_DELETE(timerUI);
    SAFE_DELETE(minimapUI);
    SAFE_DELETE(getNumUI);
    SAFE_DELETE(firstNumUI);
    SAFE_DELETE(countDown);
    SAFE_DELETE(cSign);
    playerObserver.reset();
}

void GamePlayUI::Update(ChallengeFlow* challengeFlow)
{
    nowGetCoinNum = playerObserver.lock()->GetSubjectHitCount(Object::ObjectTag::collect);
    countDown->Update();
    minimapUI->Update();
    cSign->Update();
}

void GamePlayUI::Draw()const
{
    DrawRotaGraph(manualData.x, manualData.y, manualData.size, 0, manualData.dataHandle[0], true);
    DrawRotaGraph(slashData.x,slashData.y, slashData.size, 0, slashData.dataHandle[0], true);
    firstNumUI->Draw(firstCoinNum);
    getNumUI->Draw(nowGetCoinNum); 
    timerUI->Draw();
    minimapUI->Draw();
    countDown->DrawUI();
    cSign->Draw();
}