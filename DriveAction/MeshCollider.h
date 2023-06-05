#include "ConflictProccesor.h"
#include "Object.h"
/// <summary>
/// ステージの障害物とかの当たり判定
/// </summary>
class MeshCollider final :public ConflictProccesor
{
public:
    /// <summary>
    /// モデルハンドルから当たり判定を作る 
    /// </summary>
    MeshCollider(int setModelHandle, Object::ObjectTag setTag);
    ~MeshCollider()override;
    /// <summary>
    /// 当たり判定を返す
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    ConflictExamineResultInfo HitCheck(HitCheckExamineObjectInfo)override;
    /// <summary>
    /// 球との当たり判定
    /// </summary>
    /// <param name="examineInfo"></param>
    /// <returns></returns>
    ConflictExamineResultInfo GetSphereConflictModelInfo(HitCheckExamineObjectInfo examineInfo);
    /// <summary>
    /// meshなので位置とかは教えれない
    /// </summary>
    /// <returns></returns>
    HitCheckExamineObjectInfo GetHitExamineCheckInfo()override;
    /// <summary>
    /// 当たった場合の反応
    /// </summary>
    /// <param name="resultInfo"></param>
    void ConflictProccess(std::list<ConflictExamineResultInfo> resultInfo)override;
private:
    int modelHandle = -1;
    Object::ObjectTag tag = Object::ObjectTag::stage;
    float bouncePower;
};