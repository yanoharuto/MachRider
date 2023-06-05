#include "CSVFileLoader.h"
#include <fstream>
#include <sstream>

using namespace std;
CSVFileLoader::CSVFileLoader(std::string fileName)
{
    lineCount = 0;
    ifstream ifs(fileName.c_str());

    string line;
    while (getline(ifs, line)) 
    {
        lineCount++;
        Split(line, ',');
    }

}

CSVFileLoader::~CSVFileLoader()
{
}

std::vector<std::string> CSVFileLoader::GetLoadStringData()
{
    return loadData;
}

std::vector<const char*> CSVFileLoader::GetLoadCharData()
{
    std::vector<const char*> charVec;
    for (int i = 0; i < loadData.size(); i++)
    {
        charVec.push_back(loadData[i].c_str());
    }
    return charVec;
}

int CSVFileLoader::GetLineCount()
{
    return lineCount;
}

void CSVFileLoader::Split(std::string& input, char delimiter)
{
    istringstream stream(input);
    string field;
    while (getline(stream, field, delimiter)) {
        loadData.push_back(field);
    }
}
