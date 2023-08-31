#pragma once
#include <vector>
#include <string>

/// <summary>
/// CSV�t�@�C����ǂݍ���ŕ�����R���e�i�ŕԂ�
/// </summary>
class CSVFileLoader
{
public:
    /// <summary>
    /// CSV�t�@�C����ǂݍ���
    /// </summary>
    /// <param name="filePass">�ǂݍ��ރt�@�C���̃p�X</param>
    CSVFileLoader(std::string filePass);
    /// <summary>
    /// ���ɂȂ�
    /// </summary>
    ~CSVFileLoader() {};
    /// <summary>
    /// CSV�t�@�C����ǂݍ���
    /// </summary>
    /// <returns></returns>
    std::vector <std::string> GetLoadStringData()const;
    /// <summary>
    /// CSV�t�@�C����ǂݍ���
    /// </summary>
    /// <returns></returns>
    std::vector <const char*> GetLoadCharData()const;
    /// <summary>
    /// �ǂݍ��񂾃t�@�C���̍s
    /// </summary>
    /// <returns></returns>
    int GetLineCount()const;
private:
    /// <summary>
    /// �ǂݍ��񂾃t�@�C���̊e�s�̃f�[�^�𒊏o
    /// </summary>
    /// <param name="input">�e�s�̃f�[�^</param>
    /// <param name="delimiter">�~�߂镶��</param>
    void Split(std::string& input, char delimiter);
    //�ǂݍ��񂾃t�@�C���̃f�[�^
    std::vector <std::string> loadData;
    //�ǂݍ��񂾃t�@�C���̍s
    int lineCount;
};

