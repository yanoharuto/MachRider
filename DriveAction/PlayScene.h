#pragma once
#include "SceneBase.h"
class Menu;
/// <summary>
/// 
/// </summary>
class PlayScene final:
    public SceneBase
{
public:
    PlayScene();
    ~PlayScene() override;
    //���j���[���J���Ă�蒼�����肷��ꍇ������
    SceneType Update() override;
    void Draw()override;
private:
    Menu* menu;
};