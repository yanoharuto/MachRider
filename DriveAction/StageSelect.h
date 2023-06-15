#pragma once
#include <vector>
#include <string>

/// <summary>
/// タイトル画面でステージ選ぶ時に使う
/// </summary>
class StageSelect
{
public:
    /// <summary>
    /// ステージごとに必要なアセットのアドレスが
    /// 書いてあるファイルの
    /// アドレスが書いてあるファイルを読み込む
    /// </summary>
    /// <returns></returns>
    StageSelect();
    ~StageSelect();
    /// <summary>
    /// 遊ぶステージ変更するときに使う
    /// </summary>
    /// <param name="next">次のステージTrue前のステージかfalse</param>
    void Update();
    /// <summary>
    /// どのステージを選んでいるか
    /// </summary>
    /// <returns></returns>
    static std::string GetLoadeStageName();
private:
    int dataNum;
    //ステージの一覧的な奴
    std::string allStageAddresFile = "data/stageData/stageDataList.csv";

    std::vector<std::string> dataLoader;
    //各ステージのデータのパス
    static std::string fileAddres;
};

