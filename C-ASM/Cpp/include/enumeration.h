#include <iostream>


namespace CardGame_Scoped {
    enum class Suit { Diamonds, Hearts, Clubs, Spades };
    void PlayCard(Suit suit) {
        if (suit == Suit::Clubs){
            std::cout << "Suit Eqaul Clubs from Scoped Version!" <<"\n"; 
        }
    }
}

namespace CardGame_NonScoped {
    enum Suit { Diamonds, Hearts, Clubs, Spades};
    void PlayCard(Suit suit) {
        if (suit == Clubs) {
            std::cout <<"Suits equal Clubs from NonScoped" <<"\n";
        }
    }
}

namespace ScopedEnumConversions
{
    enum class Suit { Diamonds, Hearts, Clubs, Spades };

    void AttemptConversions()
    {
        Suit hand;
        hand = Suit::Clubs; //Correct.
        int account_num = 135692;
        hand = static_cast<Suit>(account_num); // OK, but probably a bug!!!
        account_num = static_cast<int>(Suit::Hearts); // OK
    }
}
