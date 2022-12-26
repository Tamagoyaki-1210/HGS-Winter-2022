#include "CLevel.h"
#include "cstdio"
#include "block.h"

CLevel::CLevel()
    : m_BlockHeight(BlockSize / 2.f), m_BlockWidth(BlockSize / 2.f)
{
}

CLevel::~CLevel()
{
	//delete m_BlockArray;
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
               // CBlock::Create(D3DXVECTOR3(m_BlockWidth + (BlockSize * nCntMapW), m_BlockHeight + (BlockSize * nCntMapH), 0.f), D3DXVECTOR2(m_BlockWidth * 2, m_BlockHeight * 2), CBlock::NORMAL);
                break;

            case 1:
				CBlock::Create(D3DXVECTOR3(m_BlockWidth + (BlockSize * nCntMapW), m_BlockHeight + (BlockSize * nCntMapH), 0.f), D3DXVECTOR2(m_BlockWidth * 2, m_BlockHeight * 2), CBlock::BLOCK);
                break;

			case 2:
				CBlock::Create(D3DXVECTOR3(m_BlockWidth + (BlockSize * nCntMapW), m_BlockHeight + (BlockSize * nCntMapH), 0.f), D3DXVECTOR2(m_BlockWidth * 2, m_BlockHeight * 2), CBlock::GOAL);
				break;

			case 3:
				CBlock::Create(D3DXVECTOR3(m_BlockWidth + (BlockSize * nCntMapW), m_BlockHeight + (BlockSize * nCntMapH), 0.f), D3DXVECTOR2(m_BlockWidth * 2, m_BlockHeight * 2), CBlock::THORN);
				break;
			case 4:
				CBlock::Create(D3DXVECTOR3(m_BlockWidth + (BlockSize * nCntMapW), m_BlockHeight + (BlockSize * nCntMapH), 0.f), D3DXVECTOR2(m_BlockWidth * 2, m_BlockHeight * 2), CBlock::UPBLOCK);
				break;

			case 5:
				CBlock::Create(D3DXVECTOR3(m_BlockWidth + (BlockSize * nCntMapW), m_BlockHeight + (BlockSize * nCntMapH), 0.f), D3DXVECTOR2(m_BlockWidth * 2, m_BlockHeight * 2), CBlock::DOWNBLOCK);
				break;

			case 6:
				CBlock::Create(D3DXVECTOR3(m_BlockWidth + (BlockSize * nCntMapW), m_BlockHeight + (BlockSize * nCntMapH), 0.f), D3DXVECTOR2(m_BlockWidth * 2, m_BlockHeight * 2), CBlock::WOODCRATE);
				break;
            default:
                break;
            }
        }
    }
}
