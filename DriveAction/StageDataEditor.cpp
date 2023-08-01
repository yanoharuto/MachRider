#include <fstream>
#include <string>
#include "StageDataEditor.h"
#include "UserInput.h"
#include "EditObjectData.h"
#include "UserInput.h"
#include "OriginalMath.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
//���ҏW���Ă���I�u�W�F�N�g�̃|�W�V����
EditArrangementData StageDataEditor::nowEditObjData = {};
/// ���W�A�C�e���̐�
int StageDataEditor::collectNum = 0;

/// ���W�A�C�e����������ǂ̃^�C�~���O�ŏo�Ă��邩
int StageDataEditor::missionNum = 0;
//�I�����Ă��镨�̈ʒu��\��
int StageDataEditor::selectAura = -1;
//�I�����Ă��镨�̌�����\��
int StageDataEditor::dirEffect = -1;
/// <summary>
///�X�e�[�W�ɔz�u����I�u�W�F�N�g�̈ʒu�Ȃǂ�ۑ�����
/// </summary>
/// <param name="setFileName">�ǂ̃t�@�C���ɕۑ����邩������</param>
StageDataEditor::StageDataEditor(std::string setFileName)
{
    saveFileName = setFileName;
    missionNum = 0;
    collectNum = 0;
    //�I���G�t�F�N�g
    if (selectAura == -1)
    {
        EffectManager::LoadEffect(collectAura);
        EffectManager::LoadEffect(compass);
        selectAura = EffectManager::GetPlayEffect3D(collectAura);
        dirEffect = EffectManager::GetPlayEffect3D(compass);
    }
    //�������łɃt�@�C��������Ȃ�f�[�^������Ă���
    editDataVec = FirstPositionGetter::CSVConvertFirstData(setFileName);
    //��x�t�@�C�����폜
    remove(saveFileName.c_str());
}

StageDataEditor::~StageDataEditor()
{
}
/// <summary>
/// ���ҏW���Ă���I�u�W�F�N�g�̃|�W�V����
/// </summary>
/// <returns></returns>
VECTOR StageDataEditor::GetEditObjPos()
{
    return  VGet(nowEditObjData.posX,0,nowEditObjData.posZ);
}
/// <summary>
/// ���Ԗڂ̃~�b�V�������ύX����
/// </summary>
void StageDataEditor::ChangeMissionNum()
{
    if (UserInput::GetInputState(SKey) == Hold)
    {
        if (UserInput::GetInputState(Up) == Push)
        {
            //���W�A�C�e���̐���葽���Ȃ�Ȃ�
            if (missionNum + 1 > collectNum)
            {
                missionNum = collectNum;
            }
            else
            {
                missionNum++;
            }
        }
        else if (UserInput::GetInputState(Down) == Push)
        {
            //0��菭�Ȃ��Ȃ�Ȃ�
            if (missionNum - 1 < 0)
            {
                missionNum = 0;
            }
            else
            {
                missionNum--;
            }
        }
    }
}
/// <summary>
/// �ҏW�ς݃f�[�^�̍폜
/// </summary>
/// <param name="eraceNum">�폜����̂͐擪���牽�Ԗڂ�</param>
void StageDataEditor::EraceEndEditData(int eraceNum)
{
    auto editData = editDataVec.begin();
    editData += eraceNum;
    editDataVec.erase(editData);
}

/// <summary>
/// �����̏�����������
/// </summary>
/// <param name="data"></param>
void StageDataEditor::SaveEditObjectData(EditArrangementData data)const
{
    std::ofstream writing_file;
    // �t�@�C�����J����
    writing_file.open(saveFileName, std::ios::app);
    //��؂蕶��
    std::string colon = ",";
    //�I�u�W�F�N�g�̎�ނ�
    writing_file << std::to_string(data.objKind) + colon << std::endl;
    //���Ԗڂ̃~�b�V�����̎���
    writing_file << std::to_string(data.missionNum) + colon << std::endl;
    //�ʒu
    writing_file << std::to_string(data.posX) + colon << std::endl;
    writing_file << std::to_string(data.posZ) + colon << std::endl;
    //����
    writing_file << std::to_string(data.dirX) + colon << std::endl;
    writing_file << std::to_string(data.dirZ) + colon << std::endl;
    writing_file.close();
}
/// <summary>
/// �I�𕨂̌����ƈʒu���킩��G�t�F�N�g�̍X�V
/// </summary>
void StageDataEditor::UpdateEffect()
{
    VECTOR dir = VGet(nowEditObjData.dirX, 0, nowEditObjData.dirZ);
    //�I���������̕�����������G�t�F�N�g����]����
    float degree = OriginalMath::GetDegreeMisalignment(VGet(1,0,0),dir);
    if (VCross(VGet(1, 0, 0),dir).y < 0)
    {
        SetRotationPlayingEffekseer3DEffect(dirEffect, 0, -degree * RAGE, 0);
    }
    else
    {
        SetRotationPlayingEffekseer3DEffect(dirEffect, 0, degree * RAGE, 0);
    }
    //�I���������̃|�W�V������������G�t�F�N�g
    SetPosPlayingEffekseer3DEffect(selectAura, nowEditObjData.posX, 0, nowEditObjData.posZ);
    SetPosPlayingEffekseer3DEffect(dirEffect, nowEditObjData.posX, 0, nowEditObjData.posZ);
}