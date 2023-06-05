#include "MeshCollider.h"
#include "ConflictManager.h"
MeshCollider::MeshCollider(int setModelHandle, Object::ObjectTag setTag)
{
    modelHandle = setModelHandle;
    tag = setTag;
    ConflictManager::AddConflictObjInfo(this);
}

MeshCollider::~MeshCollider()
{
}
/// <summary>
/// �����蔻���Ԃ�
/// </summary>
/// <param name=""></param>
/// <returns></returns>
ConflictExamineResultInfo MeshCollider::HitCheck(HitCheckExamineObjectInfo examinInfo)
{
    return GetSphereConflictModelInfo(examinInfo);
}


/// <summary>
/// MV1CollCheck_Sphere���g���ă��f���n���h�����˒��������ׂ��
/// </summary>
/// <param name="modelHandle">���ׂ郂�f��</param>
/// <param name="examineInfo">���ׂ邽�߂ɕK�v�ȏ��</param>
/// <returns>�Ԃ������ʒu��Ԃ���B�Ԃ����ĂȂ��Ȃ�HitFlag��false</returns>
ConflictExamineResultInfo MeshCollider::GetSphereConflictModelInfo(HitCheckExamineObjectInfo examineInfo) 
{
    DxLib::MV1_COLL_RESULT_POLY_DIM polyDimInfo = MV1CollCheck_Sphere(modelHandle, -1, examineInfo.pos, examineInfo.radius);
    //�͂������̃|�W�V����
    VECTOR bounceVec = {};
    //�͂������̃|�W�V����
    VECTOR nowPos = examineInfo.pos;
    bool hitFlag = false;
    //�����������ǂ���
    ConflictExamineResultInfo resultInfo;
    resultInfo.tag = tag;
    //model�ɂԂ����Ă��邩
    if (polyDimInfo.HitNum != 0)
    {
        hitFlag = true;
        //������Ȃ��ʒu�Ɉړ�����܂ŏ���
        while (hitFlag && fabsf(VSize(examineInfo.velocity)) > 0)
        {
            //�|���S���̐�����������΂�
            for (int i = 0; i < polyDimInfo.HitNum; i++)
            {
                MV1_COLL_RESULT_POLY polyInfo = polyDimInfo.Dim[i];//�|���S���̒��_���
                float a = -VDot(VNorm(examineInfo.velocity), polyInfo.Normal);//�@������͂������傫�����o��
                //�͂������x�N�g��
                bounceVec = VSub(examineInfo.velocity, VScale(polyInfo.Normal, 2 * a));
                //�͂������̃|�W�V����
                nowPos = VAdd(nowPos, bounceVec);
            }
            MV1CollResultPolyDimTerminate(polyDimInfo);//��x�|���S����������
            //������x�������Ă��镔�������邩���ׂ�
            polyDimInfo = MV1CollCheck_Sphere(modelHandle, -1, nowPos, examineInfo.radius);
            //�����������ĂȂ�������I��
            hitFlag = polyDimInfo.HitNum != 0;
        }
        //�ŏI�I��BouncePower��������΂�
        resultInfo.hit = HitSituation::Enter;
        resultInfo.bounceVec = VScale(VNorm(VSub(examineInfo.pos, nowPos)),20);
        resultInfo.pos = nowPos;
        //�㏈��
        MV1CollResultPolyDimTerminate(polyDimInfo);
        return  resultInfo;
    }
    //�������ĂȂ��ꍇ
    resultInfo.hit = HitSituation::NotHit;
    MV1CollResultPolyDimTerminate(polyDimInfo);
    return resultInfo;
}
/// <summary>
/// mesh�Ȃ̂ňʒu�Ƃ��͋�����Ȃ�
/// </summary>
/// <returns></returns>
HitCheckExamineObjectInfo MeshCollider::GetHitExamineCheckInfo()
{
    return { {},{},0};
}
/// <summary>
/// ���������ꍇ�̔���
/// </summary>
/// <param name="resultInfo"></param>
void MeshCollider::ConflictProccess(std::list<ConflictExamineResultInfo> resultInfo)
{
}