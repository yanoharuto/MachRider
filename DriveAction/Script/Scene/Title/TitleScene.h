#pragma once
#include "SceneBase.h"
/// <summary>
/// タイトル
/// </summary>
class TitleScene final :
    public SceneBase
{
public:
    /// <summary>
    /// TitleSceneFlowを確保
    /// </summary>
    TitleScene();
    /// <summary>
    /// タイトルでの処理
    /// </summary>
    /// <returns>ゲーム終了かEditorモードかPlayシーンに遷移</returns>
    SceneType Update();
private:
};

