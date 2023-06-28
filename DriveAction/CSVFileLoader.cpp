#include "CSVFileLoader.h"
#include <fstream>
#include <sstream>

using namespace std;
/// <summary>
/// CSVファイルを読み込む
/// </summary>
/// <param name="fileName"></param>
CSVFileLoader::CSVFileLoader(std::string fileName)
{
    lineCount = 0;
    ifstream ifs(fileName.c_str());

    string line;
    while (getline(ifs, line)) 
    {
        lineCount++;
        Split(line, ',');//,まで読み込む
    }

}
CSVFileLoader::~CSVFileLoader()
{
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
    for (int i = 0; i < loadData.size(); i++)
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
