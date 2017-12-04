#include <iostream>
#include <time.h>
#include <ncurses.h>
#include <map>
#include <unistd.h>

using namespace std;
void swap(int &a, int &b){
	int t=a;
	a = b;
	b = t;
}


WINDOW *create_newwin(int height,int width,int starty,int startx);
void destory_win(WINDOW *local_win);

int game_win_height=35;
int game_win_width=45;

int startx,starty,hint_win_height,hint_win_width;
WINDOW * game_win, *hint_win;
int ch;

class Piece
{
public:
	char shape; 
	int head_x;
	int head_y;

	int box_shape[4][4];

	

public:
	void initial();
	void set_shape(char shape);
	void move();
	void rotate();
	bool judge();
	
};




int main()
{

	initscr();
	raw();
	//cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr,TRUE);

	refresh();

	
	hint_win_height=10;
	hint_win_width=20;


	// starty=(LINES - height)/2;
	// startx=(COLS - width)/2;

	game_win = create_newwin(game_win_height, game_win_width, 0,0);
	wborder(game_win, '*', '*', '*', '*', '*', '*', '*', '*');
	wrefresh(game_win);

	hint_win = create_newwin(hint_win_height, hint_win_width, 5, game_win_width+10);

	Piece* pp = new Piece;
	pp->initial();
	pp->set_shape('T');
	for(int i=0; i<4;i++)
		for(int j=0;j<4;j++)
		{
			if(pp->box_shape[i][j]==1)
				mvwaddch(game_win,i+1,game_win_width/2+j,'#');
				wrefresh(game_win);
		}



	while((ch = getch() )!= KEY_F(1))
	{
		pp->move();

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


void Piece::initial()
{
	this->head_x=game_win_width/2;
	this->head_y=1;
}

void Piece::set_shape(char shape)
{
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			box_shape[i][j]=0;
	switch(shape)
	{
		case 'T':
			this->box_shape[0][0]=1;
			this->box_shape[0][1]=1;
			this->box_shape[0][2]=1;
			this->box_shape[1][1]=1;
			break;
		case 'S':
			this->box_shape[0][1]=1;
			this->box_shape[0][2]=1;
			this->box_shape[1][0]=1;
			this->box_shape[1][1]=1;
			break;
		case 'Z':		
			this->box_shape[0][0]=1;
			this->box_shape[0][1]=1;
			this->box_shape[1][1]=1;
			this->box_shape[1][2]=1;
			break;
		case 'J':
			this->box_shape[0][1]=1;
			this->box_shape[1][1]=1;
			this->box_shape[2][0]=1;
			this->box_shape[2][1]=1;
			break;

		case 'L':
			this->box_shape[0][0]=1;
			this->box_shape[1][0]=1;
			this->box_shape[2][0]=1;
			this->box_shape[2][1]=1;
			break;

		case 'I':
			this->box_shape[0][0]=1;
			this->box_shape[1][0]=1;
			this->box_shape[2][0]=1;
			this->box_shape[3][0]=1;
			break;

		case 'O':
			this->box_shape[0][0]=1;
			this->box_shape[0][1]=1;
			this->box_shape[1][0]=1;
			this->box_shape[1][1]=1;
			break;
	}

}
void Piece::rotate()
{
	for(int i=0;i<4;i++)
		for(int j=0;j<4-i;j++)
			swap(this->box_shape[i][j],this->box_shape[4-1-j][4-1-i]);
	for(int i=0;i<4/2;i++)
		for(int j=0;j<4;j++)
			swap(this->box_shape[i][j],this->box_shape[4-1-i][j]);

}

void Piece::move(){
	if(ch==KEY_LEFT){
		for(int i=0; i<4;i++)
			for(int j=0;j<4;j++){
				if(this->box_shape[i][j]==1){
					mvwaddch(game_win,head_y+i,head_x+j,' ');
					mvwaddch(game_win,head_y+i,head_x+j-1,'#');

				}
			}
			
		wrefresh(game_win);
		this->head_x--;
	}

	if(ch==KEY_RIGHT){
		for(int i=0; i<4;i++)
			for(int j=3;j>=0;j--){
				if(this->box_shape[i][j]==1){
					mvwaddch(game_win,head_y+i,head_x+j,' ');
					mvwaddch(game_win,head_y+i,head_x+j+1,'#');

				}
			}

		wrefresh(game_win);
		this->head_x++;
	}

}




