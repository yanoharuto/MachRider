#include "UIManager.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "DxLib.h"
std::vector<std::string> UIManager::initDataVec;
std::unordered_map<int, UIData> UIManager::loadUIDataMap;
UIManager::UIManager()
{
    CSVFileLoader* initDataFile = new CSVFileLoader(initUIDataPassFile);
    initDataVec = initDataFile->GetLoadStringData();
    SAFE_DELETE(initDataFile);
}

UIManager::~UIManager()
{
    for (auto itr = loadUIDataMap.begin(); itr != loadUIDataMap.end(); itr++)
    {
        auto graphs = ((*itr).second).dataHandle;
        for (int i = 0; i < graphs.size(); i++)
        {
            DeleteGraph(graphs[i]);
        }
    }
}

UIData UIManager::CreateUIData(UIKind uiKind)
{
    return CreateUIData(static_cast<int>(uiKind));
}

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
        CSVFileLoader* initDataFile = new CSVFileLoader(initDataVec[kindNum]);
        std::vector<std::string> dataVec = initDataFile->GetLoadStringData();
        //�ʒu�Ƃ����Ƃ���������ǂݎ��
        data.x = atoi(dataVec[drawX].c_str());
        data.y = atoi(dataVec[drawY].c_str());
        //��������
        int divXNum = atoi(dataVec[xNum].c_str());
        //�c������
        int divYNum = atoi(dataVec[yNum].c_str());
        data.width = atoi(dataVec[width].c_str()) / divXNum;
        data.height = atoi(dataVec[height].c_str()) / divYNum;
        //�摜�𕪊��ǂݍ���
        int graphArray[1000];
        LoadDivGraph(dataVec[graphPass].c_str(), divXNum * divYNum, divXNum, divYNum, data.width, data.height, graphArray);
        for (int i = 0; i < divXNum + divYNum - 1; i++)
        {
            data.dataHandle.push_back(graphArray[i]);
        }
        //�傫���ƃR�}���葬�x
        data.size = static_cast<float>(atof(dataVec[UISize].c_str()));
        data.frameSpeed = static_cast<float>(atof(dataVec[frameSpeed].c_str()));
        //�ă_�E�����[�h���鎞�p�ɕۑ�����
        loadUIDataMap.insert(std::make_pair(kindNum, data));
        //�������f�[�^������
        SAFE_DELETE(initDataFile);
    }
    return data;
}