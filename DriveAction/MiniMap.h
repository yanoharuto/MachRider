#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <list>
#include "DxLib.h"
#include "UIManager.h"

class ObjectObserver;
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
    static void AddMarker(ObjectObserver* obserber);
private:
    /// <summary>
    /// �Q�[���̂RD �}�b�v�̃T�C�Y�ɍ��킹��
    /// </summary>
    /// <param name="pos"></param>
    /// <returns></returns>
    static VECTOR ConvertPosition(VECTOR pos);
    //�v���C���[�̃}�[�J�[�̐F
    const unsigned int playerColor = GetColor(255,0,0);
    //���W���̐F
    const unsigned int coinColor = GetColor(0,115,255);
    //���@��Icon�̑傫��
    static const int iconSize = 5;
    //�~�j�}�b�v�̉摜�̉���
    static int mapGraphWidth;
    //�~�j�}�b�v�̉摜�̏c��
    static int mapGraphHeight;
    //�}�b�v�̑傫��
    static const float mapSize;
    //���W���̈ʒu�̏k��
    static const float collectBetween;
    //�}�b�v�̑傫���̌W��
    static float mapSizeCoefficient;
    //��]�x����
    float mapRotate = 0;
    //�~�j�}�b�v
    static UIData miniMap;
    //�}�b�v�̒��S���ɂ���
    std::weak_ptr<ObjectObserver> playerObserver;
    //�}�[�J�[�̈ʒu���X�V���邽�߂̃��X�g
    static std::list<ObjectObserver*> markerObserverList;
    //�`��ʒu�̃��X�g
    std::list<VECTOR> drawPosList;
};