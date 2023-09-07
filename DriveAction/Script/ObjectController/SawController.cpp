#include "SawController.h"
#include "DrawModel.h"
#include "Saw.h"
#include "Utility.h"
/// <summary>
/// �v���C���[���͂�����΂��ۋ�
/// </summary>
SawController::SawController()
    :AddableObjectController(ObjectInit::saw)
{
    drawModel = new DrawModel(controllObjKind);
}
/// <summary>
/// �ۋ���ǉ�
/// </summary>
/// <param name="editData">�ǉ�����ʒu�Ȃǂ̏��</param>
void SawController::AddObject(PlacementData editData)
{
    actorList.push_back(new Saw(editData));
}
/// <summary>
/// ��]������@�j�󂳂ꂽ��j��
/// </summary>
void SawController::Update()
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
