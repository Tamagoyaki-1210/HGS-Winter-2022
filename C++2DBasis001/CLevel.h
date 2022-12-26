#pragma once
constexpr float BlockSize = 40.f;

constexpr int HeightMax = 18;
constexpr int WidthMax = 160;

class CLevel
{
public:

    CLevel();
    ~CLevel();

    bool LoadMapFile(const char* file_path);
  
private:
    int m_BlockArray[HeightMax][WidthMax];

    float m_BlockHeight{},m_BlockWidth{};
};

