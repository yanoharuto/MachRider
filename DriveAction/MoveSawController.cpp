#include "MoveSawController.h"
#include "MoveSaw.h"
#include "ModelViewer.h"
#include "Utility.h"
/// <summary>
/// �ړ������]�̂�����̊Ǘ���
/// </summary>
MoveSawController::MoveSawController()
    :ActorController(ObjectInit::moveSaw)
{
    viewer = new ModelViewer(controllObjKind);
}
/// <summary>
/// �ړ������]�̂�����̒ǉ�
/// </summary>
/// <param name="editData"></param>
void MoveSawController::AddObject(std::vector<EditArrangementData> editData)
{
    if (!editData.empty())
    {
        for (int i = 0; i < editData.size(); i++)
        {
            //������ނȂ�ǉ�
            if (editData[i].objKind == controllObjKind)
            {
                actorList.push_back(new MoveSaw(editData[i]));
            }
        }
    }
}

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
