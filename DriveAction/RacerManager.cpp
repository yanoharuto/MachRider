#include "RacerManager.h"
#include "CPU.h"
#include "Player.h"
#include "Utility.h"
#include "RacerGenerater.h"
#include "SoundPlayer.h"
#include "ObjectSubject.h"
#include "FirstPositionGetter.h"
/// <summary>
/// ������
/// </summary>
/// <param name="racerNum">�ԏ��̐��������X�g�ɒǉ������</param>
/// <returns></returns>
RacerManager::RacerManager(int playerNum)
{
    for (int i = 0; i < playerNum; i++)
    {
        racerList.push_back(CreatePlayer());
    }
}
//�f�X�g���N�^
RacerManager::~RacerManager()
{
    for (auto ite = racerList.begin(); ite != racerList.end(); ite++)
    {
        SAFE_DELETE((*ite));
    }
}
/// <summary>
/// �ԏ�肽���̍X�V
/// </summary>
/// <param name="deltaTime">�t���[���Ԃ̌o�ߎ���</param>
/// <param name="circuit">����R�[�X</param>
void RacerManager::RacerUpdate( )
{
    Racer* racer;
    ConflictExamineResultInfo conflictResultInfo;
    for (auto racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        //�Ԃ̍X�V�@
        racer->Update();
    }
}
/// <summary>
/// �㉺�ɓ���
/// </summary>
void RacerManager::UpDown()
{
    Racer* racer;
    for (auto racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        racer->UpDown();
    }
}


/// <summary>
  /// �`��
  /// </summary>
  /// <returns></returns>
void RacerManager::Draw()
{
    Racer* racer;
    for (auto racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        racer->Draw();
    }
}

ObjectSubject* RacerManager::GetPlayerSubject(int num)
{
    ObjectSubject* subject = (*racerList.begin())->GetSubject();
    return subject;
}

Player* RacerManager::CreatePlayer()
{
    auto firstPosList = FirstPositionGetter::GetFirstPositionLoad(FirstPositionDataKind::playerPosition);
    Player* newPlayer = new Player(firstPosList[0][0]);
    return newPlayer;
}
