#pragma once
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include "DxLib.h"

/// <summary>
/// ���X�g���x�N�^�[
/// �ɕϊ�����
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="list"></param>
/// <returns></returns>
template<typename T>
static std::vector<T> ConvertListToVector(std::list<T> list)
{
    std::vector<T> newList(list.begin(), list.end());
    return newList;
}
/// <summary>
/// �x�N�^�[���烊�X�g�ɂ���
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="vector"></param>
/// <returns></returns>
template<typename T>
static std::list<T> ConvertVectorToList(std::vector<T> vector)
{
    std::list<T> newVec(vector.begin(), vector.end());
    return newVec;
}
