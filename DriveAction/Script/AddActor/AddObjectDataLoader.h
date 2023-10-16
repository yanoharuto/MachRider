#pragma once
#include "AssetManager.h"
#include <string>
#include <vector>
/// <summary>
/// オブジェクトの追加情報を読み取るクラス
/// </summary>
class AddObjectDataLoader final:public AssetManager
{
public:
    enum class AddData;
    /// <summary>
    /// 追加情報を読み取る
    /// </summary>
    /// <param name="loadData">読み取りたい追加情報</param>
    AddObjectDataLoader(AddData loadData);
    /// <summary>
    /// 追加情報を文字列で渡す
    /// </summary>
    /// <returns>文字列で渡す</returns>
    std::vector<std::string> GetLoadData()const;
    //追加情報の種類
    enum class AddData
    {
        circleFlyShip,//円陣組んでる飛行船の追加情報
        upDownFlyShip,//上下に移動する飛行船の追加情報
        bomberShip,//爆弾落とす飛行船の追加情報
        moveSaw,//移動回転のこぎりの追加情報
        playerSpeed//プレイヤーの移動情報
    };
private:
    //読み取った追加情報
    std::vector<std::string> loadAddData;
    //Jsonで使うスキーマのパス
    const std::string schemaPass = "data/Json/Schema/objectAddDataSchema.json";
};