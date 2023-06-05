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
    fileNameIte = dataLoader.begin();
    fileAddres = *fileNameIte;
    fileNameIte++;
}

StageSelect::~StageSelect()
{
}

void StageSelect::Update()
{
    //�㉺�ɉ�������ύX
    if (UserInput::GetInputState(Up))
    {
        fileNameIte++;
        if (fileNameIte == dataLoader.end())
        {
            fileNameIte = dataLoader.begin();
        }
    }
    else if (UserInput::GetInputState(Down))
    {
        if (fileNameIte == dataLoader.begin())
        {
            fileNameIte = dataLoader.end();
        }
        fileNameIte--;
    }
    fileAddres = *fileNameIte;
}
/// <summary>
/// �ǂ̃X�e�[�W��I��ł��邩
/// </summary>
/// <returns>�I�΂�Ă���X�e�[�W�̃A�h���X��Ԃ�</returns>
std::string StageSelect::GetLoadeStageName()
{
    return fileAddres;
}