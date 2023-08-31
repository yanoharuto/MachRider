#include "SceneBase.h"
#include "Utility.h"
#include "SceneFlowBase.h"
/// <summary>
/// 現在のシーンの保存
/// </summary>
/// <param name="_SceneType">現在のシーンの保存</param>
SceneBase::SceneBase(SceneType _SceneType)
{
    nowSceneType = _SceneType;
}
/// <summary>
/// SceneFlowの解放
/// </summary>
SceneBase::~SceneBase()
{
    SAFE_DELETE(sceneFlow);
}
/// <summary>
/// シーンの更新
/// </summary>
/// <returns>次のシーン</returns>
SceneType SceneBase::Update()
{
    //シーンごとの処理
    sceneFlow->Update();
    if (sceneFlow->GetIsEndProccess())//処理が終わったら
    {
        //次のシーンに飛ぶ
        return sceneFlow->GetNextSceneType();
    }
    return nowSceneType;
}
/// <summary>
/// 描画
/// </summary>
void SceneBase::Draw() const
{
    sceneFlow->Draw();
}