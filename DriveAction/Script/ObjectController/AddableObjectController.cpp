#include "AddableObjectController.h"

AddableObjectController::AddableObjectController(ObjectInit::InitObjKind kind)
    :ActorController(kind)
{
}
/// <summary>
/// リストに対象のオブジェクトを纏めて追加
/// </summary>
/// <param name="placeDataVec">配置位置リスト</param>
void AddableObjectController::OnAddObject(std::vector<PlacementData> placeDataVec)
{
    if (!placeDataVec.empty())
    {
        for (int i = 0; i < placeDataVec.size(); i++)
        {
            //同じ種類なら追加
            if (placeDataVec[i].objKind == controllObjKind)
            {
                AddObject(placeDataVec[i]);
            }
        }
    }
}