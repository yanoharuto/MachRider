#include <fstream>
#include <iostream>
#include "JsonFileLoader.h"
#include "istreamwrapper.h"
#include "schema.h"
#include "stringbuffer.h"
/// <summary>
/// Json�`���̃t�@�C�����J��
/// </summary>
/// <param name="filePass">�J�������t�@�C��</param>
/// <param name="schemaFilePass">�J���t�@�C����Schema</param>
JsonFileLoader::JsonFileLoader(std::string filePass, std::string schemaFilePass)
{
    //�X�L�[�}���珑�����𒲂ׂ�
    std::ifstream schema_ifs(schemaFilePass);
    rapidjson::IStreamWrapper schema_isw(schema_ifs);
    rapidjson::Document schema_doc;
    schema_doc.ParseStream(schema_isw);
    //�ǂݎ�肽���f�[�^�t�@�C�����J��
    std::ifstream ifs(filePass);
    rapidjson::IStreamWrapper isw(ifs);
    loadDoc.ParseStream(isw);
    //�X�L�[�}�ʂ�̏����������ׂ�
    rapidjson::SchemaDocument schema(schema_doc);
    rapidjson::SchemaValidator validator(schema);
    isAccept = loadDoc.Accept(validator);
    //���s����
    if (!isAccept) {
        rapidjson::StringBuffer sb;
        validator.GetInvalidDocumentPointer().StringifyUriFragment(sb);//���\�[�X�̏ꏊ��SB�ɓn��
        std::cout << "Invalid schema:" << sb.GetString() << std::endl;
        std::cout << "Invalid keyword:" << validator.GetInvalidSchemaKeyword() << std::endl;
    }
}
/// <summary>
/// Schema�ƊJ�������t�@�C�����K�����Ă���Ȃ�
/// </summary>
/// <returns>�K�������Ȃ�True</returns>
bool JsonFileLoader::IsAccept() const
{
    return isAccept;
}
/// <summary>
/// float�^
/// </summary>
/// <param name="dataName">�ǂݎ�肽���f�[�^</param>
/// <returns>��肽���f�[�^</returns>
float JsonFileLoader::GetLoadFloat(std::string dataName)const
{
    return loadDoc[dataName.c_str()].GetFloat();
}
/// <summary>
/// �K�v�ȃf�[�^�������ǂݎ��
/// </summary>
/// <param name="dataName">�ǂݎ�肽���f�[�^�̖��O</param>
/// <returns>��肽���f�[�^</returns>
std::string JsonFileLoader::GetLoadString(std::string dataName) const
{
    return loadDoc[dataName.c_str()].GetString();
}
