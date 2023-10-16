#include "UIManager.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "DxLib.h"
//全てのUIのパス
std::vector<std::string> UIManager::uiPathVec;
/// <summary>
/// 全てのUI画像のパスをuiPathVecに渡す
/// </summary>
UIManager::UIManager()
{
    CSVFileLoader* initDataFile = new CSVFileLoader(GetInitCsvFilePass(AssetList::ui));
    uiPathVec = initDataFile->GeFileStringData();
    SAFE_DELETE(initDataFile);
}
/// <summary>
/// UIを所得
/// </summary>
/// <param name="uiKind">所得したいUIの種類</param>
/// <returns>UIの描画に必要な情報を返す</returns>
UIData UIManager::CreateUIData(UIInit::UIKind uiKind)
{
    return CreateUIData(CAST_I(uiKind));
}
/// <summary>
/// 引数のUIの画像を削除する
/// </summary>
/// <param name="ui">消したいUI画像</param>
void UIManager::DeleteUIGraph(UIData* ui)
{
    int size = ui->dataHandle.size();
    for (int i = 0; i < size; i++)
    {
        DeleteGraph(ui->dataHandle[i]);
    }
}
/// <summary>
/// UIを所得
/// </summary>
/// <param name="uiKind">所得したいUI</param>
/// <returns></returns>
UIData UIManager::CreateUIData(int kindNum)
{
    UIData data;

    using enum InitUIData;
    //データ読み取り
    CSVFileLoader* initDataFile = new CSVFileLoader(uiPathVec[kindNum]);
    std::vector<std::string> dataVec = initDataFile->GeFileStringData();
    //位置とか幅とか分割数を読み取る
    data.x = STR_TO_I(dataVec[CAST_I(drawX)]);
    data.y = STR_TO_I(dataVec[CAST_I(drawY)]);
    //横分割数
    int divXNum = STR_TO_I(dataVec[CAST_I(xNum)]);
    //縦分割数
    int divYNum = STR_TO_I(dataVec[CAST_I(yNum)]);
    data.width = STR_TO_I(dataVec[CAST_I(width)]) / divXNum;
    data.height = STR_TO_I(dataVec[CAST_I(height)]) / divYNum;
    //画像を分割読み込み
    int graphArray[1000];
    LoadDivGraph(dataVec[CAST_I(graphPass)].c_str(), divXNum * divYNum, divXNum, divYNum, data.width, data.height, graphArray);
    for (int i = 0; i < divXNum + divYNum - 1; i++)
    {
        data.dataHandle.push_back(graphArray[i]);
    }
    //大きさとコマ送り速度
    data.size = STR_TO_F(dataVec[CAST_I(size)]);
    data.frameSpeed = STR_TO_F(dataVec[CAST_I(frameSpeed)]);
    //初期化データを消す
    SAFE_DELETE(initDataFile);

    return data;
}