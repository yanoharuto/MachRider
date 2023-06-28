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
    //ƒV[ƒ“‚²‚Æ‚Ìˆ—
    sceneFlow->Update();
    if (sceneFlow->GetIsEndProccess())//ˆ—‚ªI‚í‚Á‚½‚ç
    {
        return sceneFlow->GetNextSceneType();
    }
    return nowSceneType;
}
void SceneBase::Draw()
{
    sceneFlow->Draw();
}