#pragma once
#include <string>
#include "SceneFlowBase.h"
#include "UIManager.h"

class StageSelect;
class StageInitializer;
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
    void Draw()const override;
private:
    //�X�e�[�W�̏��
    StageSelect* stageSelect;
    SwitchUI* switchUI;
    const float logoSize = 1.0f;
    int stageNum = 0;
    UIData titleLogoData;
    UIData stageNameData;
};