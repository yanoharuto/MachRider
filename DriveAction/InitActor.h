#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "DxLib.h"
#include "InitObjKind.h"

namespace ObjectInit
{
    /// <summary>
    ///����������v�f
    /// </summary>
    enum InitObjParamator
    {
        //model�̑��΃p�X
        assetPass = 2,
        //�傫��
        modelSize = 5,
        //�ŏ��̃|�W�V����
        firstPosY = 8,
        //model�̓����蔼�a
        collRadius = 11,
        //���˕Ԃ�̑傫��
        bouncePower = 14,
        //�}�b�v�̏����ʒu�Ŏg���Ă���ԍ�
        mapTiledNum = 17,
        //�ǉ����̒u���Ă���ꏊ
        addDataPass = 23
    };
    /// <summary>
    /// �Q�[���L�����̏����ʒu�Ƃ������蔻��̑傫���Ƃ�
    /// </summary>
    struct ActorParameter
    {
        //�������x
        float firstPosY;
        //�����蔻��̑傫��
        float setRadius;
        //���˕Ԃ��
        float setBouncePow;
    };
    /// <summary>
    /// ����������̂ɕK�v�ȃf�[�^��Z��
    /// </summary>
    struct InitDataPass
    {
        //model��Pass
        std::string modelPass;
        //�ǉ�����Pass
        std::string addData;
        /// <summary>
        /// �������璊�o
        /// </summary>
        /// <param name="paramatorString"></param>
        void GetExtractParamator(std::vector<std::string> paramatorString)
        {
            modelPass = paramatorString[InitObjParamator::assetPass];
            addData = paramatorString[InitObjParamator::addDataPass];
        }
        /// <summary>
        /// �������璊�o
        /// </summary>
        /// <param name="paramatorString"></param>
        void GetExtractParamator(std::vector <const char*> paramatorString)
        {
            modelPass = paramatorString[InitObjParamator::assetPass];
            addData = paramatorString[InitObjParamator::addDataPass];
        }
    };
}
using namespace ObjectInit;
/// <summary>
/// actor�̏�����������
/// </summary>
class InitActor
{
public:
    InitActor();
    ~InitActor();
    /// <summary>
    /// �������ɕK�v�ȏ�������
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    static ActorParameter GetActorParamator(InitObjKind obj);
    /// <summary>
    /// �����̎�ނ̕`�惂�f����n��
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    static int GetModelHandle (InitObjKind obj);
    /// <summary>
    /// �ǉ���񕶎���x�N�^�[��n��
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    static std::string GetAddDataPass (InitObjKind obj);
    /// <summary>
    /// �����ʒu�̔ԍ���Ԃ�
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    static int GetActorTileNum(InitObjKind obj);
private:
    /// <summary>
    /// �������ɕK�v�ȐF�X�ȃp�X������
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    static InitDataPass GetActorInitPassData(InitObjKind obj);
    /// <summary>
    /// �����������������
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    static std::vector<std::string> GetActorParametorString(InitObjKind obj);
    //initActorFileName�̐�̃t�@�C�����珊�������f�[�^���܂Ƃ߂�Vector
    static std::vector<std::string> objectInitDataPassVec;
    //����������p�X��Z�߂Ă���t�@�C���̖��O
    static std::string initActorFileName; 
};