#include <iostream>
#include <memory>
#include "CollectController.h"
#include "FirstPositionGetter.h"
#include "Coin.h"
#include "MiniMap.h"
#include "ObjectObserver.h"
#include "OriginalMath.h"
#include "Utility.h"
#include "InitActor.h"
#include "ModelViewer.h"
#include "Object.h"

//���W�A�C�e�����������Ă��邩
bool CollectController::isActive = false;
//���W�A�C�e�����S��Delete���ꂽ��
bool CollectController::isDestroyAll = false;
//�Q�[���I��������
bool CollectController::isMissionEnd = false;
/// ���ݓ����Ă�����W�A�C�e���̈ʒu
VECTOR CollectController:: nowActiveCollectItemPos;
//�c���Ă�����W�A�C�e���̐�
int CollectController::remainingCollectNum = 0;
//���W�A�C�e���̑���
int CollectController::totalCollectNum = 0;
/// <summary>
/// �R�C����\��New���čő喇����ۑ�
/// </summary>
CollectController::CollectController()
    :ActorController(collect)
{
    auto getter = new FirstPositionGetter();
    auto editDataVec = getter->GetInitData(Object::collect);

    for (int i = 0; i < editDataVec.size(); i++)
    {
        //���W�A�C�e���̈ʒu���R���X�g���N�^�ɗ^����
        Coin* newCoin = new Coin(editDataVec[i]);

        actorList.push_back(newCoin);
        
        //�}�b�v�Ɉʒu��`���邽�߃I�u�U�[�o�[��n��
        MiniMap::AddMarker(std::make_unique<ObjectObserver>(newCoin));
    }
    //static�ϐ��̏�����
    totalCollectNum = actorList.size();//���W�A�C�e���ő�l
    remainingCollectNum = totalCollectNum;//�c��̐�
    isMissionEnd = false;
    isActive = false;//����������
    isDestroyAll = false;
    viewer = new ModelViewer(collect);
}
/// <summary>
/// actorList�̐擪�̎��W�A�C�e�������X�V
/// </summary>
void CollectController::Update()
{
    //�C�e���[�^�[
    auto objIte = actorList.begin();
    (*objIte)->Update();
    isActive = (*objIte)->GetObjectState() == Object::ObjectState::active;
    //�����ݓ����Ă���A�C�e���̏ꏊ���X�V
    nowActiveCollectItemPos = (*objIte)->GetPos();
    //�c���Ă���A�C�e���̐�
    remainingCollectNum = actorList.size();
    //����Ă��邯�ǃG�t�F�N�g���o���Ă���r���Ȃ猻�������ւ炷
    if ((*objIte)->GetObjectState() != Object::ObjectState::active) remainingCollectNum --;

    //�������݂��Ă��Ȃ�������X�V�I��
    Actor* brokenObj = (*objIte);
    switch ((*objIte)->GetObjectState())
    {
    case Object::dead:
        //�����Ă���������������
        actorList.erase(objIte);
        SAFE_DELETE(brokenObj);
        //�S�������ꂽ�Ȃ�True
        isDestroyAll = actorList.empty();
        break;
    case Object::activeEnd://�Ō�̈�Ȃ�
        isMissionEnd = actorList.size() == 1;
        break;
    default:
        break;
    }
}
/// <summary>
/// ���W�A�C�e���̕`��
/// </summary>
void CollectController::Draw() const
{
    viewer->Draw((*actorList.begin()));
}
/// <summary>
/// �Q�[�����n�܂�O�̏���
/// </summary>
void CollectController::GameReserve()
{
    //�C�e���[�^�[
    auto objIte = actorList.begin();
    (*objIte)->GameReserve();
    //�����ݓ����Ă���A�C�e���̏ꏊ���X�V
    nowActiveCollectItemPos = (*objIte)->GetPos();
}
/// <summary>
/// �����̏ꏊ�Ǝ��W�A�C�e���̈ʒu�̋����x�N�g�����o��
/// </summary>
/// <param name="pos"></param>
/// <returns></returns>
VECTOR CollectController::GetBetween(VECTOR pos)
{
    return VSub(nowActiveCollectItemPos, pos);
}
/// <summary>
/// ���W�A�C�e���������Ă��邩
/// </summary>
/// <returns></returns>
bool CollectController::IsActiveCollect()
{
    return isActive;
}
/// <summary>
/// �v���C���[���W�߂Ȃ���΂����Ȃ��A�C�e���̐�
/// </summary>
/// <returns></returns>
int CollectController::GetTotalCollectNum()
{
    return totalCollectNum;
}
/// <summary>
/// �c���Ă���A�C�e���̐�
/// </summary>
/// <returns></returns>
int CollectController::GetRemainingCollectNum()
{
    return remainingCollectNum;
}
/// <summary>
/// �S�ẴA�C�e����������I�������ǂ���
/// </summary>
/// <returns></returns>
bool CollectController::IsEndingMission()
{
    return isMissionEnd;
}
/// <summary>
/// �S�ẴA�C�e�����j�󂳂ꂽ��
/// </summary>
/// <returns></returns>
bool CollectController::IsDestroyAllItem()
{
    return isDestroyAll;
}
