#include "MoveSawController.h"
#include "MoveSaw.h"
#include "DrawModel.h"
#include "Utility.h"
/// <summary>
/// ˆÚ“®‚·‚é‰ñ“]‚Ì‚±‚¬‚è‚ÌŠÇ—Ò
/// </summary>
MoveSawController::MoveSawController()
    :AddableObjectController(ObjectInit::moveSaw)
{
    drawModel = new DrawModel(controllObjKind);
}
/// <summary>
/// ‰ñ“]‚Ì‚±‚¬‚è‚ğˆÚ“®‚³‚¹‚é@”j‰ó‚³‚ê‚½‚ç”jŠü
/// </summary>
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
/// <summary>
/// ˆÚ“®‚·‚é‰ñ“]‚Ì‚±‚¬‚è‚Ì’Ç‰Á
/// </summary>
/// <param name="editData">ˆÊ’u‚âŒü‚«</param>
void MoveSawController::AddObject(PlacementData editData)
{
    actorList.push_back(new MoveSaw(editData));
}