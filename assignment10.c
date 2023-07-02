// PROJECT ARCODE

// SPECIAL THANKS TO PROFESSOR CHANDRANATH ADAK & PROFFERSOR MAYANK AGARWAL FOR GUIDING US.

// Header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

// GAME 1 -- BROKEN CALCULATOR (By HARSHVARDHAN [2201EE30] & LAKSHYA SINGH [2201CE30])
// GAME 2 -- MINESWEEPER (By ISH KAPOOR [2201EE31])
// GAME 3 -- HANGMAN (By KUSHAL AGARWAL [2201MC22] & MOJAMMIL WARSI [2201CB34])
// GAME 4 -- QUIZ GAME (By ADIL [2201CS46] & MRIDUL [2201MM21])
// GAME 5 -- SUDUKO (By KANISHK SINGHAL [2201MC21])
// GAME 6 -- Tic-Tac-Toe (By METLA UMESH CHANDRA [2201AI24])

// Game 1 starts -

typedef struct stack1 // creating stack1 for postfix conversion
{
    char arr[35];
    int top;
} st1;

void push1(st1 *s, char item)
{
    s->arr[++s->top] = item;
}
char pop1(st1 *s)
{
    return s->arr[s->top--];
}

typedef struct stack2 // creating stack for postfix solving
{
    int arr[35];
    int top;
} st2;

void push2(st2 *s, int item)
{
    s->arr[++s->top] = item;
}

int pop2(st2 *s)
{
    s->top--;
    return s->arr[s->top + 1];
}

int prec(char a) // function for precedence
{
    if (a == '+' || a == '-')
        return 0;
    if (a == '*' || a == '/')
        return 1;
    if (a == '^')
        return 2;
    if (a == '(')
        return -1;
}

char *infixtopostfix(char a[], char arr[])
{
    st1 sck1;
    st1 *stack1 = &sck1; // stack1 for expressison conversion
    stack1->top = -1;    // initializing staack
    int index = 0;

    for (int i = 0; i < 100 && a[i] != '\0'; i++)
    {
        switch (a[i])
        {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
        {
            arr[index++] = a[i];
            break;
        }

        case '*':
        case '/':
        case '+':
        case '-':
        {
            if (stack1->arr[stack1->top] == '(')
            {
                push1(stack1, a[i]);
                break;
            }
            while (prec(a[i]) <= prec(stack1->arr[stack1->top]) && stack1->top != -1)
            {
                arr[index++] = pop1(stack1);
            }
            push1(stack1, a[i]);
            break;
        }

        case '(':
        case '^':
        {
            push1(stack1, a[i]);
            break;
        }

        case ')':
        {
            while (stack1->arr[stack1->top] != '(')
            {
                arr[index++] = pop1(stack1);
            }
            pop1(stack1);
            break;
        }
        }
    }
    while (stack1->top != -1)
        arr[index++] = pop1(stack1);

    return arr;
}

int postfixsolve(char *a)
{
    st2 sck2;
    st2 *stack2 = &sck2; // stack2 for solving expression
    stack2->top = -1;    // initializing stack

    for (int i = 0; i < 100 && a[i] != '\0'; i++)
    {
        switch (a[i])
        {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
        {
            push2(stack2, a[i] - 48);
            break;
        }

        case '+':
        {
            push2(stack2, (pop2(stack2) + pop2(stack2)));
            break;
        }
        case '*':
        {
            push2(stack2, (pop2(stack2) * pop2(stack2)));
            break;
        }
        case '-':
        {
            int a = pop2(stack2);
            push2(stack2, (pop2(stack2) - a));
            break;
        }
        case '/':
        {
            int a = pop2(stack2);
            push2(stack2, (pop2(stack2) / a));
            break;
        }
        case '^':
        {
            int a = pop2(stack2);
            push2(stack2, (int)pow(pop2(stack2), a));
            break;
        }
        }
    }
    return stack2->arr[stack2->top];
}

int notincheck(char a, char arr[])
{
    int flag = 1;
    for (int j = 0; j < strlen(arr); j++)
    {
        if (a == arr[j])
        {
            flag = 0;
            break;
        }
    }
    return flag;
}
// LEVELS

int source(int numbers[], int elements, char operands[], char operators[], int level)
{
    char both[15];
    strcat(both, operands);
    strcat(both, operators);
    int result = 0;
    char *expression;
    char *postexpression;

    while (elements != 0)

    {
        expression = (char *)malloc(200);
        postexpression = (char *)malloc(200);
        printf("\n \033[1;34m     [         \033[0m");
        printf("\033[1;33m%d\033[0m", result);
        printf("\033[1;34m         ]\033[0m", result); // Format
        printf("\n\n\n\033[1;36m      Numbers Avaialable\033[0m \033[1;34m :\033[0m  ");
        for (int i = 0; i < strlen(operands); i++)
            printf("\033[1;35m  %c  \033[0m", operands[i]);
        printf("\n\n\n ");
        printf("\033[1;36m     Operators Available\033[0m \033[1;34m: \033[0m  ");
        for (int i = 0; i < strlen(operators); i++)
            printf("\033[1;35m  %c  \033[0m", operators[i]);
        printf("   \n\n\n ");
        printf(" \033[1;36m    Numbers remaining\033[0m \033[1;34m : \033[0m  \033[1;35m");

        for (int i = 0; i < elements; i++)
        {
            printf(" %d  ", numbers[i]);
        }
        printf("\033[0m\n\n\n\033[1;36m      ENTER your expresssion\033[0m \033[1;32mpress c to confirm/clear\033[0m \033[1;34m : \033[0m ");
        scanf("%s", expression);
        system("cls");

        if (expression[0] == 'c')
        {
            for (int i = 0; i < elements; i++)
            {
                if (result == numbers[i])
                {
                    for (int j = i; j < elements - 1; j++)
                        numbers[j] = numbers[j + 1];
                    elements--;
                }
            }
            result = 0;
            // free(expression);
        }
        else
        {
            int flag1 = 0;
            for (int i = 0; i < strlen(expression); i++)
            {
                if (notincheck(expression[i], both))
                {
                    flag1 = 1;
                    break;
                }
            }
            if (flag1 == 1)
            {
                printf("\033[1;31m      INVALID OPERATOR or OPERAND\033[0m\n");
                // free(expression);
            }
            else
            {
                result = postfixsolve(infixtopostfix(expression, postexpression));
            }
        }
    }
}

void level1()
{
    int numbers[] = {6, 18, 12, 29, 43, 91};
    int elements = 6;
    int level = 1;
    char operands[5] = "23";
    char operator[5] = "+*";
    source(numbers, elements, operands, operator, level);
    printf(" \n\n\n\n YOu have passed level %d \n\n\n", level);
}

void level2()
{
    int numbers[] = {3, 19, 41, 99, 200};
    int elements = 5;
    int level = 2;
    char operands[5] = "457";
    char operator[5] = "-*/";
    source(numbers, elements, operands, operator, level);
    printf(" \n\n\n\n YOu have passed level %d \n\n\n", level);
}
void level3()
{
    int numbers[] = {21, 69, 146, 169, 231};
    int elements = 5;
    int level = 3;
    char operands[9] = "256";
    char operator[8] = "+-*()";
    source(numbers, elements, operands, operator, level);
    printf(" \n\n\n\n YOu have passed level %d \n\n\n", level);
}
void level4()
{
    int numbers[] = {69, 97, 294, 784, 3969};
    int elements = 5;
    int level = 4;
    char operands[9] = "237";
    char operator[9] = "+-^()";
    source(numbers, elements, operands, operator, level);
    printf(" \n\n\n\n YOu have passed level %d \n\n\n", level);
}

// GAME 2 -- MINESWEEPER (By ISH KAPOOR [2201EE31])

#define FLUSH fflush(stdin)

void difficulty(void);
void beginner(void);
void intermediate(void);
void expert(void);
void minefield_generator(void);
void print_minefield(void);
void guess(void);
void boom(void);
void print_final_minefield(void);
void win(void);
void play_again(void);
void game_over(void);
void custom(void);

int x, y;
int M, N;
float diff;
int total_mines = 0;
int mines = 0;
int minefield[30][30];       // This 2-D array contains all of the mines, numbers and blank spaces
int blank_minefield[30][30]; // This contains the minefield full of '|-|' characters
int final_minefield[30][30];

void difficulty(void) // Function for choosing the difficulty level
{
    diff = 0;
    while ((diff != 1) && (diff != 2) && (diff != 3) && (diff != 4))
    {
        printf("\t\tChoose a difficulty level(1-3) or 4 for a custom game:");
        scanf("%f", &diff);
        FLUSH;
        if ((diff != 1) && (diff != 2) && (diff != 3) && (diff != 4))
        {
            printf("\t\tPlease enter either 1, 2, 3 or 4\n");
        }
    }

    if (diff == 1) // If, else if and else statements that each go to the respective difficulty
    {
        beginner();
    }
    else if (diff == 2)
    {
        intermediate();
    }
    else if (diff == 3)
    {
        expert();
    }
    else if (diff == 4)
    {
        custom();
    }
}

void beginner(void) // Gives the minefield the 'beginner' grid and mines
{
    M = 9;
    N = 9;
    total_mines = 10;
    minefield_generator();
    guess();
}

void intermediate(void) // Gives the minefield the 'intermediate' grid and mines
{
    M = 16;
    N = 16;
    total_mines = 40;
    minefield_generator();
    guess();
}

void expert(void) // Gives the minefield the 'expert' grid size and mines
{
    M = 16;
    N = 30;
    total_mines = 99;
    minefield_generator();
    guess();
}

void custom(void)
{
    M = 0;
    N = 0;
    total_mines = 0;
    printf("\t\tPlease enter the size of the dimensions you want\n");
    printf("\t\tFirst value:\n");
    scanf("%d", &M);
    printf("\t\tSecond value:\n");
    scanf("%d", &N);
    printf("\t\tNumber of mines you want to assign to the board:\n");
    scanf("%d", &total_mines);
    minefield_generator();
    guess();
}

void minefield_generator(void) // Function that generates the minefield
{
    int i = 0, j = 0;

    srand(time(NULL)); // Starts the random no. generator

    while (j < N) // Nested loop for making the blank minefield and final minefield
    {
        while (i < M)
        {
            minefield[i][j] = '-';
            blank_minefield[i][j] = minefield[i][j];
            final_minefield[i][j] = minefield[i][j];
            i++;
        }
        i = 0;
        j++;
    }
    mines = 0;
    while (mines < total_mines) // Randomly generates the mines into the minefield
    {
        i = rand() % (M);
        j = rand() % (N);
        if (minefield[i][j] != '*') // If statement that checks if there is a mine already there and doesn't place a mine if there is
        {
            minefield[i][j] = '*';
            final_minefield[i][j] = minefield[i][j];
            mines++;
        }
    }
    i = 0;
    j = 0;

    while (j < N) // While loop that generates the numbers for any adjacent mines
    {
        while (i < M)
        {
            if (minefield[i][j] != '*')
            {
                minefield[i][j] = 0;
            }
            if ((minefield[i - 1][j - 1] == '*') && (minefield[i][j] != '*'))
            {
                minefield[i][j]++;
            }
            if ((minefield[i - 1][j] == '*') && (minefield[i][j] != '*'))
            {
                minefield[i][j]++;
            }
            if ((minefield[i][j - 1] == '*') && (minefield[i][j] != '*'))
            {
                minefield[i][j]++;
            }
            if ((minefield[i - 1][j + 1] == '*') && (minefield[i][j] != '*'))
            {
                minefield[i][j]++;
            }
            if ((minefield[i + 1][j - 1] == '*') && (minefield[i][j] != '*'))
            {
                minefield[i][j]++;
            }
            if ((minefield[i + 1][j] == '*') && (minefield[i][j] != '*'))
            {
                minefield[i][j]++;
            }
            if ((minefield[i][j + 1] == '*') && (minefield[i][j] != '*'))
            {
                minefield[i][j]++;
            }
            if ((minefield[i + 1][j + 1] == '*') && (minefield[i][j] != '*'))
            {
                minefield[i][j]++;
            }
            i++;
        }
        i = 0;
        j++;
    }
    i = 0;
    j = 0;
}

void print_minefield(void) // This function prints the minefield
{
    int i = 0, j = 0, z = 0;
    while (z < M) // This while loop prints out the line of co-ordinates along the x axis of the minefield
    {
        if (z == 0)
        {
            printf("\t");
        }
        printf("|%d|\t", z);
        z++;
    }
    printf("\n\n");

    while (j < N) // Loop that prints out each character in the minefield
    {
        printf("|%d|\t", j);
        while (i < M)
        {
            if (blank_minefield[i][j] == '-')
            {
                printf("|%c|\t", blank_minefield[i][j]);
            }
            else if (minefield[i][j] == 0) // This changes any spaces with values of zero to the character 'B'
            {
                blank_minefield[i][j] = 'B';
                printf("|%c|\t", blank_minefield[i][j]);
            }
            else
            {
                printf("|%d|\t", blank_minefield[i][j]);
            }
            i++;
        }
        printf("\n");
        i = 0;
        j++;
    }
}

void guess(void)
{
    int q = 0, i = 0, j = 0, match = 0;
    print_minefield();
    while (j < N) // While loop for testing whether or not the user has cleared the minefield
    {
        while (i < M)
        {
            if (minefield[i][j] == blank_minefield[i][j])
            {
                match++;
            }
            i++;
        }
        i = 0;
        j++;
    }
    if (match == ((M * N) - total_mines)) // If the user has cleared the minefield, the win() function is run
    {
        win();
    }
    printf("\nEnter the x value, then a space, then the y value:");
    scanf("%d %d", &x, &y); // Reading in the co-ordinates for the guess
    FLUSH;
    if ((x >= M) || (x < 0) || (y < 0) || (y >= N))
    {
        printf("\nPlease enter a value inside the grid\n");
        guess();
    }
    if (minefield[x][y] == '*') // Runs the boom() function if the user selects a mine
    {
        boom();
    }
    if (blank_minefield[x][y] != '-')
    {
        printf("\nPlease enter a value that has not already been entered\n");
        guess();
    }

    else // Checks if the adjacent spaces are blank, then changes the values in the blank_minefield array. Because they are changed, they will now print out in the print_minefield function
    {
        blank_minefield[x][y] = minefield[x][y];
        if (minefield[x][y] == 0)
        {
            if (minefield[x - 1][y - 1] == 0)
            {
                blank_minefield[x - 1][y] = minefield[x - 1][y];
            }
            if (minefield[x - 1][y] == 0)
            {
                blank_minefield[x - 1][y] = minefield[x - 1][y];
            }
            if (minefield[x][y - 1] == 0)
            {
                blank_minefield[x][y - 1] = minefield[x][y - 1];
            }
            if (minefield[x - 1][y + 1] == 0)
            {
                blank_minefield[x - 1][y + 1] = minefield[x - 1][y + 1];
            }
            if (minefield[x + 1][y - 1] == 0)
            {
                blank_minefield[x + 1][y - 1] = minefield[x + 1][y - 1];
            }
            if (minefield[x + 1][y] == 0)
            {
                blank_minefield[x + 1][y] = minefield[x + 1][y];
            }
            if (minefield[x][y + 1] == 0)
            {
                blank_minefield[x][y + 1] = minefield[x][y + 1];
            }
            if (minefield[x + 1][y + 1] == 0)
            {
                blank_minefield[x + 1][y + 1] = minefield[x + 1][y + 1];
            }
        }
        guess();
    }
}

void boom(void) // Runs the print_final_minefield function, then the play_again function
{
    print_final_minefield();
    printf("\n\t\tYou hit a mine at %d,%d\n\t\tYOU LOSE!!!!", x, y);
    play_again();
}

void print_final_minefield(void) // Prints the minefield, showing where all of the mines are placed
{
    int i = 0, j = 0, z = 0;
    while (z < M)
    {
        if (z == 0)
        {
            printf("\t");
        }
        printf("|%d|\t", z);
        z++;
    }
    printf("\n\n");

    while (j < N)
    {
        printf("|%d|\t", j);
        while (i < M)
        {
            printf("|%c|\t", final_minefield[i][j]);
            i++;
        }
        printf("\n");
        i = 0;
        j++;
    }
}

void win(void) // Runs the play_again function
{
    printf("\n\n\n\t\t\tYOU WIN!!!!!\n\n\n");
    play_again();
}

void play_again(void) // Gives the user the option to play again
{
    char option[2];
    printf("\n\t\tWould you like to play again(Y/N)?:");
    scanf("%c", &option[0]);
    FLUSH;
    if ((option[0] == 'Y') || (option[0] == 'y')) // Restarts the program from after the welcome message
    {
        difficulty();
    }
    else if ((option[0] == 'N') || (option[0] == 'n'))
    {
        game_over();
    }
    else
    {
        printf("Please enter either Y or N");
        play_again();
    }
}

void game_over(void) // Ends the program
{
    printf("\n\n\t\tGame Over");
    exit(1);
}

// Game 3 -- Hangman (By kushal Agarwal [2201MC22] & Mojammil Warsi [2201CB34])

void showHangman(int);

void showHangman(int choice)
// This function show the hangman after each wrong try
{
    switch (choice)
    {

    case 0:
        system("cls");
        printf("\n\t||===== ");
        printf("\n\t||  \033[1;31m  | \033[0m");
        printf("\n\t||   \033[1;31m%cO/\033[0m", '\\');
        printf("\n\t||    \033[1;31m|\033[0m ");
        printf("\n\t||   \033[1;31m/ %c\033[0m", '\\');
        printf("\n\t||      ");
        break;
    case 1:
        system("cls");
        printf("\n\t||===== ");
        printf("\n\t||   \033[1;31m | \033[0m");
        printf("\n\t||  \033[1;31m %cO/\033[0m", '\\');
        printf("\n\t||   \033[1;31m |\033[0m ");
        printf("\n\t||   \033[1;31m  %c\033[0m", '\\');
        printf("\n\t||      ");
        break;
    case 2:
        system("cls");
        printf("\n\t||===== ");
        printf("\n\t||    \033[1;31m|\033[0m ");
        printf("\n\t||  \033[1;31m %cO/\033[0m", '\\');
        printf("\n\t||   \033[1;31m |\033[0m ");
        printf("\n\t||      ");
        printf("\n\t||      ");
        break;
    case 3:
        system("cls");
        printf("\n\t||===== ");
        printf("\n\t||     \033[1;31m|\033[0m ");
        printf("\n\t||   \033[1;31m %cO/\033[0m", '\\');
        printf("\n\t||      ");
        printf("\n\t||      ");
        printf("\n\t||      ");
        break;
    case 4:
        system("cls");
        printf("\n\t||===== ");
        printf("\n\t||     \033[1;31m|\033[0m ");
        printf("\n\t||   \033[1;31m %cO\033[0m ", '\\');
        printf("\n\t||      ");
        printf("\n\t||      ");
        printf("\n\t||      ");
        break;
    case 5:
        system("cls");
        printf("\n\t||===== ");
        printf("\n\t||     \033[1;31m|\033[0m ");
        printf("\n\t||     \033[1;31mO\033[0m ");
        printf("\n\t||      ");
        printf("\n\t||      ");
        printf("\n\t||      ");
        break;
    }
    return;
}

// GAME 4 -- QUIZ GAME (By MRIDUL [2201MM21] & ADIL ANSARI [2201CS46])

void mainhome();

int check(char c) // making a function for checking validity of input...
{
    if (toupper(c) != 'A' && toupper(c) != 'B' && toupper(c) != 'C' && toupper(c) != 'D')
    {
        return 1;
    }
    else
        return 0;
}
void show_record();
int count = 0; // declaring global variables to store the score during the game...
int count1 = 0;
int maxcount = 0;
void quit()
{
    return; // For exiting we are simply returning...
}
void question()
{
    char s = getchar();
    // Code for warmup round.
    for (int i = 1; i <= 3; i++) // three question for warmup round...
    {
        system("cls");
        char c;
        char ch;
        switch (i)
        {
        case 1:
        A:
            printf("\n\nWhat is the brain of computer system called?");
            printf("\n\nA.UPS\t\tB.GPU\n\nC.CPU\t\tD.None of the above\n");

            scanf("%c", &c); // taking input as character

            if (toupper(c) == 'C')
            {
                count1++;
                printf("\ncorrect.\n");
                ch = getchar();
                char ci = getchar();
                break;
            }

            else if (check(c)) // if input is wrong then again repeat the question //if input is wrong then repeat the question
            {
                printf("\nInvalid Choice\n");
                printf("\nPlease press enter to again enter the choice");
                getchar();
                getchar();
                goto A;
            }

            else
            {
                printf("\nWrong answer.\n");
                ch = getchar();
                char ci = getchar();
                break;
            }

        case 2:
        A1:
            system("cls");
            printf("\n\nWhich of the following is a Palindrome number?");
            printf("\n\nA.42042\t\tB.101010\n\nC.23232\t\tD.01234\n");

            scanf("%c", &c); // taking input as character

            if (toupper(c) == 'C')
            {
                count1++;
                printf("\ncorrect.\n");
                ch = getchar();
                char ci = getchar();
                break;
            }
            else if (check(c)) // if input is wrong then repeat the question
            {
                printf("\n Invalid Choice\n");
                printf("\nPlease press enter to again enter the choice.\n");
                getchar();
                getchar();
                goto A1;
            }
            else
            {
                printf("\nWrong answer.\n");
                ch = getchar();
                char ci = getchar();
                break;
            }
        case 3:
        A2:
            printf("\n\n\nWhat does RAM stands for?");
            printf("\n\nA.Remote Access Memory\t\tB.Random Access Memory\n\nC.Reallocate Automatic Memory\t\tD.None of these\n");
            scanf("%c", &c); // taking input as character
            if (toupper(c) == 'B')
            {
                count1++;
                printf("\ncorrect.\n");
                ch = getchar();
                char ci = getchar();
                break;
            }
            else if (check(c)) // if input is wrong then repeat the question
            {
                printf("\nInvalid Choice\n");
                printf("\nPlease press enter to again enter the choice");
                getchar();
                getchar();
                goto A2;
            }
            else
            {
                printf("\nWrong answer.\n");
                ch = getchar();
                char ci = getchar();
                break;
            }
        }
    }
    // code for final round.
    if (count1 >= 2) // if qualified then only move to final round
    {
        system("cls");
        printf("\nCongratulation you are qualified for the final round.\n");
        printf("\nPress enter to resume the game.\n");
        getchar();
        for (int i = 1; i <= 10; i++) // 10 questions for final round
        {
            system("cls");
            char c;
            char ch;
            switch (i)
            {
            case 1:
            A4:
                printf("\n\nWhich among the following is not an operating system?");
                printf("\n\nA.UNIX\t\tB.LINUX\n\nC.OS X\t\tD.PITEX\n");

                scanf("%c", &c); // taking input as character

                if (toupper(c) == 'D')
                {
                    count++;
                    printf("\ncorrect.\n");
                    ch = getchar();
                    char ci = getchar();
                    break;
                }
                else if (check(c)) // if input is wrong then repeat the question
                {
                    printf("\nInvalid Choice\n");
                    printf("\nPlease press enter to again enter the choice");
                    getchar();
                    getchar();
                    goto A4;
                }
                else
                {
                    printf("\nWrong answer.\n");
                    ch = getchar();
                    char ci = getchar();
                    break;
                }

            case 2:
            A5:
                printf("\n\n\n Who among the following is popular as the father of computer?");
                printf("\n\nA. Charles Babbage\t\tB.Scott Aaronson\n\nC. Charles Bachman\t\tD. David A. Bader\n");

                scanf("%c", &c); // taking input as character
                if (toupper(c) == 'A')
                {
                    count++;
                    printf("\ncorrect.\n");
                    ch = getchar();
                    char ci = getchar();
                    break;
                }
                else if (check(c)) // if input is wrong then repeat the question
                {
                    printf("\nInvalid Choice\n");
                    printf("\nPlease press enter to again enter the choice");
                    getchar();
                    getchar();
                    goto A5;
                }
                else
                {
                    printf("\nWrong answer.\n");
                    ch = getchar();
                    char ci = getchar();
                    break;
                }
            case 3:
            A6:
                printf("\n\n\nWho among the following first invented the computer mouse?");
                printf("\n\nA - Douglas C. Engelbartr\t\tB - Adam Osborne\n\nC - Adi Shamir\t\tD - Alain Glavieux\n");
                scanf("%c", &c); // taking input as character
                if (toupper(c) == 'A')
                {
                    count++;
                    printf("\ncorrect.\n");
                    ch = getchar();
                    char ci = getchar();
                    break;
                }
                else if (check(c)) // if input is wrong then repeat the question
                {
                    printf("\nInvalid Choice\n");
                    printf("\nPlease press enter to again enter the choice");
                    getchar();
                    getchar();
                    goto A6;
                }
                else
                {
                    printf("\nWrong answer.\n");
                    ch = getchar();
                    char ci = getchar();
                    break;
                }
            case 4:
            A7:
                printf("\n\n\nWho among the following is known as the Father of DNA Computing?");
                printf("\n\nA - Leonard Adleman\t\tB - Lee de Forest\n\nC - Leonardo da Vinci\t\tD - Leon Bollee\n");
                scanf("%c", &c); // taking input as character
                if (toupper(c) == 'A')
                {
                    count++;
                    printf("\ncorrect.\n");
                    ch = getchar();
                    char ci = getchar();
                    break;
                }
                else if (check(c)) // if input is wrong then repeat the question
                {
                    printf("\nInvalid Choice\n");
                    printf("\nPlease press enter to again enter the choice");
                    getchar();
                    getchar();
                    goto A7;
                }
                else
                {
                    printf("\nWrong answer.\n");
                    ch = getchar();
                    char ci = getchar();
                    break;
                }
            case 5:
            A8:
                printf("\n\n\nThe information stored in a computer is known as");
                printf("\n\nA - Facts\t\tB - Files\n\nC - Data\t\tD - Directory or repository\n");
                scanf("%c", &c); // taking input as character
                if (toupper(c) == 'C')
                {
                    count++;
                    printf("\ncorrect.\n");
                    ch = getchar();
                    char ci = getchar();
                    break;
                }
                else if (check(c)) // if input is wrong then repeat the question
                {
                    printf("\nInvalid Choice\n");
                    printf("\nPlease press enter to again enter the choice");
                    getchar();
                    getchar();
                    goto A8;
                }
                else
                {
                    printf("\nWrong answer.\n");
                    ch = getchar();
                    char ci = getchar();
                    break;
                }
            case 6:
            A9:
                printf("\n\n\nWhich among the following works faster?");
                printf("\n\nA - RAM\t\tB - Cache\n\nC - Register\t\tD - ROM\n");
                scanf("%c", &c); // taking input as character
                if (toupper(c) == 'B')
                {
                    count++;
                    printf("\ncorrect.\n");
                    ch = getchar();
                    char ci = getchar();
                    break;
                }
                else if (check(c)) // if input is wrong then repeat the question
                {
                    printf("\nInvalid Choice\n");
                    printf("\nPlease press enter to again enter the choice");
                    getchar();
                    getchar();
                    goto A9;
                }
                else
                {
                    printf("\nWrong answer.\n");
                    ch = getchar();
                    char ci = getchar();
                    break;
                }
            case 7:
            A10:
                printf("\n\n\nWhich among the following is not a computer virus?");
                printf("\n\nA - Good morning\t\tB - I Love you\n\nC - Monkey\t\tD - Happy Birthday Joshi\n");
                scanf("%c", &c); // taking input as character
                if (toupper(c) == 'A')
                {
                    count++;
                    printf("\ncorrect.\n");
                    ch = getchar();
                    char ci = getchar();
                    break;
                }
                else if (check(c)) // if input is wrong then repeat the question
                {
                    printf("\nInvalid Choice\n");
                    printf("\nPlease press enter to again enter the choice");
                    getchar();
                    getchar();
                    goto A10;
                }
                else
                {
                    printf("\nWrong answer.\n");
                    ch = getchar();
                    char ci = getchar();
                    break;
                }
            case 8:
            A11:
                printf("\n\n\n A person who sends irrelevant or unsolicited messages by using Internet, usually to large numbers of users, for the purposes of advertising, spreading malware, phishing, etc. is known as");
                printf("\n\nA - Programmer\t\tB - Hacker\n\nC - Spammer\t\tD - Hobbyist\n");
                scanf("%c", &c); // taking input as character
                if (toupper(c) == 'C')
                {
                    count++;
                    printf("\ncorrect.\n");
                    ch = getchar();
                    char ci = getchar();
                    break;
                }
                else if (check(c)) // if input is wrong then repeat the question
                {
                    printf("\nInvalid Choice\n");
                    printf("\nPlease press enter to again enter the choice");
                    getchar();
                    getchar();
                    goto A11;
                }
                else
                {
                    printf("\nWrong answer.\n");
                    ch = getchar();
                    char ci = getchar();
                    break;
                }
            case 9:
            A12:
                printf("\n\n\nWhich among the following facilitates users to upload web page files from the personal computers to server?");
                printf("\n\nA - Transmission Control Protocol\t\tB - File Transfer Protocol\n\nC - Hyper Text Markup Language\t\tD - HTTP\n");
                scanf("%c", &c); // taking input as character
                if (toupper(c) == 'B')
                {
                    count++;
                    printf("\ncorrect.\n");
                    ch = getchar();
                    char ci = getchar();
                    break;
                }
                else if (check(c)) // if input is wrong then repeat the question
                {
                    printf("\nInvalid Choice\n");
                    printf("\nPlease press enter to again enter the choice");
                    getchar();
                    getchar();
                    goto A12;
                }
                else
                {
                    printf("\nWrong answer.\n");
                    ch = getchar();
                    char ci = getchar();
                    break;
                }
            case 10:
            A13:
                printf("\n\n\nWhich of the following computer program is written in binary form?");
                printf("\n\nA - Machine Language\t\tB - Pascal\n\nC- Java\t\tD - C\n");
                scanf("%c", &c); // taking input as character
                if (toupper(c) == 'A')
                {
                    count++;
                    printf("\ncorrect.\n");
                    ch = getchar();
                    char ci = getchar();
                    break;
                }
                else if (check(c)) // if input is wrong then repeat the question
                {
                    printf("\nInvalid Choice\n");
                    printf("\nPlease press enter to again enter the choice");
                    getchar();
                    getchar();
                    goto A13;
                }
                else
                {
                    printf("\nWrong answer.\n");
                    ch = getchar();
                    char ci = getchar();
                    break;
                }
            }
        }
        system("cls");
        printf("\nThankyou for playing the game.\n");
        printf("\nYou can see your score by pressing enter.\n");
        getchar();
        show_record();
    }
    else
    {
        count = 0;
        system("cls");
        printf("\nyou are not qualified for the final round. :(\n");
        printf("\nPress ENTER to return to mainhome.\n");
        getchar();
        mainhome();
    }
}
void help() // function to show when pressed "HELP"...
{
    {
        system("cls");
        printf("\n\n                              HELP");
        printf("\n -------------------------------------------------------------------------");
        printf("\n ............... Quiz Game...........");
        printf("\n >> There are two rounds in the game, WARMUP ROUND & FINAL ROUND");
        printf("\n >> In warmup round you will be asked a total of 3 questions to test your general");
        printf("\n    knowledge. You will be eligible to play the game if you can give atleast 2");
        printf("\n    right answers otherwise you can't play the Game...........");
        printf("\n >> Your game starts with the CHALLANGE ROUND. In this round you will be asked");
        printf("\n    total 10 questions each right answer will be awarded a score of +1.");
        printf("\n >> You will be given 4 options and you have to press A, B ,C or D for the");
        printf("\n    right option");
        printf("\n >> You will be asked questions continuously if you keep giving the right answers.");
        printf("\n >> No negative marking for wrong answers");

        printf("\n\n\t*********************BEST OF LUCK*********************************");
        printf("\n\n\t*****C PROGRAM QUIZ GAME is developed by OUR TEAM********");
    }
    printf("\n\nPress ENTER to return to main menu.\n");
    getchar();
    getchar();
    mainhome();
}
void show_record() // function for showing the highest score
{
    system("cls");
    int c;
    if (count > 0)
    {
        if (count >= maxcount)
        {
            maxcount = count; // calculating the highest score.
            printf("\nYour highest score is: %d\n", maxcount);
        }
    }
    else
    {
        printf("\nyour score is 0. \n");
        printf("\n Because you are not qualified for the final round :(\n");
    }
    printf("\nPress 0 to return to mainhome.\n");
    scanf("%d", &c);
    if (c == 0)
    {
        mainhome();
    }
    else
    {
        printf("Please enter the correct key.");
    }
}
void reset() // function to reset the score
{
    count = 0; // setting the score value to 0...
    system("cls");
    printf("\nYour score has been reset to 0.\n");
    printf("\nPress 1 to start the new game.\n");
    printf("\nPress 0 to return to the main menu.\n");
    int c;
    scanf("%d", &c);
    if (c == 0)
    {
        mainhome();
    }
    if (c == 1)
    {
        question();
    }
}
void mainhome()
{

    int choice;
    system("cls"); // displaying the initial page if the game
    printf("\t\t\tC PROGRAM QUIZ GAME\n");
    printf("\n\t\t________________________________________");

    printf("\n\t\t\t   WELCOME ");
    printf("\n\t\t\t      to ");
    printf("\n\t\t\t   THE GAME ");
    printf("\n\t\t________________________________________");
    printf("\n\t\t________________________________________");
    printf("\n\t\t   CAN YOU SCORE FULL!!!!!!!!!!!    ");
    printf("\n\t\t________________________________________");
    printf("\n\t\t________________________________________");
    printf("\n\t\t > Press 1 to start the game");
    printf("\n\t\t > Press 2 to view the highest score  ");
    printf("\n\t\t > Press 3 for help ");
    printf("\n\t\t > press 4 to reset the game             ");
    printf("\n\t\t > press 5 to quit");
    printf("\n\t\t________________________________________\n\n");
    scanf("%d", &choice);
    if (choice == 2)
    {
        show_record();
    }
    else if (choice == 1)
    {
        system("cls");
        printf("\nYou will be given a warmup round containing 3 question if you will score more than 1\n");
        printf("You will get a chance to play the final round.\n\n");
        printf("Let's start the game press ENTER to start.\n");
        getchar();
        question();
    }
    else if (choice == 3)
    {
        help();
    }
    else if (choice == 4)
    {
        reset();
    }
    else
    {
        quit();
    }
}

// GAME 5 -- SUDOKU (By KANISHK SINGHAL [2201MC21])

#define size 9
bool FIND_EMPTY_POSITION(int SUDOKU_GRID[size][size], int *SUDOKU_ROW, int *SUDOKU_COL);
bool IS_PLACABLE(int SUDOKU_GRID[size][size], int SUDOKU_ROW, int SUDOKU_COL, int num);
bool LETS_SOLVE_SUDOKU(int SUDOKU_GRID[size][size]);
void DISPLAY_SUDOKU(int SUDOKU_GRID[size][size]);
void GENERATE_THE_PUZZLE(int SUDOKU_GRID[size][size]);
bool SOLUTION_CHECK(int SUDOKU_GRID[size][size], int SUDOKU_ROW, int SUDOKU_COL, int num);
bool IS_GRID_FULLY_FILLED(int grid[size][size]);
void PLAY_SUDOKU(int SUDOKU_GRID[size][size]);

// Function for finding the next empty cell in the SUDOKU_GRID
bool FIND_EMPTY_POSITION(int SUDOKU_GRID[size][size], int *SUDOKU_ROW, int *SUDOKU_COL)
{
    for (*SUDOKU_ROW = 0; *SUDOKU_ROW < size; (*SUDOKU_ROW)++)
    {
        for (*SUDOKU_COL = 0; *SUDOKU_COL < size; (*SUDOKU_COL)++)
        {
            if (SUDOKU_GRID[*SUDOKU_ROW][*SUDOKU_COL] == 0)
            {
                return true; // Found an empty cell
            }
        }
    }
    return false; // No empty cell found
}

// Function for checking if it is safe to place a number in a particular cell
bool IS_PLACABLE(int SUDOKU_GRID[size][size], int SUDOKU_ROW, int SUDOKU_COL, int num)
{
    // checking if the number already exists in the SUDOKU_ROW
    for (int i = 0; i < size; i++)
    {
        if (SUDOKU_GRID[SUDOKU_ROW][i] == num || SUDOKU_GRID[i][SUDOKU_COL] == num)
        {
            return false;
        }
    }

    // Checking if the number exists in the 3x3 box
    int sr = SUDOKU_ROW - SUDOKU_ROW % 3;
    int sc = SUDOKU_COL - SUDOKU_COL % 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (SUDOKU_GRID[i + sr][j + sc] == num)
            {
                return false;
            }
        }
    }

    return true;
}

// Function which will solve Sudoku puzzle using backtracking
bool LETS_SOLVE_SUDOKU(int SUDOKU_GRID[size][size])
{
    int SUDOKU_ROW, SUDOKU_COL;

    // Find the next empty cell in the SUDOKU_GRID
    if (!FIND_EMPTY_POSITION(SUDOKU_GRID, &SUDOKU_ROW, &SUDOKU_COL))
    {
        return true; // All the cells are filled, puzzle SOLVE
    }

    // Generating a random order of numb to try
    int numb[size];
    for (int i = 0; i < size; i++)
    {
        numb[i] = i + 1;
    }

    // Shuffling the numb array
    for (int i = size - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = numb[i];
        numb[i] = numb[j];
        numb[j] = temp;
    }

    // Trying each number in the shuffled order
    for (int i = 0; i < size; i++)
    {
        int num = numb[i];
        if (IS_PLACABLE(SUDOKU_GRID, SUDOKU_ROW, SUDOKU_COL, num))
        {
            SUDOKU_GRID[SUDOKU_ROW][SUDOKU_COL] = num; // Placing the number in the cell

            if (LETS_SOLVE_SUDOKU(SUDOKU_GRID))
            {
                return true; // This number leads to a solution
            }

            SUDOKU_GRID[SUDOKU_ROW][SUDOKU_COL] = 0; // This number doesn't lead to a solution, backtrack
        }
    }

    return false; // Backtracking to previous cell
}

// Function for displaying the Sudoku SUDOKU_GRID
void DISPLAY_SUDOKU(int SUDOKU_GRID[size][size])
{
    for (int SUDOKU_ROW = 0; SUDOKU_ROW < size; SUDOKU_ROW++)
    {
        for (int SUDOKU_COL = 0; SUDOKU_COL < size; SUDOKU_COL++)
        {
            if (SUDOKU_COL % 3 == 0)
            {
                printf("\033[1;35m |\033[0m");
            }
            if (SUDOKU_GRID[SUDOKU_ROW][SUDOKU_COL] == 0)
            {
                printf(" .");
            }
            else
            {
                printf(" %d", SUDOKU_GRID[SUDOKU_ROW][SUDOKU_COL]);
            }
        }
        printf("\033[1;35m |\033[0m\n");
        if ((SUDOKU_ROW + 1) % 3 == 0 && SUDOKU_ROW != size - 1)
        {
            printf("\033[1;35m  ------- ------- -------\033[0m\n");
        }
    }
}

// Function for generating an unsolved Sudoku puzzle
void GENERATE_THE_PUZZLE(int SUDOKU_GRID[size][size])
{
    srand(time(NULL));

    // Clearing the SUDOKU_GRID
    for (int SUDOKU_ROW = 0; SUDOKU_ROW < size; SUDOKU_ROW++)
    {
        for (int SUDOKU_COL = 0; SUDOKU_COL < size; SUDOKU_COL++)
        {
            SUDOKU_GRID[SUDOKU_ROW][SUDOKU_COL] = 0;
        }
    }

    // Solving the Sudoku puzzle to get a complete solution
    LETS_SOLVE_SUDOKU(SUDOKU_GRID);

    // Removing random entries to create an unsolved puzzle
    int entriesToRemove = 40; // Adjusting the number of entries to remove for controlling the difficulty level

    while (entriesToRemove > 0)
    {
        int SUDOKU_ROW = rand() % size;
        int SUDOKU_COL = rand() % size;

        if (SUDOKU_GRID[SUDOKU_ROW][SUDOKU_COL] != 0)
        {
            SUDOKU_GRID[SUDOKU_ROW][SUDOKU_COL] = 0;
            entriesToRemove--;
        }
    }
}

// Function to checking if the entered number in a cell leads to a valid solution
bool SOLUTION_CHECK(int SUDOKU_GRID[size][size], int SUDOKU_ROW, int SUDOKU_COL, int num)
{
    // Creating a temporary copy of the SUDOKU_GRID
    int TEMPORARY_GRID[size][size];
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            TEMPORARY_GRID[i][j] = SUDOKU_GRID[i][j];
        }
    }

    // Placing the entered number in the specified cell
    TEMPORARY_GRID[SUDOKU_ROW][SUDOKU_COL] = num;

    // checking if the temporary SUDOKU_GRID can be SOLVE
    return LETS_SOLVE_SUDOKU(TEMPORARY_GRID);
}

// Function for checking if grid is full
bool IS_GRID_FULLY_FILLED(int grid[size][size])
{
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            if (grid[row][col] == 0)
            {
                return false;
            }
        }
    }
    return true;
}
// Function for playing the Sudoku game
void PLAY_SUDOKU(int SUDOKU_GRID[size][size])
{
    int WRONG_ENTRY = 0;
    bool SOLVE = false;

    while (!SOLVE)
    {
        int SUDOKU_ROW, SUDOKU_COL, num;
        if (WRONG_ENTRY < 3)
        {
            printf("\n\033[1;36mEnter the sudoku_row, column (both 1 to 9), and entry (space-separated) or '0 0 0' to exit: \033[0m");
            scanf("%d%d%d", &SUDOKU_ROW, &SUDOKU_COL, &num);
        }

        if (SUDOKU_ROW == 0 && SUDOKU_COL == 0 && num == 0)
        {
            printf("\033[1;35mQuitting the game.\033[0m\n");
            printf("\n\033[1;36mSolved Puzzle:\033[0m\n");
            int solvedGrid[size][size];
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    solvedGrid[i][j] = SUDOKU_GRID[i][j];
                }
            }
            LETS_SOLVE_SUDOKU(solvedGrid);
            DISPLAY_SUDOKU(solvedGrid);
            break;
        }

        // Converting to zero-based indices
        SUDOKU_ROW--;
        SUDOKU_COL--;

        // checking if any input is invalid (non-zero) and updating the WRONG_ENTRY counter
        if (SUDOKU_ROW < 0 || SUDOKU_ROW >= size || SUDOKU_COL < 0 || SUDOKU_COL >= size || num < 0 || num > 9)
        {
            printf("\033[1;31mInvalid input. Try again.\033[0m\n");
            continue;
        }

        if (num == 0)
        {
            // If the given number is zero, it's a valid input, but we don't need to do anything. It will be treated as an empty cell in Sudoku.
            DISPLAY_SUDOKU(SUDOKU_GRID);
            continue;
        }

        if (WRONG_ENTRY == 3)
        {
            printf("\033[1;31mYou have used all your wrong entries. Game over!\033[0m\n");
            break;
        }

        // checking if the entry is valid (safe) and if it matches the solution
        if (!IS_PLACABLE(SUDOKU_GRID, SUDOKU_ROW, SUDOKU_COL, num) || !SOLUTION_CHECK(SUDOKU_GRID, SUDOKU_ROW, SUDOKU_COL, num))
        {
            printf("\033[1;31mWrong entry. Try again.\033[0m\n");
            WRONG_ENTRY++;
            printf("Wrong entries left: %d\n", 3 - WRONG_ENTRY);
            continue;
        }
        if (WRONG_ENTRY < 3)
        {

            SUDOKU_GRID[SUDOKU_ROW][SUDOKU_COL] = num;
            DISPLAY_SUDOKU(SUDOKU_GRID);
        }
        SOLVE = IS_GRID_FULLY_FILLED(SUDOKU_GRID);
        if (SOLVE)
        {
            printf("Congratulations! You SOLVE the Sudoku puzzle!\n");
        }
    }
}

// GAME 6 -- TIC-TAC-TOE (By METLA UMESH [2201AI24])

void printBoard(char board[5][5], int siz)
{
    int i, j;

    // Print top border
    printf("+");
    for (i = 0; i < siz; i++)
    {
        printf("---+");
    }
    printf("\n");

    // Print board
    for (i = 0; i < siz; i++)
    {
        printf("|");
        for (j = 0; j < siz; j++)
        {
            printf(" %c |", board[i][j]);
        }
        printf("\n");

        // Print border
        printf("+");
        for (j = 0; j < siz; j++)
        {
            printf("---+");
        }
        printf("\n");
    }
}

int checkWin(char board[5][5], int siz, char symbol)
{
    int i, j;

    // Check rows
    for (i = 0; i < siz; i++)
    {
        int count = 0;
        for (j = 0; j < siz; j++)
        {
            if (board[i][j] == symbol)
                count++;
        }
        if (count == siz)
            return 1;
    }

    // Check columns
    for (j = 0; j < siz; j++)
    {
        int count = 0;
        for (i = 0; i < siz; i++)
        {
            if (board[i][j] == symbol)
                count++;
        }
        if (count == siz)
            return 1;
    }

    // Check diagonals
    int count1 = 0, count2 = 0;
    for (i = 0; i < siz; i++)
    {
        if (board[i][i] == symbol)
            count1++;
        if (board[i][siz - 1 - i] == symbol)
            count2++;
    }
    if (count1 == siz || count2 == siz)
        return 1;

    return 0;
}

void playTicTacToe(int siz, int startPlayer)
{
    char board[5][5];
    int i, j, row, col, turn = startPlayer;
    char symbol;
    char player1[100], player2[100];

    printf("Enter Player 1's name: ");
    scanf("%s", player1);
    printf("Enter Player 2's name: ");
    scanf("%s", player2);

    printf("%s: O\n", player1);
    printf("%s: X\n", player2);
    printf("Let's begin!\n");

    // Initialize the board
    for (i = 0; i < siz; i++)
    {
        for (j = 0; j < siz; j++)
        {
            board[i][j] = '-';
        }
    }

    while (1)
    {
        symbol = (turn == 1) ? 'O' : 'X';

        printf("\n%s's turn (%c):\n", (turn == 1) ? player1 : player2, symbol);
        printBoard(board, siz);

        // Get the player's move
        printf("Enter the row and column (1-%d): ", siz);
        scanf("%d %d", &row, &col);
        row--;
        col--;

        // Check if the move is valid
        if (row >= 0 && row < siz && col >= 0 && col < siz && board[row][col] == '-')
        {
            board[row][col] = symbol;

            // Check if the player wins
            if (checkWin(board, siz, symbol))
            {
                printf("\nCongratulations! %s wins!\n", (turn == 1) ? player1 : player2);
                printBoard(board, siz);
                break;
            }

            // Check for a draw
            int isDraw = 1;
            for (i = 0; i < siz; i++)
            {
                for (j = 0; j < siz; j++)
                {
                    if (board[i][j] == '-')
                    {
                        isDraw = 0;
                        break;
                    }
                }
            }

            if (isDraw)
            {
                printf("\nIt's a draw!\n");
                printBoard(board, siz);
                break;
            }
        }
        else
        {
            printf("\nInvalid move! Try again.\n");
        }

        // Switch to the next player's turn
        turn = (turn % 2) + 1;
    }
}

int main()
{
    int choice;

    printf("\n\t\t\t!!!!!Welcome to ArcOde !!!!!\n\n");
    printf("\t\tPlease select a game to play:\n\n");
    printf("1. Broken Calculator\n\n");
    printf("2. Minesweeper\n\n");
    printf("3. Hangman\n\n");
    printf("4. Quiz Game\n\n");
    printf("5. Sudoku\n\n");
    printf("6. Tic-Tac-Toe\n\n");

    printf("Your choice: ");
    scanf("%d", &choice);

    system("cls");

    if (choice == 1)
    {
        printf(" \n\n\n\n \033[1;34mSam's calculator got smashed , but some of it still works.\033[0m\n");
        printf(" \033[1;34mCan you help Sam get the answers?\033[0m\n\n\n");

        int n;
        printf("\033[1;35m Enter level 1 - 4 : \033[0m");
        scanf("%d", &n);
        system("cls");
        do
        {
            switch (n)
            {
            case 1:
            {
                level1();
                break;
            }
            case 2:
            {
                level2();
                break;
            }
            case 3:
            {
                level3();
                break;
            }
            case 4:
            {
                level4();
                break;
            }
            }
            printf("\033[1;35mwanna play other level ? (Enter it or enter 0 to quit ) : \033[0m");
            scanf("%d", &n);
        } while (n);
    }

    if (choice == 2)
    {
        printf("\t\tWelcome to Minesweeper\n");
        difficulty();
    }

    if (choice == 3)
    {
        char hangmanWord[100], tempWord[100];

        // hangmanWord[] array for the original word and tempWord[] array to get the alphabet from user and compare it with original word

        char hangmanOutput[100];

        // This array will show the remaining blanks and correct inputs

        int wrongTry = 6, matchFound = 0;

        // player will get 5 chance, so we use wrongTry as chance counter

        // matchFound to search the alphabet, if the alphabet from user does not exist
        // in the original word it will remain 0, upon finding the word, matchFound will
        // be set as 1

        int counter = 0, position = 0, winner, length, i;
        char alphabetFromUser;

        char name_player[20];
        char name_opponent[20];

        printf("\n\n\t\t'Welcome To Hangman Game'");
        printf("\n\n   Enter Your name - ");
        scanf("%s", name_player);
        printf("\n\n   Enter Opponent`s name - ");
        scanf("%s", name_opponent);
        system("cls"); // for clearing the screen

        printf("\n\n\t'It is a two player game to learn and have fun' ");

        printf("\n\n\n Rules Of The Game -");
        printf("\n\n 1> Enter any word in small case and hit >>ENTER<< ");
        printf("\n\n 2> Shhhh !!! ");
        printf("\n\n 3> Don`t tell your word to anyone except Computer ");
        printf("\n\n 4> Then give the COMPUTER to your friend and see if He / She can CRACK it !!!");
        printf("\n\n 5> He / She will get 5 chances ");

        printf("\n\n\t Enter HERE ==>  ");
        scanf("%s", hangmanWord); // get the string from opponent

        printf("\n\n\tHIT >>ENTER<<");
        getchar(); // hold the computer screen

        length = strlen(hangmanWord); // get the length of the word

        system("cls"); // for clearing the screen

        // Hangman Code Starts here !!

        printf("\n\n !!!!!!!!!!!!!!!!!!! Welcome to the HANGMAN GAME ` %s ` !!!!!!!!!!!!!!!!!\n\n\n", name_opponent);
        printf("\n\n\tHi %s , Ready for the challange ?", name_opponent);
        printf("\n\n\tYou will get 5 chances to guess the right word");
        printf("\n\n\tSo help the Man and get...set...GO..!!");

        printf("\n\n\tHIT >>ENTER<< ");
        getchar();

        system("cls");

        // show the HANGMAN

        printf("\n\t||===== ");
        printf("\n\t||    \033[1;31m| \033[0m ");
        printf("\n\t||      ");
        printf("\n\t||      ");
        printf("\n\t||      ");
        printf("\n\t||      ");

        printf("\n\n     The word has %d alphabets \n\n", length);

        // tell the user how many alphabets the word has

        for (i = 0; i < length; i++)
        {
            hangmanOutput[i] = '_';
            hangmanOutput[length] = '\0';
        }

        for (i = 0; i < length; i++)
        {
            printf(" ");
            printf("%c", hangmanOutput[i]);

            // Show the Word With n(length of the original word) number of underscores (_)
        }
        while (wrongTry != 0) // while loop for exiting the program when no try left
        {
            matchFound = 0;
            printf("\n\n   enter any alphabet from a to z and please use small case!!");
            printf("\n\n\t Enter HERE ==> ");

            fflush(stdin);

            scanf("%c", &alphabetFromUser);
            // get alphabet from user

            if (alphabetFromUser < 'a' || alphabetFromUser > 'z')

            // In case player gives input other than 'a' to 'z' the console will ask again
            {
                system("cls");
                printf("\n\n\t Wrong input TRY AGAIN ");
                matchFound = 2;
            }
            fflush(stdin);
            if (matchFound != 2)
            {
                for (counter = 0; counter < length; counter++)
                // for loop to check whether player input alphabet exists or not in the word
                {
                    if (alphabetFromUser == hangmanWord[counter])
                    {
                        matchFound = 1;
                    }
                }

                if (matchFound == 0)
                // In case of wrong guess
                {
                    printf("\n\t :( You have %d tries left ", --wrongTry);
                    printf("\n\n\tHIT >>ENTER<< ");
                    getchar();
                    showHangman(wrongTry);
                    getchar();
                }

                else
                {
                    for (counter = 0; counter < length; counter++)
                    {
                        matchFound = 0;
                        if (alphabetFromUser == hangmanWord[counter])
                        {
                            position = counter;
                            matchFound = 1;
                        }
                        if (matchFound == 1)
                        {
                            for (i = 0; i < length; i++)
                            {
                                if (i == position)
                                {
                                    hangmanOutput[i] = alphabetFromUser;
                                }
                                else if (hangmanOutput[i] >= 'a' && hangmanOutput[i] <= 'z')
                                // If the position already occupied by same alphabet then no need to fill again EASY!! and continue
                                {
                                    continue;
                                }

                                else
                                {
                                    hangmanOutput[i] = '_';
                                    // Put a blank at not guessed alphabet position
                                }
                            }
                            tempWord[position] = alphabetFromUser;
                            // put the alphabet in another char array to check with the original word

                            tempWord[length] = '\0';
                            // put the NULL character at the end of the temp string

                            winner = strcmp(tempWord, hangmanWord);
                            // upon True comparison it will return 0

                            if (winner == 0)
                            // if the player guessed the whole word right then he/she is the WINNER
                            {
                                printf("\n\n\t \t YAHOO!!!!! %s is the WINNER  !!!!!", name_opponent);
                                printf("\n\n\t The Word was %s ", hangmanWord);
                                printf("\n\n\n\n\t\tTOO EASY HUH???\n\n");
                                getchar();
                                return 0;
                            }
                        }
                    }
                }
            }

            printf("\n\n\t");
            for (i = 0; i < length; i++)
            {
                printf(" ");
                printf("%c", hangmanOutput[i]);
                // Show the original Word With blanks and right Input alphabet
            }

            getchar();
        }

        if (wrongTry <= 0)
        // if the player can not guess the whole word in 5 chaces
        {
            printf("\n\n\t The Word was - %s ", hangmanWord);
            printf("\n\n\t The man is dead you IDIOT !!!!!");
            printf("\n\n\t Better luck next time !!!");
        }
        getchar();
    }

    if (choice == 4)
    {
        mainhome();
    }

    if (choice == 5)
    {
        int SUDOKU_GRID[size][size];
        char player_name[20];

        printf("\t\t\t\t\033[1;34mC SUDOKU GAME\033[0m\n");

        printf("\n\t\t\t\t  WELCOME ");
        printf("\n\t\t\t\t     TO ");
        printf("\n\t\t\t\t THE GAME ");
        printf("\n\t\t______________________________________");
        printf("\n\t\t______________________________________");
        printf("\n\t\t   CAN YOU SOLVE IT FULL!!!!!!!!!!!    ");
        printf("\n\t\t______________________________________");
        printf("\n\t\t______________________________________");

        printf("\n\n\033[1;34mEnter Your name - \033[0m");
        scanf("%s", player_name);

        system("cls"); // for clearing the screen

        GENERATE_THE_PUZZLE(SUDOKU_GRID); // Generating an unsolved Sudoku puzzle

        printf("\033[1;32mUnsolved Puzzle:\033[0m\n");
        DISPLAY_SUDOKU(SUDOKU_GRID);

        printf("\033[1;32m\n\tLet's play!\033[0m\n");

        PLAY_SUDOKU(SUDOKU_GRID);
    }

    if (choice == 6)
    {
        int choic, siz;
        int startPlayer;

        printf("Please select the level :\n");
        printf("1. Tic-Tac-Toe (3x3)\n");
        printf("2. Tic-Tac-Toe (4x4)\n");
        printf("3. Tic-Tac-Toe (5x5)\n");
        printf("Your choice: ");
        scanf("%d", &choic);

        switch (choic)
        {
        case 1:
            siz = 3;
            break;
        case 2:
            siz = 4;
            break;
        case 3:
            siz = 5;
            break;
        default:
            printf("Invalid choice! Exiting...\n");
            return 0;
        }

        printf("Enter the player who will start the game (1 for Player 1, 2 for Player 2): ");
        scanf("%d", &startPlayer);

        playTicTacToe(siz, startPlayer);
    }
}