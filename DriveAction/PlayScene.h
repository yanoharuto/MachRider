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
    //メニューを開いてやり直したりする場合がある
    SceneType Update() override;
    void Draw()override;
private:
    Menu* menu;
};