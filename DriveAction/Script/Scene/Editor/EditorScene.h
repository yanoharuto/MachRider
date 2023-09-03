#pragma once
#include "SceneBase.h"
#include "Menu.h"
/// <summary>
/// 編集シーンクラス
/// </summary>
class EditorScene final : public SceneBase
{
public:
    /// <summary>
    /// 編集シーンの流れをNew
    /// </summary>
    EditorScene();
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
};

