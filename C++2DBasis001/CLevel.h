#pragma once
#include <string>

constexpr int HeightMax = 10;
constexpr int WidthMax = 100;

enum class BlockType
{
    NORMAL,
    BLOCK,
};

class CLevel
{
public:

    CLevel(float BlockHeight, float BlockWidth);
    ~CLevel();

    bool LoadMapFile(const char* file_path);
  
private:
    int m_BlockArray[HeightMax - 1][WidthMax - 1];

    float m_BlockHeight{},m_BlockWidth{};
};

