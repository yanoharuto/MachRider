#include "StageSelect.h"
#include "UserInput.h"
#include "UIDrawer.h"
#include "Utility.h"
#include "StageDataManager.h"
/// <summary>
/// �X�e�[�W���ƂɕK�v�ȃA�Z�b�g�̃A�h���X��
/// �����Ă���t�@�C����
/// �A�h���X�������Ă���t�@�C����ǂݍ���
/// </summary>
/// <returns></returns>
StageSelect::StageSelect()
{
    stageNum = 0;
    stageNameData = UIManager::CreateUIData(stageName);
    selectButtonData = UIManager::CreateUIData(stageSelectButton);
}
/// <summary>
/// �V�ԃX�e�[�W�ύX����Ƃ��Ɏg��
/// </summary>
/// <param name="next">���̃X�e�[�WTrue�O�̃X�e�[�W��false</param>
void StageSelect::Update()
{
    //�㉺�ɉ�������ύX
    if (UserInput::GetInputState(Down) == Push)
    {
        stageNum++;
        //�X�e�[�W���̌��E�ɗ�����0��
        if (stageNum >= StageDataManager::GetStageTotalNumber())
        {
            stageNum = 0;
        }
    }
    else if (UserInput::GetInputState(Up) == Push)
    {
        stageNum--;
        //�X�e�[�W���̍Œ�ɗ�����ő�l��
        if (stageNum < 0)
        {
            stageNum = StageDataManager::GetStageTotalNumber() - 1;
        }
    }
    //�ύX�������Ƃ�`����
    StageDataManager::ChangeStageData(this);
}
/// <summary>
/// �X�e�[�W�ꗗ��\��
/// </summary>
void StageSelect::Draw() const
{
    UIData data = stageNameData;
    for (int i = 0; i < data.dataHandle.size(); i++)
    {
        if (i == stageNum)//���݂̃X�e�[�W�͑傫��������Ƃ��炵�ĕ\��
        {
            data.x -= data.width / 2;
            data.size *= selectSizeCoefficient;
        }
        else
        {
            data.x = stageNameData.x;
            data.size = stageNameData.size;
        }
        UIDrawer::DrawRotaUI(data, i);
        data.y += data.height;
    }
    UIDrawer::DrawRotaUI(selectButtonData);
}
/// <summary>
/// �X�e�[�W�̔ԍ�
/// </summary>
/// <returns></returns>
int StageSelect::GetStageNum()const
{
    return stageNum;
}
