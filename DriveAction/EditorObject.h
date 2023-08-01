#pragma once
#include "Actor.h"
#include "EditObjectData.h"
#include "InitObjKind.h"
/// <summary>
/// エディタ上で表示するオブジェクト
/// </summary>
class EditorObject :
    public Actor
{
public:
    /// <summary>
    /// 編集したいものを引数に下さい
    /// </summary>
    /// <param name="kind"></param>
    EditorObject(ObjectInit::InitObjKind kind);
    /// <summary>
    /// 初期位置が最初から決まっている奴
    /// </summary>
    /// <param name="editData"> 位置とオブジェクトの種類と向き</param>
    EditorObject(EditArrangementData editData);
    ~EditorObject();
    /// <summary>
    /// 各オブジェクトを動かしたり回転させたりする
    /// </summary>
    void Update()override;
    /// <summary>
    /// オブジェクトの位置や回転などを渡す
    /// </summary>
    /// <returns></returns>
    EditArrangementData GetEditObjectData()const;
protected:
    /// <summary>
    /// 入力を反映して移動と回転を更新
    /// </summary>
    void ReflectInput();
    //オブジェクトの種類
    int objKind = 0;  
    //回転速度
    static const int rotaSpeed = 2;
    //移動速度
    static const int moveSpeed = 5;
};