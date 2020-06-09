#include <iostream>
#include <vector>
#include <stdlib.h>
#include<sstream>
#include<time.h>
#include<iomanip>
#include <fstream>

using namespace std;


void deck_int(int deck[13][4]);
void print(int deck[13][4]);
void hit(string &card, int &points, int deck[13][4]);
int player2(int deck [13][4],int &points1, int &points2 , int &dealer_points );
int player1(int deck [13][4],int &points1, int &points2 , int &dealer_points );
int dealer(int deck [13][4],int &points1, int &points2 , int &dealer_points);
void save_game(int game_points1, int game_points2, int game_dealer);


int main()
{
    cout << "WELCOME TO BLACKJACK \n \n" ;
    cout << "******************** \n \n";
    cout << "PRESS ENTER TO START \n\n" ;
    cin.get();
    string game = "yes", load="";
    int game_points1=0, game_points2=0, game_dealer=0;
    cout << "Do you want to load previous game?"<< endl;
    cin>> load;
    if (load=="yes")
    {
        ifstream load("savegame.txt");
        load>> game_points1 >> game_points2 >> game_dealer;
        cout << "Player 1 total points are " << game_points1 << endl;
        cout << "Player 2 total points are " << game_points2 << endl;
        cout << "Dealer total points are " << game_dealer << endl;

    }
    while (game=="yes")
    {
        int deck[13][4];
        srand(time(0));
        int points1=0, points2=0 , dealer_points=0;
        deck_int(deck);
        player1(deck, points1, points2, dealer_points);
        if(points1<=21)
        {
            if((points2>21 && dealer_points >21))
            {
                cout << "Player 1 wins." << endl;
                game_points1 +=1;
            }
            else if (points2>21 && points1 > dealer_points)
            {
                cout << "Player 1 wins." << endl;
                game_points1 +=1;
            }
            else if (dealer_points>21 && points1 > points2)
            {
                cout << "Player 1 wins."<< endl;
                game_points1 +=1;
            }
        }
        if (points2<=21)
        {
            if((points1>21 && dealer_points >21))
            {
                cout << "Player 2 wins."<< endl;
                game_points2 +=1;
            }
            else if (points1>21 && points2 > dealer_points)
            {
                cout << "Player 2 wins." << endl;
                game_points2 +=1;
            }
            else if (dealer_points>21 && points2 > points1)
            {
                cout << "Player 2 wins." << endl;
                game_points2 +=1;
            }
        }
        if (dealer_points<=21)
        {
            if((points1>21 && points2 >21))
            {
                game_dealer +=1;
            }
            else if (points1>21 && dealer_points > points2)
            {
                game_dealer +=1;
            }
            else if (points2>21 && dealer_points > points1)
            {
                game_dealer +=1;
            }
            else if (points2< dealer_points && dealer_points > points1)
            {
                game_dealer +=1;
            }

        }
        cout << "Player 1 total points are " << game_points1 << endl;
        cout << "Player 2 total points are " << game_points2 << endl;
        cout << "Dealer total points are " << game_dealer << endl;
        cout << "Another game?"<< endl << endl;
        cin>> game;
        cout << endl << endl;
        cout << "**********************"<< endl<< endl;
    }
    cout << "Do you want to save the game?" << endl;
    string save1= "";
    cin >> save1;
    if(save1=="yes")
    {
        save_game(game_points1, game_points2, game_dealer);
        return 0;
    }
    if(game_points1 > game_points2 && game_points1 > game_dealer)
    {
        cout << "Player 1 wins the game. ";
    }
    if(game_points1 < game_points2  && game_points2 > game_dealer)
    {
        cout << "Player 2 wins the game.";
    }
    if(game_dealer > game_points1 && game_dealer > game_points2 )
    {
        cout << "Dealer wins the game.";
    }

}

void deck_int(int deck[13][4])// 13x4 array of numbers 1-13 four times
{
    for (int j =0; j<4 ; j++)
    {
        for (int i = 0; i <13 ; i++)
        {
            deck[i][j]= i+1;
        }
    }
}

void print(int deck[13][4]) // check function
{
    for (int j =0; j<4 ; j++)
    {
        for (int i = 0; i <13 ; i++)
        {
            cout << deck [i][j] << " ";
        }
        cout << endl;
    }

}

void hit(string &card, int &points, int deck[13][4])// the most complicated function.
{
    int i = rand()%13 ; //generates random number for points.
    int j = rand()%4 ; // generates random house.
    string number; // all of this is to convert the number into string.
    stringstream convert;
    convert << i +1;
    number = convert.str();
    if (deck[i][j]==0) // check to see if card has already been taken.
    {
        hit(card,points,deck);
    }
    else if (j==0)// checks suit, after which it checks card and adds points, points being accessed from memory is constantly changing
    {

        if (i==0)
        {
            card = "ACE OF SPADES";
            if ((points + 11) > 21)
            {
                points +=1;
            }
            else
            {
                points +=11;
            }
            deck[i][j] = 0;
        }
        else if(i==10)
        {
            card = "JACK OF SPADES";
            points += 10;
            deck[i][j] = 0;
        }
        else if(i==11)
        {
            card = "QUEEN OF SPADES";
            points += 10;
            deck[i][j] = 0;
        }
        else if(i==12)
        {
            card = "KING OF SPADES";
            points += 10;
            deck[i][j] = 0;
        }
        else
        {
            card= number + " OF SPADES";
            deck[i][j] = 0;
            points += i+1;
        }
    }
    else if (j==1)// code repeated for different sets 3 more times so same thing, ps it also returns name of the card.
    {
        if (i==0)
        {
            card = "ACE OF CLUBS";
            if ((points + 11) > 21)
            {
                points +=1;
            }
            else
            {
                points +=11;
            }
            deck[i][j] = 0;
        }
        else if(i==10)
        {
            card = "JACK OF CLUBS";
            points += 10;
            deck[i][j] = 0;
        }
        else if(i==11)
        {
            card = "QUEEN OF CLUBS";
            points += 10;
            deck[i][j] = 0;
        }
        else if(i==12)
        {
            card = "KING OF CLUBS";
            points += 10;
            deck[i][j] = 0;
        }
        else
        {
            card= number + " OF CLUBS";
            deck[i][j] = 0;
            points += i+1;
        }
    }
    else if (j==2)
    {
        if (i==0)
        {
            card = "ACE OF DIAMONDS";
            if ((points + 11) > 21)
            {
                points +=1;
            }
            else
            {
                points +=11;
            }
            deck[i][j] = 0;
        }
        else if(i==10)
        {
            card = "JACK OF DIAMONDS";
            points += 10;
            deck[i][j] = 0;
        }
        else if(i==11)
        {
            card = "QUEEN OF DIAMONDS";
            points += 10;
            deck[i][j] = 0;
        }
        else if(i==12)
        {
            card = "KING OF DIAMONDS";
            points += 10;
            deck[i][j] = 0;
        }
        else
        {
            card= number + " OF DIAMONDS";
            deck[i][j] = 0;
            points += i+1;
        }
    }
    else if (j==3)
    {
        if (i==0)
        {
            card = "ACE OF HEARTS";
            if ((points + 11) > 21)
            {
                points +=1;
            }
            else
            {
                points +=11;
            }
            deck[i][j] = 0;
        }
        else if(i==10)
        {
            card = "JACK OF HEARTS";
            points += 10;
            deck[i][j] = 0;
        }
        else if(i==11)
        {
            card = "QUEEN OF HEARTS";
            points += 10;
            deck[i][j] = 0;
        }
        else if(i==12)
        {
            card = "KING OF HEARTS";
            points += 10;
            deck[i][j] = 0;
        }
        else
        {
            card= number + " OF HEARTS";
            deck[i][j] = 0;
            points += i+1;
        }
    }




}


int player2(int deck [13][4], int &points1, int &points2, int &dealer_points) // same code as player1
{
    string card= "";
    hit(card,points2,deck);// hit is activated
    cout << card << endl <<endl; // the card is displayed as random as it gets
    cout << "Player2 points are  " << points2<< endl << endl; // the players points constantly get updated with every hit
    if (points2 > 21)//check to see if it exceeds 21 returns zero if it does
    {
        cout << "Player 2 loses, points exceeded 21."<< endl;
        if (points1<=21 )
        {
            cout << "Does player 1 want to hit?"<< endl << endl;
            string a = " ";
            cin >> a;
            if (a=="yes")
            {
                player1(deck,points1,points2, dealer_points);

            }
            else
            {
                dealer(deck,points1,points2, dealer_points);


            }
        }
    }
    else
    {   if (points1<=21 )
        {
            cout << "Does player 1 want to hit?"<< endl << endl;
            string a = " ";
            cin >> a;
            if (a=="yes")
            {
                player1(deck,points1,points2, dealer_points);
            }
            else if(points2 <=21)
            {
                cout << "Does Player 2 want to make a hit?" << endl << endl;
                string a= " ";
                cin >> a;
                while (a=="yes")
                {
                    hit(card,points2,deck);
                    cout << card << endl << endl;
                    cout << "Player 2 points are  " << points2<< endl << endl;
                    if(points1 > 21) // another check for 21
                    {
                        cout << "Player 2 is out of the game"<< endl;
                        dealer(deck, points1, points2 , dealer_points);
                    }
                    else
                    {
                        cout << "Does player 2 want to make another hit?"<< endl << endl;
                        cin >> a;
                    }
                }
                dealer(deck,points1,points2, dealer_points);
            }
            else
            {
                cout << "Dealer wins" << endl;
            }
        }
        else if(points2<=21)//if the player is satisfied the player here is asked again until he says no
        {
            cout << "Does Player 2 want to make a hit?" << endl << endl;
            string a = " ";
            cin >> a;
            while (a=="yes")
            {
                hit(card,points2,deck);
                cout << card << endl << endl;
                cout << "Player 2 points are  " << points2<< endl << endl;
                if(points1 > 21) // another check for 21
                {
                    cout << "Player 2 is out of the game"<< endl;
                    dealer(deck, points1, points2 , dealer_points);
                }
                else
                {
                    cout << "Does player 2 want to make another hit?"<< endl << endl;
                    cin >> a;
                }
            }
            dealer(deck,points1,points2, dealer_points);
        }
    }
}


int player1 (int deck [13][4],int &points1, int &points2 , int &dealer_points)
{
    string card= "";
    if (points1==0)
    {
        hit(card,dealer_points,deck);// hit is activated
        cout << card << endl <<endl; // the card is displayed as random as it gets
        cout << "Dealer's points are  " <<dealer_points<< endl << endl;
    }
    card= "";
    hit(card,points1,deck);// hit is activated
    cout << card << endl <<endl; // the card is displayed as random as it gets
    cout << "Player1 points are  " << points1<< endl << endl; // the players points constantly get updated with every hit
    if (points1 > 21)//check to see if it exceeds 21 returns zero if it does
    {
        cout << "Player 1 loses, points exceeded 21."<< endl;
        if (points2<=21 )
        {
            cout << "Does player 2 want to hit?"<< endl << endl;
            string a = " ";
            cin >> a;
            if (a=="yes")
            {
                player2(deck,points1,points2, dealer_points);
            }
            else if(points1 <=21)
            {
                cout << "Does Player 1 want to make a hit?" << endl << endl;
                string a= " ";
                cin >> a;
                while (a=="yes")
                {
                    hit(card,points1,deck);
                    cout << card << endl << endl;
                    cout << "Player 1 points are  " << points1<< endl << endl;
                    if(points1 > 21) // another check for 21
                    {
                        cout << "Player 1 is out of the game"<< endl;
                        dealer(deck, points1, points2 , dealer_points);
                    }
                    cout << "Does player 1 want to make another hit?"<< endl << endl;
                    cin >> a;
                }
                dealer(deck,points1,points2, dealer_points);
            }
        }
        else
        {
            cout << "Delear WINS." << endl;
        }
    }
    else
    {   if (points2<=21 )
        {
            cout << "Does player 2 want to hit?"<< endl << endl;
            string a = " ";
            cin >> a;
            if (a=="yes")
            {
                player2(deck,points1,points2, dealer_points);
            }
            else if(points1 <=21)
            {
                cout << "Does Player 1 want to make a hit?" << endl << endl;
                string a= " ";
                cin >> a;
                while (a=="yes")
                {
                    hit(card,points1,deck);
                    cout << card << endl << endl;
                    cout << "Player 1 points are  " << points1<< endl << endl;
                    if(points1 > 21) // another check for 21
                    {
                        cout << "Player 1 is out of the game"<< endl;
                        dealer(deck, points1, points2 , dealer_points);
                    }
                    cout << "Does player 1 want to make another hit?"<< endl << endl;
                    cin >> a;
                }
                dealer(deck,points1,points2, dealer_points);
            }
            else
            {
                cout << "Dealer wins" << endl;
            }
        }
        else if(points1<=21)//if the player is satisfied the player here is asked again until he says no
        {
            cout << "Does Player 1 want to make a hit?" << endl << endl;
            string a = " ";
            cin >> a;
            while (a=="yes")
            {
                hit(card,points1,deck);
                cout << card << endl << endl;
                cout << "Player 1 points are  " << points1<< endl << endl;
                if(points1 > 21) // another check for 21
                {
                    cout << "Player 1 is out of the game"<< endl;
                    dealer(deck, points1, points2 , dealer_points);
                }
                cout << "Does player 1 want to make another hit?"<< endl << endl;
                cin >> a;

            }
            dealer(deck,points1,points2, dealer_points);
        }
    }
}



int dealer(int deck [13][4],int &points1, int &points2, int &dealer_points)
{
    string card= "";
    hit(card,dealer_points,deck);// hit is activated
    cout << card << endl <<endl; // the card is displayed as random as it gets
    cout << "Dealer's points are  " << dealer_points<< endl << endl;
    if (dealer_points > 21)
    {
        cout << "Dealer loses \n \n" ;
        return 0;
    }
    else if(dealer_points > points1 && dealer_points > points2)
    {
        cout << "Dealer Wins. \n \n";
        return 0;
    }
    else if(dealer_points == points1 && dealer_points == points2)
    {
        cout << "DRAW. \n \n ";
        return 0;
    }
    else
    {
        dealer(deck,points1,points2, dealer_points);
    }
}

void save_game(int game_points1, int game_points2, int game_dealer)
{
    ofstream save("savegame.txt");
    save << game_points1 << " " << game_points2 << " " << game_dealer ;


}

