#pragma once
#include <vector>
#include <string>

enum LoadData
{
    stage,
    challenge
};

class CSVFileLoader
{
public:
    CSVFileLoader(std::string fileName);
    ~CSVFileLoader();
    std::vector <std::string> GetLoadStringData();
    std::vector <const char*> GetLoadCharData();
    int GetLineCount();
private:
    void Split(std::string& input, char delimiter);
    std::vector <std::string> loadData;
    int lineCount;
};

