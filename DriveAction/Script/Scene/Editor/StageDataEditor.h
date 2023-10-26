#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "EditObjectData.h"
#include "InitObjKind.h"
#include "FirstPositionGetter.h"
//新しく編集中ならselectEditNumが-1
#define NEW_EDIT_NUM -1

class EditorObject;
class EditorDrawModel;
class CameraObserver;
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
    /// <param name="setFileName">編集するファイルの名前</param>
    /// <param name="objKind">編集するオブジェクトの種類</param>
    StageDataEditor(std::string setFileName,InitObjKind objKind);
    /// <summary>
    /// 描画役と編集オブジェクトの解放
    /// </summary>
    virtual ~StageDataEditor();
    /// <summary>
    /// 新しく編集したり過去に編集したものを再編集したりする
    /// </summary>
    virtual void Update(std::weak_ptr<CameraObserver> cameraObserever);
    /// <summary>
    /// 編集中や編集し終えたオブジェクトの描画
    /// </summary>
    virtual void Draw()const;
    /// <summary>
    /// 編集が終了したか
    /// </summary>
    /// <returns>編集が終了したらTrue</returns>
    bool IsEndEditing()const 
    {
        return nowEditAction == EditActionKind::select; 
    };
    /// <summary>
    /// 編集しているオブジェクトの種類
    /// </summary>
    /// <returns></returns>
    InitObjKind GetEditObjectKind()const
    {
        return editKind;
    }
    /// <summary>
    /// 編集しているオブジェクトの配置情報
    /// </summary>
    /// <returns>編集しているオブジェクトの配置情報</returns>
    PlacementData GetNowEditObjPlaceData()const
    {
        return nowEditObjPlaceData;
    };
    /// <summary>
    /// 編集しているオブジェクトのVectorコンテナ
    /// </summary>
    /// <returns></returns>
    std::vector<PlacementData> GetPlacementDataVector()const
    {
        return editedPlacementDataVec;
    };
    /// <summary>
    /// 編集中かどうかを返す
    /// </summary>
    /// <returns>編集中ならTrue</returns>
    bool IsNowEdit() const
    {
        return nowEditAction != EditActionKind::select;
    }
    /// <summary>
    /// 現在編集しているアイテムの出てくるタイミングを変更
    /// </summary>
    void ChangeEditedCollectNum();
    //編集で行う事
    enum class EditActionKind
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
    /// 編集済みデータの削除
    /// </summary>
    /// <param name="eraceNum">削除するのは先頭から何番目か</param>
    void EraceEndEditData(int eraceNum);
    /// <summary>
    /// 編集済みのオブジェクトを選択する
    /// </summary>
    void SelectEditedObject();
    /// <summary>
    /// 編集操作
    /// </summary>
    void Edit(std::weak_ptr<CameraObserver> cameraObserever);
    /// <summary>
    /// NowEditObjDataメンバ変数を更新する
    /// </summary>
    void UpdateNowEditObjData();
    //今編集しているオブジェクトの情報
    static PlacementData nowEditObjPlaceData;
    // 編集したいエネミーの種類
    InitObjKind editKind = InitObjKind::saw;
    //編集終了フラグ
    EditActionKind nowEditAction = EditActionKind::select;
    //現在編集中のオブジェクト
    EditorObject* editObject;
    /// 収集アイテムの数
    static int collectNum;  
    /// 収集アイテムを取ったどのタイミングで出てくるか
    static int getCollectNum;
    //オブジェクトの描画担当
    EditorDrawModel* drawer;
    //編集済みデータ
    std::vector<PlacementData> editedPlacementDataVec;
    //編集済みの物を左右キーで選ぼうとすると変動
    int selectEditedNum = -1;
    //編集ファイル置き場
    static const std::string editFilePath;
};