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
        private int MineCount;

        public Minsweeper()
        {
            InitializeComponent();

            Init();
        }

        public void Init()
        {
            MineCount = 10;
        }
    }
}
