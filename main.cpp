#include <ncurses.h>
#include <unistd.h> //usleep()
#include <cstdlib>  //rand()
#include <cstdio>
#include<fstream>
#include <ctime>

void move_player_down(WINDOW *board);  */ USER-DEFINED FUNCTION PROTOCOLS /* 
void move_player_left(WINDOW *board);     
void move_player_right(WINDOW *board);
void move_player_up(WINDOW *board);
void create_food(WINDOW *board);

int flag = 1;                         
bool isFoodEaten = true;
unsigned int food_x = 100;
unsigned int food_y = 100;
int score = 0;
char warn=ERR;
ofstream writer("high.txt");
char highscore;

int main()
{


    initscr();
    curs_set(0);
    raw();
    WINDOW *board;
    WINDOW *stat;
    start_color();
    noecho();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    ifstream reader("high.txt");
    reader.get(highscore);
    reader.close();
    board = newwin(20, 50, 2, 5);
    box(board, 0, 0);
    wrefresh(board);
    stat = newwin(20, 24, 2, 55);
    box(stat, 0, 0);
    wrefresh(stat);
    wattron(board, COLOR_PAIR(1) | A_BOLD | A_BLINK);
    wattron(stat, COLOR_PAIR(2));
    mvwaddch(board, 2, 1, '0' | COLOR_PAIR(1) | A_BOLD);
    mvwprintw(stat, 2, 6, "SNAKE GAME");
    mvwprintw(stat, 4, 2, "SCORE : ");
    mvwprintw(stat,5,2,"HIGH SCORE : %c",highscore);
    wattroff(stat, COLOR_PAIR(2));
    wrefresh(stat);

    while (flag == 1)
    {

        char ch;
        ch = wgetch(board);
        if(ch==ERR)
        {
            ch=warn;
        }
        
       
        switch (ch)
        
        case 'd':
        case 'D':
            warn=ERR;
            move_player_right(board);
            break;
        case 'a':
        warn=ERR;
            move_player_left(board);
            break;
        case 'w':
        warn=ERR;
            move_player_up(board);
            break;
        case 's':
        warn=ERR;
            move_player_down(board);
            break;
        }
        
        mvwprintw(stat, 4, 11, "%d", score);
        wrefresh(stat);
        wrefresh(board);
    }
    if (flag != 1)
    {
        
        writer<<score;
        writer.close();
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
    if (isFoodEaten == true)
    {
        create_food(board);
    }
    getyx(board, y, x);
    halfdelay(1);
    

    if (flag == 1)
    {
        for(x;warn==ERR;x++)
        {

            usleep(10000);
            mvwaddch(board, y, x - 1, ' ' | COLOR_PAIR(1) | A_BOLD);
            mvwaddch(board, y, x, '0' | COLOR_PAIR(1) | A_BOLD);
            wrefresh(board);
            if (x  == food_x && y == food_y)
            {
                isFoodEaten = true;
                score++;
            }
            if (x == 49)
            {
                flag = 3;
            
            }
            warn=wgetch(board);
            
        }   

              
        
        wrefresh(board);
        

        
    }
}

void move_player_left(WINDOW *board)
{
    int x, y;
    if (isFoodEaten == true)
    {
        create_food(board);
    }

    getyx(board, y, x);
    halfdelay(1);
    
    

        if (flag == 1)
    {
        
        for(x;warn==ERR;x--)
        {
            usleep(10000);
            mvwaddch(board, y, x - 1, ' ' | COLOR_PAIR(1) | A_BOLD);
            mvwaddch(board, y, x - 2, '0' | COLOR_PAIR(1) | A_BOLD);
            wrefresh(board);
            if (x - 2 == food_x && y == food_y)
            {
                isFoodEaten = true;
                score++;
            }
            if (x == 2)
            {
                flag = 3;
            }
            warn=wgetch(board);
        }    

        getyx(board, y, x);
        
        wrefresh(board);
        
    }
}

void move_player_up(WINDOW *board)
{
    int x, y;
    if (isFoodEaten == true)
    {
        create_food(board);
    }
    getyx(board, y, x);
    halfdelay(1);
        
        if (flag == 1)
        {
        
            for(y;warn==ERR;y--)
            {
                usleep(10000);
                mvwaddch(board, y, x - 1, ' ' | COLOR_PAIR(1) | A_BOLD);
                mvwaddch(board, y - 1, x - 1, '0' | COLOR_PAIR(1) | A_BOLD);
                wrefresh(board);
                if (x-1 == food_x && y - 1 == food_y)
                {
                    isFoodEaten = true;
                    score++;
                }
                if (y == 1)
                {
                flag = 4;
                }

                warn=wgetch(board);
            }
            getyx(board, y, x);
            
            wrefresh(board);
            getyx(board, y, x);
            
        }
}

void move_player_down(WINDOW *board)
{
    int x, y;
    if (isFoodEaten == true)
    {
        create_food(board);
    }
    getyx(board, y, x);
    halfdelay(1);
      
    if (flag == 1)
    {
         for(y;warn==ERR;y++)
         {
            usleep(10000); 
            mvwaddch(board, y, x - 1, ' ' | COLOR_PAIR(1) | A_BOLD);
            mvwaddch(board, y + 1, x - 1, '0' | COLOR_PAIR(1) | A_BOLD);
            wrefresh(board);
            if (x-1 == food_x && y + 1 == food_y)
            {
                isFoodEaten = true;
                score++;
            }
            if (y == 18)
            {
                flag = 5;
            }
            warn=wgetch(board);
         }  

        getyx(board, y, x);

        
        wrefresh(board);
        getyx(board, y, x);
        
        
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
