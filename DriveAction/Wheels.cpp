#include "Wheels.h"
#include <math.h>
#include "EffekseerForDXLib.h"
#include "UserInput.h"
#include "OriginalMath.h"
#include "AssetManager.h"
//左側タイヤの初期角度
static const float firstLWheelRota = 0.0f;
//右側タイヤの初期角度
static const float firstRWheelRota = 180.0f;
//車の回転力
static const float wheelDriveRotaPower = 4.4f;
//タイヤが左右に傾く力
static const float wheelCurvePower = 1.7f;
//この角度までタイヤは傾くよ
static const float maxWheelRotaY = 45.5f;
//進行方向に影響するまでに必要なタイヤの角度
static const float rotaCalculationLine = 1.2f;

Wheels::Wheels(const WheelArgumentCarInfo InitInfo)
{
	carInfo = InitInfo;
	InitWheel(lFWheel, modelHandle, VGet(-fWheelPos.x, fWheelPos.y, -fWheelPos.z), firstLWheelRota);
	InitWheel(lBWheel, modelHandle, VGet(bWheelPos.x, fWheelPos.y, -fWheelPos.z), firstLWheelRota);
	InitWheel(rBWheel, modelHandle, VGet(bWheelPos.x, fWheelPos.y, fWheelPos.z), firstRWheelRota);
	InitWheel(rFWheel, modelHandle, VGet(-fWheelPos.x, fWheelPos.y, fWheelPos.z), firstRWheelRota);
}

Wheels::~Wheels()
{
	MV1DeleteModel(modelHandle);
	MV1DeleteModel(lFWheel.modelHandle);
	MV1DeleteModel(rFWheel.modelHandle);
	MV1DeleteModel(lBWheel.modelHandle);
	MV1DeleteModel(rBWheel.modelHandle);
}

void Wheels::Draw()
{
	MV1DrawModel(lFWheel.modelHandle);
	MV1DrawModel(rFWheel.modelHandle);
	MV1DrawModel(lBWheel.modelHandle);
	MV1DrawModel(rBWheel.modelHandle);
}

/// <summary>
/// 左右キーを入力したら傾け、上下キーで回転させる
/// </summary>
/// <param name="_Key">入力情報</param>
void Wheels::WheelUpdate(const WheelArgumentCarInfo info)
{
	carInfo = info;
	AllSetWheelMatrix();
	//車が速いとよく回る
	if (carInfo.carSpeed > 0)
	{
		wheelDriveSpeed += -carInfo.carSpeed * wheelDriveRotaPower;
	}
	//タイヤを傾ける処理
	if (UserInput::GetInputState(Right) != Free)
	{		
		isStraightDash = false;
		if (wheelDriveRota < maxWheelRotaY)
		{
			wheelDriveRota += wheelCurvePower;
		}
		else
		{
			wheelDriveRota = maxWheelRotaY;
		}

	}
	else if (UserInput::GetInputState(Left) != Free)
	{		
		isStraightDash = false;
		if (wheelDriveRota > -maxWheelRotaY)
		{
			wheelDriveRota -= wheelCurvePower;
		}
		else
		{
			wheelDriveRota = -maxWheelRotaY;
		}
	}
	//どっちも押されてなかったらタイヤを元に戻す
	else if (fabsf(wheelDriveRota) > rotaCalculationLine)
	{
		wheelDriveRota += wheelDriveRota > 0 ? -wheelCurvePower : wheelCurvePower;
		//ある程度戻ってたら角度を0にする
		if (fabsf(wheelDriveRota) < rotaCalculationLine)
		{
			wheelDriveRota = 0;
		}
		isStraightDash = true;
	}	
}

/// <summary>
/// どの向きに曲がればいいかタンジェントを返すよ
/// </summary>
/// <param name="velocitySize">速さのベクトルの大きさ</param>
/// <returns>負の数ならだったら左</returns>
float Wheels::GetMoveDirTheta(const float velocitySize)
{
	if (wheelDriveRota > rotaCalculationLine)
	{
		return atan2f(velocitySize, GetRotationRadius(firstLWheelRota)); 
	}
	else if (wheelDriveRota < -rotaCalculationLine)
	{
		return -atan2f(velocitySize,GetRotationRadius(firstLWheelRota));
	}
	return 0.0f;
}

void Wheels::AllSetWheelMatrix()
{
	//左前タイヤ
	SetWheelMatrix(lFWheel, wheelDriveSpeed, firstLWheelRota + wheelDriveRota);
	//左後ろタイヤ
	SetWheelMatrix(lBWheel, wheelDriveSpeed, firstLWheelRota);
	//右前タイヤ	
	SetWheelMatrix(rFWheel, -wheelDriveSpeed, firstRWheelRota + wheelDriveRota);
	//右後ろタイヤ
	SetWheelMatrix(rBWheel, -wheelDriveSpeed, firstRWheelRota);
}
/// <summary>
/// 回転するための半径を返す
/// </summary>
/// <param name="firstWheelRota"></param>
/// <returns></returns>
float Wheels::GetRotationRadius(const float firstWheelRota)
{

	if (fabsf(wheelDriveRota) > rotaCalculationLine)
	{
		//タイヤの角度をタンジェントに
		float rota = tan(static_cast<float> (fabsf(wheelDriveRota)) * RAGE);
		//回転半径を出す
		float radius = (fWheelPos.x + bWheelPos.x) / rota;
		//車の向きに後ろタイヤをY軸分回転させる
		VECTOR bWDir = VTransform(carInfo.direction, MGetRotY((firstWheelRota) * RAGE));
		//後ろタイヤの横向きを出す
		bWDir = VNorm(VCross(bWDir, VGet(0, 1, 0)));
		//回転半径の中心座標を出す
		VECTOR circleAxisPos = VScale(bWDir, radius);

		//進行方向を曲げるのに必要な円の半径を出す
		return  VSize(circleAxisPos);
	}
	return 0.0f;
}
/// <summary>
	/// 車から見たタイヤの座標が返ってくる
	/// </summary>
	/// <param name="_wheel"></param>
VECTOR Wheels::WheelGetPos(const Wheel& wheel)
{
	//タイヤの前方方向の位置
	VECTOR between = VScale(carInfo.direction, -wheel.betweenBody.x);
	//タイヤの横方向の位置と足す
	between = VAdd(between, VScale(VCross(carInfo.direction, VGet(0, 1, 0)), -wheel.betweenBody.z));
	//高さを合わせる
	between.y = fWheelPos.y;
	return  between;
}
/// <summary>
	/// タイヤの位置と回転を設定
	/// </summary>
	/// <param name="_wheel">設定したいタイヤ</param>
	/// <param name="_rotaX">タイヤの転がるときの回転</param>
	/// <param name="_rotaY">タイヤの向きがずれるときの回転</param>

void Wheels::SetWheelMatrix(Wheel& wheel, const float rotaX, const float rotaY)
{
	//タイヤの位置を車の向きに合わせる
	MATRIX wheelPos = MMult(carInfo.matrix, MGetTranslate(WheelGetPos(wheel)));

	MATRIX wheelRota = MMult(MGetRotX(rotaX * RAGE), MGetRotY(rotaY * RAGE));
	wheel.matrix = MMult(wheelRota, wheelPos);
	MV1SetMatrix(wheel.modelHandle, wheel.matrix);
}
/// <summary>
/// タイヤの初期化
/// </summary>
/// <param name="_Wheel">初期化したいタイヤ</param>
/// <param name="_ModelHandle">タイヤのモデル</param>
/// <param name="_Pos">車から見た位置</param>
/// <param name="_Rota">回転角</param>
void Wheels::InitWheel(Wheel& wheel, int DuplicateSourceModel, VECTOR pos, float rota)
{
	wheel.modelHandle = MV1DuplicateModel(DuplicateSourceModel);
	wheel.betweenBody = pos;
	VECTOR wheelPos = WheelGetPos(wheel);
	MATRIX bodyMat = MV1GetMatrix(DuplicateSourceModel);

	wheel.matrix = MMult(MGetRotY(rota * RAGE), MMult(bodyMat, MGetTranslate(wheelPos)));
	MV1SetMatrix(wheel.modelHandle, wheel.matrix);
}