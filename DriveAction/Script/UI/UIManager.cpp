#include "UIManager.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "DxLib.h"
//�S�Ă�UI�̃p�X
std::vector<std::string> UIManager::uiPathVec;
//UI�摜�̏��
std::unordered_map<int, UIData> UIManager::loadUIDataMap;
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
/// �eUI�Ɏg���Ă���摜������
/// </summary>
UIManager::~UIManager()
{
    for (auto itr = loadUIDataMap.begin(); itr != loadUIDataMap.end(); itr++)
    {
        //�����ǂݍ��݉摜������
        auto graphs = ((*itr).second).dataHandle;
        for (int i = 0; i < SAFE_GET_SIZE(graphs); i++)
        {
            DeleteGraph(graphs[i]);
        }
    }
    loadUIDataMap.clear();
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
/// UI������
/// </summary>
/// <param name="uiKind">����������UI</param>
/// <returns></returns>
UIData UIManager::CreateUIData(int kindNum)
{
    UIData data;
    if (loadUIDataMap.contains(kindNum))//���łɃ_�E�����[�h���Ă���Ȃ�
    {
        data = loadUIDataMap[kindNum];
    }
    else
    {
        //�f�[�^�ǂݎ��
        CSVFileLoader* initDataFile = new CSVFileLoader(uiPathVec[kindNum]);
        std::vector<std::string> dataVec = initDataFile->GeFileStringData();
        //�ʒu�Ƃ����Ƃ���������ǂݎ��
        data.x = SAFE_STR_TO_I(dataVec[drawX]);
        data.y = SAFE_STR_TO_I(dataVec[drawY]);
        //��������
        int divXNum = SAFE_STR_TO_I(dataVec[xNum]);
        //�c������
        int divYNum = SAFE_STR_TO_I(dataVec[yNum]);
        data.width = SAFE_STR_TO_I(dataVec[width]) / divXNum;
        data.height = SAFE_STR_TO_I(dataVec[height]) / divYNum;
        //�摜�𕪊��ǂݍ���
        int graphArray[1000];
        LoadDivGraph(dataVec[graphPass].c_str(), divXNum * divYNum, divXNum, divYNum, data.width, data.height, graphArray);
        for (int i = 0; i < divXNum + divYNum - 1; i++)
        {
            data.dataHandle.push_back(graphArray[i]);
        }
        //�傫���ƃR�}���葬�x
        data.size = SAFE_STR_TO_F(dataVec[UISize]);
        data.frameSpeed = SAFE_STR_TO_F(dataVec[frameSpeed]);
        //�ă_�E�����[�h���鎞�p�ɕۑ�����
        loadUIDataMap.insert(std::make_pair(kindNum, data));
        //�������f�[�^������
        SAFE_DELETE(initDataFile);
    }
    return data;
}