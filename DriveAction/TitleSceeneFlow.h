#pragma once
#include <string>
#include "SceneFlowBase.h"
#include "UIManager.h"

class StageSelect;
class StageManager;
class SwitchUI;


/// <summary>
/// タイトルシーンの処理の流れ
/// </summary>
class TitleSceeneFlow :public SceneFlowBase
{
public:
    TitleSceeneFlow();
    ~TitleSceeneFlow();
    void Update() override;
    void Draw() override;
private:
    //ステージの情報
    StageSelect* stageSelect;
    StageManager* stageManager;
    UIManager* uiManager;
    SwitchUI* switchUI;
    const float logoSize = 1.0f;
    const float setNearValue = 0.1f;
    const float setFarValue = 10000.0f;
    UIData titleLogoData;
};