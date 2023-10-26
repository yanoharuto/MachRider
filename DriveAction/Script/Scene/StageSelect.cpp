#include "StageSelect.h"
#include "UserInput.h"
#include "UIDrawer.h"
#include "Utility.h"
#include "StageDataManager.h"
/// <summary>
/// �X�e�[�W�I��UI�̓ǂݍ���
/// ��ԍŏ��̃X�e�[�W�ɕύX
/// </summary>
StageSelect::StageSelect()
{
    selectStageNum = 0;
    StageDataManager::ChangeStageData(this);
    stageNameUIData = UIManager::CreateUIData(UIKind::stageName);
    selectButtonUIData = UIManager::CreateUIData(UIKind::stageSelectButton);
}
/// <summary>
/// UI�̍폜
/// </summary>
StageSelect::~StageSelect()
{
    UIManager::DeleteUIGraph(&selectButtonUIData);
    UIManager::DeleteUIGraph(&stageNameUIData);
}
/// <summary>
/// �\���L�[�ŗV�ԃX�e�[�W�ύX
/// </summary>
void StageSelect::Update()
{
    //�㉺�ɉ�������ύX
    if (UserInput::GetInputState(UserInput::KeyInputKind::Down) == UserInput::InputState::Push)
    {
        selectStageNum++;
        //�X�e�[�W���̌��E�ɗ�����0��
        if (selectStageNum >= StageDataManager::GetStageTotalNumber())
        {
            selectStageNum = 0;
        }
    }
    else if (UserInput::GetInputState(UserInput::KeyInputKind::Up) == UserInput::InputState::Push)
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
    UIData stageNameUI = stageNameUIData;
    for (int i = 0; i < CONTAINER_GET_SIZE(stageNameUIData.dataHandle); i++)
    {
        if (i == selectStageNum)//���ݑI��ł���X�e�[�W�͑傫��������Ƃ��炵�ĕ\��
        {
            stageNameUI.x -= stageNameUIData.width / 2;
            stageNameUI.size *= selectSizeCoefficient;
        }
        else
        {
            stageNameUI.x = stageNameUIData.x;
            stageNameUI.size = stageNameUIData.size;
        }
        //�e�X�e�[�W�̑I��UI��`��
        UIDrawer::DrawRotaUI(stageNameUI, i);
        stageNameUI.y += stageNameUIData.height;
    }
    //�I������Ƃ��̃{�^����\��
    UIDrawer::DrawRotaUI(selectButtonUIData);
}
/// <summary>
/// �X�e�[�W�̔ԍ�����
/// </summary>
/// <returns>���I�����Ă���X�e�[�W�̔ԍ�</returns>
int StageSelect::GetSelectStageNum()const
{
    return selectStageNum;
}