#include "MoveSawController.h"
#include "MoveSaw.h"
#include "ModelViewer.h"
MoveSawController::MoveSawController()
    :ActorController(ObjectInit::moveSaw)
{
    viewer = new ModelViewer(controllObjKind);
}

void MoveSawController::AddObject(std::vector<EditArrangementData> editData)
{
    if (!editData.empty())
    {
        for (int i = 0; i < editData.size(); i++)
        {
            //同じ種類なら追加
            if (editData[i].objKind == controllObjKind)
            {
                actorList.push_back(new MoveSaw(editData[i]));
            }
        }
    }
}
