using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Minesweeper
{
    class BlockManager
    {
        // 최대 지뢰 개수
        private const int maxMineCount = 10;
        public int MaxMinCount
        {
            get
            {
                return maxMineCount;
            }
        }

        private Block[,] blocks = new Block[9, 9];
        public Block[,] GetBlocks()
        {
            return blocks;
        }
        public Block GetBlock(int x, int y)
        {
            return blocks[x, y];
        }

        // 랜덤 클래스
        Random random = new Random();

        public void InitBlock()
        {
            for(int i = 0; i < blocks.GetLength(0); i++)
            {
                for(int j = 0; j < blocks.GetLength(1); j++)
                {
                    SafeBlock tmpBlock = new SafeBlock();
                    tmpBlock.Init();
                    blocks[i, j] = tmpBlock;
                }
            }

            SetMine();
        }

        // 지뢰 블록 설정
        private void SetMine()
        {
            int count = 0;

            while(count < maxMineCount)
            {
                int randomX= random.Next(blocks.GetLength(0));
                int randomY = random.Next(blocks.GetLength(1));

                // 지뢰가 아닌 경우
                if(blocks[randomX, randomY].BlockType != BLOCKTYPE.MINE)
                {
                    MineBlock tmpMine = new MineBlock();
                    tmpMine.Init();
                    blocks[randomX, randomY] = tmpMine;
                    count++;
                }
            }
        }

        private void CheckMine(int blockIndex)
        {
        }

        public void OpenBlock(int x, int y)
        {
            if (blocks[x, y].BlockType == BLOCKTYPE.SAFE)
            {
                blocks[x, y].BlockIsOpen();
            }
        }
    }
}
