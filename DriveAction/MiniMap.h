#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <list>
#include "DxLib.h"
#include "UIManager.h"
#include "ObjectObserver.h"

/// <summary>
/// �v���C���[�𒆐S�ɋ߂��ɃA�C�e�������邩���ׂ�����
/// </summary>
class MiniMap
{
public:
    MiniMap(std::weak_ptr<ObjectObserver> player);
    ~MiniMap();
    /// <summary>
    /// �~�j�}�b�v�ɕ\������}�[�J�[�̈ʒu���X�V
    /// </summary>
    void Update();
    /// <summary>
    /// �}�b�v�ɕ\������_�ƃ��[�_�[�̘g
    /// </summary>
    void Draw()const;
    /// <summary>
    /// �}�b�v�ɔ��f���������A�C�e���̒ǉ�
    /// </summary>
    /// <param name="obserber"></param>
    static void AddMarker(std::unique_ptr<ObjectObserver> obserber);
private:

    /// <summary>
    /// �~�j�}�b�v�̑傫���ɕϊ�����
    /// </summary>
    /// <param name="between">�����̃A�C�e������̋���</param>
    /// <returns></returns>
    VECTOR ConvertPosition(VECTOR between);
    //�v���C���[�̃}�[�J�[�̐F
    const unsigned int playerColor = GetColor(255,0,0);
    //���W���̐F
    const unsigned int coinColor = GetColor(0,115,255);
    //���@��Icon�̑傫��
    static const int iconSize = 5;
    //�~�j�}�b�v�̉摜�̉���
    static int mapGraphWidth;
    //�~�j�}�b�v�̉摜�̏c��
    static int mapGraphLength;
    //���W���̈ʒu�̏k��
    float betweenSize = 0.25f;
    //�~�j�}�b�v
    static UIData miniMap;
    //�}�b�v�̒��S���ɂ���
    std::weak_ptr<ObjectObserver> playerObserver;
    //�}�[�J�[�̈ʒu���X�V���邽�߂̃��X�g
    static std::list<std::unique_ptr<ObjectObserver>> markerObserverList;
    //�`��ʒu�̃��X�g
    std::list<VECTOR> drawPosList;
};