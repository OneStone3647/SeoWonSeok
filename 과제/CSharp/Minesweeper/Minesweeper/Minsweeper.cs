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
        }

        public void DrawBlock()
        {
            int count = 0;
            foreach(Control control in tableLayoutPanel1.Controls)
            {
                Label blockLabel = control as Label;
                if(blockLabel != null)
                {
                    
                }
            }
        }
    }
}
