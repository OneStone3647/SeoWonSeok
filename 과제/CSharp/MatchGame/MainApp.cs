using System;
using System.Windows.Forms;

namespace MatchGame
{
    class MainApp : Form
    {
        Card newCard = new Card();

        public MainApp()
        {
        }

        void Init()
        {
            this.Width = 800;
            this.Height = 1000;

            newCard.Init(5);
            newCard.ShowCard();
        }

        static void Main(string[] args)
        {
            MainApp form = new MainApp();
            form.Init();

            Application.Run(form);

            Console.ReadKey();
        }
    }
}
