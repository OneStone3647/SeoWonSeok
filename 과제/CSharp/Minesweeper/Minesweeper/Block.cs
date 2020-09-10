using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Minesweeper
{
    class Block
    {
        private bool bIsOpen;
        private int blockNum;

        public bool IsOpen
        {
            get
            {
                return bIsOpen;
            }
            set
            {
                bIsOpen = value;
            }
        }

        public int BlockNum
        {
            get
            {
                return blockNum;
            }
            set
            {
                blockNum = value;
            }
        }

        public Block(bool bIsOpen, int BlockNum)
        {
            this.bIsOpen = bIsOpen;
            this.blockNum = BlockNum;
        }
    }
}
