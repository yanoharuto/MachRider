#pragma once
#include "SceneBase.h"
class Menu;
/// <summary>
/// ゲームを遊ぶシーン
/// </summary>
class PlayScene final:
    public SceneBase
{
public:
    PlayScene();
    ~PlayScene() override;
    /// <summary>
    /// ゲームを遊ぶ
    /// </summary>
    /// <returns></returns>
    SceneType Update() override;
    /// <summary>
    /// メニューを開いている時と遊んでいるときで処理が違う
    /// </summary>
    void Draw()const override;
private:
    //一時停止したりリトライする用
    Menu* menu;
};