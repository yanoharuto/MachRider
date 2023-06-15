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
    //上下に押したら変更
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
/// どのステージを選んでいるか
/// </summary>
/// <returns>選ばれているステージのアドレスを返す</returns>
std::string StageSelect::GetLoadeStageName()
{
    return fileAddres;
}