#include "Utility.h"
#include "CreatePosAndDirData.h"
#include "OriginalMath.h"
CreatePosAndDirData::CreatePosAndDirData()
{
    dirDataCreator = new VectorDataCreator(dirFileName);
    posDataCreator = new VectorDataCreator(posFileName);
}

CreatePosAndDirData::~CreatePosAndDirData()
{
    SAFE_DELETE(dirDataCreator);
    SAFE_DELETE(posDataCreator);
}

void CreatePosAndDirData::WriteWhereToTurn(VECTOR pos, VECTOR dir)
{

    float angular = OriginalMath::GetDegreeMisalignment(prevVec, dir);
    //‹È‚ª‚Á‚Ä‚¢‚éêŠ‚ð‹L˜^‚·‚é
    if (angular > turnProccesLine)
    {
        WritePosAndDir(pos, dir);
        prevVec = dir;
    }
}

void CreatePosAndDirData::WritePosAndDir(VECTOR pos, VECTOR dir)
{
#ifdef _DEBUG
    dirDataCreator->WriteVECTOR(dir);
    posDataCreator->WriteVECTOR(pos);
#endif
}