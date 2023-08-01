#include "PlayerViewer.h"
#include "DxLib.h"
#include "OriginalMath.h"
#include "PlayerCar.h"
/// <summary>
	/// �v���C���[�̋@�̂̌X���ȂǂɑΉ�����Viewer
	/// </summary>
PlayerViewer::PlayerViewer()
	:ModelViewer(ObjectInit::player)
{
}
/// <summary>
/// �v���C���[�̊p�x�ɍ��킹�ĉ�]����
/// </summary>
/// <param name="drawObj"></param>
void PlayerViewer::Draw(PlayerCar* drawObj) const
{
    //�`�悷�郂�f�����Ȃ��Ȃ�I��
    if (modelHandle == -1)return;
    //�ύX�O�̍s���ۑ�
    MATRIX tmpMat = MV1GetMatrix(modelHandle);
    //������ς���
    ModelSetMatrix(drawObj);
    // �RD���f���̃|�W�V�����ݒ�
    MV1SetPosition(modelHandle, drawObj->GetPos());
    float mSize = drawObj->GetModelSize();
    //�T�C�Y�ύX
    MV1SetScale(modelHandle, VGet(mSize, mSize, mSize));
    MV1DrawModel(modelHandle);
    //�s������ɖ߂�
    MV1SetRotationMatrix(modelHandle, tmpMat);
}

/// <summary>
/// �`�惂�f���̍s����Z�b�g
/// </summary>
void PlayerViewer::ModelSetMatrix(PlayerCar* player) const
{
    //�v���C���[�̊p�x��������Ă���
	VECTOR playerRota = player->GetModelRotateVec();
	
	// �����ɍ��킹�ĉ�].
	MV1SetRotationZYAxis(modelHandle, player->GetDir(), VGet(0.0f, 1.0f, 0.0f), playerRota.z);
	// ���f���Ɍ����Ăق��������ɉ�].
	MATRIX tmpMat = MV1GetMatrix(modelHandle);
	MATRIX rotYMat = MGetRotY((180.0f + playerRota.y) * RAGE);
	tmpMat = MMult(tmpMat, rotYMat);
	MV1SetRotationMatrix(modelHandle, tmpMat);
}
