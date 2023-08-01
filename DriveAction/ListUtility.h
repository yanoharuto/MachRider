#pragma once
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include "DxLib.h"

/// <summary>
/// リストをベクター
/// に変換する
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
/// ベクターからリストにする
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
/// <summary>
/// 要素がVectorの中に無いか調べる
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="vector"></param>
/// <param name="element"></param>
/// <returns></returns>
template<typename T>
static std::vector<T*>::iterator FindVector(std::vector<T*>* vector,T* element)
{
    for (auto itr = (*vector).begin(); itr != (*vector).end(); itr++)
    {
        if ((*itr) == element)
        {
            return itr;
        }
    }
    return (*vector).end();
}
template<typename T>
static std::list<T*>::iterator FindList(std::list<T*>* vector, T* element)
{
    for (auto itr = (*vector).begin(); itr != (*vector).end(); itr++)
    {
        if ((*itr) == element)
        {
            return itr;
        }
    }
    return (*vector).end();
}