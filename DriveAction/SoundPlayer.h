#pragma once
#include <map>
#include <string>
#include <vector>
#include"DxLib.h"

namespace SoundInit
{
    enum SoundParamator
    {
        //音の相対パス
        soundPass = 2,
        //音量
        soundVolume = 5,
        //音が聞こえる範囲
        soundRadius = 8
    };
    enum SoundKind
    {
        //爆撃機の飛ぶ音
        bomberShipFlight = 2,
        //プレイヤーの動くときの音
        playerFlight = 5,
        //プレイヤーのダメージを受けた時の音
        playerDamage = 8,
        //コインをゲットしたときの音
        coinGet = 11,
        //カウントダウン
        countDown = 14,
        //遊んでいるときのBGM
        playBGM = 17,
        //拍手
        clap = 20,
        //ゲーム開始
        fanfare = 23,
        //タイトルのBGM
        titleBGM = 26,
        //スコアを表示するときに鳴る音
        scoreStartSE = 29,
        //スコアを表示し終わったときに鳴る音
        scoreEndSE = 32,
        //次のシーンに行く時の音
        sceneNextSE = 35,
        //スコア表示したときのファンファーレ
        gameEndFanfare = 38,
        //プレイヤーがチャージしたときの音
        playerCharge = 41, 
    };
}
using namespace SoundInit;
class SoundPlayer
{
public:
    /// <summary>
    /// 音を出すやつ
    /// </summary>
    SoundPlayer();
    /// <summary>
    /// 音を全部止めて消す
    /// </summary>
    ~SoundPlayer();
    /// <summary>
    /// 効果音を鳴らす
    /// </summary>
    /// <param name="kind">音の種類</param>
    static void Play2DSE(SoundKind kind);
    /// <summary>
    /// 3d空間での音を鳴らす
    /// </summary>
    /// <param name="pos">なっている音の位置</param>
    /// <param name="kind">音の種類</param>
    static void Play3DSE(SoundKind kind);
    /// <summary>
    /// 鳴らしたい音の位置を変える
    /// </summary>
    /// <param name="pos">なっている音の位置</param>
    /// <param name="kind">音の種類</param>
    static void SetPosition3DSound(VECTOR pos, SoundKind kind);
    /// <summary>
    /// 音を鳴らす
    /// </summary>
    /// <param name="kind">音の種類</param>
    static void PlayBGM(SoundKind kind);
    /// <summary>
    /// 音を止める
    /// </summary>
    /// <param name="kind">音の種類</param>
    static void StopSound(SoundKind kind);
    /// <summary>
    /// 全ての音を止める
    /// </summary>
    static void StopAllSound();
    /// <summary>
    /// 音をロードして使いまわせるようにする
    /// </summary>
    /// <param name="kind">音の種類</param>
    static void LoadSound(SoundKind kind);
    /// <summary>
    /// ３Dの音をロードして使いまわせるようにする
    /// </summary>
    /// <param name="kind">音の種類</param>
    static void Load3DSound(SoundKind kind);
    /// <summary>
    /// その音が鳴ってるかどうか調べる
    /// </summary>
    /// <param name="kind">音の種類</param>>
    /// <returns>なってたらTrue</returns>
    static bool IsPlaySound(SoundKind kind);
    
private:
    //音にをEnum型で呼び出すためのマップ
    static std::map<SoundKind, int> soundHandleMap;
    //初期化ファイルに入っている音の情報パスのコンテナ
    static std::vector <std::string> initFilePassData;
    //初期化ファイルへのパス
    std::string initSoundFileName = "data/Sound/SoundInitPass.csv";
};

