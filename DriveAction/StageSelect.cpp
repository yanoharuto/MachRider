#include "StageSelect.h"
#include "UserInput.h"
#include "UIDrawer.h"
#include "Utility.h"
/// <summary>
/// �X�e�[�W���ƂɕK�v�ȃA�Z�b�g�̃A�h���X��
/// �����Ă���t�@�C����
/// �A�h���X�������Ă���t�@�C����ǂݍ���
/// </summary>
/// <returns></returns>
StageSelect::StageSelect()
    :StageDataPass()
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
        if (stageNum >= dataLoader.size())
        {
            stageNum = 0;
        }
    }
    else if (UserInput::GetInputState(Up) == Push)
    {
        stageNum--;
        if (stageNum < 0)
        {
            stageNum = dataLoader.size() - 1;
        }
    }
    //�I��ł���X�e�[�W�̃A�h���X��ۑ�
    fileAddres = dataLoader[stageNum];
}
/// <summary>
/// ���ݑI��ł���X�e�[�W��\��
/// </summary>
void StageSelect::Draw() const
{
    UIData data = stageNameData;
    for (int i = 0; i < data.dataHandle.size(); i++)
    {
        if (i == stageNum)
        {
            data.x -= data.width / 2;
        }
        else
        {
            data.x = stageNameData.x;
        }
        UIDrawer::DrawRotaUI(data, i);
        data.y += data.height;
    }
    UIDrawer::DrawRotaUI(selectButtonData);
}
