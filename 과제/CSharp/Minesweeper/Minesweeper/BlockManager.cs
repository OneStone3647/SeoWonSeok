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

        private Block[] blocks = new Block[81];
        public Block GetBlock(int index)
        {
            return blocks[index];
        }

        // 랜덤 클래스
        Random random = new Random();

        public void InitBlock()
        {
            for(int i =0; i < blocks.Count(); i++)
            {
                SafeBlock tmpBlock = new SafeBlock();
                tmpBlock.Init();
                blocks[i] = tmpBlock;
            }

            SetMine();
        }

        // 지뢰 블록 설정
        private void SetMine()
        {
            int count = 0;

            while(count < maxMineCount)
            {
                int randomNumber = random.Next(blocks.Count());

                // 지뢰가 아닌 경우
                if(blocks[randomNumber].BlockType != BLOCKTYPE.MINE)
                {
                    MineBlock tmpMine = new MineBlock();
                    tmpMine.Init();
                    blocks[randomNumber] = tmpMine;
                    count++;
                }
            }
        }
    }
}
