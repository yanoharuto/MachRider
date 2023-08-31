#pragma once
#include "DxLib.h"
/// <summary>
/// �ۑ����������
/// </summary>
struct PlacementData
{
    //�I�u�W�F�N�g�̎��
    int objKind = 0;
    //���Ԗڂ̎��W�A�C�e���̃^�C�~���O��
    int collectNum = 0;
    //�|�W�V����X
    float posX = 0;
    //�|�W�V����Z
    float posZ = 0;
    //����X
    float dirX = 0;
    //����Z
    float dirZ = 0;
};
/// <summary>
/// �ۑ����������̎��
/// </summary>
enum EditArrangementDataKind
{
    objectKindNum = 0,
    missionTurnNum = 1,
    positionX = 2,
    positionZ = 3,
    directionX = 4,
    directionZ = 5,
};
//�������f�[�^�̎�ނ̐�
#define EDIT_ARRANGEMENT_DATA_KIND_NUM 6