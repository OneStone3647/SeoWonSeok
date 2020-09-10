using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Minesweeper
{
    enum BLOCKNUM
    {
        NUM_0 = 0,
        NUM_1,
        NUM_2,
        NUM_3,
        NUM_4,
        NUM_5,
        NUM_6,
        NUM_7,
        NUM_8,
        BLOCK,
        FLAG,
        MINE
    }

    class BlockManager
    {
        // 최대 지뢰 개수
        private const int MaxMineCount = 10;
        public int maxMinCount
        {
            get
            {
                return MaxMineCount;
            }
        }

        private Block[] Blocks = new Block[81];
        
        private Image[] BlockImage = new Image[12]
        {
            Image.FromFile("block_0.bmp"),
            Image.FromFile("block_1.bmp"),
            Image.FromFile("block_2.bmp"),
            Image.FromFile("block_3.bmp"),
            Image.FromFile("block_4.bmp"),
            Image.FromFile("block_5.bmp"),
            Image.FromFile("block_6.bmp"),
            Image.FromFile("block_7.bmp"),
            Image.FromFile("block_8.bmp"),
            Image.FromFile("block.bmp"),
            Image.FromFile("flag.bmp"),
            Image.FromFile("mine.bmp")
        };

        // 랜덤 클래스
        Random random = new Random();

        public void InitBlock()
        {
            for(int i =0; i < Blocks.Count(); i++)
            {
                Block tmpBlock = new Block(false, (int)BLOCKNUM.BLOCK);
                Blocks[i] = tmpBlock;
            }

            SetMine();
        }

        // 지뢰 블록 설정
        private void SetMine()
        {
            List<int> MineBlockList = new List<int>();
            MineBlockList.Add(random.Next(Blocks.Count()));

            while (true)
            {
                int count = 0;
                int randomNumber = random.Next(Blocks.Count());
                for (int i = 0; i < MineBlockList.Count; i++)
                {
                    if (MineBlockList[i] == randomNumber)
                    {
                        break;
                    }
                    else
                    {
                        count++;

                        if (MineBlockList.Count == count)
                        {
                            MineBlockList.Add(randomNumber);
                        }
                    }

                    if (count + 1 == MaxMineCount)
                    {
                        for (int j = 0; j < MineBlockList.Count; j++)
                        {
                            Blocks[MineBlockList[j]].BlockNum = (int)BLOCKNUM.MINE;
                        }
                        return;
                    }
                }
            }
        }
    }
}
