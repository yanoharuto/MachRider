#pragma once
#include <string>
#include <fstream>
#include "DxLib.h"
/// <summary>
/// ベクターのデータをメモ帳に記録する
/// </summary>
class VectorDataCreator
{
public:
    VectorDataCreator();
    /// <summary>
    /// 開くメモ帳のファイルネーム
    /// </summary>
    /// <param name="setFileName"></param>
    VectorDataCreator(std::string setFileName);
    ~VectorDataCreator();
    /// <summary>
    /// 追加で書き込む
    /// </summary>
    /// <param name="vec"></param>
    void WriteVECTOR(VECTOR vec);
private:
    //書き込むファイル
    std::ofstream writing_file;
    //書き込むファイルの名前
    std::string fileName;
};

