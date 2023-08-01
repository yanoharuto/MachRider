#include "SawController.h"
#include "ModelViewer.h"
#include "Saw.h"
/// <summary>
/// プレイヤーをはじき飛ばす丸鋸
/// </summary>
SawController::SawController()
    :ActorController(ObjectInit::saw)
{
    viewer = new ModelViewer(controllObjKind);
}
/// <summary>
/// 丸鋸を追加
/// </summary>
/// <param name="editData">追加する位置などの情報</param>
void SawController::AddObject(std::vector<EditArrangementData> editData)
{
    if (!editData.empty())
    {
        for (int i = 0; i < editData.size(); i++)
        {
            //同じ種類なら追加
            if (editData[i].objKind == controllObjKind)
            {
                actorList.push_back(new Saw(editData[i]));
            }
        }
    }
}