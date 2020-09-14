using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Minesweeper
{
    // 블록을 나타내는 열거형
    enum BLOCKTYPE
    {
        NONE,
        SAFE,
        MINE
    }

    class Block
    {
        protected bool bIsOpen;
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

        protected bool bIsFlag;
        public bool IsFlag
        {
            get
            {
                return bIsFlag;
            }
            set
            {
                bIsFlag = value;
            }
        }

        protected BLOCKTYPE eBlockType;
        public BLOCKTYPE BlockType
        {
            get
            {
                return eBlockType;
            }
            set
            {
                eBlockType = value;
            }
        }

        protected Image blockImage;
        public Image BlockImage
        {
            get
            {
                return blockImage;
            }
        }
        protected Image flagImage;
        public Image FlagImage
        {
            get
            {
                return flagImage;
            }
        }

        public void Init()
        {
            bIsOpen = false;
            eBlockType = BLOCKTYPE.NONE;
            blockImage = Image.FromFile("block.bmp");
            flagImage = Image.FromFile("flag.bmp");
        }

        public void BlockIsOpen()
        {
            bIsOpen = true;
            bIsFlag = false;
        }
    }

    class MineBlock : Block
    {
        private Image mineImage;
        public Image MineImage
        {
            get
            {
                return mineImage;
            }
        }

        public void Init()
        {
            base.Init();
            eBlockType = BLOCKTYPE.MINE;
            mineImage = Image.FromFile("mine.bmp");
        }
    }

    class SafeBlock : Block
    {
        private Image numImage;
        public Image NumImage
        {
            get
            {
                return numImage;
            }
        }

        private int mineCount;
        public int MineCount
        {
            get
            {
                return mineCount;
            }
        }
        public void IncreaseMineCount()
        {
            mineCount++;
        }

        public void Init()
        {
            base.Init();
            mineCount = 0;
        }

        public void SetNumBlock()
        {
            string numBlock = String.Format("block_{0}.bmp", mineCount);
            numImage = Image.FromFile(numBlock);
        }
    }
}
