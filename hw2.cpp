//Data Structure Project 2 Solitiare Game by Taewon Lee 2016-12161
//function name following camelCase
//class Card, cardPile, Solitaire
//infinite loop is controlled by only moving cards with biggest groups,
//if there's no available moves,
//move smaller group only if the largest 'card' is output-able(except it's useless move)
//for example, suppose [S][9] [D][8] [S][7] is in one of the playing Piles.
//if [S][9] can go output Piles, and there is [C][9] in the other playing Piles,
//then move [D][8] [S][7] under [C][9]
//result is printed as "test.txt"
#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
using namespace std;
const string shapes[4] = {"S", "D", "C", "H"}; //spade, Diamond, Clover, Heart to print out
class Card
{
public:
    int shape;  // 0: space, 1: diamond, 2: clover, 3: heart
    int number; // card number
    Card(int shape, int number);
    Card();
};
class cardPile //stack, consructor gets Card class as an input
{
public:
    string name; //playpile, stock, waste, output
    Card pile[52];
    int top = -1;
    int movablePosition = -1; // to check where is movable -> checking hidden cards
    void push(Card card);
    bool outputable(cardPile *out, int where);  //to check the top card can be moved to output pile
    bool playable(cardPile *next, int where);   //to check the group of top cards can be moved to the other playingPile
    bool cardMove(cardPile *next, int howmany); //move the card to the playingPile using double stack
    bool moveOutable(cardPile *next);           //move the card to output pile
    void print();
    void shuffle(); //to shuffle the cards to initialize
    Card pop();
    cardPile();
    cardPile(string name);
    ~cardPile();
};
//card pile initialize, run & output the sequences along with scores
//7 playing piles 1 waste pile  1stock 4 output piles
//Steps are boolean to check it's operated or not
class Solitaire
{
public:
    int score = -52;
    cardPile stock = cardPile("stock"), wastePile = cardPile("wastePile");
    cardPile playingPile0 = cardPile("PlayPile0"), playingPile1 = cardPile("PlayPile1"), playingPile2 = cardPile("PlayPile2"), playingPile3 = cardPile("PlayPile3"), playingPile4 = cardPile("PlayPile4"), playingPile5 = cardPile("PlayPile5"), playingPile6 = cardPile("PlayPile6");
    cardPile outputPile0 = cardPile("outPile0"), outputPile1 = cardPile("outPile1"), outputPile2 = cardPile("outPile2"), outputPile3 = cardPile("outPile3");
    cardPile *playPiles[7] = {&playingPile0, &playingPile1, &playingPile2, &playingPile3, &playingPile4, &playingPile5, &playingPile6};
    cardPile *outPiles[4] = {&outputPile0, &outputPile1, &outputPile2, &outputPile3};
    void initialize(); //initializing the game
    bool firstStep();  //firststep(according to the textbook)
    bool secondStep(); //secondstep(according to the textbook)
    bool thirdStep();  //thirdstep(according to the textbook)
    void runGame();    //start a game
    void print();      //print
    Solitaire(/* args */);
    ~Solitaire();
};
bool cardPile::cardMove(cardPile *next, int howmany) //boolean to check whether go back to step (a) or not
{
    ofstream out;
    out.open("test.txt", ios::app);
    cardPile tempPile;
    for (int i = 0; i < howmany; i++) //cardPile works as Stack, double-stacking is queue
        tempPile.push(this->pop());
    for (int i = 0; i < howmany; i++)
    {
        next->push(tempPile.pop());
        out << "[" << shapes[next->pile[next->top].shape] << "][" << next->pile[next->top].number << "] ";
    }
    out << ": " << this->name << " -> " << next->name << endl;
    return true;
}
bool cardPile::outputable(cardPile *out, int where)
{
    if (pile[where].number == 1 && out->top == -1) //if it's A and empty output pile exists
        return true;
    if (pile[where].shape == out->pile[out->top].shape && pile[where].number == (out->pile[out->top].number) + 1)
        return true;
    return false;
}
bool cardPile::playable(cardPile *next, int where)
{
    if (top == -1) //check it's empty
        return false;
    if (where == 0 && pile[where].number == 13) //if it's K and no need to move: to avoid loop
        return false;
    if (next->top == -1 && pile[where].number == 13) //check if it's K
        return true;
    if (pile[where].number == (next->pile[next->top].number) - 1 && //check it's playable
        (pile[where].shape % 2) != (next->pile[next->top].shape) % 2)
        return true;
    return false;
}
void cardPile::shuffle()
{
    srand(time(0));
    for (int i = 0; i < top; i++)
    {
        int n = rand() % top;
        Card temp;
        temp.number = pile[i].number;
        temp.shape = pile[i].shape;
        pile[i].number = pile[n].number;
        pile[i].shape = pile[n].shape;
        pile[n].number = temp.number;
        pile[n].shape = temp.shape;
    }
}
void cardPile::print()
{
    ofstream out("test.txt", ios::app);
    out << this->name << ": ";
    if (movablePosition < 0)
    {
        out << endl;
        return;
    }
    for (int i = 0; i < movablePosition; i++)
        out << "[-][-], ";
    for (int i = movablePosition; i < top + 1; i++)
        out << "[" << shapes[pile[i].shape] << "][" << pile[i].number << "], ";
    out << endl;
    out.close();
}
void cardPile::push(Card card)
{
    top++;
    pile[top].shape = card.shape;
    pile[top].number = card.number;
}
Card cardPile::pop()
{
    if (top == -1)
    {
        throw "pile is already empty!";
    }
    if (movablePosition == top)
        movablePosition--;
    top--;
    return pile[top + 1];
}
cardPile::cardPile()
{
}
cardPile::cardPile(string name)
{
    this->name = name;
}
cardPile::~cardPile()
{
}
Card::Card()
{
    this->shape = -1;
    this->number = 0;
}
Card::Card(int shape, int number)
{
    this->shape = shape;
    this->number = number;
}
void Solitaire::initialize()
{
    for (int i = 0; i < 4; i++)
        for (int j = 1; j < 14; j++)
            stock.push(Card(i, j));
    stock.shuffle();
    for (int i = 0; i < 7; i++)
    {
        stock.cardMove(playPiles[i], i + 1);
        playPiles[i]->movablePosition = i;
    }
}
void Solitaire::runGame()
{
    int p = 53;
    while (true)
    {
        if (firstStep())
            continue;
        if (secondStep())
            continue;
        if (thirdStep())
            continue;
        if (score == 208) //when you win the game
            break;
        if (stock.top > -1) //there's no available move
        {
            wastePile.movablePosition++;
            stock.cardMove(&wastePile, 1);
        }
        else if (stock.top == -1) //stock is exhausted
        {
            if (p != wastePile.top + 1) //there's an available move
            {
                p = wastePile.top + 1;
                wastePile.cardMove(&stock, p);
            }
            else //game is impossible to solve
                break;
        }
    }
}
bool Solitaire::firstStep()
{
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 4; j++)
            if (playPiles[i]->outputable(outPiles[j], playPiles[i]->top)) //something can go output from playingpile?
            {
                score += 5;
                return playPiles[i]->cardMove(outPiles[j], 1);
            }
    for (int j = 0; j < 4; j++)
        if (wastePile.outputable(outPiles[j], wastePile.top)) //something can go output from wastePile?
        {
            score += 5;
            return wastePile.cardMove(outPiles[j], 1);
        }
    return false;
}
bool Solitaire::secondStep()
{
    if (wastePile.top == -1 && stock.top != -1) //wastePile is empty, stock is not empty
    {
        stock.cardMove(&wastePile, 1); //stock -> wastePile
        wastePile.movablePosition++;   //keep the movable position
    }
    for (int i = 0; i < 7; i++)
        if (wastePile.playable(playPiles[i], wastePile.movablePosition)) //something can go from waste to playingpile?
            return wastePile.cardMove(playPiles[i], 1);
    return false;
}
bool Solitaire::thirdStep() //movablePosition
{
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++)
        {
            //checking the biggest unit is movable to the other playingPile
            if (playPiles[i]->playable(playPiles[j], playPiles[i]->movablePosition))
                return playPiles[i]->cardMove(playPiles[j], playPiles[i]->top - playPiles[i]->movablePosition + 1);
            //checking some small unit is movable and it's largest card is outable, or it's useless to move
            //it's better to divide even if these process share double for-loop
            //because usually it's able to move biggest unit, and it's better
            for (int k = playPiles[i]->movablePosition; k < playPiles[i]->top; k++)
                for (int l = 0; l < 4; l++)
                    if (playPiles[i]->outputable(outPiles[l], k) && playPiles[i]->playable(playPiles[j], k + 1))
                        return playPiles[i]->cardMove(playPiles[j], playPiles[i]->top - k);
        }
    return false;
}

void Solitaire::print() //printing
{
    ofstream out("test.txt", ios::app);
    out << "score: " << this->score << endl;
    out << "stock remain: " << stock.top + 1 << endl;
    out << wastePile.name << ": ";
    for (int j = 0; j < wastePile.top + 1; j++)
        out << "[" << shapes[wastePile.pile[j].shape] << "][" << wastePile.pile[j].number << "], ";
    out << endl;
    for (int i = 0; i < 7; i++)
        playPiles[i]->print();
    for (int i = 0; i < 4; i++)
    {
        out << outPiles[i]->name << ": ";
        for (int j = 0; j < outPiles[i]->top + 1; j++)
            out << "[" << shapes[outPiles[i]->pile[j].shape] << "][" << outPiles[i]->pile[j].number << "], ";
        out << endl;
    }
}
Solitaire::Solitaire(/* args */)
{
}
Solitaire::~Solitaire()
{
}
int main()
{
    Solitaire solitaireGame;
    solitaireGame.initialize();
    ofstream out("test.txt");
    out << "game Started" << endl;
    out.close();
    out.open("test.txt", ios::app);
    solitaireGame.print();
    solitaireGame.runGame();
    solitaireGame.print();
    return 0;
}
