#include "CPU.h"
#include "Utility.h"
#include "Utility.h"
#include "FlyShipKind.h"
CPU::CPU()
{
}

CPU::CPU(VECTOR firstPos)
{
    car = new CPUCar(firstPos, VGet(1.0f,0,0));

}

CPU::~CPU()
{
}

void CPU::Update()
{
    //���̃`�F�b�N�|�C���g�̍X�V
    HitCheckExamineObjectInfo carInfo;
    carInfo.SetExamineInfo(car);
}