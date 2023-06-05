#pragma once
#include "SceneType.h"

/// <summary>
/// シーンごとの処理の流れ
/// </summary>
class SceneFlowBase abstract
{
public:
    SceneFlowBase() 
    {
        isEndProccess = false; 
    };
    virtual ~SceneFlowBase() {};
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="deltaTime"></param>
    virtual void Update() = 0;
    /// <summary>
    /// 描画
    /// </summary>
    virtual void Draw() = 0;
    /// <summary>
    /// 処理が終わったか
    /// </summary>
    /// <returns></returns>
    bool GetIsEndProccess() { return isEndProccess; };
    /// <summary>
    /// 次のシーンのタイプ
    /// </summary>
    /// <returns></returns>
    SceneType GetNextSceneType() { return nextSceneType; };
protected:
    //処理が終わったか
    bool isEndProccess = false;
    //次のシーンはどれか
    SceneType nextSceneType = SceneType::TITLE;
};