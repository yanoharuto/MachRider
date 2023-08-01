#pragma once
#include "StageDataEditor.h"
#include <unordered_map>
#include <vector>

class EnemyDataEditor :
    public StageDataEditor
{
public:
    EnemyDataEditor();
    ~EnemyDataEditor();
    /// <summary>
    /// 更新
    /// </summary>
    void Update()override;
    /// <summary>
    /// 編集済みのオブジェクトを描画
    /// </summary>
    void DrawAllEditedObject()const override;
    /// <summary>
    /// 現在編集している物を描画
    /// </summary>
    void DrawNowEditObject()const override;
    /// <summary>
    /// 文字を描画
    /// </summary>
    void DrawEditString() const override;
    /// <summary>
    /// 選択されているときの文字を描画
    /// </summary>
    void DrawSelectString()const override;
private:
    /// <summary>
    /// 編集するエネミーを選択
    /// </summary>
    void SelectEnemy();
    /// <summary>
    /// 編集する過去のエネミーを選択
    /// </summary>
    void SelectEditedEnemy();
    
    /// <summary>
    /// 各エネミーの描画担当役
    /// </summary>
    std::unordered_map<ObjectInit::InitObjKind,EditorModelViewer*> eneViewerMap;
    /// <summary>
    /// 現在編集しているエネミー
    /// </summary>
    EditorObject* nowEditEne;
    /// <summary>
    /// 編集したいエネミーの種類
    /// </summary>
    ObjectInit::InitObjKind kind = ObjectInit::saw;
    //エディターの名前の位置
    const int drawStrY = 800;
    //エディターの色
    const unsigned int selectColor = GetColor(0, 255, 0);
    //エディターの名前
    const std::string drawEditString = "Enemy"; 
    //選択している編集済みエネミーの番号 
    int selectEditedEneNum = -1;
    //編集済みエネミーを選択中か
    bool isSelectEditedEne = false;
};