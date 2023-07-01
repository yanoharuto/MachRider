#include "CollectController.h"
#include "FirstPositionGetter.h"
#include "Coin.h"
#include "MiniMap.h"
#include "ObjectObserver.h"
#include "ObjectSubject.h"
#include "OriginalMath.h"
#include "Utility.h"
#include "InitActor.h"
//���W�A�C�e�����������Ă��邩
bool CollectController::isActive = false;
//�Q�[���I��������
bool CollectController::isChallengeEnd = false;
/// ���ݓ����Ă�����W�A�C�e���̈ʒu
VECTOR CollectController:: nowActiveCollectItemPos;
//�c���Ă�����W�A�C�e���̐�
int CollectController::remainingCollectNum = 0;
//���W�A�C�e���̑���
int CollectController::totalCollectNum = 0;
/// <summary>
/// �R�C���̐ݒu
/// </summary>
CollectController::CollectController()
{
    auto getter = new FirstPositionGetter();
    auto challengeDataVec = getter->GetChallengeData();

    for (auto ite = challengeDataVec.begin(); ite != challengeDataVec.end(); ite++)
    {
        //���W�A�C�e���̈ʒu���R���X�g���N�^�ɗ^����
        Coin* newCoin = new Coin((*ite).collectPos[InitActor::GetActorTileNum(collect)][0]);

        actorList.push_back(newCoin);
        ObjectSubject* subject = new ObjectSubject(newCoin);
        subjectList.push_back(std::move(subject));
        //�}�b�v�Ɉʒu��`���邽�߃I�u�U�[�o�[��n��
        MiniMap::AddMarker(new ObjectObserver(subject));
    }
    //static�ϐ��̏�����
    totalCollectNum = actorList.size();//���W�A�C�e���ő�l
    remainingCollectNum = totalCollectNum;//�c��̐�
    isChallengeEnd = false;
    isActive = false;//����������
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
    if ((*objIte)->GetObjectState()== Object::ObjectState::dead)
    {
        //�����Ă��������
        Actor* brokenObj = (*objIte);
        actorList.erase(objIte);
        SAFE_DELETE(brokenObj);
        //���X�g�̒��g����ɂȂ�����
        isChallengeEnd = actorList.empty();
    }
}
/// <summary>
/// ���W�A�C�e���̕`��
/// </summary>
void CollectController::Draw() const
{
    (*actorList.begin())->Draw();
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
bool CollectController::IsEndingChallenge()
{
    return isChallengeEnd;
}
