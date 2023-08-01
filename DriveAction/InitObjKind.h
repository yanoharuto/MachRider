#pragma once
namespace ObjectInit
{
    /// <summary>
    /// ����������I�u�W�F�N�g�̎��
    /// </summary>
    enum InitObjKind
    {
        //�v���C���[�@
        player = 2,
        //�傫����
        moveSaw = 5,
        //��]�ۋ�
        saw = 8,
        //�����@
        bomberShip = 11,
        //���e
        bomber = 14,
        //�㉺�Ƀ��[�U�[����s�D
        upDownLaserShip = 17,
        //�~��ɕ��ԋ@��
        circleLaserShip = 20,
        //����背�[�U�[
        littleRadiusLaser = 23,
        //���背�[�U�[
        bigRadiusLaser = 26,
        //�^�C��
        wheel = 29,
        //�R�C��
        collect = 32,
        //��
        stageFloor = 35,
        //�X�J�C�h�[��
        skyDome = 38,
        //�X�e�[�W�̊O�ɏo�Ȃ��悤�ɂ����
        wall = 41
    };
}