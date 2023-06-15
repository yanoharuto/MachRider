#include "StageSelect.h"
#include "Utility.h"
#include "ListUtility.h"
#include "CSVFileLoader.h"
#include "UserInput.h"
std::string StageSelect::fileAddres;

StageSelect::StageSelect()
{
    auto fileLoader = new CSVFileLoader(allStageAddresFile);
    dataLoader = fileLoader->GetLoadStringData();
    SAFE_DELETE(fileLoader);
    dataNum = 0;
    fileAddres = dataLoader[dataNum];
}

StageSelect::~StageSelect()
{
}

void StageSelect::Update()
{
    //�㉺�ɉ�������ύX
    if (UserInput::GetInputState(Up))
    {
        dataNum++;
        if (dataNum >= dataLoader.size())
        {
            dataNum = 0;
        }
    }
    else if (UserInput::GetInputState(Down))
    {
        dataNum--;
        if (dataNum < 0)
        {
            dataNum = dataLoader.size() - 1;
        }
    }
    fileAddres = dataLoader[dataNum];
}
/// <summary>
/// �ǂ̃X�e�[�W��I��ł��邩
/// </summary>
/// <returns>�I�΂�Ă���X�e�[�W�̃A�h���X��Ԃ�</returns>
std::string StageSelect::GetLoadeStageName()
{
    return fileAddres;
}