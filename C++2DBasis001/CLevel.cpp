#include "CLevel.h"
#include "cstdio"
#include "block.h"

CLevel::CLevel()
{
    m_BlockWidth = BlockSize / 2;
    m_BlockHeight = BlockSize / 2;
}

CLevel::~CLevel()
{
}

bool CLevel::LoadMapFile(const char* file_path)
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
            case 0:
                CBlock::Create(
                    D3DXVECTOR3(m_BlockWidth + (m_BlockWidth * nCntMapW), m_BlockHeight + (m_BlockHeight * nCntMapH), 0.f),
                    D3DXVECTOR2(m_BlockWidth * 2, m_BlockHeight * 2));
                break;

            case 1:
                break;

            default:
                break;
            }
        }
    }
}
