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
            // 첫번째 클릭과 두번째 클릭을 했을 경우 일종의 쿨타임
            if(firstClicked != null && secondClicked != null)
            {
                return;
            }

            // as 연산자: 형변환이 가능하면 형변환을 수행하고, 그렇지 않으면 null값을 대입합니다.
            Label clickedLabel = sender as Label;
            if(clickedLabel != null)
            {
                if(clickedLabel.ForeColor == null)
                {
                    return;
                }

                if(clickedLabel.ForeColor == Color.Black)
                {
                    return;
                }

                // 첫번째 클릭이 없다면 첫번째 클릭을 등록합니다.
                if(firstClicked == null)
                {
                    firstClicked = clickedLabel;
                    firstClicked.ForeColor = Color.Black;
                    return;
                }

                // 두번째 클릭을 등록합니다.
                secondClicked = clickedLabel;
                secondClicked.ForeColor = Color.Black;

                CheckForWinner();

                // 첫번째 클릭돠 두번째 클릭이 같을 경우
                if(firstClicked.Text == secondClicked.Text)
                {
                    firstClicked = null;
                    secondClicked = null;
                }
                else
                {
                    timer1.Start();
                }
            }
        }

        private void CheckForWinner()
        {
            Label label;
            for(int i =0; i<tableLayoutPanel1.Controls.Count; i++)
            {
                label = tableLayoutPanel1.Controls[i] as Label;
                if (label != null && label.ForeColor == label.BackColor)
                {
                    return;
                }
            }

            MessageBox.Show("You Win!!");
            Close();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            timer1.Stop();

            firstClicked.ForeColor = firstClicked.BackColor;
            secondClicked.ForeColor = secondClicked.BackColor;

            firstClicked = null;
            secondClicked = null;
        }
    }
}
