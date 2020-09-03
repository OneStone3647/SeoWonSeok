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

        // 등록할 카드 리스트
        List<Card> tmpCardList = new List<Card>()
        {
            new Card(false, "Dog", Image.FromFile("00.bmp"), Image.FromFile("back.bmp")),
            new Card(false, "Dog", Image.FromFile("00.bmp"), Image.FromFile("back.bmp")),
            new Card(false, "Tiger", Image.FromFile("01.bmp"), Image.FromFile("back.bmp")),
            new Card(false, "Tiger", Image.FromFile("01.bmp"), Image.FromFile("back.bmp")),
            new Card(false, "Dock", Image.FromFile("02.bmp"), Image.FromFile("back.bmp")),
            new Card(false, "Dock", Image.FromFile("02.bmp"), Image.FromFile("back.bmp")),
            new Card(false, "Elephant", Image.FromFile("03.bmp"), Image.FromFile("back.bmp")),
            new Card(false, "Elephant", Image.FromFile("03.bmp"), Image.FromFile("back.bmp")),
            new Card(false, "Bull", Image.FromFile("04.bmp"), Image.FromFile("back.bmp")),
            new Card(false, "Bull", Image.FromFile("04.bmp"), Image.FromFile("back.bmp")),
            new Card(false, "Horse", Image.FromFile("05.bmp"), Image.FromFile("back.bmp")),
            new Card(false, "Horse", Image.FromFile("05.bmp"), Image.FromFile("back.bmp")),
            new Card(false, "Cat", Image.FromFile("06.bmp"), Image.FromFile("back.bmp")),
            new Card(false, "Cat", Image.FromFile("06.bmp"), Image.FromFile("back.bmp")),
            new Card(false, "Monkey", Image.FromFile("07.bmp"), Image.FromFile("back.bmp")),
            new Card(false, "Monkey", Image.FromFile("07.bmp"), Image.FromFile("back.bmp")),
            new Card(false, "Frog", Image.FromFile("08.bmp"), Image.FromFile("back.bmp")),
            new Card(false, "Frog", Image.FromFile("08.bmp"), Image.FromFile("back.bmp")),
            new Card(false, "Chicken", Image.FromFile("09.bmp"), Image.FromFile("back.bmp")),
            new Card(false, "Chicken", Image.FromFile("09.bmp"), Image.FromFile("back.bmp"))
        };

        // 등록한 카드 리스트
        List<Card> CardList = new List<Card>();

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
                    // 등록할 카드 리스트에서 랜덤한 순서로 카드 리스트에 등록합니다.
                    int randomNumber = random.Next(tmpCardList.Count);
                    cardLabel.Image = tmpCardList[randomNumber].BackImage;
                    CardList.Add(tmpCardList[randomNumber]);
                    tmpCardList.RemoveAt(randomNumber);
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
                if(CardList[clickedLabel.TabIndex].bIsOpen == true)
                {
                    return;
                }

                //// 첫번째 클릭이 없다면 첫번째 클릭을 등록합니다.
                if(firstClicked == null)
                {
                    clickedLabel.Image = CardList[clickedLabel.TabIndex].FrontImage;
                    CardList[clickedLabel.TabIndex].bIsOpen = true;
                    firstClicked = clickedLabel;
                    return;
                }

                //// 두번째 클릭을 등록합니다.
                clickedLabel.Image = CardList[clickedLabel.TabIndex].FrontImage;
                CardList[clickedLabel.TabIndex].bIsOpen = true;
                secondClicked = clickedLabel;

                CheckForWinner();

                //// 첫번째 클릭과 두번째 클릭이 같을 경우
                if(CardList[firstClicked.TabIndex].CardName == CardList[secondClicked.TabIndex].CardName)
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
            foreach (Control control in tableLayoutPanel1.Controls)
            {
                Label label = control as Label;
                if (label != null && CardList[label.TabIndex].bIsOpen == false)
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

            firstClicked.Image = CardList[firstClicked.TabIndex].BackImage;
            secondClicked.Image = CardList[secondClicked.TabIndex].BackImage;
            CardList[firstClicked.TabIndex].bIsOpen = false;
            CardList[secondClicked.TabIndex].bIsOpen = false;

            firstClicked = null;
            secondClicked = null;
        }
    }
}
