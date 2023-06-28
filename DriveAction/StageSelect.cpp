#include "StageSelect.h"
#include "UserInput.h"
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
}
/// <summary>
/// �V�ԃX�e�[�W�ύX����Ƃ��Ɏg��
/// </summary>
/// <param name="next">���̃X�e�[�WTrue�O�̃X�e�[�W��false</param>
void StageSelect::Update()
{
    //�㉺�ɉ�������ύX
    if (UserInput::GetInputState(Up) == Push)
    {
        stageNum++;
        if (stageNum >= dataLoader.size())
        {
            stageNum = 0;
        }
    }
    else if (UserInput::GetInputState(Down) == Push)
    {
        stageNum--;
        if (stageNum < 0)
        {
            stageNum = dataLoader.size() - 1;
        }
    }
    fileAddres = dataLoader[stageNum];
}
/// <summary>
/// ���ݑI��ł���X�e�[�W��\��
/// </summary>
void StageSelect::Draw() const
{
    DrawGraph(stageNameData.x, stageNameData.y, stageNameData.dataHandle[stageNum], true);
}
