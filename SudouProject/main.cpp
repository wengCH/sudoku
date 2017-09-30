#include<iostream>
#include<string>
#include<time.h>
#include<cstring>
#include<stdlib.h>
#include<fstream>
#include<istream>
using namespace std;

int t=time(0); 
int table[9][9];
int number;
fstream outfile("BIN/sudoku.txt",  ios::out);
void printSudoku(int a[9][9])
{
	int i,j;
	if (outfile.is_open())
	{
		for(i=0;i<9;i++)
		{
			for(j=0;j<9;j++)
			{
				outfile<<table[i][j]<<" ";
			}
			outfile<<endl;
		}
		outfile<<endl; 
	}
} 
void shuffle(int arr[], int n, int tablex) {
	int tmp, rd;
	srand((unsigned)(t++));
	for (int i = 0; i < n; i++) {
		rd = rand() % 9;
		tmp = arr[rd];
		arr[rd] = arr[i];
		arr[i] = tmp;
	}
	if (tablex == 0 && arr[0] != 6)shuffle(arr, n, tablex);
}
bool test(int x, int y, int v) {
	int _x = x / 3 * 3;
	int _y = y / 3 * 3;
	for (int i = _x; i < _x + 3; i++) {
		for (int j = _y; j < _y + 3; j++) {
			if (table[i][j] == v) {
				return false;
			}
		}
	}
	for (int i = 0; i < 9; i++) {
		if (table[x][i] == v || table[i][y] == v)
			return false;
	}
	return true;
}
bool put(int line, int index) {
	if (index > 8)
		return true;
	if (table[line][index] != 0) {
		return put(line, index + 1);
	}
	int num[] = { 1,2,3,4,5,6,7,8,9 };
	shuffle(num, 9, 1);
	for (int i = 0; i < 9; i++) {
		if (test(line, index, num[i]) == true) {
			table[line][index] = num[i];
			if (put(line, index + 1) == true) {
				return true;
			}
		}
	}
	table[line][index] = 0;
	return false;
}
bool put_line(int line) {
	if (line > 8)return true;
	if (put(line, 0) == true) {
		if (put_line(line + 1) == true)
			return true;
	}
	for (int i = 0; i < 9; i++) {
		table[line][i] = 0;
	}
	return false;
}

int main(int argc,char *argv[]) {
    if(argc!=3)
	{
		cout<<"输入格式有误"<<endl;
		return 0;
	}
	else if(strcmp(argv[1],"-c") != 0)
	{
		cout<<"输入格式有误"<<endl;
		return 0;
	}
	else
	{
		for(int i = 0;i < strlen(argv[2]);i++)
				if (argv[2][i] <'0'|| argv[2][i]>'9')
				{
					cout<<"输入格式有误" << endl;
					return 0;
				}
	}
	number=atoi(argv[2]);
    while (number--) {
	    for (int i = 0; i < 9; i++) {
		    table[0][i] = i + 1;
		}
      	shuffle((int *)&table[0], 9, 0);
       	while (!put_line(1))
       	{
	      	shuffle((int *)&table[0], 9, 0);
	    }
		printSudoku(table);
    } 
	outfile.close();
	return 0;
}
