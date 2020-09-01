using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MatchGame
{
    public partial class MatchGame : Form
    {
        // 랜덤 클래스
        Random random = new Random();

        List<string> cards = new List<string>()
        {
            "!", "!", "N", "N", ",", ",", "k", "k",
        "b", "b", "v", "v", "w", "w", "z", "z",
        "a", "a","c","c"
        };

        //List<Image> cards = new List<Image>()
        //{
        //    Image.FromFile("00.bmp"), Image.FromFile("00.bmp"),
        //    Image.FromFile("01.bmp"), Image.FromFile("01.bmp"),
        //    Image.FromFile("02.bmp"), Image.FromFile("02.bmp"),
        //    Image.FromFile("03.bmp"), Image.FromFile("03.bmp"),
        //    Image.FromFile("04.bmp"), Image.FromFile("04.bmp"),
        //    Image.FromFile("05.bmp"), Image.FromFile("05.bmp"),
        //    Image.FromFile("06.bmp"), Image.FromFile("06.bmp"),
        //    Image.FromFile("07.bmp"), Image.FromFile("07.bmp"),
        //    Image.FromFile("08.bmp"), Image.FromFile("08.bmp"),
        //    Image.FromFile("09.bmp"), Image.FromFile("09.bmp"),
        //};

        Label firstClicked = null;
        Label secondClicked = null;

        // 생성자
        public MatchGame()
        {
            InitializeComponent();

            AssignCardToSquares();
        }

        // 카드를 등록합니다.
        public void AssignCardToSquares()
        {
            foreach (Control control in tableLayoutPanel1.Controls)
            {
                // as 연산자: 형변환이 가능하면 형변환을 수행하고, 그렇지 않으면 null값을 대입합니다.
                Label cardLabel = control as Label;
                if (cardLabel != null)
                {
                    int randomNumber = random.Next(cards.Count);
                    //cardLabel.Image = cards[randomNumber];
                    cardLabel.Text = cards[randomNumber];
                    cardLabel.ForeColor = cardLabel.BackColor;
                    cards.RemoveAt(randomNumber);
                }
            }
        }

        private void Label_Click(object sender, EventArgs e)
        {
            // as 연산자: 형변환이 가능하면 형변환을 수행하고, 그렇지 않으면 null값을 대입합니다.
            Label clickedLabel = sender as Label;
            if(clickedLabel != null)
            {
                if(clickedLabel.ForeColor == Color.Black)
                {
                    return;
                }

                clickedLabel.ForeColor = Color.Black;
            }
        }
    }
}
