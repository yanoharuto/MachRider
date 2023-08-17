#pragma once
/// <summary>
/// シーンの内訳
/// </summary>
enum class SceneType
{
    //再ロード
    RELOAD,
    //タイトル
    TITLE,
    //ゲームプレイ
    PLAY,
    //編集
    EDITOR,
    //ゲーム終了
    ESCAPE
};