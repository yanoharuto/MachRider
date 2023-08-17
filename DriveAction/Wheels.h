#pragma once
#include "DxLib.h"
#include <string>
/// <summary>
/// タイヤ一つ一つが持っている情報
/// </summary>
struct Wheel
{
	int modelHandle = -1;//Duplicateするので本体は別
	VECTOR betweenBody = {};//車までの距離
	MATRIX matrix;
};
/// <summary>
/// タイヤに引数で渡してほしい車の情報
/// </summary>
struct WheelArgumentCarInfo
{
	MATRIX matrix;//車のmodelの行列
	VECTOR direction;//車の向き
	float carSpeed;//速さの大きさ

	void Init(MATRIX setM, VECTOR setDir, float setSpeed)
	{
		matrix = setM;
		direction = setDir;
		carSpeed = setSpeed;
	}
};

/// <summary>
/// 車が走る向きを渡すよ。あとタイヤが回転したり描画する
/// </summary>
class Wheels 
{
public:
    Wheels(const WheelArgumentCarInfo InitInfo);
    ~Wheels();
    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

	/// <summary>
	/// 左右キーを入力したら傾け、上下キーで回転させる
	/// </summary>
	/// <param name="_Key">入力情報</param>
	void WheelUpdate(const WheelArgumentCarInfo info);

	/// <summary>
	/// どの向きに曲がればいいかタンジェントを返すよ
	/// </summary>
	/// <param name="velocitySize">速さのベクトルの大きさ</param>
	/// <returns>負の数ならだったら左</returns>
	float GetMoveDirTheta(const float velocitySize);
private:	

	/// <summary>
	/// 全てのタイヤのマトリックスをセットする
	/// </summary>
	void AllSetWheelMatrix();
	/// <summary>
    /// 回転するための半径を返す
    /// </summary>
    /// <param name="firstWheelRota"></param>
    /// <returns></returns>
	float GetRotationRadius(const float firstWheelRota);
	/// <summary>
    /// 車から見たタイヤの座標が返ってくる
    /// </summary>
    /// <param name="_wheel"></param>
	VECTOR WheelGetPos(const Wheel& wheel);
	/// <summary>
    /// タイヤの位置と回転を設定
    /// </summary>
    /// <param name="_wheel">設定したいタイヤ</param>
    /// <param name="_rotaX">タイヤの転がるときの回転</param>
    /// <param name="_rotaY">タイヤの向きがずれるときの回転</param>
	void SetWheelMatrix(Wheel& wheel, const float rotaX, const float rotaY);
	/// <summary>
	/// タイヤの初期化
	/// </summary>
	/// <param name="_Wheel">初期化したいタイヤ</param>
	/// <param name="_ModelHandle">タイヤのモデル</param>
	/// <param name="_Pos">車から見た位置</param>
	/// <param name="_Rota">回転角</param>
	void InitWheel(Wheel& wheel, int DuplicateSourceModel, VECTOR pos, float rota);
	
	//車の回転速度
	float wheelDriveSpeed = 0.0f;
	//車の左右への傾き
	float wheelDriveRota = 0.0f;
	//まっすぐ進んでいるかどうか
	bool isStraightDash;

	//タイヤのモデルハンドル
	int modelHandle;
	//左前方タイヤ
	Wheel lFWheel;
	//左後方タイヤ
	Wheel lBWheel;
	//右前方タイヤ
	Wheel rFWheel;
	//右後方タイヤ
	Wheel rBWheel;
	//車の情報
	WheelArgumentCarInfo carInfo;
	VECTOR wheelEffectPos;
	const VECTOR fWheelPos = { 6.1f,0.8f,2.8f };
	const VECTOR bWheelPos = { 3.8f,0.8f,2.8f };
};