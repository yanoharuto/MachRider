#include "StageDataPass.h"
#include "Utility.h"
#include "ListUtility.h"
#include "CSVFileLoader.h"

std::string StageDataPass::fileAddres = "-1";
StageDataPass::StageDataPass()
{
    auto fileLoader = new CSVFileLoader(allStageAddresFile);//�S�X�e�[�W�̃f�[�^���X�g��ǂݎ��
    dataLoader = fileLoader->GetLoadStringData();
    SAFE_DELETE(fileLoader);
}
StageDataPass::~StageDataPass()
{
}
/// <summary>
/// �X�e�[�W�̖��O
/// </summary>
/// <returns></returns>
std::string StageDataPass::GetLoadeStageName()const
{
    if (fileAddres == "-1")
    {
        fileAddres = dataLoader[0];//�Ƃ肠�����擪��n��
    }
    return fileAddres;
}
/// <summary>
/// �����ɂ��Ă̕�������o��
/// </summary>
/// <param name="dataKind"></param>
/// <returns></returns>
std::string StageDataPass::LoadStageData(StageData dataKind)const
{
    auto fileLoader = new CSVFileLoader(StageDataPass::GetLoadeStageName());
    auto setStageInitDataVec = fileLoader->GetLoadStringData();
    SAFE_DELETE(fileLoader);
    return setStageInitDataVec[dataKind];
}