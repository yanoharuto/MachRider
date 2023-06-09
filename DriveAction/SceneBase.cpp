#include "SceneBase.h"
#include "Utility.h"
#include "SceneFlowBase.h"
SceneBase::SceneBase(SceneType _SceneType)
{
    nowSceneType = _SceneType;

}

SceneBase::~SceneBase()
{
    SAFE_DELETE(sceneFlow);
}

SceneType SceneBase::Update()
{
    //シーンごとの処理
    sceneFlow->Update();
    if (sceneFlow->GetIsEndProccess())//処理が終わったら
    {
        return sceneFlow->GetNextSceneType();
    }
    return nowSceneType;
}
void SceneBase::Draw()
{
    sceneFlow->Draw();
}