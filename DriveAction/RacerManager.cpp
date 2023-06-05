#include "RacerManager.h"
#include "CPU.h"
#include "Player.h"
#include "Utility.h"
#include "RacerGenerater.h"
#include "SoundPlayer.h"
#include "ObjectSubject.h"
#include "FirstPositionGetter.h"
/// <summary>
/// 初期化
/// </summary>
/// <param name="racerNum">車乗りの数だけリストに追加するよ</param>
/// <returns></returns>
RacerManager::RacerManager(int playerNum)
{
    for (int i = 0; i < playerNum; i++)
    {
        racerList.push_back(CreatePlayer());
    }
}
//デストラクタ
RacerManager::~RacerManager()
{
    for (auto ite = racerList.begin(); ite != racerList.end(); ite++)
    {
        SAFE_DELETE((*ite));
    }
}
/// <summary>
/// 車乗りたちの更新
/// </summary>
/// <param name="deltaTime">フレーム間の経過時間</param>
/// <param name="circuit">走るコース</param>
void RacerManager::RacerUpdate( )
{
    Racer* racer;
    ConflictExamineResultInfo conflictResultInfo;
    for (auto racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        //車の更新　
        racer->Update();
    }
}
/// <summary>
/// 上下に動く
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
  /// 描画
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
