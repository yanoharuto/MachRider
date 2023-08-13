#include "ActorController.h"
#include "Actor.h"
#include "ModelViewer.h"
#include "Utility.h"
/// <summary>
/// �f���[�g
/// </summary>
ActorController::~ActorController()
{
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        SAFE_DELETE(*ite);
    }
    actorList.clear();
    SAFE_DELETE(viewer);
}
/// <summary>
/// �Q�[���J�n��������
/// </summary>
void ActorController::GameReserve()
{
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        (*ite)->GameReserve();
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
void ActorController::Draw() const
{
    if (viewer != nullptr)
    {
        for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
        {
            //Viewer�ɓn���ĕ`�悵�Ă��炤
            viewer->Draw((*ite));
        }
    }
}
/// <summary>
/// �������I���Ă���false
/// </summary>
/// <returns></returns>
bool ActorController::IsAlive() const
{
    //���g���Ȃ������玀��ł�
    if (actorList.empty())return false;
    //����łȂ��Ȃ�true��Ԃ�
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        if ((*ite)->GetObjectState() != Object::ObjectState::dead)return true;
    }
    return false;
}
