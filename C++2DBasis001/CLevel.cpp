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
