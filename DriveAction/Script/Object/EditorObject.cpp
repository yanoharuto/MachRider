#include "EditorObject.h"
#include "UserInput.h"
#include "OriginalMath.h"
#include "CameraObserver.h"
//移動速度
const int EditorObject::moveSpeed = 17;
//回転速度
const int EditorObject::rotaSpeed = 2;

/// <summary>
/// エディタ上で使用するオブジェクト
/// </summary>
EditorObject::EditorObject()
    :Object()
{
    position = {};
    direction = VGet(1, 0, 0);
    
}
/// <summary>
/// 各オブジェクトを動かしたり回転させたりする
/// </summary>
void EditorObject::Update(std::weak_ptr<CameraObserver> cameraObserever)
{
    //入力情報を反映
    ReflectInput(cameraObserever);
}
/// <summary>
/// 描画に必要な構造体を渡す
/// </summary>
/// <returns>位置と向きと描画したいオブジェクトの種類</returns>
PlacementData EditorObject::GePlacementData() const
{
    PlacementData data;
    //向き
    data.dirX = direction.x;
    data.dirZ = direction.z;
    //ポジション
    data.posX = position.x;
    data.posZ = position.z;
    return data;
}
/// <summary>
/// 引数の配置を引き継ぎ位置を変える
/// </summary>
/// <param name="setData">配置</param>
void EditorObject::SetArrangementData(PlacementData setData)
{
    position = VGet(setData.posX, 0, setData.posZ);
    direction = VGet(setData.dirX, 0, setData.dirZ);
}
/// <summary>
/// 入力を反映して移動と回転を更新
/// </summary>
void EditorObject::ReflectInput(std::weak_ptr<CameraObserver> cameraObserever)
{
    if (UserInput::GetInputState(UserInput::KeyInputKind::WKey) == UserInput::InputState::Hold)//ｗキーを押してたら回転モード
    {
        //左右キーを押すと回転する
        if (UserInput::GetInputState(UserInput::KeyInputKind::Left) == UserInput::InputState::Hold)
        {
           direction = OriginalMath::GetYRotateVector(direction, -rotaSpeed);
        }
        else if (UserInput::GetInputState(UserInput::KeyInputKind::Right) == UserInput::InputState::Hold)
        {
            direction = OriginalMath::GetYRotateVector(direction, rotaSpeed);
        }
    }
    else //押してなかったら移動モード
    {
        //カメラの向きに合わせて移動
        VECTOR cameraDir = cameraObserever.lock()->GetCameraDir();
        cameraDir.y = 0;//平行移動だけできる
        //移動量
        VECTOR moveValue = {};
        if (UserInput::GetInputState(UserInput::KeyInputKind::Left) == UserInput::InputState::Hold)//左移動
        {
            moveValue = VCross(cameraDir, VGet(0, -moveSpeed, 0));
            position = VAdd(position, moveValue);
        }
        else if (UserInput::GetInputState(UserInput::KeyInputKind::Right) == UserInput::InputState::Hold)//右移動
        {
            moveValue = VCross(cameraDir, VGet(0, moveSpeed, 0));
            position = VAdd(position, moveValue);
        }
        else if (UserInput::GetInputState(UserInput::KeyInputKind::Up) == UserInput::InputState::Hold)//前移動
        {
            moveValue = VScale(cameraDir, -moveSpeed);
            position = VAdd(position, moveValue);
        }
        else if (UserInput::GetInputState(UserInput::KeyInputKind::Down) == UserInput::InputState::Hold)//後ろ移動
        {
            moveValue = VScale(cameraDir, moveSpeed);
            position = VAdd(position, moveValue);
        }
    }
}

