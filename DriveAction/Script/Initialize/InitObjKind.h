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
        //���[�U�[
        laser = 23,
        //�R�C��
        collect = 26,
        //��
        stageFloor = 29,
        //�X�J�C�h�[��
        skyDome = 32,
        //�X�e�[�W�̊O�ɏo�Ȃ��悤�ɂ����
        wall = 35
    };
}