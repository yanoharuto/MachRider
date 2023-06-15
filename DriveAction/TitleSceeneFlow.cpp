#include "TitleSceeneFlow.h"
#include "Utility.h"
#include "StageDataAddressStruct.h"
#include "DxLib.h"
#include "StageSelect.h"
#include "SwitchUI.h"
#include "SoundPlayer.h"
#include "UIManager.h"
#include "UserInput.h"
#include "FadeInFadeOut.h"
TitleSceeneFlow::TitleSceeneFlow()
{
    stageSelect = new StageSelect();  
    switchUI = new SwitchUI();
    titleLogoData = UIManager::CreateUIData(tilteLogo);
    stageNameData= UIManager::CreateUIData(stageName);
}

TitleSceeneFlow::~TitleSceeneFlow()
{
    SAFE_DELETE(stageSelect);
    SAFE_DELETE(switchUI);
}

void TitleSceeneFlow::Update()
{
    if (!SoundPlayer::IsPlaySound(titleBGM))
    {
        SoundPlayer::Play2DSE(titleBGM);
    }
    //スペースキーの催促
    switchUI->Update();
    stageSelect->Update();
    if (UserInput::GetInputState(Up) == Push)
    {
        stageNum++;
        if(stageNameData.dataHandle.size() <= stageNum) 
        {
            stageNum = 0;
        }
    }
    if (UserInput::GetInputState(Down) == Push)
    {
        stageNum--;
        if (0 > stageNum)
        {
            stageNum = stageNameData.dataHandle.size() - 1;
        }
    }
    if (UserInput::GetInputState(Space)==Push)
    {
        isEndProccess = true;
        nextSceneType = SceneType::PLAY;
    }
}

void TitleSceeneFlow::Draw()const
{  
    DrawRotaGraph(titleLogoData.x, titleLogoData.y, titleLogoData.size, 0, titleLogoData.dataHandle[0], true, false);
    DrawGraph(stageNameData.x, stageNameData.y, stageNameData.dataHandle[stageNum], false);
}
