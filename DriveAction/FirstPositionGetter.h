#pragma once
#include "StageDataPass.h"

using namespace InitStage;
/// <summary>
/// �����ʒu��ݒ肷��
/// </summary>
class FirstPositionGetter :StageDataPass
{
public:
    FirstPositionGetter();
    ~FirstPositionGetter();
    /// <summary>
    /// �����ʒu��n��
    /// </summary>
    /// <param name="dataKind"></param>
    /// <returns></returns>
    std::unordered_map<int, std::vector<VECTOR>>GetFirstPositionLoad(FirstPositionDataKind dataKind);
    /// <summary>
    /// ���W�A�C�e���ƓG�̈ʒu�f�[�^
    /// </summary>
    /// <returns></returns>
    std::vector<ChallengeData> GetChallengeData();
private:
    /// <summary>
    /// CSV�t�@�C�����������map��key�̏ꏊ��ϊ�
    /// </summary>
    /// <param name="map"></param>
    /// <param name="fileName"></param>
    static void CSVConvertPosition(std::unordered_map<int, std::vector<VECTOR>>* map,std::string fileName);
    //��
    static int stageWidth;
    //����
    static int stageLength;
    //�v���C���[�����Ȃ��Ȃ���΂����Ȃ��ۑ��Vector
    std::vector<std::string> challengeVec;
    //�v���C���[���X�e�[�W�̃I�u�W�F�N�g�̔z�u
    std::unordered_map<FirstPositionDataKind,std::string> positionDataPassMap;
};