#pragma once
#include <string>

constexpr int HeightMax = 10;
constexpr int WidthMax = 100;

enum class BlockType
{
    NORMAL,
    BLOCK,
};

class level
{
public:

    level(int BlockHeight, int BlockWidth);
    ~level();

    bool LoadMapFile(const char* file_path);
  
private:
    int m_BlockArray[HeightMax][WidthMax];

    constexpr int m_BlockHeight{},m_BlockWidth{};
};

