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
        //�ǉ����̒u���Ă���ꏊ
        addDataPass = 17
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
    /// ����������̂ɕK�v�ȃf�[�^�̃p�X
    /// </summary>
    struct InitDataPass
    {
        //�`�惂�f���̃t�@�C���̃p�X
        std::string modelPass;
        //�ǉ����̃t�@�C���̃p�X
        std::string addData;
        /// <summary>
        /// �������璊�o
        /// </summary>
        /// <param name="pathStr"></param>
        void GetExtractParamator(std::vector<std::string> pathStr)
        {
            modelPass = pathStr[InitObjParamator::assetPass];
            addData = pathStr[InitObjParamator::addDataPass];
        }
        /// <summary>
        /// �������璊�o
        /// </summary>
        /// <param name="pathStr"></param>
        void GetExtractParamator(std::vector <const char*> pathStr)
        {
            modelPass = pathStr[InitObjParamator::assetPass];
            addData = pathStr[InitObjParamator::addDataPass];
        }
    };
}
class AssetManager;
using namespace ObjectInit;
/// <summary>
/// actor�̏�����������
/// </summary>
class InitActor final
{
public:
    /// <summary>
    /// �S�Ă�actor�̏����������邽�߂̃p�X���������t�@�C����ǂݍ���
    /// </summary>
    InitActor();
    /// <summary>
    /// �`�惂�f���Ǘ��S���̉��
    /// </summary>
    ~InitActor();
    /// <summary>
    /// �������ɕK�v�ȏ�������
    /// </summary>
    /// <param name="obj">�������������I�u�W�F�N�g</param>
    /// <returns>�������ɕK�v�ȏ��</returns>
    static ActorParameter GetActorParamator(InitObjKind obj);
    /// <summary>
    /// �����̎�ނ̕`�惂�f���n���h����n��
    /// </summary>
    /// <param name="kind">���o�������`�惂�f��</param>
    /// <returns>�`�惂�f���n���h��</returns>
    static int GetModelHandle (InitObjKind obj);
    /// <summary>
    /// �ǉ����̓������t�@�C���܂ł̃p�X��n��
    /// </summary>
    /// <param name="obj">�ǉ���񂪗~�����I�u�W�F�N�g</param>
    /// <returns>�ǉ����̓������t�@�C���܂ł̃p�X</returns>
    static std::string GetAddDataPass (InitObjKind obj);

private:
    /// <summary>
    /// �������ɕK�v�ȐF�X�ȃp�X������
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    static InitDataPass GetActorInitPassData(InitObjKind obj);
    /// <summary>
    /// �������������p�����[�^�𕶎���ŏ���
    /// </summary>
    /// <param name="obj">�������������I�u�W�F�N�g</param>
    /// <returns>�������������p�����[�^�̕�����</returns>
    static std::vector<std::string> GetActorParametorStrVec(InitObjKind obj);
    //initActorFileName�̐�̃t�@�C�����珊�������f�[�^���܂Ƃ߂�Vector
    static std::vector<std::string> objectInitDataPassVec;
    //����������p�X��Z�߂Ă���t�@�C���̖��O
    static std::string initActorFileName; 
    //�`�惂�f���n���h��������
    static AssetManager* assetManager;
};