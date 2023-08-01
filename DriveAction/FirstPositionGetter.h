#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "DxLib.h"
#include "StageDataManager.h"
#include "EditObjectData.h"
#include "InitObjKind.h"
#include "Object.h"
using namespace InitStage;
/// <summary>
/// �����ʒu���t�@�C������Ƃ��Ă��ĕϊ�����
/// </summary>
class FirstPositionGetter
{
public:
    /// <summary>
    /// �����ʒu��n��
    /// </summary>
    /// <param name="dataKind"></param>
    /// <returns></returns>
    static std::vector<EditArrangementData> GetInitData(Object::ObjectTag tag);
    /// <summary>
    /// CSV�t�@�C������X�e�[�W�ɔz�u���邽�߂̏�������
    /// </summary>
    /// <param name="fileName"></param>
    static std::vector<EditArrangementData> CSVConvertFirstData(std::string fileName);
private:

};