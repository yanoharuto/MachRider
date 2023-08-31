#include "AddableObjectController.h"

AddableObjectController::AddableObjectController(ObjectInit::InitObjKind kind)
    :ActorController(kind)
{
}
/// <summary>
/// ���X�g�ɑΏۂ̃I�u�W�F�N�g��Z�߂Ēǉ�
/// </summary>
/// <param name="placeDataVec">�z�u�ʒu���X�g</param>
void AddableObjectController::OnAddObject(std::vector<PlacementData> placeDataVec)
{
    if (!placeDataVec.empty())
    {
        for (int i = 0; i < placeDataVec.size(); i++)
        {
            //������ނȂ�ǉ�
            if (placeDataVec[i].objKind == controllObjKind)
            {
                AddObject(placeDataVec[i]);
            }
        }
    }
}