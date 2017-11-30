#include <iostream>
#include <time.h>
#include <ncurses.h>

using namespace std;

WINDOW *create_newwin(int height,int width,int starty,int startx);
void destory_win(WINDOW *local_win);

int main()
{
	WINDOW * game_win, *hint_win;
	int startx,starty,game_win_height,game_win_width,hint_win_height,hint_win_width;
	int ch;

	initscr();
	raw();
	noecho();
	curs_set(0);
	keypad(stdscr,TRUE);

	refresh();

	game_win_height=35;
	game_win_width=45;
	hint_win_height=10;
	hint_win_width=20;


	// starty=(LINES - height)/2;
	// startx=(COLS - width)/2;

	game_win = create_newwin(game_win_height, game_win_width, 5,5);
	wborder(game_win, '*', '*', '*', '*', '*', '*', '*', '*');
	wrefresh(game_win);

	hint_win = create_newwin(hint_win_height, hint_win_width, 5, game_win_width+10);







	while((ch = getch() )!= KEY_F(1))
	{
	}

	endwin();
	return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	box(local_win,0,0);
	wrefresh(local_win);
	return local_win;
}

void destory_win(WINDOW *local_win)
{
	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(local_win);
	delwin(local_win);
}