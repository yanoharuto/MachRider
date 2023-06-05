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
    /// <param name="min"></param>
    /// <param name="max"></param>
    /// <returns></returns>
    static int GetRandom(int min, int max)
    {
        std::random_device seed;
        std::mt19937 engine(seed());
        std::uniform_int_distribution<> dist{ min,max };
        return dist(engine);
    }
    /// <summary>
    /// �����̓x�������Ȃ������x�N�g����Ԃ�
    /// </summary>
    /// <param name="rotateVector"></param>
    /// <param name="degree"></param>
    /// <returns></returns>
    static VECTOR GetYRotateVector(VECTOR rotateVector, float degree)
    {
        int deg = static_cast<int> (degree);
        float rota = 60 * RAGE;
        VECTOR tempVec = degree > 0 ? VGet(0, 1, 0) : VGet(0, -1, 0);
        VECTOR addVec = VNorm(VCross(rotateVector, tempVec));
        addVec = VScale(addVec, rota);
        for (int i = 0; i < deg / 60; i++)
        {
            rotateVector = VAdd(rotateVector, addVec);
            degree -= 60;
        }
        rota = degree * RAGE;
        addVec = VScale(VNorm(VCross(rotateVector, tempVec)), rota);
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