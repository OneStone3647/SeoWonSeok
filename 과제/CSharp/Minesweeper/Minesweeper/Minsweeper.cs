using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Minesweeper
{
    public partial class Minsweeper : Form
    {
        private BlockManager blockManager = new BlockManager();
  
        public Minsweeper()
        {
            InitializeComponent();

            Init();
        }

        public void Init()
        {
            blockManager.InitBlock();

            DrawBlock();
        }

        public void DrawBlock()
        {
            foreach(Control control in tableLayoutPanel1.Controls)
            {
                Label blockLabel = control as Label;
                if(blockLabel != null)
                {
                    blockLabel.Image = blockManager.GetBlock(blockLabel.TabIndex).BlockImage;
                }
            }
        }

        private void Label_Click(object sender, EventArgs e)
        {
            Label clickedLabel = sender as Label;
            if (clickedLabel != null)
            {
                Block tmpBlock = blockManager.GetBlock(clickedLabel.TabIndex);
                if (tmpBlock.IsOpen != true)
                {
                    tmpBlock.IsOpen = true;
                    if(tmpBlock.BlockType == BLOCKTYPE.MINE)
                    {
                        MineBlock mine = tmpBlock as MineBlock;
                        clickedLabel.Image = mine.MineImage;
                    }
                    else
                    {
                        SafeBlock safe = tmpBlock as SafeBlock;
                        clickedLabel.Image = safe.NumImage;
                    }
                }
            }
        }
    }
}
