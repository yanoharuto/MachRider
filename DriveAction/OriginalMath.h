#pragma once
#include "DxLib.h"
#include <math.h>
#include<random>
#define RAGE  static_cast<float>(DX_PI / 180.0f) //���W�A��

class OriginalMath
{
public:
    /// <summary>
    /// �������Ƒ������̊p�x�̂�����o��
    /// </summary>
    /// <param name="direction1"></param>
    /// <param name="direction2"></param>
    /// <returns>�f�O���[�ŕԂ�</returns>
    static float GetDegreeMisalignment(VECTOR direction1, VECTOR direction2)
    {
        float destinationDir = 0;
        destinationDir = VDot(direction1, direction2) / (VSize(direction2) * VSize(direction1));
        destinationDir = acosf(destinationDir) / RAGE;
        return destinationDir;
    }
    /// <summary>
    /// �����_���Ȓl��Ԃ�
    /// </summary>
    /// <param name="min">�Œ�l</param>
    /// <param name="max">�ő�l</param>
    /// <returns></returns>
    static int GetRandom(int min, int max)
    {
        std::random_device seed;
        std::mt19937 engine(seed());
        std::uniform_int_distribution<> dist{ min,max };
        return dist(engine);
    }
    /// <summary>
    /// �����̓x������y���ŋȂ������x�N�g����Ԃ�
    /// </summary>
    /// <param name="rotateVector">�Ȃ������x�N�g��</param>
    /// <param name="degree">�Ȃ������p�x</param>
    /// <returns>�Ȃ����x�N�g��</returns>
    static VECTOR GetYRotateVector(VECTOR rotateVector, float degree)
    {
        //�Z�\�x���v�Z����
        int num = abs(static_cast<int> (degree)) / 45;
        float rota = 45 * RAGE;
        VECTOR crossY = degree > 0 ? VGet(0, 1, 0) : VGet(0, -1, 0);
        //60�x�Ȃ������z�𑫂��Ă���
        VECTOR addVec = VScale(VNorm(VCross(rotateVector, crossY)), rota);
        for (int i = 0; i < num; i++)
        {
            rotateVector = VAdd(rotateVector, addVec);
        }
        //�Ō��For�ŉ񂹂Ȃ����������v�Z
        rota = (degree - num * 60) * RAGE;
        addVec = VScale(VNorm(VCross(rotateVector, crossY)), rota);
        rotateVector = VAdd(rotateVector, addVec);
        return rotateVector;
    }
    /// <summary>
    /// ������Ԃ�
    /// </summary>
    /// <param name="num"></param>
    /// <returns></returns>
    static int GetDigits(int num)
    {
        int digits = 1;
        while (num >= 10)
        {
            num /= 10;
            digits++;
        }
        return digits;
    }
};