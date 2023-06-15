#pragma once
#include "SwitchUI.h"
#include "SceneFlowBase.h"
#include <string>
class UIManager;
/// <summary>
/// リザルトシーンの処理の流れ
/// </summary>
class ResultSceneFlow:public SceneFlowBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ResultSceneFlow();

    ~ResultSceneFlow();
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update()override;
    /// <summary>
    /// 描画
    /// </summary>
    void Draw() const override;
private:
    UIManager* uiManager;
    //スペースキーの催促
    SwitchUI* switchUI;
};

