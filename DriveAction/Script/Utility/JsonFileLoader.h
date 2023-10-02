#pragma once
#include <vector>
#include "document.h"
/// <summary>
/// Jsonファイル読み取りクラス
/// </summary>
class JsonFileLoader
{
public:
    /// <summary>
    /// Json形式のファイルを開く
    /// </summary>
    /// <param name="filePass">開きたいファイル</param>
    /// <param name="schemaFilePass">開くファイルのSchema</param>
    JsonFileLoader(std::string filePass,std::string schemaFilePass);
    /// <summary>
    /// Schemaと開きたいファイルが適応しているなら
    /// </summary>
    /// <returns>適応したならTrue</returns>
    bool IsAccept()const;
    /// <summary>
    /// float型
    /// </summary>
    /// <param name="dataName">読み取りたいデータ</param>
    /// <returns>取りたいデータ</returns>
    float GetLoadFloat(std::string dataName)const;
    /// <summary>
    /// 必要なデータ文字列を読み取る
    /// </summary>
    /// <param name="dataName">読み取りたいデータの名前</param>
    /// <returns>取りたいデータ</returns>
    std::string GetLoadString(std::string dataName)const;
private:
    //Schemaと開きたいファイルが適応しているなら
    bool isAccept;
    //読み取る状態
    rapidjson::Document loadDoc;
};