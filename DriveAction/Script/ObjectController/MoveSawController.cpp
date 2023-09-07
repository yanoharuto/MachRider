#include "MoveSawController.h"
#include "MoveSaw.h"
#include "DrawModel.h"
#include "Utility.h"
/// <summary>
/// �ړ������]�̂�����̊Ǘ���
/// </summary>
MoveSawController::MoveSawController()
    :AddableObjectController(ObjectInit::moveSaw)
{
    drawModel = new DrawModel(controllObjKind);
}
/// <summary>
/// ��]�̂�������ړ�������@�j�󂳂ꂽ��j��
/// </summary>
void MoveSawController::Update()
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
/// <summary>
/// �ړ������]�̂�����̒ǉ�
/// </summary>
/// <param name="editData">�ʒu�����</param>
void MoveSawController::AddObject(PlacementData editData)
{
    actorList.push_back(new MoveSaw(editData));
}