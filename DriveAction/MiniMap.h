#pragma once
#include <string>
#include <list>
#include "DxLib.h"
#include "UIManager.h"
class RacerManager;
class ObjectObserver;
class MiniMap
{
public:
    MiniMap(RacerManager* racerManager);
    ~MiniMap();
    void Update(std::list<VECTOR> setCoinPosList);
    void Draw();
private:
    VECTOR ConvertPosition(VECTOR pos);
    //�v���C���[�̃}�[�J�[�̐F
    const unsigned int playerColor = GetColor(255,0,0);
    //���W���̐F
    const unsigned int coinColor = GetColor(200,0,200);
    
    //���@��Icon�̑傫��
    const int iconSize = 5;
    //�~�j�}�b�v�̉摜�̉���
    int mapGraphWidth = 0;
    //�~�j�}�b�v�̉摜�̏c��
    int mapGraphHeight = 0;
    //�}�b�v�̑傫��
    const float mapSize = 420;
    //���W���̏k��
    const float collectBetween = 0.3f;
    //�}�b�v�̑傫���̌W��
    float mapSizeCoefficient = 0;
    //��]�x����
    float mapRotate = 0;
    //�~�j�}�b�v
    UIData miniMap;
    ObjectObserver* playerObserver;
    std::list<VECTOR> coinPosList;
};