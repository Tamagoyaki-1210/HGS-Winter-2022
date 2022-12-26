#pragma once
#include <string>

constexpr int HeightMax = 11;
constexpr int WidthMax = 100;

enum class BlockType
{
    NORMAL,
    BLOCK,
};

class CLevel
{
public:

    CLevel(int BlockHeight, int BlockWidth);
    ~CLevel();

    bool LoadMapFile(const char* file_path);
  
private:
    int m_BlockArray[HeightMax][WidthMax];

    int m_BlockHeight{},m_BlockWidth{};
};

