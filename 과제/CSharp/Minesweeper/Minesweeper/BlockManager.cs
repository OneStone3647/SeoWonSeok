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
        BLOCKNUM_0 = 0,
        BLOCKNUM_1,
        BLOCKNUM_2,
        BLOCKNUM_3,
        BLOCKNUM_4,
        BLOCKNUM_5,
        BLOCKNUM_6,
        BLOCKNUM_7,
        BLOCKNUM_8,
        BLOCKNUM_BLOCK,
        BLOCKNUM_FLAG,
        BLOCKNUM_MINE
    }

    struct Block
    {
        bool IsOpen;
        int BlockNum;
    }

    class BlockManager
    {
        // 최대 지뢰 개수
        private const int MaxMineCount = 10;

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

        private void InitBlock()
        {
            List<int> MineBlockList = new List<int>();
            MineBlockList.Add(random.Next(Blocks.Count()));
            while (true)
            {
                int randomNumber = random.Next(Blocks.Count());
                int count = 0;
                foreach(int num in MineBlockList)
                {
                    if(randomNumber != num)
                    {
                        count++;
                    }

                    if(MineBlockList.Count == count)
                    {
                        MineBlockList.Add(randomNumber);
                    }

                }
            }
        }
    }
}
