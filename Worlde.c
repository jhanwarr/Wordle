#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//libraries needed by the program

#define MAX_TURNS 5
#define WORDS_PRESENT 8
//the constant max turns shoule be the word length 


//displaying the highlighted word as a hint for the player

void display (int pos[], char *guess)
{
    for (int i = 0; i <= MAX_TURNS; i++)
    {
        if (pos[i] == 1)
            printf("\033[1;32;42m%c\033[0;30;m ", guess[i]); //light green highlight; dark green text
        
        else if (pos[i] == 2)
            printf("\033[1;33;43m%c\033[0;0;m ", guess[i]); //yellow highlight; white text
        
        else
            printf("%c ", guess[i]); //text without any highlights
    }
    
    printf("\n");
}

//checking whether given character is present in the string req

int charCheck (char ch, const char *req, int checked[])
{
    for (int i = 0; i < MAX_TURNS; i++)
    {
        if ( (!checked[i]) && (ch == req[i]))
        {
            checked[i] = 1;
            return 1;
        }
    }
    
    return 0;
}


/*
checking the characters common and their placements for analyzing the 
background color to be displayed along with it
*/

int checkEquals (const char *guess, const char *req, int pos[], int checked[])
{
    int index[MAX_TURNS];
    
    for (int i = 0; i < MAX_TURNS; i++)
        index[i] = -1;
    //initialization of index
    
    int same_chars = 0;
    
    for (int i = 0; i < MAX_TURNS; i++)
        pos[i] = 0;
    //initialization of pos (0 stands for no highlight)
    
    for (int i = 0; i < MAX_TURNS; i++)
    {
        if (guess[i] == req[i])
        {
            index[i] = i; //adding the indices already checked for the 'guess'
            checked[i] = 1; //adding the indices checked for the 'req'
            pos[i] = 1; //the color scheme is to be green (1 stands for green)
            same_chars++;
        }
    }
    
    //checking for the characters left
    
    for (int i = 0; i < MAX_TURNS; i++)
    {
        if ( (index[i] != i) && charCheck (guess[i], req, checked))
        {
            pos[i] = 2; //the color scheme is to be yellow (2 stands for yellow)
        }
    }
    
    return same_chars;
}

//inputting the user's guess

void input (char *guess)
{
    char ch;
    while ( (ch = getchar ()) != '\n')
    {
        *guess = ch;
        guess++;
    }
    
    *guess = '\0';
    
    printf ("\n");
}

int main ()
{
    srand (time (NULL));
    //for generating random numbers

    printf("Information - \n");
    printf("You have %d chances to guess a word of length %d.\n", MAX_TURNS, MAX_TURNS);
    printf("The letters highlighted after your guess are present in the word.\n");
    printf("The letters highlighted in yellow are placed at the wrong position.\n");
    printf("The letters highlighted in green are placed at the right position.\n\n");
    //Brief info for playing the game
    

    char *words[WORDS_PRESENT] = {"apple", "adieu", "haste", "hello", "house", "right", "under", "young"};
    //set of words which would be assigned randomly
    
    int score = 0;
    int rounds = 1;
    
    //variables needed for the all the rounds
    
    
    while (1)
    {    
        //ROUNDS 
        
        
        char *req = words[rand () % (MAX_TURNS+1)];
        //choosing a randome word from the array

        char guess[MAX_TURNS + 1];
        int pos[MAX_TURNS + 1];
    
        int turn = 1;
        int won = 0;
    
        //variables needed for each rounds
    
    
        while ( (turn <= MAX_TURNS) && !won)
        {
            //TURNS in each round
            
            int checked[MAX_TURNS];
            
            for(int i = 0; i < MAX_TURNS; i++)
                checked[i] = 0;
            
            /*
            initialization of checked, which is used for ensuring 
            multiple checks for one word doesn't take place
            */
            
            while (1)
            { 
                //Validating the user input
                
                printf ("\nGuess %d: \n", turn);
                
                input (guess);
                
                if (strlen (guess) == MAX_TURNS)
                {
                    break;
                }
                
                printf ("Wrong length of the word. Please enter again with the correct length.\n");
            }
            
            int contains_same = checkEquals (guess, req, pos, checked);
            display (pos, guess);
            
            turn++;
            
            if (contains_same == MAX_TURNS)
            {
                printf ("Hurray! You won the game!\n");

                won = 1;
                score++;
            }
        }
    
        if (!won)
        {
            printf ("Oops, the word to be guessed was: %s.\n", req);
            printf ("Please try again.\n");
        }
        
        //Scorecard
        
        printf ("Statistics : \n\n");
    
        printf ("Rounds     :   %d\n", rounds);
        printf ("Score      :   %d\n\n", score);
    
        
        int choice;
        
        if(rounds == WORDS_PRESENT)
            break;
        
        printf ("Enter '0' to exit the game or '1' to play again.\n");
        scanf ("%d", &choice);
        printf ("\n\n");
        
        if (!choice)
            break;
        
        rounds++;
    }
    
    //Scorecard
    
    printf ("Statistics : \n\n");
    
    printf ("Rounds     :   %d\n", rounds);
    printf ("Score      :   %d\n\n", score);
    
    printf ("Thank You so much! I hope you had fun!");
    
    return 0;
    //returning 0 and exiting the code 
}
