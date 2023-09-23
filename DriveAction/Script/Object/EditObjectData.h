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
enum class EditArrangementDataKind
{
    //�ۑ�����I�u�W�F�N�g�̎��
    objectKindNum = 0,
    //�o�Ă���^�C�~���O�̎��W�A�C�e���̐�
    appearCollectNum = 1,
    //�������WX
    positionX = 2,
    //�������WY
    positionZ = 3,
    //��������X
    directionX = 4,
    //��������Z
    directionZ = 5,
};
//�������f�[�^�̎�ނ̐�
#define EDIT_ARRANGEMENT_DATA_KIND_NUM 6