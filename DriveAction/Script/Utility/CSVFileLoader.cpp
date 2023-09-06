#include <fstream>
#include <sstream>
#include "CSVFileLoader.h"
#include "Utility.h"
using namespace std;
/// <summary>
/// CSVファイルを読み込む
/// </summary>
/// <param name="filePass">読み込むファイルのパス</param>
CSVFileLoader::CSVFileLoader(std::string filePass)
{
    //ファイルを開いて
    lineCount = 0;
    ifstream ifs(filePass.c_str());
    //1行ずつ読み込む
    string line;
    while (getline(ifs, line)) 
    {
        lineCount++;
        Split(line, ',');//,まで読み込む
    }
    //閉じる
    ifs.close();
}
/// <summary>
/// CSVファイルを読み込む
/// </summary>
/// <returns></returns>
std::vector<std::string> CSVFileLoader::GetLoadStringData()const
{
    return loadData;
}
/// <summary>
/// CSVファイルを読み込む
/// </summary>
/// <returns></returns>
std::vector<const char*> CSVFileLoader::GetLoadCharData()const
{
    std::vector<const char*> charVec;
    for (int i = 0; i < SAFE_GET_SIZE(loadData); i++)
    {
        charVec.push_back(loadData[i].c_str());
    }
    return charVec;
}
/// <summary>
/// 読み込んだファイルの行
/// </summary>
/// <returns></returns>
int CSVFileLoader::GetLineCount()const
{
    return lineCount;
}
/// <summary>
/// 読み込んだファイルの各行のデータを抽出
/// </summary>
/// <param name="input">各行のデータ</param>
/// <param name="delimiter">止める文字</param>
void CSVFileLoader::Split(std::string& input, char delimiter)
{
    istringstream stream(input);
    string field;
    //第二引数まで移していく
    while (getline(stream, field, delimiter)) 
    {
        loadData.push_back(field);
    }
}
