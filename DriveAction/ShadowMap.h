#pragma once
#include "DxLib.h"
#include "ObjPosAndDir.h"
class ObjectObserver;
class ObjectSubject;
class RacerManager;
/// <summary>
/// �e��`�悷��N���X
/// </summary>
class ShadowMap
{
public:
    /// <summary>
    /// �e��`�悷��N���X
    /// </summary>
    ShadowMap(RacerManager* manager);
    ~ShadowMap();
    /// <summary>
    /// �e�̕`��͈͂̕ύX
    /// </summary>
    /// <param name="objInfo">�����̍��W�𒆐S�ɂ���</param>
    void SetShadowMapErea();
    /// <summary>
    /// ���ꂩ��`�悷��e�̏���
    /// </summary>
    void SetUP();
    /// <summary>
    /// �e��`�悷��̏I��
    /// </summary>
    void DrawEnd();
    /// <summary>
    /// �������񂾃V���h�E�}�b�v���g��
    /// </summary>
    void Use();
private:
    //�V���h�E�}�b�v�̍ŏ��͈͂�ݒ�
    VECTOR DrawAreaMinPos = VGet(-300.0f, -1.0f, -300.0f);
    //�V���h�E�}�b�v�̍ő�͈͂�ݒ�
    VECTOR DrawAreaMaxPos = VGet(300.0f, 700.0f, 300.0f);
    //�V���h�E�}�b�v�쐻
    int shadowMap = MakeShadowMap(2048, 2048);
    //���������ɉe�����͈͂����߂�
     ObjectObserver* playerObserber;
};

