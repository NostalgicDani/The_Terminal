/* 6/6,6/7, finished 6/12

Decided to make a terminal type game with this, let's see how it goes.

List of ideas: "terminal" - like an airport. You must survive at least two nights
                in the airport before your flight. You only have $50. What will you do? */

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>

// #include "game_header.hpp"
// #include "game_functions.cpp"

using std::cin; 
using std::cout;
using std::endl;


//global variables (don't know if it works currently how i want)
int energy = 70;
int hunger = 0;
int hydration = 70;
int money = 50;

std::string location[] = {"New York City", "Berlin", "Tokyo", "London", "Sarajevo", "Los Angeles", "Moscow", "Miami", "Las Vegas", "Belgrade", "Venice", "Paris"};
char gate1[] = {'A', 'B', 'C', 'D', 'E', 'F'};
int gate2[] = {1,12,11,15,22,15,6,8};

//time
int tock[] = {10,12,2,4,6,8,10,12,//first
2,4,6,8,10,12,2,4,6,8,10,12,//second (7-12)(13-19)(19-24)(24-28)
2,4,6,8,10,12,2,4,6/* final */ };
int i = 0;

std::string deathmsg[] = {"Ha you died", "In an airport?", "You drowned", "Miguel O'Hara caught you", "You're not Spider-Man", "You're not Tom Hanks babyyyy", "I wish I knew you wanted me", "Where'd your spidey-senses go?", "You did not get past TSA"};
//plan is for either something go down after activity, sometimes multiples. If basic, then it will go down after two choices ?



//declarations 
void begin();
void board();
void task();
void eat(); void rest(); void drink(); void beg();
void check();
std::string am_pm(int n);
void drink_check(int choice);
void food_check(int choice);
void time_left();

// main
int main() {
    printf("\n\n                  Welcome to The Terminal.\n");
    printf("\nTry to stay alive for the next two nights till your flight.\n");
    begin();
        cin.ignore();
    printf("Your ticket for ...");
        cin.ignore();
    srand((unsigned) time(NULL)); //needed for random choice?
    cout << location[(rand() % 12)];
    cout << " departs at Gate " << gate1[(rand()%6)]<<gate2[(rand()%8)] << " in two nights.";
        cin.ignore();
    cout << "\nThe game can be over when you reach 100 Hunger, 0 Hydration, or 0 Energy.";
        cin.ignore();
    do {        
        board();
        task();
        i++;        
        cin.ignore();
        cin.ignore();
        check();
        system("cls");
    } while (i < 28);
    if ( i >= 28){
        cout << "     The Terminal\n\n";
        cout << "You made it to your flight!";
        cout << "\n      It is 6pm.\n";
        cin.ignore();
        cout << "\n";
        cout << "You won!\n\n\n";
        cin.ignore();
    }

    return 0;
}

//begin game
        void begin(){ 
            char play;
            printf("\nWould you like to play? [Y/N] ");
            cin >> play;
            if (play == 'Y' || play == 'y') {
                printf("\n~Welcome to Frankfurt Airport!~\n");
            } else {
                printf("Goodbye");
                cin.ignore();
                exit(0); }
        }

//unsure
        void board(){
                system("cls");
            cout << "                  The Terminal\n";
            cout << hunger << " Hunger" << "                            " <<  money << " Dollars" << endl;
            cout <<  hydration << " Hydration" << "                         " <<  energy << " Energy" << endl;
            cout << "\n                     It is " << tock[i] << am_pm(i) <<  ".\n";
            time_left();
        }

//task
        void task(){
            std::string choice;
            cout << "\n     Choose a Task (Eat, Rest, Drink, Money) \n";
            cin >> choice;
            if (choice == "Eat" || choice == "eat") {
                eat();
            } else if (choice == "Rest" || choice == "rest"){
                rest();
            } else if (choice == "Drink" || choice == "drink"){
                drink();
            } else if (choice == "Money" || choice == "money") {
                hydration -= 10;
                energy -= 20;
                hunger += 10;
                beg();
            } else if (choice == "quit") {
                cout << "Quitting the game. Thanks for playing! ";
                cin.ignore();
                cin.ignore();
                exit(0);
            } else {
                cout << "You passed the time. ";
                hydration -= 15;
                energy -= 10;
                hunger += 15;
                cin.ignore();
            }
        }

//choices

        void eat(){
            int choice;
            cout << "What would you like to buy in the range of overpriced food?\n";
            cout << "1. Candy Bar | -5 Hunger | $5\n";
            cout << "2. Chips     |-20 Hunger | $10\n";
            cout << "3. Meal      |-40 Hunger | $20\n";
            cout << "4. Go back                                                     \n";
            do
            {
                cin >> choice;
            }
            while (choice < 1 || choice > 4);
            if (choice == 1){
                food_check(choice);
                hunger -= 5;
                money -= 5;
                hydration -= 10;
                energy -= 5;
                board();
                cout << "\nYou spent money on overpriced crappy food. At least you ate.\n";
                cout << "You now are at " <<  hunger << " Hunger and have $" <<  money << ".\n";
            cin.ignore();
            } else if (choice == 2) {
                food_check(choice);
                hunger -= 15;
                money -= 10;
                hydration -= 10;
                energy -= 5;
                board();
                cout << "\nYou spent money on overpriced crappy food. At least you ate.\n";
                cout << "You now are at " <<  hunger << " Hunger and have $" <<  money << ".\n";
            } else if (choice == 3) {
                food_check(choice);
                hunger -= 40;
                money -= 20;
                hydration -= 10;
                energy -= 5;
                board();
                cout << "\nYou spent money on overpriced crappy food. At least you ate.\n";
                cout << "You now are at " <<  hunger << " Hunger and have $" <<  money << ".\n";
            } else if (choice == 4){
                board();       
                task();
            }
        }

        void drink(){
            int choice;
            cout << "What would you like to buy?\n";
            cout << "1. Water   | $10 \n";
            cout << "2. Whiskey | $30 \n";
            cout << "3. Go back                         \n";
            do
            {
                cin >> choice;
            }
            while (choice < 1 || choice > 3);
            if (choice == 1){
                drink_check(choice);
                hydration += 30;
                money -= 10;
                hunger += 10;
                energy -= 5;
                board();
                cout << "\nYou bought a liquid past airport security.\n";
                cout << "You are now at " << hydration << " Hydration and have $" << money << ".\n";
            } else if (choice == 2) {
                drink_check(choice);
                hydration += 1+rand()%50;
                money -= 30;
                hunger += 10;
                energy -= 5;
                board();
                cout << "\nTime to get risky?\n";
                cout << "You are now at " << hydration << " Hydration and have $" << money << ".\n";
            } else if (choice == 3){
                board();       
                task();
            }
        }

        void rest(){
            int choice;
            cout << "How many even hours [2-8] would you like to sleep for? ";
            do {
            cin >> choice;
            } while (choice%2 != 0 || choice > 8  || choice < 2);
            if (choice == 2) {
                i += 1;
                hydration -= 10;
                hunger += 10;
                energy += 20;
                board();
                cout << "\nYou slept for " << choice << " hours!\nYou also gained 20 Energy!\n";
                cin.ignore();
            } else if (choice == 4) {
                i += 2;   
                hydration -= 15;
                hunger += 15;      
                energy += 30;
                board();
                cout << "\nYou slept for " << choice << " hours!\nYou also gained 30 Energy!\n";
                cin.ignore();
            } else if (choice == 6) {
                i += 3;         
                hydration -= 20;
                hunger += 20; 
                energy += 40;
                board();
                cout << "\nYou slept for " << choice << " hours!\nYou also gained 40 Energy!\n";
                cin.ignore();
            } else if (choice == 8) {
                i += 4;         
                hydration -= 20;
                hunger += 20; 
                energy += 50;
                board();
                cout << "\nYou slept for " << choice << " hours!\nYou also gained 50 Energy!\n";
                cin.ignore();
            }
        }

        /// ask for spare change (random amount of money) // or pickpocket with a chance to be jailed and game ends bc no reach plane
        void beg(){
            char choice;
            cout << "Would you like to ask for spare change or pick pocket? [S/P]? ";
            cin >> choice;
            if (choice == 'S' || choice == 's'){
                cout << "You went around asking for money.\n" ;
                int offer = 1 + (rand() % 20);
                money += offer;
                cout << "\nYou got " << offer << " dollars!";
                cin.ignore();
            } else if (choice == 'P' || choice == 'p') {
                cout << "A life of crime begins...";
                int risk = 1 + (rand() % 100);
            if (risk >= 70) {
                    money += 100;
                    cout << "You stole 100 dollars!";
            } else {
                    printf(" and ends.");
                    printf("\nThey caught you :(");
                    cin.ignore();
                    cin.ignore();
                    printf("\nGame over.");
                    cin.ignore();
                    exit(0);
            }
            }
        }

// check
        void check(){
            if ( hunger > 100){
                cout << deathmsg[0+rand()%8] << " and because Hunger > 100 ";
                cin.ignore();
                cout << "Game over.";
                cin.ignore();
                exit(0);
            } else if ( energy < 0) {
                cout << deathmsg[0+rand()%8] << " and because Energy < 0 ";
                cin.ignore();
                cout << "Game over.";
                cin.ignore();
                exit(0);
            } else if ( hydration < 0) {
                cout << deathmsg[0+rand()%8] << " and because Hydration < 0 ";
                cin.ignore();
                cout << "Game over.";
                cin.ignore();
                exit(0);
            }
        }

        void drink_check(int choice){
            if (choice == 1){
                if (money - 10 < 0) {
                    cout << "You can't buy this try again.";
                    drink();
                }
            }
            if (choice == 2){
                if (money - 30 < 0) {
                    cout << "You can't buy this try again.";
                    drink();
            }
        }
        }

        void food_check(int choice){
            if (choice == 1){
                if (money - 5 < 0) {
                    cout << "You can't buy this try again.";
                    eat();
                }
            }
            if (choice == 2){
                if (money - 10 < 0) {
                    cout << "You can't buy this try again.";
                    eat();
            }
            if (choice == 3){
                if (money - 30 < 0) {
                    cout << "You can't buy this try again.";
                    eat();
            }
        }
        }
        }

//ampm 
std::string am_pm(int n){
    if (n == 0) {
        return "am";
    } else if (n > 0 && n < 7) {
        return "pm";
    } else if (n > 6 && n < 13) {
        return "am";
    } else if (n > 12 && n < 20) {
        return "pm";
    } else if (n > 19 && n < 25) {
        return "am";
    } else if (n > 24) {
        return "pm";
    } else {
        return "fail";
    }
}

//time left
void time_left(){
    if (i==0){
      printf("                You have 56 hours left\n");
    } else if (i>0){
      printf("                You have %i hours left\n", (56-(i*2)));
    }
}
//game?