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
        private const int MaxMineCount = 10;
        public int maxMinCount
        {
            get
            {
                return MaxMineCount;
            }
        }

        private Block[] Blocks = new Block[81];


        // 랜덤 클래스
        Random random = new Random();

        public void InitBlock()
        {
            for(int i =0; i < Blocks.Count(); i++)
            {
                Block tmpBlock = new Block();
                tmpBlock.Init();
                Blocks[i] = tmpBlock;
            }

            SetMine();
        }

        // 지뢰 블록 설정
        private void SetMine()
        {
            int count = 0;

            while(count < MaxMineCount)
            {
                int randomNumber = random.Next(Blocks.Count());

                // 지뢰가 아닌 경우
                if(Blocks[randomNumber].BlockType != BLOCKTYPE.MINE)
                {
                    Blocks[randomNumber].BlockType = BLOCKTYPE.MINE;
                    count++;
                }
            }

            //List<int> MineBlockList = new List<int>();
            //MineBlockList.Add(random.Next(Blocks.Count()));

            //while (true)
            //{
            //    int count = 0;
            //    int randomNumber = random.Next(Blocks.Count());
            //    for (int i = 0; i < MineBlockList.Count; i++)
            //    {
            //        if (MineBlockList[i] == randomNumber)
            //        {
            //            break;
            //        }
            //        else
            //        {
            //            count++;

            //            if (MineBlockList.Count == count)
            //            {
            //                MineBlockList.Add(randomNumber);
            //            }
            //        }

            //        if (count + 1 == MaxMineCount)
            //        {
            //            for (int j = 0; j < MineBlockList.Count; j++)
            //            {
            //                Blocks[MineBlockList[j]].BlockNum = (int)BLOCKNUM.MINE;
            //            }
            //            return;
            //        }
            //    }
            //}
        }
    }
}
