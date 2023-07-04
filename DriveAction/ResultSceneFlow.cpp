#include "ResultSceneFlow.h"
#include "DxLib.h"
#include "Utility.h"
#include "ResultScore.h"
#include "UIManager.h"
#include "SpaceKeyUI.h"

ResultSceneFlow::ResultSceneFlow()
{
    switchUI = new FlashUI(resultSpaceKey);
}

ResultSceneFlow::~ResultSceneFlow()
{
    SAFE_DELETE(switchUI);
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
