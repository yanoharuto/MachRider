#pragma once
#include "Actor.h"
#include "DxLib.h"
/// <summary>
/// ��Q���@�i�ۂ̂��j
/// </summary>
class Saw :
    public Actor
{
public:
    Saw();
    /// <summary>
    /// �����̏ꏊ�ɐݒu����
    /// </summary>
    /// <param name="pos"></param>
    /// <param name="duplicateModelHandle"></param>
    Saw(VECTOR pos, int duplicateModelHandle);
    ~Saw();
    /// <summary>
    /// ��]������
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update() override;
private:
    //��]��
    const float addRotate = 22.0f;
    //��
    const float setRadius = 23.0f;
    //�͂����Ԃ���
    const float setBouncePower = 4.0f;
    //����
    const float thickness = 5.0f;
    //��]
    float rotate = 0;
};