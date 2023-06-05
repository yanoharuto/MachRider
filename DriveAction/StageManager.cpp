#include "StageManager.h"
#include "Utility.h"
#include "CircuitTrack.h"
#include "SkyDome.h"
#include "CSVFileLoader.h"
#include "FirstPositionGetter.h"

StageManager::StageManager()
{
    firstPositionGeneratetor = new FirstPositionGetter();
    circuit = new CircuitTrack(firstPositionGeneratetor);
    skyDome = new SkyDome();
}


StageManager::~StageManager()
{
    SAFE_DELETE(circuit);
    SAFE_DELETE(skyDome);

}

void StageManager::Update()
{
    skyDome->Update();
}

void StageManager::Draw() const
{
    circuit->Draw();
    skyDome->Draw();

}
