#include "Racer.h"
#include "Car.h"

#include "HitChecker.h"
#include"Utility.h"
#include "OriginalMath.h"
Racer::Racer()
{
}

Racer::~Racer()
{

}

void Racer::Update()
{


}


void Racer::Draw()
{
    car->Draw();
}

void Racer::UpDown()
{
    car->UpDown();
}
