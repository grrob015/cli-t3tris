#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void){

    srand(time(NULL));

    _Bool board[10][13] = {0};
    char choice = ' ';

    //variables we need
    _Bool lineComplete = true;
    int highscore = 0;
    int column;
    int score = 0;
    int moves = 0;
    char scorename[3] = {'A', 'T', 'V'};
    int piece;
    int x = 0; 
    int y = 0;
    int testing;
    int replacingX;
    int replacingY;
    

    //------------------ MENU LOOP --------------------
    for(;choice != 'q';)
    {
        //Print menu
        printf("BadT3tris by Gabe (2024)\nr: rules | h: highscore | q: quit | n: new game\n-> ");
        choice = getchar();

        //sanitize input (so we don't type nnnnnnnnnn and buffer a bunch of games with no chance to quit.)
        while('\n' != getchar());

        //switch statement for choices
        switch(choice)
        {
            case 'q':
                break; //loop conditional will end main loop
            case 'r':
                printf("BadT3tris rules:\nMake complete rows of boxes to score points.\n");
                printf("Drop shapes made of boxes into place by typing the number of the column.\n");
                printf("The number will always refer to the leftmost column, which will be marked.\n");
                printf("If the shapes reach the top of the board, the game is over!\n");
                break;
            case 'h':
                if(highscore == 0)
                {
                    printf("No High Score registered yet! Play to take the throne!\n");
                } else {
                    printf("Highscore: %d by %c %c %c\n", highscore, scorename[0], scorename[1], scorename[2]);
                }  
                break;

            //game
            case 'n':
                //game specific variables
                
                //initialize array
                for(int zingy = 0; zingy <=12; zingy++)
                {
                    //row 13 is all 1s
                    if(zingy == 12)
                    {
                        for(int zingx = 0; zingx <= 9; zingx++) board[zingx][zingy] = 1;
                    } else {
                        for(int zingx = 0; zingx <= 9; zingx++) board[zingx][zingy] = 0;
                    }
                    
                }

                // -------------- MAIN GAME LOOP ----------------- //
                for(_Bool gamefail = false; gamefail != true;)
                {
                    //pick piece, notebook has piece labels
                    piece = (rand() % 6) + 1; 

                    //print board
                    for(y = 0; y <= 11; y++)
                    {
                        //print opening edge
                        printf("<!");
                        
                        //print data from array
                        for(x = 0; x <= 9; x++)
                        {
                            if(board[x][y])
                            {
                                printf("[]");
                            } else {
                                printf(" .");
                            }
                        }
                        //safe reset of variable after loop terminates
                        x = 0;

                        //print closing edge
                        printf("!>");
                        
                        //line dependent stuff
                        //all new lines contained here.
                        switch(y)
                        {
                            //First line will print score.
                            case 0:
                                printf("  Score: %d\n", score);
                                break;
                            //Second line prints move number.
                            case 1:
                                printf("  Moves: %d\n", moves);
                                break;
                            //Third line prints next piece text
                            case 2:
                                printf("  Next piece:\n");
                                break;
                            // Fourth line is empty for formatting
                            case 3:
                                printf("\n");
                                break;
                            //Next three lines are a clumsy network of switch statements to print out piece
                            case 4:
                                switch(piece)
                                {
                                    case 1:
                                        printf("    []\n");
                                        break;
                                    case 3:
                                        printf("  []\n");
                                        break;
                                    case 4:
                                        printf("  XX[]\n");
                                        break;
                                    case 5:
                                        printf("  [][]\n");
                                        break;
                                    case 6:
                                        printf("    []\n");
                                        break;
                                    default: 
                                        printf("\n");
                                    break;
                                }
                                break;
                            case 5:
                                switch(piece)
                                {
                                    case 1:
                                        printf("    []\n");
                                        break;
                                    //only case 2 we need
                                    case 2:
                                        printf("  XX[][]\n");
                                        break;
                                    case 3:
                                        printf("  XX[]\n");
                                        break;
                                    case 4:
                                        printf("    []\n");
                                        break;
                                    case 5:
                                        printf("  XX\n");
                                        break;
                                    case 6:
                                        printf("  XX[]\n");
                                        break;
                                    default: 
                                        printf("\n");
                                        break;
                                }
                                break;
                            //We only need this for one piece.
                            case 6:
                                switch(piece)
                                {
                                    case 1:
                                        printf("    XX\n");
                                        break;
                                    default:
                                        printf("\n");
                                        break;
                                }
                                break;
                            //If no case, then next line.
                            default:
                                printf("\n");
                                break;
                        }

                    }
                    //safe reset of variable after loop terminates
                    y = 0;

                    //print bottom row of board
                    printf("  -1-2-3-4-5-6-7-8-9-10\nColumn choice -> ");



                    //take input
                    scanf("%d", &column);
                        
                    //hard code sanity checks for each piece
                    retest:

                    if(column < 1 || column > 10)
                    {
                        printf("Invalid choice of column. New column -> ");
                        scanf("%d", &column);
                        goto retest;
                    }

                    switch(piece)
                    {
                        case 1:
                            break;
                        case 2:
                            if(column > 8)
                            {
                                printf("Invalid choice of column. New column -> ");
                                scanf("%d", &column);
                                goto retest;
                            }
                        //fall through
                        case 3:
                        case 4:
                        case 5:
                        case 6:
                            if(column == 10)
                            {
                                printf("Invalid choice of column. New column -> ");
                                scanf("%d", &column);
                                goto retest;
                            }
                            break;
                    }

                    //formatting line
                    printf("\n");

                    //update board
                    moves++;
                    
                    
                    testing = 0;

                    //if statements to check if piece is "above bounds" to avoid undefined behavior
                    switch(piece)
                    {
                        case 1:
                            //finds first occupied, then unoccupied square
                            while(!(board[column - 1][testing])) testing++;
                            testing--;
                            
                            //places block
                            board[column - 1][testing] = 1;
                            if(testing - 1 >= 0) board[column - 1][testing - 1] = 1;
                            if(testing - 2 >= 0) board[column - 1][testing - 2] = 1;
                            break;
                        
                        case 2:
                            //finds first occupied, then unoccupied space
                            while(!(board[column-1][testing] || board[column][testing] || board[column+1][testing])) testing++;
                            testing--;
                            
                            //places block
                            board[column-1][testing] = 1;
                            board[column][testing] = 1;
                            board[column+1][testing] = 1;
                            break;
                        case 3:
                            //finds first occupied, then unoccupied space.
                            while(!(board[column-1][testing] || board[column][testing])) testing++;
                            testing--;

                            //places block
                            board[column-1][testing] = 1;
                            board[column][testing] = 1;
                            if(testing - 1 >= 0) board[column-1][testing-1] = 1;
                            break;
                        case 4:
                            //finds first occupied, then unoccupied space
                            testing = 1;
                            while(!(board[column-1][testing-1] || board[column][testing])) testing++;
                            testing--;

                            //places block
                            board[column][testing] = 1;
                            if(testing - 1 >= 0)
                            {
                                board[column-1][testing-1] = 1;
                                board[column][testing-1] = 1;
                            }
                            break;
                        case 5:
                            //finds first unoccupied, then occupied space
                            testing = 1;
                            while(!(board[column-1][testing] || board[column][testing -1])) testing++;
                            testing--;

                            //places block
                            board[column-1][testing] = 1;
                            if(testing - 1 >= 0)
                            {
                                board[column-1][testing-1] = 1;
                                board[column][testing-1] = 1;
                            }
                            break;
                        case 6:
                            //finds first occupied, then unoccupied space
                            while(!(board[column-1][testing] || board[column][testing])) testing++;
                            testing--;

                            //places block
                            board[column-1][testing] = 1;
                            board[column][testing] = 1;
                            if(testing - 1 >= 0) board[column][testing -1] = 1;
                            break;
                    }

                    //safe reset of variable for use later
                    testing = 0;

                    //full lines are removed from the bottom up and score is calculated + updated
                    //sorking herer
                    
                    //in this loop, testing represents the amount of lines cleared in one move
                    //the higher testing is, the bigger the score per move.
                    for(y = 11;y >= 0; y--)
                    {
                        lineComplete = true;

                        for (x = 0; x <= 9; x++) 
                        {
                            if(!(board[x][y]))
                            {
                                lineComplete = false;
                            }
                        }

                        //move everything down normally.
                        if(lineComplete && (y != 0))
                        {
                            testing++;
                            
                            for(replacingY = y; replacingY >= 1; replacingY--)
                            {
                                for(replacingX = 0; replacingX <= 9; replacingX++)
                                {
                                    board[replacingX][replacingY] = board[replacingX][replacingY - 1];
                                }
                            }

                            //after everything is replaced, move y down so a line doesn't get skipped.
                            y++;
                        
                        } else if (lineComplete && (y == 0)) {
                            
                            testing++;

                            for(replacingX = 0; replacingX <= 9; replacingX++)
                            {
                                board[replacingX][y] = 0;
                            }
                            //y doesn't need to move down, this is a one time scenario.

                        }
                    }

                    //calculate score
                    switch(testing)
                    {
                        case 1:
                            score += 40;
                            break;
                        case 2:
                            score += 100;
                            break;
                        case 3:
                            score += 250;
                            break;
                        default:
                            break;
                    }

                    //safe reset of variable
                    testing = 0;

                    //test for game fail and update var if needed
                    //im too lazy to write a for loop and i don't want to initialize a new variable
                    //every time for memory purposes
                    
                    if(board[0][0] || board[1][0] || board[2][0] || board[3][0] || board[4][0] || board[5][0] || board[6][0] || board[7][0] || board[8][0] || board[9][0])
                    {
                        gamefail = true;
                    }

                }
                // ------ END GAME LOOP ------- //

                //compare and switch highscore to score if needed
                //if new highscore, input new initials.
                
                //sanitize again
                while('\n' != getchar());

                if(score > highscore)
                {
                    highscore = score;
                    printf("New high score of %d detected!\n", score);
                    printf("Enter your initials (Three letters separated by spaces Ex. A B C): ");
                    scanf("%c %c %c",&scorename[0], &scorename[1], &scorename[2]);
                } else {
                    printf("Final score: %d\n", score);
                }

                //reset score and moves variables
                score = 0;
                moves = 0;

                //sanitize the input
                while('\n' != getchar());

                // ----------------- END MAIN MENU PORTION ------------------ //
                break;
            default: 
                printf("Invalid input.\n");
                break;
        }
    }
    return 0;
}
