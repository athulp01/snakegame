#include <ncurses.h>
#include <unistd.h> //usleep()
#include <cstdlib>  //rand()
#include <cstdio>
#include <iostream>
#include <ctime>
#include<string>

using namespace std;

void move_player_down(WINDOW *board);
void move_player_left(WINDOW *board);
void move_player_right(WINDOW *board);
void move_player_up(WINDOW *board);
void create_food(WINDOW *board);

int flag = 1; //global
bool isFoodEaten = true;
unsigned int food_x = 100;
unsigned int food_y = 100;
int score = 1;
char snake[]="00000000000000000000000000000000000000000000000000000000000000000000000";
char blank[]="                                                                       ";
int main()
{

    initscr();
    curs_set(0);
    WINDOW *board;
    WINDOW *stat;
    start_color();
    noecho();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    
    board = newwin(20, 50, 2, 5);
    box(board, 0, 0);
    wrefresh(board);
    stat = newwin(20, 24, 2, 55);
    box(stat, 0, 0);
    wrefresh(stat);
    wattron(board, COLOR_PAIR(1) | A_BOLD | A_BLINK);
    wattron(stat, COLOR_PAIR(2));
    mvwprintw(board, 2, 1,"0");
    mvwprintw(stat, 2, 6, "SNAKE GAME");
    mvwprintw(stat, 4, 2, "SCORE : ");
    wattroff(stat, COLOR_PAIR(2));
    wrefresh(stat);

    while (flag == 1)
    {

        char ch;
        ch = wgetch(board);
        switch (ch)
        {
        case 'd':
        case 'D':
            wattron(board,COLOR_PAIR(1)|A_BOLD);
            move_player_right(board);
            wattroff(board,COLOR_PAIR(1)|A_BOLD);
            break;
        case 'a':
            wattron(board,COLOR_PAIR(1)|A_BOLD);
            move_player_left(board);
            wattroff(board,COLOR_PAIR(1)|A_BOLD);
            break;
        case 'w':
            wattron(board,COLOR_PAIR(1)|A_BOLD);
            move_player_up(board);
            wattroff(board,COLOR_PAIR(1)|A_BOLD);
            break;
        case 's':
            wattron(board,COLOR_PAIR(1)|A_BOLD);
            move_player_down(board);
            wattroff(board,COLOR_PAIR(1)|A_BOLD);
            break;
        }
        if (isFoodEaten == true)
        {
            create_food(board);
        }
        mvwprintw(stat, 4, 11, "%d", score);
        wrefresh(stat);
        wrefresh(board);
    }
    if (flag != 1)
    {
        wattron(stat, COLOR_PAIR(1));
        mvwprintw(stat, 6, 1, "GAME OVER!!!!!!");
        mvwprintw(stat, 7, 1, "PRESS ANY KEY TO EXIT.");
        wrefresh(stat);
        wattroff(stat, COLOR_PAIR(2));
    }
    wgetch(board);

    delwin(board);
    delwin(stat);
    endwin();
}

void move_player_right(WINDOW *board)
{
    int x, y;
    getyx(board, y, x);

    if (x == 49)
    {
        flag = 3;
    }
    else

        if (flag == 1)
    {
        mvwaddnstr(board, y, x - score,blank,score);
        mvwaddnstr(board, y, x,snake,score);

        if (x  == food_x && y == food_y)
        {
            isFoodEaten = true;
            
            score++;
        }
        wrefresh(board);
    }
}

void move_player_left(WINDOW *board)
{
    int x, y;
    getyx(board, y, x);
    if (x == 2)
    {
        flag = 3;
    }
    else

        if (flag == 1)
    {
        if (x - 2 == food_x && y == food_y)
        {
            isFoodEaten = true;
            score++;
        }

        mvwaddnstr(board, y, x - score,blank,score);
        mvwaddnstr(board, y, (x - score)-1,snake,score);
        wrefresh(board);
        x++;
    }
}

void move_player_up(WINDOW *board)
{
    int x, y;
    getyx(board, y, x);
    if (y == 1)
    {
        flag = 4;
    }
    else

        if (flag == 1)
    {
        if (x-1 == food_x && y - 1 == food_y)
        {
            isFoodEaten = true;
            score++;
        }
        mvwaddnstr(board, y, x - score,blank,score);
        mvwaddnstr(board, y - 1, x - score,snake,score);
        wrefresh(board);
        x++;
    }
}

void move_player_down(WINDOW *board)
{
    int x, y;
    getyx(board, y, x);
    if (y == 18)
    {
        flag = 5;
    }
    else

        if (flag == 1)
    {
        if (x-1 == food_x && y + 1 == food_y)
        {
            isFoodEaten = true;
            score++;
        }
        mvwaddnstr(board, y, x - score,blank,score);
        mvwaddnstr(board, y + 1, x - score,snake,score);
        wrefresh(board);
        x++;
    }
}

void create_food(WINDOW *board)
{
    isFoodEaten = false;
    int i, j;
    getyx(board, i, j);
    srand(time(NULL));
    food_x = (rand() % 49);
    unsigned int temp = food_x;
    if (food_x ==0){food_x = temp+1;}
    food_y = (rand() % 19);
    unsigned int temp1 = food_y;
    if (food_y == 0){food_y = temp+1;}
    //mvwprintw(board,6,6,"%d  %d",food_x,food_y);
    wrefresh(board);
    wattron(board, COLOR_PAIR(2));
    mvwaddch(board, food_y, food_x, '8' | COLOR_PAIR(2));
    wattroff(board, COLOR_PAIR(2));
    wmove(board, i, j);
    wrefresh(board);
}