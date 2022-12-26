#pragma once
#include <string>

constexpr float BlockSize = 40.f;

constexpr int HeightMax = 16;
constexpr int WidthMax = 128;

class CLevel
{
public:

    CLevel();
    ~CLevel();

    bool LoadMapFile(const char* file_path);
  
private:
    int m_BlockArray[HeightMax - 1][WidthMax - 1];

    float m_BlockHeight{},m_BlockWidth{};
};

