#pragma once
#include <string>
#include <unordered_map>
namespace EffectInit
{
    /// <summary>
    /// エフェクトの種類
    /// </summary>
    enum EffectKind
    {
        //車がぶつかった時のエフェクト
        carConflict = 2,
        //車が風を切っているときのエフェクト
        carWind = 5,
        //車が加速したときのエフェクト
        carTurbo = 8,
        //車がダメージを受けた時のエフェクト
        carDamage = 11,
        //回転半径が小さいレーザー
        littleRadiusLaserEffect = 14,
        //回転半径が大きいレーザー
        laser = 17,
        //レーザーの跡
        laserTrack = 20,
        //コインをゲットしたときのエフェクト
        getCollect = 23,
        //爆弾の爆発
        bombExplosion = 26,
        //コインの出すオーラ
        collectAura = 29,
        //収集アイテムの方角を指すエフェクト
        compass = 32,
        //車の後ろから出すエフェクト
        burner = 35,
        //車が速くなる前に出すエフェクト
        turboCourse = 38,
        //勝利後の紙吹雪
        confetti = 41,
        //ターボ前段階のバーナーエフェクト
        chargeBurner = 44, 
        //高速移動中のバーナー
        turboBurner = 47
    };
    /// <summary>
    /// エフェクトの初期化に必要なもの
    /// </summary>
    enum EffectInitData
    {
        effectPass = 2,//エフェクトのパス
        effectSize = 5//エフェクトの大きさ
    };
}
using namespace EffectInit;
/// <summary>
/// エフェクトの保管庫
/// </summary>
class EffectManager
{
public:
    /// <summary>
    /// エフェクトを読み込んだり渡したりする
    /// </summary>
    EffectManager();
    /// <summary>
    /// エフェクトを解放
    /// </summary>
    ~EffectManager();
    /// <summary>
    /// エフェクトを読み込む
    /// </summary>
    /// <param name="kind">エフェクトの種類</param>
    static void LoadEffect(EffectKind kind);
    /// <summary>
    /// ロード済みの3Ⅾエフェクトを渡す
    /// </summary>
    /// <param name="kind">エフェクトの種類</param>
    /// <returns>3Ⅾエフェクトのハンドル</returns>
    static int GetPlayEffect3D(EffectKind kind);
    /// <summary>
    /// ロード済みの2Dエフェクトを渡す
    /// </summary>
    /// <param name="kind"></param>
    /// <returns>2Ⅾエフェクトのハンドル</returns>
    static int GetPlayEffect2D(EffectKind kind);
private:
    //エフェクトのハンドルが入るマップ
    static std::unordered_map <EffectKind, int> effectMap;
    //エフェクトのパスが入る文字列
    static std::vector<std::string> initDataVec;
    //各エフェクトのパスが入っているファイル
    const std::string initDataPassFile = "data/effect/initEffectPass.csv";
};