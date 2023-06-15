#pragma once
#include <string>
#include <unordered_map>
namespace EffectInit
{
    enum EffectKind
    {
        //�Ԃ��Ԃ��������̃G�t�F�N�g
        carConflict = 2,
        //�Ԃ�����؂��Ă���Ƃ��̃G�t�F�N�g
        carWind = 5,
        //�Ԃ����������Ƃ��̃G�t�F�N�g
        carTurbo = 8,
        //�Ԃ��_���[�W���󂯂����̃G�t�F�N�g
        carDamage = 11,
        //��]���a�����������[�U�[
        littleRadiusLaserEffect = 14,
        //��]���a���傫�����[�U�[
        bigRadiusLaserEffect = 17,
        //���[�U�[�̐�
        laserTrack = 20,
        //�R�C�����Q�b�g�����Ƃ��̃G�t�F�N�g
        getCollect = 23,
        //���e�̔���
        bombExplosion = 26,
        //�R�C���̏o���I�[��
        collectAura=29,
        //���W�A�C�e���̕��p���w���G�t�F�N�g
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