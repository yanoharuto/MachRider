#include <fstream>
#include <sstream>
#include "CSVFileLoader.h"
#include "Utility.h"
using namespace std;
/// <summary>
/// CSV�t�@�C����ǂݍ���
/// </summary>
/// <param name="filePass">�ǂݍ��ރt�@�C���̃p�X</param>
CSVFileLoader::CSVFileLoader(std::string filePass)
{
    //�t�@�C�����J����
    lineCount = 0;
    ifstream ifs(filePass.c_str());
    //1�s���ǂݍ���
    string line;
    while (getline(ifs, line)) 
    {
        lineCount++;
        Split(line, ',');//,�܂œǂݍ���
    }
    //����
    ifs.close();
}
/// <summary>
/// CSV�t�@�C����ǂݍ���
/// </summary>
/// <returns></returns>
std::vector<std::string> CSVFileLoader::GetLoadStringData()const
{
    return loadData;
}
/// <summary>
/// CSV�t�@�C����ǂݍ���
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
/// �ǂݍ��񂾃t�@�C���̍s
/// </summary>
/// <returns></returns>
int CSVFileLoader::GetLineCount()const
{
    return lineCount;
}
/// <summary>
/// �ǂݍ��񂾃t�@�C���̊e�s�̃f�[�^�𒊏o
/// </summary>
/// <param name="input">�e�s�̃f�[�^</param>
/// <param name="delimiter">�~�߂镶��</param>
void CSVFileLoader::Split(std::string& input, char delimiter)
{
    istringstream stream(input);
    string field;
    //�������܂ňڂ��Ă���
    while (getline(stream, field, delimiter)) 
    {
        loadData.push_back(field);
    }
}
