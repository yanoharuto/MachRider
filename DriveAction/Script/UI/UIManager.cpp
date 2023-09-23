#include "UIManager.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "DxLib.h"
//�S�Ă�UI�̃p�X
std::vector<std::string> UIManager::uiPathVec;
/// <summary>
/// �S�Ă�UI�摜�̃p�X��uiPathVec�ɓn��
/// </summary>
UIManager::UIManager()
{
    CSVFileLoader* initDataFile = new CSVFileLoader(initUIDataPassFile);
    uiPathVec = initDataFile->GeFileStringData();
    SAFE_DELETE(initDataFile);
}
/// <summary>
/// UI������
/// </summary>
/// <param name="uiKind">����������UI�̎��</param>
/// <returns>UI�̕`��ɕK�v�ȏ���Ԃ�</returns>
UIData UIManager::CreateUIData(UIKind uiKind)
{
    return CreateUIData(static_cast<int>(uiKind));
}
/// <summary>
/// ������UI�̉摜���폜����
/// </summary>
/// <param name="ui">��������UI�摜</param>
void UIManager::DeleteUIGraph(UIData* ui)
{
    int size = ui->dataHandle.size();
    for (int i = 0; i < size; i++)
    {
        DeleteGraph(ui->dataHandle[i]);
    }
}
/// <summary>
/// UI������
/// </summary>
/// <param name="uiKind">����������UI</param>
/// <returns></returns>
UIData UIManager::CreateUIData(int kindNum)
{
    UIData data;

    using enum InitUIData;
    //�f�[�^�ǂݎ��
    CSVFileLoader* initDataFile = new CSVFileLoader(uiPathVec[kindNum]);
    std::vector<std::string> dataVec = initDataFile->GeFileStringData();
    //�ʒu�Ƃ����Ƃ���������ǂݎ��
    data.x = STR_TO_I(dataVec[static_cast<int>(drawX)]);
    data.y = STR_TO_I(dataVec[static_cast<int>(drawY)]);
    //��������
    int divXNum = STR_TO_I(dataVec[static_cast<int>(xNum)]);
    //�c������
    int divYNum = STR_TO_I(dataVec[static_cast<int>(yNum)]);
    data.width = STR_TO_I(dataVec[static_cast<int>(width)]) / divXNum;
    data.height = STR_TO_I(dataVec[static_cast<int>(height)]) / divYNum;
    //�摜�𕪊��ǂݍ���
    int graphArray[1000];
    LoadDivGraph(dataVec[static_cast<int>(graphPass)].c_str(), divXNum * divYNum, divXNum, divYNum, data.width, data.height, graphArray);
    for (int i = 0; i < divXNum + divYNum - 1; i++)
    {
        data.dataHandle.push_back(graphArray[i]);
    }
    //�傫���ƃR�}���葬�x
    data.size = STR_TO_F(dataVec[static_cast<int>(UISize)]);
    data.frameSpeed = STR_TO_F(dataVec[static_cast<int>(frameSpeed)]);
    //�������f�[�^������
    SAFE_DELETE(initDataFile);

    return data;
}