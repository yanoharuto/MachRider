#pragma once
#include "DxLib.h"
#include <math.h>
#include<random>
#define RAGE  static_cast<float>(DX_PI / 180.0f) //ラジアン

class OriginalMath
{
public:
    /// <summary>
    /// 第一引数と第二引数の角度のずれを出す
    /// </summary>
    /// <param name="direction1"></param>
    /// <param name="direction2"></param>
    /// <returns>デグリーで返す</returns>
    static float GetDegreeMisalignment(VECTOR direction1, VECTOR direction2)
    {
        float destinationDir = 0;
        destinationDir = VDot(direction1, direction2) / (VSize(direction2) * VSize(direction1));
        destinationDir = acosf(destinationDir) / RAGE;
        return destinationDir;
    }
    /// <summary>
    /// ランダムな値を返す
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
    /// 引数の度数だけ曲がったベクトルを返す
    /// </summary>
    /// <param name="rotateVector"></param>
    /// <param name="degree"></param>
    /// <returns></returns>
    static VECTOR GetYRotateVector(VECTOR rotateVector, float degree)
    {
        //六十度ずつ計算する
        int num = abs(static_cast<int> (degree)) / 60;
        float rota = 60 * RAGE;
        VECTOR tempVec = degree > 0 ? VGet(0, 1, 0) : VGet(0, -1, 0);
        //60度曲がった奴
        VECTOR addVec = VScale(VNorm(VCross(rotateVector, tempVec)), rota);
        for (int i = 0; i < num; i++)
        {
            rotateVector = VAdd(rotateVector, addVec);
        }
        //最後にForで回せなかった分を計算
        rota = (degree - num * 60) * RAGE;
        addVec = VScale(VNorm(VCross(rotateVector, tempVec)), rota);
        rotateVector = VAdd(rotateVector, addVec);
        return rotateVector;
    }
    /// <summary>
    /// 桁数を返す
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