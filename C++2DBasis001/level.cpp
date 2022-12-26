#include "level.h"
#include "cstdio"


level::level(int BlockHeight, int BlockWidth)
    :m_BlockHeight(BlockHeight), m_BlockWidth(BlockWidth)
{
}

level::~level()
{
}

bool level::LoadMapFile(const char* file_path)
{
    //ファイルを読み込みモードで開く
    FILE* pFile = fopen(file_path, "r");

    if (pFile != nullptr)
    {
        //ファイルが開いた場合
        for (int nCntMapH = 0; nCntMapH < HeightMax; nCntMapH++)
        {
            for (int nCntMapW = 0; nCntMapW < WidthMax; nCntMapW++)
            {
                fscanf(pFile, "%d", &m_BlockArray[nCntMapH][nCntMapW]);
            }
        }
    }

    //ファイルを閉じる
    fclose(pFile);

    //ファイルオープンに失敗した場合
    if (pFile == nullptr)
    {
        //終了
        return false;
    }

    //縦軸の数値をずらす処理
    for (int nCntMapH = 0; nCntMapH < HeightMax; nCntMapH++)
    {
        //横軸の数値をずらす処理
        for (int nCntMapW = 0; nCntMapW < WidthMax; nCntMapW++)
        {
            switch (m_BlockArray[nCntMapH][nCntMapW])
            {
            //ブロックの設置	
            case BlockType::NORMAL:

                break;

            case BlockType::BLOCK:
                break;

            default:
                break;
            }
        }
    }
}
