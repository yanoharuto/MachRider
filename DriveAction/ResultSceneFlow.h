#pragma once
#include "SpaceKeyUI.h"
#include "SceneFlowBase.h"
#include <string>
class UIManager;
/// <summary>
/// ���U���g�V�[���̏����̗���
/// </summary>
class ResultSceneFlow:public SceneFlowBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ResultSceneFlow();

    ~ResultSceneFlow();
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update()override;
    /// <summary>
    /// �`��
    /// </summary>
    void Draw() const override;
private:
    //�X�y�[�X�L�[�̍Ñ�
    FlashUI* switchUI;
};

