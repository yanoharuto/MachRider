#include "EnemyGenerator.h"
#include "Utility.h"
#include "InitActor.h"
#include "InitObjKind.h"
#include "Utility.h"
#include "FirstPositionGetter.h"
#include "ActorController.h"
/// <summary>
/// �G�@�ʒu�ɂ��Ă̏���������
/// </summary>
EnemyGenerator::EnemyGenerator()
{
    editDataVec = FirstPositionGetter::GetInitData(Object::damageObject);
}
/// <summary>
/// �G�l�~�[�𐶐�
/// </summary>
/// <param name="collectNum">���v���C���[�͉��ڂ̎��W�A�C�e�����������</param>
void EnemyGenerator::GenerateEnemys(int collectNum, ActorController* const addObjController)
{
    addObjController->AddObject(GetNowEnemyEditData(collectNum));
}
/// <summary>
/// �G�l�~�[�̔z�u��������
/// </summary>
/// <param name="kind">�ǂ̎�ނ�</param>
/// <param name="collectNum">���Ԗڂ̎��W�A�C�e���̎���</param>
/// <returns>kind�̃G�l�~�[�̔z�u���</returns>
std::vector<EditArrangementData> EnemyGenerator::GetNowEnemyEditData(int collectNum)
{
    std::vector<EditArrangementData> editData;
    for (int i = 0; i < editDataVec.size(); i++)
    {
        ObjectInit::InitObjKind dataKind = static_cast<ObjectInit::InitObjKind>(editDataVec[i].objKind);
        //�v���C���[�����W�A�C�e��������Ă����炻�̃^�C�~���O�œG�𑝂₷
        if (editDataVec[i].missionNum == collectNum)
        {
            editData.push_back(editDataVec[i]);
        }
    }
    return editData;
}