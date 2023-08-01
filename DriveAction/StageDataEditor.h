#pragma once
#include <string>
#include <vector>
#include "EditObjectData.h"
#include "InitObjKind.h"
#include "FirstPositionGetter.h"
class EditorObject;
class EditorModelViewer;
/// <summary>
/// ステージに配置するオブジェクトの位置などを保存する
/// </summary>
class StageDataEditor abstract
{
public:
    /// <summary>
    ///ステージに配置するオブジェクトの位置などを保存する
    /// </summary>
    /// <param name="setFileName">どのファイルに保存するか教えて</param>
    StageDataEditor(std::string setFileName);
    ~StageDataEditor();
    /// <summary>
    /// 更新
    /// </summary>
    virtual void Update() = 0;
    /// <summary>
    /// 編集終了オブジェクトの描画
    /// </summary>
    virtual void DrawAllEditedObject()const {};
    /// <summary>
    /// 今現在編集中のオブジェクトの描画
    /// </summary>
    virtual void DrawNowEditObject()const = 0;
    /// <summary>
    /// 編集が終了したか
    /// </summary>
    /// <returns></returns>
    bool IsEndEditing()const { return isEndEdit; };
    /// <summary>
    /// 今編集しているオブジェクトのポジション
    /// </summary>
    /// <returns></returns>
    static VECTOR GetEditObjPos();
    /// <summary>
    /// 現在編集しているアイテムの出てくるタイミングを変更
    /// </summary>
    void ChangeMissionNum();
    /// <summary>
    /// 編集済みデータの削除
    /// </summary>
    /// <param name="eraceNum">削除するのは先頭から何番目か</param>
    void EraceEndEditData(int eraceNum);
    /// <summary>
    /// 文字を描画
    /// </summary>
    /// <param name="data"></param>
    virtual void DrawEditString() const = 0;
    /// <summary>
    /// 選択中の文字描画
    /// </summary>
    virtual void DrawSelectString() const = 0;
protected:
    /// <summary>
    /// 選択物の向きと位置がわかるエフェクトの更新
    /// </summary>
    void UpdateEffect();
    //今編集しているオブジェクトのポジション
    static EditArrangementData nowEditObjData;
    //編集終了フラグ
    bool isEndEdit = true;
    /// <summary>
    /// 引数の情報を書き込む
    /// </summary>
    /// <param name="data"></param>
    void SaveEditObjectData(EditArrangementData data)const;
    /// <summary>
    /// データ保存ファイル
    /// </summary>
    std::string saveFileName;
    /// 収集アイテムの数
    static int collectNum;  
    /// 収集アイテムを取ったどのタイミングで出てくるか
    static int missionNum;
    //オブジェクトの描画担当
    EditorModelViewer* viewer;
    //選択エフェクト
    static int selectAura;
    //向きが分かりやすくなるエフェクト
    static int dirEffect;
    //編集済みデータ
    std::vector<EditArrangementData> editDataVec;
};