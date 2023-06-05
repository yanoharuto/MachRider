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
    //上下に押したら変更
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
/// どのステージを選んでいるか
/// </summary>
/// <returns>選ばれているステージのアドレスを返す</returns>
std::string StageSelect::GetLoadeStageName()
{
    return fileAddres;
}