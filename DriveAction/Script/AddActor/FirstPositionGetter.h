#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "DxLib.h"
#include "EditObjectData.h"
#include "InitObjKind.h"
#include "Object.h"

/// <summary>
/// �����ʒu���t�@�C������Ƃ��Ă��ĕϊ�����
/// </summary>
class FirstPositionGetter
{
public:
    /// <summary>
    /// �����ʒu��n��
    /// </summary>
    /// <param name="dataKind">�I�u�W�F�N�g�̎�ނɂ���ēǂݍ��ޏ���ύX����</param>
    /// <returns>���̃I�u�W�F�N�g�̈ʒu���܂Ƃ߂��R���e�i</returns>
    static std::vector<PlacementData> GetPlaceData(Object::ObjectTag tag);

    static std::vector<PlacementData> GetPlaceData(std::string fileName, ObjectInit::InitObjKind kind);
private:
    /// <summary>
    /// CSV�t�@�C������X�e�[�W�ɔz�u���邽�߂̏�������
    /// </summary>
    /// <param name="fileName">�z�u���܂ł̃p�X</param>
    /// <param name="kind">�����������z�u���̎��</param>
    /// <returns>CSV�t�@�C������X�e�[�W�ɔz�u���邽�߂̏��</returns>
    static std::vector<PlacementData> CSVConvertFirstData(std::vector<std::string> placeStrData);
};