#include "ResultSceneFlow.h"
#include "DxLib.h"
#include "Utility.h"
#include "ResultScore.h"
#include "UIManager.h"
#include "SwitchUI.h"

ResultSceneFlow::ResultSceneFlow()
{
    uiManager = new UIManager();
    switchUI = new SwitchUI();
}

ResultSceneFlow::~ResultSceneFlow()
{
    SAFE_DELETE(switchUI);
    SAFE_DELETE(uiManager);
}

void ResultSceneFlow::Update()
{
    switchUI->Update();
    int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    if (key & PAD_INPUT_10)
    {
        isEndProccess = true;
        nextSceneType = SceneType::TITLE;
    }
}

void ResultSceneFlow::Draw() const
{
    
}
