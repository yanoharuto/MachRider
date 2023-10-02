#include <fstream>
#include <iostream>
#include "JsonFileLoader.h"
#include "istreamwrapper.h"
#include "schema.h"
#include "stringbuffer.h"
/// <summary>
/// Json形式のファイルを開く
/// </summary>
/// <param name="filePass">開きたいファイル</param>
/// <param name="schemaFilePass">開くファイルのSchema</param>
JsonFileLoader::JsonFileLoader(std::string filePass, std::string schemaFilePass)
{
    //スキーマから書き方を調べる
    std::ifstream schema_ifs(schemaFilePass);
    rapidjson::IStreamWrapper schema_isw(schema_ifs);
    rapidjson::Document schema_doc;
    schema_doc.ParseStream(schema_isw);
    //読み取りたいデータファイルを開く
    std::ifstream ifs(filePass);
    rapidjson::IStreamWrapper isw(ifs);
    loadDoc.ParseStream(isw);
    //スキーマ通りの書き方か調べる
    rapidjson::SchemaDocument schema(schema_doc);
    rapidjson::SchemaValidator validator(schema);
    isAccept = loadDoc.Accept(validator);
    //失敗した
    if (!isAccept) {
        rapidjson::StringBuffer sb;
        validator.GetInvalidDocumentPointer().StringifyUriFragment(sb);//リソースの場所をSBに渡す
        std::cout << "Invalid schema:" << sb.GetString() << std::endl;
        std::cout << "Invalid keyword:" << validator.GetInvalidSchemaKeyword() << std::endl;
    }
}
/// <summary>
/// Schemaと開きたいファイルが適応しているなら
/// </summary>
/// <returns>適応したならTrue</returns>
bool JsonFileLoader::IsAccept() const
{
    return isAccept;
}
/// <summary>
/// float型
/// </summary>
/// <param name="dataName">読み取りたいデータ</param>
/// <returns>取りたいデータ</returns>
float JsonFileLoader::GetLoadFloat(std::string dataName)const
{
    return loadDoc[dataName.c_str()].GetFloat();
}
/// <summary>
/// 必要なデータ文字列を読み取る
/// </summary>
/// <param name="dataName">読み取りたいデータの名前</param>
/// <returns>取りたいデータ</returns>
std::string JsonFileLoader::GetLoadString(std::string dataName) const
{
    return loadDoc[dataName.c_str()].GetString();
}
