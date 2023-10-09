#pragma once
#include <string>
#include <unordered_map>

class AssetManager abstract
{
public:
    enum class AssetList;
    AssetManager() {};
    virtual ~AssetManager() {};

    enum class AssetList
    {
        camera,
        effect,
        object,
        ui,
        sound,
        stageData,
        objectAddData
    };
protected:
    /// <summary>
    /// �������Ŏg���t�@�C���̃p�X������
    /// </summary>
    /// <param name="fileKind">�~�����t�@�C���̎��</param>
    /// <returns></returns>
   static std::string GetInitFilePass(AssetList fileKind);
private:
    //�������t�@�C���̖��O
    static std::string const initFileNames[];
    //csv�t�@�C���܂ł̃p�X
    static std::string const initCSVFilePass;
    //json�t�@�C���܂ł̃p�X
    static std::string const initJSONFilePass;
};