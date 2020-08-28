using System;
using System.Windows.Forms;

namespace MatchGame
{
    class MainApp
    {
        static void Main(string[] args)
        {
            Application.Run(new CardManager());

            Console.ReadKey();
        }
    }
}
