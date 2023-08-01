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
            //“¯‚¶Ží—Þ‚È‚ç’Ç‰Á
            if (editData[i].objKind == controllObjKind)
            {
                actorList.push_back(new MoveSaw(editData[i]));
            }
        }
    }
}
