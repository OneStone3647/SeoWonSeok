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
        protected bool m_bIsOpen;
        public bool bIsOpen
        {
            get
            {
                return m_bIsOpen;
            }
            set
            {
                m_bIsOpen = value;
            }
        }

        protected bool m_bIsFlag;
        public bool bIsFlag
        {
            get
            {
                return m_bIsFlag;
            }
            set
            {
                m_bIsFlag = value;
            }
        }

        protected BLOCKTYPE m_eBlockType;
        public BLOCKTYPE BlockType
        {
            get
            {
                return m_eBlockType;
            }
            set
            {
                m_eBlockType = value;
            }
        }

        protected Image   m_BlockImage;
        protected Image   m_FlagImage;

        public void Init()
        {
            m_bIsOpen = false;
            m_eBlockType = BLOCKTYPE.NONE;
            m_BlockImage = Image.FromFile("block.bmp");
            m_FlagImage = Image.FromFile("flag.bmp");
        }

        public void IsOpen()
        {
            m_bIsOpen = true;
            m_bIsFlag = false;
        }
    }

    class MineBlock : Block
    {
        private Image m_MineImage;
        public Image MineImage
        {
            get
            {
                return m_MineImage;
            }
        }

        public void Init()
        {
            m_eBlockType = BLOCKTYPE.MINE;
            m_MineImage = Image.FromFile("mine.bmp");
        }
    }

    class SafeBlock : Block
    {
        private Image m_NumBlock;
        public Image NumBlock
        {
            get
            {
                return m_NumBlock;
            }
        }

        private int m_MineCount;
        public int MineCount
        {
            get
            {
                return m_MineCount;
            }
        }
        public void IncreaseMineCount()
        {
            m_MineCount++;
        }

        public void Init()
        {
            m_MineCount = 0;            
        }

        public void SetNumBlock()
        {
            string numBlock = String.Format("block_{0}.bmp", m_MineCount);
            m_NumBlock = Image.FromFile(numBlock);
        }
    }
}
