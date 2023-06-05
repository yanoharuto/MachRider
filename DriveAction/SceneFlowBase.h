#pragma once
#include "SceneType.h"

/// <summary>
/// �V�[�����Ƃ̏����̗���
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
    /// �X�V
    /// </summary>
    /// <param name="deltaTime"></param>
    virtual void Update() = 0;
    /// <summary>
    /// �`��
    /// </summary>
    virtual void Draw() = 0;
    /// <summary>
    /// �������I�������
    /// </summary>
    /// <returns></returns>
    bool GetIsEndProccess() { return isEndProccess; };
    /// <summary>
    /// ���̃V�[���̃^�C�v
    /// </summary>
    /// <returns></returns>
    SceneType GetNextSceneType() { return nextSceneType; };
protected:
    //�������I�������
    bool isEndProccess = false;
    //���̃V�[���͂ǂꂩ
    SceneType nextSceneType = SceneType::TITLE;
};