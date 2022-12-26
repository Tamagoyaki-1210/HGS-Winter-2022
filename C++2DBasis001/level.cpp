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
