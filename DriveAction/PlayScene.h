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
    //ƒƒjƒ…[‚ğŠJ‚¢‚Ä‚â‚è’¼‚µ‚½‚è‚·‚éê‡‚ª‚ ‚é
    SceneType Update() override;
    void Draw()override;
private:
    Menu* menu;
};