#pragma once
#include <string>
#include <unordered_map>
namespace EffectInit
{
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
        bigRadiusLaserEffect = 17,
        //レーザーの跡
        laserTrack = 20,
        //コインをゲットしたときのエフェクト
        getCollect = 23,
        //爆弾の爆発
        bombExplosion = 26,
        //コインの出すオーラ
        collectAura=29,
        //収集アイテムの方角を指すエフェクト
        compass=32
    };
    enum EffectInitData
    {
        effectPass = 2,
        effectSize = 5
    };
}
using namespace EffectInit;

class EffectManager
{
public:
    EffectManager();
    ~EffectManager();
    static void LoadEffect(EffectKind kind);
    static int GetPlayEffect3D(EffectKind kind);
    static int GetPlayEffect2D(EffectKind kind);
private:
    static std::unordered_map <EffectKind, int> effectMap;
    static std::vector<std::string> initDataVec;
    const std::string initDataPassFile = "data/effect/initEffectPass.csv";
};