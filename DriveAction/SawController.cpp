#include "SawController.h"
#include "ModelViewer.h"
#include "Saw.h"
/// <summary>
/// �v���C���[���͂�����΂��ۋ�
/// </summary>
SawController::SawController()
    :ActorController(ObjectInit::saw)
{
    viewer = new ModelViewer(controllObjKind);
}
/// <summary>
/// �ۋ���ǉ�
/// </summary>
/// <param name="editData">�ǉ�����ʒu�Ȃǂ̏��</param>
void SawController::AddObject(std::vector<EditArrangementData> editData)
{
    if (!editData.empty())
    {
        for (int i = 0; i < editData.size(); i++)
        {
            //������ނȂ�ǉ�
            if (editData[i].objKind == controllObjKind)
            {
                actorList.push_back(new Saw(editData[i]));
            }
        }
    }
}