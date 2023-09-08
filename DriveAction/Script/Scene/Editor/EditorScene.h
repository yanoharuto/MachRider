#pragma once
#include <iostream>
#include <memory>
#include "SceneBase.h"

class Menu;
class EditorCameraObserver;
class EditorManager;
class EditManual;
class EditorEffect;
class EditorCamera;
/// <summary>
/// 編集シーンクラス
/// </summary>
class EditorScene final : public SceneBase
{
public:
    /// <summary>
    /// メニュー画面やカメラ、編集クラスなどを確保
    /// </summary>
    EditorScene();
    /// <summary>
    /// コンストラクタで確保した物を開放
    /// </summary>
    ~EditorScene()override;
    /// <summary>
    /// メニューとEditorの更新
    /// </summary>
    /// <returns>タイトルに戻ったりゲームを終了したりEditorを再読み込みしたりする</returns>
    SceneType Update()override;
    /// <summary>
    /// メニュー画面とEditorの描画
    /// </summary>
    void Draw()const override;
private:
    //メニュー
    Menu* menu;
    //編集物の種類を変更する
    EditorManager* editManager;
    //編集操作説明
    EditManual* manual;
    //編集時に出てくるエフェクトの更新役
    EditorEffect* editorEffect;
    //カメラ
    std::shared_ptr<EditorCamera> camera;
    //カメラの向きを編集オブジェクトに伝えるクラス
    std::shared_ptr<EditorCameraObserver> cameraObserver;
};