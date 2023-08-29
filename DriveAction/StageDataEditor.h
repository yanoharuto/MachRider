#pragma once
#include <string>
#include <vector>
#include "EditObjectData.h"
#include "InitObjKind.h"
#include "FirstPositionGetter.h"
#define NEW_EDIT_NUM -1
class EditorObject;
class EditorDrawModel;
enum ActionKind;
using namespace ObjectInit;
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
    StageDataEditor(std::string setFileName,InitObjKind objKind);
    virtual ~StageDataEditor();
    /// <summary>
    /// 新しく編集したり過去に編集したものを再編集したりする
    /// </summary>
    virtual void Update();
    /// <summary>
    /// 編集中や編集し終えたオブジェクトの描画
    /// </summary>
    virtual void Draw()const;
    /// <summary>
    /// 編集が終了したか
    /// </summary>
    /// <returns>編集が終了したらTrue</returns>
    bool IsEndEditing()const { return nowEditAction == EditActionKind::select; };
    /// <summary>
    /// 今編集しているオブジェクトのポジション
    /// </summary>
    /// <returns></returns>
    static VECTOR GetEditObjPos();
    /// <summary>
    /// 現在編集しているアイテムの出てくるタイミングを変更
    /// </summary>
    void ChangeEditedCollectNum();
    /// <summary>
    /// 編集済みデータの削除
    /// </summary>
    /// <param name="eraceNum">削除するのは先頭から何番目か</param>
    void EraceEndEditData(int eraceNum);
    //編集で行う事
    enum EditActionKind
    {
        //編集中
        edit,
        //再編集中
        reEdit,
        //編集するか再編集するか選択中
        select,
    };
protected:
    /// <summary>
    /// 選択物の向きと位置がわかるエフェクトの更新
    /// </summary>
    void UpdateEffect();
    /// <summary>
    /// 編集済みのオブジェクトを選択する
    /// </summary>
    void SelectEditedObject();

    /// <summary>
    /// 編集操作
    /// </summary>
    void Edit();
    /// <summary>
    /// NowEditObjDataメンバ変数を更新する
    /// </summary>
    void UpdateNowEditObjData();
    
    //今編集しているオブジェクトの情報
    static PlacementData nowEditObjData;
    // 編集したいエネミーの種類
    InitObjKind editKind = saw;
    //編集終了フラグ
    EditActionKind nowEditAction = select;
    //現在編集中のオブジェクト
    EditorObject* editObject;
    /// 収集アイテムの数
    static int collectNum;  
    /// 収集アイテムを取ったどのタイミングで出てくるか
    static int getCollectNum;
    //オブジェクトの描画担当
    EditorDrawModel* drawer;
    //選択エフェクト
    static int selectAura;
    //向きが分かりやすくなるエフェクト
    static int dirEffect;
    //配置中のオブジェクトの向きが分かるエフェクトのサイズ
    static int dirEffectSize;
    //編集済みデータ
    std::vector<PlacementData> placementDataVec;
    //編集済みの物を左右キーで選ぼうとすると変動
    int selectEditedNum = -1;
};