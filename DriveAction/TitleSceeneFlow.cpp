#include "TitleSceeneFlow.h"
#include "Utility.h"
#include "StageDataAddressStruct.h"
#include "DxLib.h"
#include "StageSelect.h"
#include "SwitchUI.h"
#include "StageManager.h"
#include "SoundPlayer.h"
#include "UIManager.h"
TitleSceeneFlow::TitleSceeneFlow()
{
    uiManager = new UIManager();
    stageSelect = new StageSelect();  
    switchUI = new SwitchUI();
    titleLogoData = UIManager::CreateUIData(tilteLogo);
    stageManager = new StageManager();
    SetCameraNearFar(setNearValue, setFarValue);
}

TitleSceeneFlow::~TitleSceeneFlow()
{
    SAFE_DELETE(stageManager);
    SAFE_DELETE(stageSelect);
    SAFE_DELETE(switchUI);
    SAFE_DELETE(uiManager);

}

void TitleSceeneFlow::Update()
{
    if (!SoundPlayer::IsPlaySound(titleBGM))
    {
        SoundPlayer::Play2DSE(titleBGM);
    }
    //スカイドームを回転
    stageManager->Update();
    //スペースキーの催促
    switchUI->Update();

    int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    if (key & PAD_INPUT_10)
    {
        isEndProccess = true;
        nextSceneType = SceneType::PLAY;
    }
}

void TitleSceeneFlow::Draw()
{  
    stageManager->Draw();
    switchUI->Draw();
    DrawRotaGraph(titleLogoData.x, titleLogoData.y, titleLogoData.size, 0, titleLogoData.dataHandle[0], true, false);
}
