#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Valid checker function. Checks if the seed is valid
 * 1 if valid, 0 if invalid*/
int valid_seed(char * buffer){

    /* We just want to iterate through the string not the whole array
     * so with the help of strlen(), we can get the real length of
     * the string, and iterate through each of its characters.*/
    int strLength = 0;
    strLength = strlen(buffer);

    /* Check each digit to see if they are actually digits*/
    for (int i=0; i < strLength - 1; i++) {

        /* Once this line reaches then it's going to skip to the next iteration
         * because, we already know that this is a digit, thus its valid*/
        if ((buffer[i] >= '0' && buffer[i] <= '9') || buffer[i] == '-'){
            continue;
        }

        /* If they are not digits then its invalid automatically
         * and we return 0*/
        return 0;
    }

    /* The second check is for the range. If the number is bigger or smaller
     * than the set range, then its invalid.*/
    int num = 0;
    sscanf(buffer, "%d" , &num);

    if (num >= 1 && num <= 9999){
        return 1; /* If it's within the range, then it passed the two checks, so it's valid!*/
    }

    return 0; /* If it reaches this line, then it didn't pass the second check, so it's invalid*/
}

/*Generates a word based on the seed!*/
void generate_word(char * word){
    /*Generates word and saves it into an array of chars*/
    for (int i=0; i < 5; i++){
        word[i] = (char)((rand() % 26) + 97);
    }

    /*Adds a null byte at the end*/
    word[5] = '\0';
}

/* This functions purpose is to validate the sides inputted
 * and the correct format of them*/
int validate_sides(char * arr){
    /* SeenX and SeenNum supposed to save the times were x and the digits were seen */
    int seenX = 0;
    int seenNum = 0;

    /* These variables are treated as booleans to check the requirements on when each is valid*/
    int for_X = 0;
    int for_Digit = 0;

    /* Check the string length, so we can use it inside our loop*/
    int stringLen = strlen(arr);

    /* Iterates through each character inside the array while checking them for validity*/
    for (int i=0; i < stringLen - 1; i++){

        /* Since the correct format is "x" then we can assume that it will only be valid if x is seen only once, more
         * than that, and we can assume that is not valid because there is more than one x! ie: "1xx2" is not valid,
         * more than two x's
         *
         * It also checks that x is not the first nor the last character, because that would be invalid.*/
        for_X = (arr[i] == 'x' && seenX == 0 && i != 0 && i != (stringLen - 1));

        /* Here we are checking the digits, and if they are from 1 to 5. Also, if there is more than 2 digits seen then
         * we can assume that the input is invalid! Why? because, since its numbers are from 1 to 5 then it's going
         * to be a max of two digit! ex: "1x2" 1 is one digit, and 2 is another digit which is 2 in total.
         * While "23x2" 23 is two digits and 2 is one digit, in total is 3 which is not right! */
        for_Digit = (arr[i] >= '1' && arr[i] <= '5' && seenNum < 3);

        /* Depending on which case each one is, it will be counted as valid and skip to the next iteration.
         *
         * For_Digit: Everytime the digit is valid within [1,5] then it skips to the next iteration, while
         *            also adding 1 to the seenNum variable
         *
         * For_X: 'x' must appear exactly once and cannot be at the start or end.
         *        Notice: "1x1" this correct input has only one x. More than that? Something is wrong thus is invalid.
         *
         * */
        if (for_Digit || for_X || arr[i] == ' '){

            if (for_X) {
                seenX = 1;
            }

            if (for_Digit){
                seenNum++;
            }

            continue;
        }

        /*If it fails the if statement above then it is not a valid input for sides*/
        return 0;
    }

    /* After exiting the loop we check that it meets criteria:
     *      1. Only one x
     *      2. Only 2 digits
     *
     * Once it meets this criteria then it returns 1, which is valid!*/
    if (seenX == 1 && seenNum == 2){
        return 1;
    }

    /*If everything above fails, then its absolutely invalid*/
    return 0;
}

int validate_player_name(char * arr){
    /* Discarding the new-line character*/
    int stringLength = strlen(arr) - 1;

    if (stringLength > 8 || stringLength < 2) {return 0;}

    for (int i=0; i < stringLength; i++){
        if ((arr[i] >= 'a' && arr[i] <= 'z') || (arr[i] >= 'A' && arr[i] <= 'Z')){
            continue;
        }
        return 0;
    }
    return 1;
}

/* Rolls a die randomly between 0 and number of sides */
int roll_dice(int side) {
    return ((rand() % side) + 1);
}

/* Encrypts word by using the sum of all sides from the player
 * and makes an entirely new word!*/
void cipher(char * arr, int shift) {

    /* In order to iterate through each char, we need
     * its length.*/
    int arr_length = strlen(arr);
    int num = 0;

    /* Our loop iterates and changes each letter
     * to another based on the shift number (alphabetical)*/
    for (int i = 0; i < arr_length; i++) {
        num = (int) arr[i];
        num += shift;

        /* If the shift makes the letter bigger than the last letter (z)
         * then, it goes back to the beginning + the difference. */
         while(num > 'z'){
            num -= 26;
         }

         arr[i] = (char) num;
    }
}

/* Prints current word of player. When they are playing*/
void printWord(char * playerName,char * word, int times){
    printf("<* %s's word is:", playerName);

    for (int i=0; i< times; i++){
        printf("%c", word[i]);
    }
    printf("\n");
}


int main(void) {
    /* We make a buffer, and another array*/
    char buffer[100];
    char word[6];

    /* We initialize our variables seed, and the sides for our dice */
    int seed = 0;
    int sideA = 0;
    int sideB = 0;

    /* We initialize Player A Assets*/
    char playerA[10];
    int playerASum = 0;
    int playerACounter= 0;

    /* We initialize PLayer B Assets*/
    char playerB[] = "Bob";
    int playerBSum = 0;
    int playerBCounter = 0;

    /* Temporary values for rolls*/
    int temp1 = 0;
    int temp2 = 0;

    printf(" \n"
            " -----------------------------------------------------------------\n"
            "| Welcome to Dungeon Cube Cesar! I hope you are in for a fun time! |\n"
            " -----------------------------------------------------------------\n\n"
            "  --------------------------------------------------------------------------------\n"
            "| How you doing traveler? Before we continue we need a few things from you! Ready? | \n"
            "| We need a seed from you, this will determine the games duration!                 | \n"
            "  --------------------------------------------------------------------------------\n\n");

    printf(">> ");

    /* Seed Check: Checks the seed inputted by the user and parse it into a string*/
    while (1){
        printf("Please input a seed from [1-9999] (Has to be a number): ");
        fgets(buffer, 100, stdin);
        printf("\n");

        /* If the input is a valid seed, then it converts it to a number
         * and exits the loop
         */
        if (valid_seed(buffer)){
            sscanf(buffer, "%d", &seed);
            break;
        }

        /* Else it will loop until there is a valid input*/
        printf(">> Wrong Input! ");
    }

    /* As soon as we get our seed, we can set our srand() function
     * so we can generate our random numbers!
     */
    srand(seed);

    /* Once we have our seed made, we now randomly generate our word for the game!*/
    generate_word(word);

    printf(">* Alright! Now that we have the seed, this will be the generated word for the game!\n\n"
           " -------------------------\n"
           "| Word of the Game: %s\n"
           " -------------------------\n\n", word);

    printf("## Oops! I forgot to ask about your name! What's your name traveler?\n");
    printf(">> ");

    /* This loop check that the name is a valid one! Will repeat until a valid name is entered*/
    while(1){
        printf("Please enter your name (Only Alphabetical characters and Max 8 characters): ");
        fgets(playerA, 100, stdin);
        printf("\n");

        /* If this is true, then the loop breaks! it also makes sure to get rid of the newline!*/
        if (validate_player_name(playerA)){
            playerA[strlen(playerA) - 1] = '\0';
            break;
        }

        /* Else it repeats!*/
        printf(">> Wrong Input!! ");
    }

    printf("\n------------------------------------------------------------\n"
           "|* Nice to meet you, %s! You will have fun with this game!\n"
           "------------------------------------------------------------\n\n", playerA);

    printf("## Now how would you like the two dices for this game to be? \n");

    /* This is the loop where we check for the sides of the dice, if they are valid sides
     * based on input! then it exits the loop, else they will get re-prompted */
    printf(">> ");
    while(1) {
        printf("Please input your sides int the form of \"#x#\" (Where # is a number): ");
        fgets(buffer, 100, stdin);
        printf("\n");

        if (validate_sides(buffer)){
            break;
        }

        printf(">> Wrong Input! ");
    }

    /* In here we parse the sides and store them in new variables*/
    int seenNum = 1;

    /* My logic: If the sides are valid input, then we can assume there will only be be two digits,
     * one digit in the left and another on in the right!
     *
     * The first number (digit) belongs to side A
     * The second number (digit) belongs to side B */
    for (int i = 0; i < strlen(buffer) - 1; i++){
        if (buffer[i] >= '0' && buffer[i] <= '9'){
            if (seenNum == 1){
                sscanf(&buffer[i], "%d", &sideA);
            }
            if (seenNum == 2){
                sscanf(&buffer[i], "%d", &sideB);
            }
            seenNum++;
        }
    }

    printf("* It's time to start!\n\n\n");

    /* One of the rules of the game is that if a user rolls the maximum number possible for both dices
     * they get a letter taken off from their word. */
    int maxRoll = sideA + sideB;
    int round = 1; /*Keeps track of rounds*/

    /* Essentially this loop is the whole game. It breaks once one person has lost, which
     * is the one who completed the word, or in this case the one who's accumulated 5 letters.
     */
    while(playerACounter < 5 && playerBCounter < 5){
        /* Prints the rounds*/
        printf("***************************************\n\n");
        printf(" -----------------------\n");
        printf("* Round %d starting now!\n", round);
        printf(" -----------------------\n\n");

        /* This part shows the rolls for each player*/
        printf(" --------------------------------\n\n");
        printf("|- %s is rolling the dice now!\n", playerA);
        temp1 = roll_dice(sideA) + roll_dice(sideB);
        playerASum += temp1; /* This is a temporary variable where current round rolls are stored*/
        printf("|-> %s rolled a %d\n", playerA, temp1);

        printf("\n");

        printf("|- %s is rolling the dice now!\n", playerB);
        temp2 = (roll_dice(sideA) + roll_dice(sideB));
        playerBSum += temp2;
        printf("|-> %s rolled a %d\n", playerB, temp2);
        printf("\n --------------------------------\n\n");

        /* A player whose rolls are less than the other player, gets added a letter*/
        if(temp2 > temp1){
            playerACounter += 1;
        }

        if (temp1 > temp2){
            playerBCounter += 1;
        }

        /* if a user gets the maximum rolls possible, then it will get a letter subtracted.*/
        if (temp1 == maxRoll && playerACounter != 0){
            playerACounter -= 1;
        }

        if (temp2 == maxRoll && playerBCounter != 0){
            playerBCounter -= 1;
        }

        /* Prints the state of the current word for each player based on current round*/
        printWord(playerA, word, playerACounter);
        printf("\n");
        printWord(playerB, word, playerBCounter);
        round++;
        printf("\n --------------------------------\n\n");
        printf("***************************************\n");
        printf("\n\n\n");
    }

    /* These two ternary operators decide the loser based on who has 5 letters (completed word)*/
    char * loser = (playerBCounter == 5) ? playerB: (playerACounter == 5) ? playerA: NULL;

    /* if the loser variable points to the same address of the first letter of the players name.
     * Then it's sum gets selected.*/
    int loserSum = (loser == &playerB[0]) ? playerBSum : (loser == &playerA[0]) ? playerASum: 0;

    printf("********************************\n\n");
    printf("|>> %s has lost the game!\n\n", loser);

    /* Cipher uses current word array, and shifts letter places based on the sum*/
    cipher(word, loserSum);

    //printf("player B: %d, player A: %d\n", playerBSum, playerASum);
    printf("|>> Their encrypted word is %s\n\n", word);
    printf("********************************\n\n");
    return 0;
}
