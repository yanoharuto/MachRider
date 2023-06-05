#pragma once
#include <vector>
#include <unordered_map>
#include <string>
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
    struct ActorParametor
    {
        //�������x
        float firstPosY;
        //model�̑傫��
        float setModelSize;
        //�����蔻��̑傫��
        float setRadius;
        //���˕Ԃ��
        float setBouncePow;
        //Tiled�Ŋ���U��ꂽ�ԍ�
        int tiledNum;
        /// <summary>
        /// �������璊�o
        /// </summary>
        /// <param name="paramatorString"></param>
        /// <returns></returns>
        void GetExtractParamator(std::vector <const char*> paramatorString)
        {
            char* end;
            firstPosY = strtof(paramatorString[InitObjParamator::firstPosY], &end);
            setModelSize = strtof(paramatorString[InitObjParamator::modelSize], &end);
            setBouncePow = strtof(paramatorString[InitObjParamator::bouncePower], &end);
            setRadius = strtof(paramatorString[InitObjParamator::collRadius], &end);
            tiledNum = strtof(paramatorString[InitObjParamator::mapTiledNum], &end);
        }
        /// <summary>
        /// �������璊�o
        /// </summary>
        /// <param name="paramatorString"></param>
        /// <returns></returns>
        void GetExtractParamator(std::vector<std::string> paramatorString)
        {
            char* end;
            firstPosY = strtof(paramatorString[InitObjParamator::firstPosY].c_str(), &end);
            setModelSize = strtof(paramatorString[InitObjParamator::modelSize].c_str(), &end);
            setBouncePow = strtof(paramatorString[InitObjParamator::bouncePower].c_str(), &end);
            setRadius = strtof(paramatorString[InitObjParamator::collRadius].c_str(), &end);
            tiledNum = strtof(paramatorString[InitObjParamator::mapTiledNum].c_str(), &end);
        }
    };
    /// <summary>
    /// ����������̂ɕK�v�ȃf�[�^��Z��
    /// </summary>
    struct InitDataPass
    {
        //�����ʒu�̏ꏊ�̃t�@�C����Pass
        std::string firstPosPass;
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
    static ActorParametor GetActorParamator(InitObjKind obj);
    /// <summary>
    /// �������ɕK�v�ȐF�X�ȃp�X������
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    static InitDataPass GetActorInitPassData(InitObjKind obj);
private:
    /// <summary>
    /// �����������������
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    static std::vector<std::string> GetActorParametorString(InitObjKind obj);
    //initActorFileName�̐�̃t�@�C�����珊�������f�[�^���܂Ƃ߂�Vector
    static std::vector<std::string> objectInitDataPassVec;
    //model�̃p�X�Ƃ��ۑ�
    static std::unordered_map<InitObjKind,InitDataPass> initPassDataFileMap;
    //����������p�X��Z�߂Ă���t�@�C���̖��O
    static std::string initActorFileName; 
};