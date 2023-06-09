#pragma once
#include <vector>
#include <string>

/// <summary>
/// 
/// </summary>
class CSVFileLoader
{
public:
    /// <summary>
    /// CSVファイルを読み込む
    /// </summary>
    /// <param name="fileName"></param>
    CSVFileLoader(std::string fileName);
    ~CSVFileLoader();
    /// <summary>
    /// CSVファイルを読み込む
    /// </summary>
    /// <returns></returns>
    std::vector <std::string> GetLoadStringData()const;
    /// <summary>
    /// CSVファイルを読み込む
    /// </summary>
    /// <returns></returns>
    std::vector <const char*> GetLoadCharData()const;
    /// <summary>
    /// 読み込んだファイルの行
    /// </summary>
    /// <returns></returns>
    int GetLineCount()const;
private:
    /// <summary>
    /// 読み込んだファイルの各行のデータを抽出
    /// </summary>
    /// <param name="input">各行のデータ</param>
    /// <param name="delimiter">止める文字</param>
    void Split(std::string& input, char delimiter);
    //読み込んだファイルのデータ
    std::vector <std::string> loadData;
    //読み込んだファイルの行
    int lineCount;
};

