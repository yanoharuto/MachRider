#pragma once
#include <string>
#include "SceneFlowBase.h"
#include "UIManager.h"

class StageSelect;
class StageManager;
class SwitchUI;


/// <summary>
/// �^�C�g���V�[���̏����̗���
/// </summary>
class TitleSceeneFlow :public SceneFlowBase
{
public:
    TitleSceeneFlow();
    ~TitleSceeneFlow();
    void Update() override;
    void Draw() override;
private:
    //�X�e�[�W�̏��
    StageSelect* stageSelect;
    StageManager* stageManager;
    UIManager* uiManager;
    SwitchUI* switchUI;
    const float logoSize = 1.0f;
    const float setNearValue = 0.1f;
    const float setFarValue = 10000.0f;
    UIData titleLogoData;
};