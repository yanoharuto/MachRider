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
    MiniMap(std::shared_ptr<ObjectObserver> player);
    ~MiniMap();
    void Update();
    void Draw()const;
    static void AddMarker(ObjectObserver* obserber);
private:
    static VECTOR ConvertPosition(VECTOR pos);
    //�v���C���[�̃}�[�J�[�̐F
    const unsigned int playerColor = GetColor(255,0,0);
    //���W���̐F
    const unsigned int coinColor = GetColor(200,0,200);
    
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
    std::weak_ptr<ObjectObserver> playerObserver;

    static std::list<VECTOR> posList;
    std::list<VECTOR> drawPosList;
};