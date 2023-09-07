#include "UIManager.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "DxLib.h"
//全てのUIのパス
std::vector<std::string> UIManager::uiPathVec;
//UI画像の情報
std::unordered_map<int, UIData> UIManager::loadUIDataMap;
/// <summary>
/// 全てのUI画像のパスをuiPathVecに渡す
/// </summary>
UIManager::UIManager()
{
    CSVFileLoader* initDataFile = new CSVFileLoader(initUIDataPassFile);
    uiPathVec = initDataFile->GeFileStringData();
    SAFE_DELETE(initDataFile);
}
/// <summary>
/// 各UIに使っている画像を消去
/// </summary>
UIManager::~UIManager()
{
    for (auto itr = loadUIDataMap.begin(); itr != loadUIDataMap.end(); itr++)
    {
        //分割読み込み画像を消去
        auto graphs = ((*itr).second).dataHandle;
        for (int i = 0; i < SAFE_GET_SIZE(graphs); i++)
        {
            DeleteGraph(graphs[i]);
        }
    }
    loadUIDataMap.clear();
}
/// <summary>
/// UIを所得
/// </summary>
/// <param name="uiKind">所得したいUIの種類</param>
/// <returns>UIの描画に必要な情報を返す</returns>
UIData UIManager::CreateUIData(UIKind uiKind)
{
    return CreateUIData(static_cast<int>(uiKind));
}
/// <summary>
/// UIを所得
/// </summary>
/// <param name="uiKind">所得したいUI</param>
/// <returns></returns>
UIData UIManager::CreateUIData(int kindNum)
{
    UIData data;
    if (loadUIDataMap.contains(kindNum))//すでにダウンロードしているなら
    {
        data = loadUIDataMap[kindNum];
    }
    else
    {
        //データ読み取り
        CSVFileLoader* initDataFile = new CSVFileLoader(uiPathVec[kindNum]);
        std::vector<std::string> dataVec = initDataFile->GeFileStringData();
        //位置とか幅とか分割数を読み取る
        data.x = SAFE_STR_TO_I(dataVec[drawX]);
        data.y = SAFE_STR_TO_I(dataVec[drawY]);
        //横分割数
        int divXNum = SAFE_STR_TO_I(dataVec[xNum]);
        //縦分割数
        int divYNum = SAFE_STR_TO_I(dataVec[yNum]);
        data.width = SAFE_STR_TO_I(dataVec[width]) / divXNum;
        data.height = SAFE_STR_TO_I(dataVec[height]) / divYNum;
        //画像を分割読み込み
        int graphArray[1000];
        LoadDivGraph(dataVec[graphPass].c_str(), divXNum * divYNum, divXNum, divYNum, data.width, data.height, graphArray);
        for (int i = 0; i < divXNum + divYNum - 1; i++)
        {
            data.dataHandle.push_back(graphArray[i]);
        }
        //大きさとコマ送り速度
        data.size = SAFE_STR_TO_F(dataVec[UISize]);
        data.frameSpeed = SAFE_STR_TO_F(dataVec[frameSpeed]);
        //再ダウンロードする時用に保存する
        loadUIDataMap.insert(std::make_pair(kindNum, data));
        //初期化データを消す
        SAFE_DELETE(initDataFile);
    }
    return data;
}