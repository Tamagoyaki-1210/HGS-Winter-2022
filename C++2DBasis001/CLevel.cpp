#include "CLevel.h"
#include "cstdio"
#include "block.h"

CLevel::CLevel(int BlockHeight, int BlockWidth)
    :m_BlockHeight(BlockHeight), m_BlockWidth(BlockWidth)
{
}

CLevel::~CLevel()
{
}

bool CLevel::LoadMapFile(const char* file_path)
{
    //�t�@�C����ǂݍ��݃��[�h�ŊJ��
    FILE* pFile = fopen(file_path, "r");

    if (pFile != nullptr)
    {
        //�t�@�C�����J�����ꍇ
        for (int nCntMapH = 0; nCntMapH < HeightMax; nCntMapH++)
        {
            for (int nCntMapW = 0; nCntMapW < WidthMax; nCntMapW++)
            {
                fscanf(pFile, "%d", &m_BlockArray[nCntMapH][nCntMapW]);
            }
        }
    }

    //�t�@�C�������
    fclose(pFile);

    //�t�@�C���I�[�v���Ɏ��s�����ꍇ
    if (pFile == nullptr)
    {
        //�I��
        return false;
    }

    //�c���̐��l�����炷����
    for (int nCntMapH = 0; nCntMapH < HeightMax; nCntMapH++)
    {
        //�����̐��l�����炷����
        for (int nCntMapW = 0; nCntMapW < WidthMax; nCntMapW++)
        {
            switch (m_BlockArray[nCntMapH][nCntMapW])
            {
            //�u���b�N�̐ݒu	
            case 0:
				CBlock::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100.0f, 0.0f), D3DXVECTOR2(300, 60));
                break;

            case 1:
                break;

            default:
                break;
            }
        }
    }
}
