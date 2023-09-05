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
        isEndProcesss = false; 
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
    virtual void Draw() const = 0;
    /// <summary>
    /// �������I�������
    /// </summary>
    /// <returns></returns>
    bool GetIsEndProcesss() { return isEndProcesss; };
    /// <summary>
    /// ���̃V�[���̃^�C�v
    /// </summary>
    /// <returns></returns>
    SceneType GetNextSceneType() { return nextSceneType; };
protected:
    //�������I�������
    bool isEndProcesss = false;
    //���̃V�[���͂ǂꂩ
    SceneType nextSceneType = SceneType::TITLE;
};