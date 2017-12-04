#include <iostream>
#include <map>

using namespace std;

class Piece
{
public:
	char shape; 
	int start_x;
	int start_y;

	int box_shape[4][4];

	

public:
	void init_shape(char shape);
	void move();
	void rotate(int piece[4][4]);
	bool judge();
	
};

void Piece::init_shape(char shape)
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

		case 'I'
			this->box_shape[0][0]=1;
			this->box_shape[1][0]=1;
			this->box_shape[2][0]=1;
			this->box_shape[3][0]=1;
			break;

		case 'O'
			this->box_shape[0][0]=1;
			this->box_shape[0][1]=1;
			this->box_shape[1][0]=1;
			this->box_shape[1][1]=1;
			break;
	}

}

void Piece::rotate(int &piece)
{
	for(int i=0;i<4;i++)
		for(int j=0;j<4-1;j++)
			swap(piece[i][j],piece[4-1-j][4-1-i]);
	for(int i=0;i<4/2;i++)
		for(int j=0;j<4;j++)
			swap(piece[i][j],piece[4-1-i][i]);

}
void swap(int &a, int &b){
	int t=a;
	a = b;
	b = t;
}






class BoxMap
{
public:
	//BoxMap();
	~BoxMap();

	void SetMap(int *Map, int rows, int cols);
	int** GetMapPointer();
private:
	int m_rows,m_cols;
	int** MapPointer;
};

void BoxMap::SetMap(int *Map, int rows, int cols)
{
	this->m_cols=cols;
	this->m_rows=rows;

	MapPointer = new int* [m_rows];
	for(int i=0; i<m_rows;i++)
		MapPointer[i] = new int [m_cols];

	int *p=Map;
	for(int i=0; i<m_rows; i++)
		for(int j=0; j<m_cols; j++)
		{
			MapPointer[i][j] = *p;
			p++;
		}

}

int **BoxMap::GetMapPointer()
{
	return MapPointer;
}
int BoxMap::GetMapRows()
{
	return m_rows;
}
int BoxMap::GetMapCols()
{
	return m_cols;
}

BoxMap::~BoxMap()
{
	if(MapPointer)
	{
		for (int i=0; i< m_rows; i++)
		{
			delete []MapPointer[i];
			MapPointer[i] = NULL;
		}
		delete MapPointer;
		cout << "~BoxMap()" << endl;
	}
}