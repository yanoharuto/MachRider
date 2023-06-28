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
    //�V�[�����Ƃ̏���
    sceneFlow->Update();
    if (sceneFlow->GetIsEndProccess())//�������I�������
    {
        return sceneFlow->GetNextSceneType();
    }
    return nowSceneType;
}
void SceneBase::Draw()
{
    sceneFlow->Draw();
}