#include "StageDataPass.h"
#include "Utility.h"
#include "ListUtility.h"
#include "CSVFileLoader.h"

std::string StageDataPass::fileAddres = "-1";
StageDataPass::StageDataPass()
{
    auto fileLoader = new CSVFileLoader(allStageAddresFile);//全ステージのデータリストを読み取る
    dataLoader = fileLoader->GetLoadStringData();
    SAFE_DELETE(fileLoader);
}
StageDataPass::~StageDataPass()
{
}
/// <summary>
/// ステージの名前
/// </summary>
/// <returns></returns>
std::string StageDataPass::GetLoadeStageName()const
{
    if (fileAddres == "-1")
    {
        fileAddres = dataLoader[0];//とりあえず先頭を渡す
    }
    return fileAddres;
}
/// <summary>
/// 引数についての文字列を出す
/// </summary>
/// <param name="dataKind"></param>
/// <returns></returns>
std::string StageDataPass::LoadStageData(StageData dataKind)const
{
    auto fileLoader = new CSVFileLoader(StageDataPass::GetLoadeStageName());
    auto setStageInitDataVec = fileLoader->GetLoadStringData();
    SAFE_DELETE(fileLoader);
    return setStageInitDataVec[dataKind];
}