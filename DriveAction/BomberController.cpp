#include "BomberController.h"
#include "Bomber.h"
#include "ObjectObserver.h"
#include "DrawModel.h"
#include "Utility.h"
/// <summary>
/// ���e����W
/// </summary>
/// <param name="sub"></param>
BomberController::BomberController()
    :DamageObjectController(ObjectInit::bomber)
{
    drawModel = new DrawModel(ObjectInit::bomber);
}
/// <summary>
/// ���e���X�V�ł���悤�ɂ���
/// </summary>
/// <param name="sub">���e�𓊉������I�u�W�F�N�g</param>
void BomberController::AddObject(std::unique_ptr<ObjectObserver> sub)
{
    actorList.push_back(new Bomber(std::move(sub)));
}
/// <summary>
/// ���e�𗎉�������
/// </summary>
void BomberController::Update()
{
    //�j�����郊�X�g
    std::list<std::list<Actor*>::iterator> brokenList;
    //�X�V
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        (*ite)->Update();
        if ((*ite)->GetObjectState() == Object::dead)//���j�I����͔j��
        {
            brokenList.push_back(ite);
            SAFE_DELETE(*ite);
        }
    }
    //actorList����폜
    for (auto ite = brokenList.begin(); ite != brokenList.end(); ite++)
    {
        actorList.erase(*(ite));
    }
}