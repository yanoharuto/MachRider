#include "MoveSawController.h"
#include "MoveSaw.h"
#include "ModelViewer.h"
#include "Utility.h"
/// <summary>
/// ˆÚ“®‚·‚é‰ñ“]‚Ì‚±‚¬‚è‚ÌŠÇ—Ò
/// </summary>
MoveSawController::MoveSawController()
    :ActorController(ObjectInit::moveSaw)
{
    viewer = new ModelViewer(controllObjKind);
}
/// <summary>
/// ˆÚ“®‚·‚é‰ñ“]‚Ì‚±‚¬‚è‚Ì’Ç‰Á
/// </summary>
/// <param name="editData"></param>
void MoveSawController::AddObject(std::vector<EditArrangementData> editData)
{
    if (!editData.empty())
    {
        for (int i = 0; i < editData.size(); i++)
        {
            //“¯‚¶í—Ş‚È‚ç’Ç‰Á
            if (editData[i].objKind == controllObjKind)
            {
                actorList.push_back(new MoveSaw(editData[i]));
            }
        }
    }
}

void MoveSawController::Update()
{
    //”jŠü‚·‚éƒŠƒXƒg
    std::list<std::list<Actor*>::iterator> brokenList;
    //XV
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        (*ite)->Update();
        if ((*ite)->GetObjectState() == Object::dead)//”š”jI—¹Œã‚Í”jŠü
        {
            brokenList.push_back(ite);
            SAFE_DELETE(*ite);
        }
    }
    //actorList‚©‚çíœ
    for (auto ite = brokenList.begin(); ite != brokenList.end(); ite++)
    {
        actorList.erase(*(ite));
    }
}
