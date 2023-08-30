#include "PlayScene.h"
#include "PlaySceneFlow.h"

#include "Utility.h"
#include "SoundPlayer.h"
#include "FadeInFadeOut.h"
#include "Clock.h"
#include "Menu.h"
/// <summary>
/// メニュー画面とゲームの流れの確保と音をロード
/// </summary>
PlayScene::PlayScene()
    :SceneBase(SceneType::PLAY)
{
    sceneFlow = new PlaySceneFlow();
    
    SoundPlayer::LoadSound(playBGM);
    menu = new Menu();
}
/// <summary>
/// メニューとゲームの開放と音を止める
/// </summary>
PlayScene::~PlayScene()
{
    SAFE_DELETE(menu);
    SAFE_DELETE(sceneFlow);
    SoundPlayer::StopSound(playBGM);
}
/// <summary>
/// ゲームを遊ぶ
/// </summary>
/// <returns></returns>
SceneType PlayScene::Update()
{
    //メニューでプレイヤーが何を選んだか
    menu->Update();
    MenuState menuState = menu->GetMenuState();
    

    switch (menuState)
    {
    case continueGame:
        //menu画面が開いてないなら普通の処理
        if (menu->IsMenuOpen() == false)
        {
            //シーンごとの処理
            sceneFlow->Update();
            //処理が終わったら
            if (sceneFlow->GetIsEndProccess())
            {
                return sceneFlow->GetNextSceneType();
            }
        }
    break;
    //ゲームをやり直す
    case retry:
        nowSceneType = SceneType::RELOAD;
        break;
        //タイトルに戻る
    case returnTitle:
        nowSceneType = SceneType::TITLE;
        break;
        //ゲーム終了
    case exitGame:
        nowSceneType = SceneType::ESCAPE;
        break;
    default:
        break;
    }
    
    return nowSceneType;
}
/// <summary>
/// メニューを開いている時と遊んでいるときで処理が違う
/// </summary>
void PlayScene::Draw()const
{
    if (Menu::IsMenuOpen())//メニューを開いていたらメニュー画面を描画
    {
         menu->Draw();
    }
    else//遊んでいるときの状態を描画
    {
        sceneFlow->Draw();
    }
}
