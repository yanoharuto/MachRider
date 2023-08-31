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
    selectStageNum = 0;
    StageDataManager::ChangeStageData(this);
    stageNameUI = UIManager::CreateUIData(stageName);
    selectButtonUI = UIManager::CreateUIData(stageSelectButton);
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
        selectStageNum++;
        //�X�e�[�W���̌��E�ɗ�����0��
        if (selectStageNum >= StageDataManager::GetStageTotalNumber())
        {
            selectStageNum = 0;
        }
    }
    else if (UserInput::GetInputState(Up) == Push)
    {
        selectStageNum--;
        //�X�e�[�W���̍Œ�ɗ�����ő�l��
        if (selectStageNum < 0)
        {
            selectStageNum = StageDataManager::GetStageTotalNumber() - 1;
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
    //stageNameUI��Copy
    UIData stageNameData = stageNameUI;
    for (int i = 0; i < stageNameData.dataHandle.size(); i++)
    {
        if (i == selectStageNum)//���ݑI��ł���X�e�[�W�͑傫��������Ƃ��炵�ĕ\��
        {
            stageNameData.x -= stageNameData.width / 2;
            stageNameData.size *= selectSizeCoefficient;
        }
        else
        {
            stageNameData.x = stageNameUI.x;
            stageNameData.size = stageNameUI.size;
        }
        //�e�X�e�[�W�̑I��UI��`��
        UIDrawer::DrawRotaUI(stageNameData, i);
        stageNameData.y += stageNameData.height;
    }
    //�I������Ƃ��̃{�^����\��
    UIDrawer::DrawRotaUI(selectButtonUI);
}
/// <summary>
/// �X�e�[�W�̔ԍ�����
/// </summary>
/// <returns>���I�����Ă���X�e�[�W�̔ԍ�</returns>
int StageSelect::GetSelectStageNum()const
{
    return selectStageNum;
}
