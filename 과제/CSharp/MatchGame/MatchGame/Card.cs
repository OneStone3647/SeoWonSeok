using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace MatchGame
{
    class Card
    {
        public bool bIsOpen;
        public string CardName;
        public Image FrontImage;
        public Image BackImage;

        public Card(bool bFlag, string CardName, Image FrontImage, Image BackImage)
        {
            this.bIsOpen = bFlag;
            this.CardName = CardName;
            this.FrontImage = FrontImage;
            this.BackImage = BackImage;
        }
    }
}
