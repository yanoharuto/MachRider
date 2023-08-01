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
        //���̃V�[���ɔ��
        return sceneFlow->GetNextSceneType();
    }
    return nowSceneType;
}
/// <summary>
/// �`��
/// </summary>
void SceneBase::Draw() const
{
    sceneFlow->Draw();
}