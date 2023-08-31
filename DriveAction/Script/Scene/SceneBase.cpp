#include "SceneBase.h"
#include "Utility.h"
#include "SceneFlowBase.h"
/// <summary>
/// ���݂̃V�[���̕ۑ�
/// </summary>
/// <param name="_SceneType">���݂̃V�[���̕ۑ�</param>
SceneBase::SceneBase(SceneType _SceneType)
{
    nowSceneType = _SceneType;
}
/// <summary>
/// SceneFlow�̉��
/// </summary>
SceneBase::~SceneBase()
{
    SAFE_DELETE(sceneFlow);
}
/// <summary>
/// �V�[���̍X�V
/// </summary>
/// <returns>���̃V�[��</returns>
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