#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "DxLib.h"
#include "StageInitializer.h"
using namespace InitStage;
/// <summary>
/// �����ʒu��ݒ肷��
/// </summary>
class FirstPositionGetter
{
public:
    FirstPositionGetter();
    ~FirstPositionGetter();
    /// <summary>
    /// �����ʒu�����[�h
    /// </summary>
    /// <param name="dataKind"></param>
    /// <returns></returns>
    std::unordered_map<int, std::vector<VECTOR>>GetFirstPositionLoad(FirstPositionDataKind dataKind);
    std::vector<ChallengeData> GetChallengeData();
private:
    static void CSVConvertPosition(std::unordered_map<int, std::vector<VECTOR>>* map,std::string fileName);
    static int stageWidth;
    static int stageLength;
    //�v���C���[�����Ȃ��Ȃ���΂����Ȃ��ۑ��Vector
    std::vector<std::string> challengeVec;
    //�v���C���[���X�e�[�W�̃I�u�W�F�N�g�̔z�u
    std::unordered_map<FirstPositionDataKind,std::string> positionDataPassMap;
};