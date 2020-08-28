using System;
using System.IO;
using System.Drawing;
using System.Windows.Forms;

namespace MatchGame
{
    class CardManager : Form
    {

        //Bitmap CardImage = null;

        //public void Init(int cardID)
        //{
        //    string fileName;
        //    if (cardID != 10)
        //    {
        //        fileName = "0.bmp";
        //        fileName = fileName.Insert(1, cardID.ToString());
        //    }
        //    else
        //    {
        //        fileName = "back.bmp";
        //    }

        //    if (File.Exists(fileName) == false)
        //    {
        //        MessageBox.Show("이미지 파일이 없습니다.");
        //    }
        //    else
        //    {
        //        CardImage = new Bitmap(fileName);
        //    }
        //}

        //public void ShowCard()
        //{
        //    Graphics g = CreateGraphics();
        //    g.DrawImage(CardImage, 0, 0);
        //}

        private Bitmap CardImage = null;

        public CardManager()
        {
            Init();
            CardInit();
        }

        private void Init()
        {
            this.Size = new System.Drawing.Size(800, 1000);
            this.Text = "MatchGame";
        }

        private void CardInit()
        {
            int cardID = 5;
            string fileName;
            if (cardID != 10)
            {
                fileName = "0.bmp";
                fileName = fileName.Insert(1, cardID.ToString());
            }
            else
            {
                fileName = "back.bmp";
            }

            if (File.Exists(fileName) == false)
            {
                MessageBox.Show("이미지 파일이 없습니다.");
            }
            else
            {
                CardImage = new Bitmap(fileName);
            }
        }

        private void CardManager_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            g.DrawImage(CardImage, 20, 20);
        }
    }
}
