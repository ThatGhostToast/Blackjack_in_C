/**
 * @file BlackJack.c
 * @author Zachary Almas
 * @brief Blackjack application used for my ITT-310 final.
 * @version 1.0
 * @date
 */

//TODO: RNG is kinda stupid I wonder if there's a fix
//TODO: Reduce code

//=-=-=-= Include Statements =-=-=-=
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

//=-=-=-= Card Structure =-=-=-=
struct card
{
    char symbol;
    int value;
};

//=-=-=-= Global Money Variable =-=-=-=
int money = 1000; // The user's money has to be stored as a global variable so the winnings and losses are saved.

//=-=-=-= Function Declarations =-=-=-=
void theRules();
void MenuPrompt(int counter);
void PlayGame();
void ColorRed();
void ColorBlue();
void ColorReset();
char YNInputValidation();
char NumInputValidation();
int WinCheck(int userTotal, int houseTotal);
int BetMaker();
struct card GenerateRandomCard();
struct card EmergencySubtraction(struct card cardCheck);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

/**
 * @brief Main method of the application
 * @return Returns 0 if all code executes.
 */
int main()
{
    // Declare variables
    bool menuLoop = true; // Boolean variable used to loop over the menu when the user is making a selection
    int counter = 0;      // Integer variable used to change the prompt in the menu based on if the user read the rules or not

    // Welcome the user
    printf("Welcome to BlackJack!\nWould you like to continue? (y/n)\n");

    // If the user selected 'y' then the game will continue
    if (YNInputValidation() == 'y')
    {
        // Loop that surrounds the menu.
        while (menuLoop)
        {
            // Prompting the user with menu selections
            MenuPrompt(counter);

            // Switch statement that controls menu selection
            switch (NumInputValidation()) // Taking in user menu selection
            {
            case '1': // The rules.
                counter++;
                theRules(); // Function designed to display the rules
                sleep(5);   // Gives the user some time to read the rules before returning to the menu
                break;
            case '2': // Start Game
                printf("\n");
                menuLoop = false;
                PlayGame(); // Function that holds the game
                menuLoop = true;
                break;
            case '3': // Quit Game
                exit(0);
                return 0;
            default: // Something went wrong
                printf("ERROR: Something went wrong on our end...");
                break;
            }
        }
    }
    else
    {
        exit(0);
        return 0;
    }

    return 0;
}

/**
 * @brief Function used to validate user input when the user needs to enter a 'y' or 'n'
 * @return Returns the valid character
 */
char YNInputValidation()
{
    char userIn[255];   // Holds the user input
    bool check = false; // Used to loop the prompt if the user is not entering the correct information

    scanf("%s", userIn);            // Taking in user input first
    userIn[0] = tolower(userIn[0]); // Converting user input to lowercase to have accurate testing

    // Checking loop
    while (check == false)
    {
        // Since the input needs to be 1 character long, if the input is longer than 1 character it's automatically incorrect
        if (strlen(userIn) == 1)
        {
            // If the first character entered is a 'y' or 'n' then the input is valid and the function will return the character
            if (userIn[0] == 'y' || userIn[0] == 'n')
            {
                check = true;
            }
            else
            {
                // If the character entered is not a 'y' or 'n' then the check will remain false and it will prompt the user again
                check = false;
            }
        }

        // Prompting the user for input again if they did not enter correct information
        if (check == false)
        {
            printf("Please enter y or n.");
            scanf("%s", userIn);
            userIn[0] = tolower(userIn[0]);
        }
    }
    return userIn[0]; // Returning the validated input
}

/**
 * @brief Function used to validate user input in the game menu where a user needs to enter 1, 2, or 3
 * @return Returns the validated selection
 */
char NumInputValidation()
{
    char userIn[255];
    bool check = false; // Used to loop the prompt if the user is not entering the correct information

    scanf("%s", userIn); // Taking in user input first

    // Checking loop
    while (check == false)
    {
        // Since the input needs to be 1 character long, if the input is longer than 1 character it's automatically incorrect
        if (strlen(userIn) == 1)
        {
            // If the first character entered is a 'y' or 'n' then the input is valid and the function will return the character
            if (userIn[0] == '1' || userIn[0] == '2' || userIn[0] == '3')
            {
                check = true;
            }
            else
            {
                // If the character entered is not a 'y' or 'n' then the check will remain false and it will prompt the user again
                check = false;
            }
        }

        // Prompting the user for input again if they did not enter correct information
        if (check == false)
        {
            printf("Please enter 1, 2, or 3.");
            scanf("%s", userIn);
        }
    }
    return userIn[0]; // Returning the validated input
}

/**
 * @brief Function used to randomly generate a new card for the user
 * @return Returns the new card
 */
struct card GenerateRandomCard()
{
    int lower = 1;                                    // Lowest number for the RNG
    int upper = 13;                                   // Highest number for the RNG
    srand(time(NULL));                                // srand to actually randomize the numbers generated
    int rng = (rand() % (upper - lower + 1)) + lower; // Randomly generated number
    struct card newCard;                              // New card being returned

    // Switch statement that turns the randomly generated number into a card
    switch (rng)
    {
    case 1: // Creating an ACE
        newCard.symbol = 'A';
        newCard.value = 11;
        return newCard;

    case 2: // Creating a 2
        newCard.symbol = '2';
        newCard.value = 2;
        return newCard;

    case 3: // Creating a 3
        newCard.symbol = '3';
        newCard.value = 3;
        return newCard;

    case 4: // Creating a 4
        newCard.symbol = '4';
        newCard.value = 4;
        return newCard;

    case 5: // Creating a 5
        newCard.symbol = '5';
        newCard.value = 5;
        return newCard;

    case 6: // Creating a 6
        newCard.symbol = '6';
        newCard.value = 6;
        return newCard;

    case 7: // Creating a 7
        newCard.symbol = '7';
        newCard.value = 7;
        return newCard;

    case 8: // Creating an 8
        newCard.symbol = '8';
        newCard.value = 8;
        return newCard;

    case 9: // Creating a 9
        newCard.symbol = '9';
        newCard.value = 9;
        return newCard;

    case 10: // Creating a 10
        newCard.symbol = 'X';
        newCard.value = 10;
        return newCard;

    case 11: // Creating a Jack
        newCard.symbol = 'J';
        newCard.value = 10;
        return newCard;

    case 12: // Creating a Queen
        newCard.symbol = 'Q';
        newCard.value = 10;
        return newCard;

    case 13: // Creating a King
        newCard.symbol = 'K';
        newCard.value = 10;
        return newCard;

    default: // Default (just in case) should never throw
        printf("Something went wrong! That shouldn't have happened...");
        break;
    }
}

/**
 * @brief Function used to perform an emergency subtraction if a hand goes over 21
 * @note This should only affect the game if there is an Ace in one of the hands as the ace is the only one with an emergency subtraction value
 * @param cardCheck Card being passed in to change value
 * @return Returns the same card but with the adjusted value
 */
struct card EmergencySubtraction(struct card cardCheck)
{
    // Subtracting 10 from the value
    cardCheck.value = cardCheck.value - 10;
    return cardCheck;
}

/**
 * @brief Function that contains the game.
 */
void PlayGame()
{
    // Initialize loop variables
    bool gameLoop = true;  // Boolean that loops when the user wants to keep playing
    bool winner = false;   // Boolean variable used to check if theres a winner when playing blackjack
    bool turn = true;      // Boolean that determines who's turn it is
    bool finished = false; // Boolean that determines when both the user and house are finished making their moves

    while (gameLoop == true)
    {
        // Initialize game variables
        int bet = 0;           // The bet the user enters
        int houseTotal = 0;    // Total value of the houses cards
        int userTotal = 0;     // Total value of the users cards
        int roundCounter = 0;  // Counter used to tell what round its on
        int houseHandSize = 2; // Size of the house hand array that will be changed as the game plays
        int userHandSize = 2;  // Size of the user hand array that will be changed as the game plays

        // Initializing the house and user hands and allocating the first space for it
        struct card *houseHand = (struct card *)malloc(houseHandSize * sizeof(struct card)); // The hand of the dealer
        struct card *userHand = (struct card *)malloc(userHandSize * sizeof(struct card));   // The hand of the user

        // Prompting the user to enter a bet
        printf("How much would you like to bet? (Current total: $%d)\n", money);
        bet = BetMaker(); // Entering the bet

        // Game Loop (This is where the fun begins)
        while (winner == false)
        {
            // Reset value totals
            houseTotal = 0;
            userTotal = 0;

            // Displaying the houses hand
            for (int i = 0; i < houseHandSize; i++)
            {
                // Used to generate the first couple of cards. (This has to be implemented or the first 4 cards are all the same)
                if (roundCounter == 0 || roundCounter == 1)
                {
                    houseHand[i] = GenerateRandomCard();
                    // If statement used to make the program sleep to give the RNG time to generate a new number
                    if (roundCounter == 0)
                    {
                        sleep(1);
                    }
                }

                // Calculate the total
                houseTotal = houseTotal + houseHand[i].value;

                //Change the color to red to make the house hand more recognizable
                ColorRed();

                if (houseTotal == 21)
                {
                    // Display the hand
                    printf("[ %c ]", houseHand[i].symbol);
                }
                else
                {
                    if (turn)
                    {
                        // Display the hand with the first card hidden if its the user's turn
                        if (roundCounter == 0)
                        {
                            printf("[ ? ]");
                        }
                        else
                        {
                            printf("[ %c ]", houseHand[i].symbol);
                        }
                    }
                    else
                    {
                        // Display the hand
                        printf("[ %c ]", houseHand[i].symbol);
                    }
                }
                roundCounter++;
            }

            // First checking if an ace can be reduced before busting the house
            if (houseTotal > 21)
            {
                // Resetting the total to be counted again
                houseTotal = 0;
                // Loops over the users hand to check every card for an ace
                for (int x = 0; x < houseHandSize; x++)
                {
                    if (houseHand[x].symbol == 'A' && houseHand[x].value == 11)
                    {
                        // Calling EmergencySubtraction() to change the aces value to a 1 instead of 11
                        houseHand[x] = EmergencySubtraction(houseHand[x]);
                    }
                    // Adding to the total
                    houseTotal = houseTotal + houseHand[x].value;
                }
            }

            // Displays the houses score. If its the users turn it hides the first cards value
            if (turn && houseTotal != 21)
            {
                printf(" House Score: %d\n\n", houseHand[1].value);
            }
            else
            {
                // Once it becomes the houses turn, the hidden card flips and the full value is displayed
                printf(" House Score: %d\n\n", houseTotal);
            }

            // Change the console color to blue to make the users hand more recognizable
            ColorBlue();

            // Displaying the user hand
            for (int i = 0; i < userHandSize; i++)
            {
                // Used to generate the first couple of cards. (This has to be implemented or the first 4 cards are all the same)
                if (roundCounter == 2 || roundCounter == 3)
                {
                    userHand[i] = GenerateRandomCard();
                    // If statement used to make the program sleep to give the RNG time to generate a new number
                    if (roundCounter == 2)
                    {
                        sleep(1);
                    }
                }

                // Calculate the total
                userTotal = userTotal + userHand[i].value;
                // Display the hand
                printf("[ %c ]", userHand[i].symbol);
                roundCounter++;
            }

            // First checking if an ace can be reduced before busting the user
            if (userTotal > 21)
            {
                // Resetting the total to be counted again
                userTotal = 0;
                // Loops over the users hand to check every card for an ace
                for (int x = 0; x < userHandSize; x++)
                {
                    if (userHand[x].symbol == 'A' && userHand[x].value == 11)
                    {
                        // Calling EmergencySubtraction() to change the aces value to a 1 instead of 11
                        userHand[x] = EmergencySubtraction(userHand[x]);
                    }
                    // Adding to the total
                    userTotal = userTotal + userHand[x].value;
                }
            }

            //Print the user score
            printf(" User Score: %d\n", userTotal);

            //Reset the console color
            ColorReset();

            // Checking if the house got 21 right away
            if (houseHand[0].value + houseHand[1].value == 21)
            {
                winner = true;
            }
            else
            {
                // If turn is true then it is the users turn
                if (turn)
                {
                    // If the user has 21 it locks them in
                    if (userTotal == 21)
                    {
                        turn = false;
                    }
                    else
                    {
                        // If the user busts the game ends
                        if (userTotal > 21)
                        {
                            finished = true;
                        }
                        else
                        {
                            // Prompt the user with move options and take user input
                            printf("What would you like to do?\n1. Hit\n2. Stand\n3. Double Down\n");
                            switch (NumInputValidation())
                            {
                            case '1': // Adding another card to the users hand
                                // Counter used to determine how big the new array needs to be.
                                userHandSize++;
                                // Creating a temporary location to store the old array values
                                struct card *temp = userHand;
                                // Changing the size of the array to allow for another card to be added
                                userHand = (struct card *)malloc(userHandSize * sizeof(struct card));
                                // For loop that adds the old array values to the new array, and then adds a new card
                                for (int x = 0; x < userHandSize; x++)
                                {
                                    if (x == (userHandSize - 1))
                                    {
                                        // At the end of the array, generate a new card
                                        userHand[x] = GenerateRandomCard();
                                    }
                                    else
                                    {
                                        // Adding the old values to the new array
                                        userHand[x] = temp[x];
                                    }
                                }
                                break;
                            case '2': // Ending the users turn
                                turn = false;
                                break;
                            case '3': // Adding another card to the users hand, doubling the bet, and ending the turn
                                // Doubling the bet
                                bet = bet * 2;
                                // Counter used to determine how big the new array needs to be.
                                userHandSize++;
                                // Creating a temporary location to store the old array values
                                struct card *temp2 = userHand;
                                // Changing the size of the array to allow for another card to be added
                                userHand = (struct card *)malloc(userHandSize * sizeof(struct card));
                                // For loop that adds the old array values to the new array, and then adds a new card
                                for (int x = 0; x < userHandSize; x++)
                                {
                                    if (x == (userHandSize - 1))
                                    {
                                        // At the end of the array, generate a new card
                                        userHand[x] = GenerateRandomCard();
                                    }
                                    else
                                    {
                                        // Adding the old values to the new array
                                        userHand[x] = temp2[x];
                                    }
                                }
                                // Since doubling down is the last move you can make, the turn changes
                                turn = false;
                                break;
                            }
                        }
                    }
                }
                else // Else it is the houses turn
                {
                    if (houseTotal >= 18 || houseTotal > 21)
                    {
                        // If the house is at 18 or above they cannot get another card.
                        finished = true;
                    }
                    else
                    {
                        // Counter used to determine how big the new array needs to be.
                        houseHandSize++;
                        // Creating a temporary location to store the old array values
                        struct card *temp3 = houseHand;
                        // Changing the size of the array to allow for another card to be added
                        houseHand = (struct card *)malloc(houseHandSize * sizeof(struct card));
                        // For loop that adds the old array values to the new array, and then adds a new card
                        for (int x = 0; x < houseHandSize; x++)
                        {
                            if (x == (houseHandSize - 1))
                            {
                                // At the end of the array, generate a new card
                                houseHand[x] = GenerateRandomCard();
                                sleep(1);
                            }
                            else
                            {
                                // Adding the old values to the new array
                                houseHand[x] = temp3[x];
                            }
                        }
                    }
                }

                // After all turns are complete run this
                if (finished)
                {
                    winner = true;
                }
            }
        }

        // Display who won to the user
        switch (WinCheck(userTotal, houseTotal))
        {
        case 1: // If the user won
            printf("Congratulations! You win!\n");
            money = money + bet;
            break;

        case 2: // If the house won
            printf("The House wins! Better luck next time!\n");
            money = money - bet;
            break;

        case 3: // If there was a tie
            printf("It was a tie! No winners.\n");
            break;
        }

        // Prompt the user if they want to play again
        printf("Would you like to play again? (y/n)\n");
        char keepGoing = YNInputValidation();

        // If they want to play again, reset game variables
        if (keepGoing == 'n')
        {
            // If they don't want to continue start the menu loop again and close the game loop
            gameLoop = false;
        }
        else
        {
            // Resetting some of the game loops
            winner = false;
            finished = false;
            turn = true;
        }
    }
}

/**
 * @brief Function used to check for a winner
 * @param userTotal The user total value from the game loop
 * @param houseTotal The house total value from the game loop
 * @return Returns 0 if theres no winner, 1 if the user won, 2 if the house won, and 3 if it was a tie
 */
int WinCheck(int userTotal, int houseTotal)
{
    // If the user has blackjack
    if (userTotal == 21 && houseTotal != 21)
    {
        return 1;
    }
    // If the house has blackjack
    if (userTotal != 21 && houseTotal == 21)
    {
        return 2;
    }
    // If the user busted but the house didn't
    if (userTotal > 21 && houseTotal < 21)
    {
        return 2;
    }
    // If the house busted but the user didn't
    if (userTotal < 21 && houseTotal > 21)
    {
        return 1;
    }
    // If it was a tie
    if (userTotal == houseTotal)
    {
        return 3;
    }
    // If the user has a higher score than the house
    if (userTotal > houseTotal)
    {
        return 1;
    }
    // If the house has a higher score than the user
    if (userTotal < houseTotal)
    {
        return 2;
    }

    return 0;
}

/**
 * @brief Function used to take a user's bet
 * @return Returns the valid bet
 */
int BetMaker()
{
    char userIn[255];   // Holds the user input
    bool check = false; // Used to loop the prompt if the user is not entering the correct information
    bool oob = false;   // Used to loop the prompt if the user enters a bet that is outside the money range
    int bet;            // User bet thats being returned

    scanf("%s", userIn); // Taking in user input

    // Checking loop
    while (check == false)
    {
        int digitCounter = 0; // Counts how many digits are in the string
        int counter = 0;      // Counts how many characters are in the string

        // Looping over the whole string to check each digit
        for (int i = 0; userIn[i] != '\0'; i++)
        {
            // Counting the digits in the string
            if (isdigit(userIn[i]) != 0)
            {
                digitCounter++;
            }
            // Counting the ammount of characters in the string
            counter++;
        }

        // Checking to make sure every character in the string is a digit
        if (counter == digitCounter)
        {
            bet = atoi(userIn); // Converting the string into an integer
            // If statement checking if the user has money available
            if (bet <= money && bet >= 0)
            {
                check = true;
            }
            else
            {
                oob = true;
            }
        }

        // Prompting the user for input again if they did not enter correct information
        if (check == false && oob == false)
        {
            printf("Please enter a number.\n");
            scanf("%s", userIn);
        }
        // Prompting the user for input again if they entered a number that is out of bounds
        if (check == false && oob == true)
        {
            printf("You don't have the available money to make that bet... Money available: %d\n", money);
            printf("Please enter a valid number.\n");
            scanf("%s", userIn);
        }
    }

    printf("Bet Entered: $%d\n", bet); // Displaying the entered bet
    return bet;                        // Returning the validated bet
}

/**
 * @brief Function that prints the menu selections to the user
 * @param counter Variable that determines what prompt gets displayed to the user
 */
void MenuPrompt(int counter)
{
    // If statement that changes the prompt based on if the user read the rules once or not.
    if (counter == 0)
    {
        printf("Would you like to read the rules or start the game?\n1.  Read Rules.\n2.  Start Game.\n3.  Quit.\n");
    }
    else
    {
        printf("\nWould you like to read the rules again or start the game?\n1.  Read Rules.\n2.  Start Game.\n3.  Quit.\n");
    }
}

/**
 * @brief Function that prints the rules.
 */
void theRules()
{
    printf("=-=-=-=-=-=-=-= The Rules =-=-=-=-=-=-=-=\n");
    printf("The goal of Black Jack is to get as close\n");
    printf("to 21 as possible. You start the game with\n");
    printf("2 cards, and when it's your turn to are\n");
    printf("allowed to draw as many cards as you like\n");
    printf("as long as you don't go over 21. Each number\n");
    printf("card is worth it's number. Jack, Queen, and\n");
    printf("Kind are all worth 10. And an Ace is worth\n");
    printf("either 1 or 11 depending on what you need.\n");
    printf("If you're closer to 21 than the house you\n");
    printf("win! If you both have the same number it's\n");
    printf("a tie. If the house pulls 21 right away they\n");
    printf("automatically win.\n");
}

/**
 * @brief Changes the console color to red to display the house hand
 */
void ColorRed(){
    printf("\033[1;31m");
}

/**
 * @brief Change the console color to blue to display the user hand
 */
void ColorBlue(){
    printf("\033[0;36m");
}

/**
 * @brief Resets the console color
 */
void ColorReset(){
    printf("\033[0m");
}