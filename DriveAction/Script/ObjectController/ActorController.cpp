#include "ActorController.h"
#include "Actor.h"
#include "DrawModel.h"
#include "Utility.h"
#include "CameraObserver.h"
/// <summary>
/// �`����ƃI�u�W�F�N�g�̃f���[�g
/// </summary>
ActorController::~ActorController()
{
    DeleteActorListAndDrawModel();
}
/// <summary>
/// �Q�[���J�n��������
/// </summary>
void ActorController::PrepareGame()
{
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        (*ite)->PrepareGame();
    }
}
/// <summary>
/// �X�V
/// </summary>
void ActorController::Update()
{
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        //�eactor�̍X�V
        (*ite)->Update();
    }
}
/// <summary>
/// �`�揈��
/// </summary>
void ActorController::Draw(std::weak_ptr<CameraObserver> cameraObserever) const
{
    if (drawModel != nullptr)
    {
        for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
        {
            if(cameraObserever.lock()->IsLookingCamera(*ite))//�J�����͈͓̔��Ȃ�
            {
                //Drawer�ɓn���ĕ`�悵�Ă��炤
                drawModel->Draw((*ite));
            }
        }
    }
}
/// <summary>
/// �`�����ActorList�̉��
/// </summary>
void ActorController::DeleteActorListAndDrawModel()
{
    if (!actorList.empty())
    {
        for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
        {
            SAFE_DELETE(*ite);
        }
        actorList.clear();
    }
    SAFE_DELETE(drawModel);
}