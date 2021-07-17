#pragma once
#include <iostream> 
#include <vector> 
#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <stdio.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_color.h>
#include <allegro5\allegro_windows.h>
using namespace std;

const int width_boarder = 10;
int root[90];
int lowest_col;
int lowest_row;
int highest_col;
int highest_row;
int com_put_stone = 0;
int sw_point[9][9] = { 0 };
int lib[90] = { 0 };
int m = 0;
int max_lib = 0;
int sw_fsRoot[9][9] = { 0 };
int sw_group[9][9] = { 0 };
int lib_flag[9][9] = { 0 };


//give 0 to all elements of an array
void zero_array(int array[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			array[i][j] = 0;
		}
	}
}

void zero_lib(int lib[90])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			lib[i * width_boarder + j] = 0;
		}
	}
}

//counting liberty of stones and their connection (x * width_boarder + y for each cordination cuases working with 1 number instead of 2 numbers as cordinations)
void count_lib(int stone_array[9][9], int lib[], int lib_flag[9][9], int i, int j)
{
	int lib_count = 0;
	if (i + 1 < 9 && stone_array[i + 1][j] == 0)
	{
		lib_count++;
	}
	if (i - 1 >= 0 && stone_array[i - 1][j] == 0)
	{
		lib_count++;
	}
	if (j + 1 < 9 && stone_array[i][j + 1] == 0)
	{
		lib_count++;
	}
	if (j - 1 >= 0 && stone_array[i][j - 1] == 0)
	{
		lib_count++;
	}
	lib[i * width_boarder + j] = lib_count;
	if (lib_count == 1)
	{
		if (stone_array[i][j] == 1)
			lib_flag[i][j] = 1;
		else if (stone_array[i][j] == -1)
			lib_flag[i][j] = -1;
	}
}

//assigning special roots to each cordinations
void quantify_root(int root[])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			root[i * width_boarder + j] = i * width_boarder + j;
		}
	}
}

//checking the group of the last put stone and add it to the correct group
void check_add_group(int stone_array[9][9], int root[], int save_root, int sw_group[9][9], int i, int j)
{
	if (i >= 0 && i <= 8 && j >= 0 && j <= 8)
	{
		sw_group[i][j] = 1;
		if (stone_array[i][j] == stone_array[i - 1][j] && i - 1 >= 0 && sw_group[i - 1][j] == 0)
		{
			root[(i - 1) * width_boarder + j] = save_root;
			check_add_group(stone_array, root, save_root, sw_group, i - 1, j);
		}
		if (stone_array[i][j] == stone_array[i + 1][j] && i + 1 < 9 && sw_group[i + 1][j] == 0)
		{
			root[(i + 1) * width_boarder + j] = save_root;
			check_add_group(stone_array, root, save_root, sw_group, i + 1, j);
		}
		if (stone_array[i][j] == stone_array[i][j - 1] && j - 1 >= 0 && sw_group[i][j - 1] == 0)
		{
			root[i * width_boarder + (j - 1)] = save_root;
			check_add_group(stone_array, root, save_root, sw_group, i, j - 1);
		}
		if (stone_array[i][j] == stone_array[i][j + 1] && j + 1 < 9 && sw_group[i][j + 1] == 0)
		{
			root[i * width_boarder + (j + 1)] = save_root;
			check_add_group(stone_array, root, save_root, sw_group, i, j + 1);
		}
	}
}

//finding the group and liberties and using it for capturing
void find_same_root(int stone_array[9][9], int root[], int sw_fsRoot[9][9], int lib[], int i, int j)
{
	sw_fsRoot[i][j] = 1;
	if (root[i * width_boarder + j] == root[(i + 1) * width_boarder + j])
	{
		if (i + 1 < 9 && sw_fsRoot[i + 1][j] == 0)
			find_same_root(stone_array, root, sw_fsRoot, lib, i + 1, j);
		if (lib[i * width_boarder + j] > lib[(i + 1) * width_boarder + j])
		{
			lib[(i + 1) * width_boarder + j] = lib[i * width_boarder + j];
		}
		else
		{
			lib[i * width_boarder + j] = lib[(i + 1) * width_boarder + j];
		}
	}
	if (root[i * width_boarder + j] == root[(i - 1) * width_boarder + j])
	{
		if (i - 1 >= 0 && sw_fsRoot[i - 1][j] == 0)
			find_same_root(stone_array, root, sw_fsRoot, lib, i - 1, j);
		if (lib[i * width_boarder + j] > lib[(i - 1) * width_boarder + j])
		{
			lib[(i - 1) * width_boarder + j] = lib[i * width_boarder + j];
		}
		else
		{
			lib[i * width_boarder + j] = lib[(i - 1) * width_boarder + j];
		}
	}
	if (root[i * width_boarder + j] == root[i * width_boarder + (j + 1)])
	{
		if (j + 1 < 9 && sw_fsRoot[i][j + 1] == 0)
			find_same_root(stone_array, root, sw_fsRoot, lib, i, j + 1);
		if (lib[i * width_boarder + (j + 1)] > lib[i * width_boarder + j])
		{
			lib[i * width_boarder + j] = lib[i * width_boarder + (j + 1)];
		}
		else
		{
			lib[i * width_boarder + (j + 1)] = lib[i * width_boarder + j];
		}
	}
	if (root[i * width_boarder + j] == root[i * width_boarder + (j - 1)])
	{
		if (j - 1 >= 0 && sw_fsRoot[i][j - 1] == 0)
			find_same_root(stone_array, root, sw_fsRoot, lib, i, j - 1);
		if (lib[i * width_boarder + (j - 1)] > lib[i * width_boarder + j])
		{
			lib[i * width_boarder + j] = lib[i * width_boarder + (j - 1)];
		}
		else
		{
			lib[i * width_boarder + (j - 1)] = lib[i * width_boarder + j];
		}
	}
}

//suicide 
void suicide(int stone_array[9][9], int i, int j, int &turn)
{
	if (i == 0)
	{
		if (j == 0)
		{
			if (stone_array[i + 1][j] == stone_array[i][j + 1] && stone_array[i + 1][j] != 0)
			{

				//stone_array[i][j] = 0;
				turn *= (-1);
				//draw_display(stone_array);
			}
		}
		else if (j == 8)
		{
			if (stone_array[i + 1][j] == stone_array[i][j - 1] && stone_array[i + 1][j] != 0)
			{
				//stone_array[i][j] = 0;
				turn *= (-1);
				//draw_display(stone_array);
			}
		}
		else if (stone_array[i + 1][j] == stone_array[i][j + 1] && stone_array[i][j - 1] == stone_array[i][j + 1] && stone_array[i + 1][j] != 0)
		{
			//stone_array[i][j] = 0;
			turn *= (-1);
			//draw_display(stone_array);
		}
	}
	else if (i == 8)
	{
		if (j == 0)
		{
			if (stone_array[i - 1][j] == stone_array[i][j + 1] && stone_array[i - 1][j] != 0)
			{
				//stone_array[i][j] = 0;
				turn *= (-1);
				//draw_display(stone_array);
			}
		}
		else if (j == 8)
		{
			if (stone_array[i - 1][j] == stone_array[i][j - 1] && stone_array[i - 1][j] != 0)
			{
				//stone_array[i][j] = 0;
				turn *= (-1);
				//draw_display(stone_array);
			}
		}
		else if (stone_array[i - 1][j] == stone_array[i][j + 1] && stone_array[i][j - 1] == stone_array[i][j + 1] && stone_array[i - 1][j] != 0)
		{
			//stone_array[i][j] = 0;
			turn *= (-1);
			//draw_display(stone_array);
		}
	}
	else if (j == 0 && i != 0 && i != 8)
	{
		if (stone_array[i - 1][j] == stone_array[i][j + 1] && stone_array[i + 1][j] == stone_array[i][j + 1] && stone_array[i - 1][j] != 0)
		{
			//stone_array[i][j] = 0;
			turn *= (-1);
			//draw_display(stone_array);
		}
	}
	else if (j == 8 && i != 0 && i != 8)
	{
		if (stone_array[i - 1][j] == stone_array[i + 1][j] && stone_array[i][j - 1] == stone_array[i + 1][j] && stone_array[i - 1][j] != 0)
		{
			//stone_array[i][j] = 0;
			turn *= (-1);
			//draw_display(stone_array);
		}
	}
	else
	{
		if (stone_array[i + 1][j] == stone_array[i - 1][j] && stone_array[i][j + 1] == stone_array[i - 1][j] && stone_array[i][j - 1] == stone_array[i - 1][j] && stone_array[i - 1][j] != 0)
		{
			//stone_array[i][j] = 0;
			turn *= (-1);
			//draw_display(stone_array);
		}
	}
}


//save computer's group with 1 liberty
void SaveOwnGroup(int stone_array[9][9], int lib_flag[9][9], int &turn)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (lib_flag[i][j] == 1)
			{
				for (int m = -1; m < 2 && turn == 1; m++)
				{
					if (stone_array[i + m][j] == 0)
					{
						create_bitmap_white_stone("white_stone.png", i * 70 + 100, j * 70 + 100, 50, 50);
						stone_array[i + m][j] = 1;
						turn *= (-1);
					}
					else if (stone_array[i][j + m] == 0)
					{
						create_bitmap_white_stone("white_stone.png", i * 70 + 100, j * 70 + 100, 50, 50);
						stone_array[i][j + m] = 1;
						turn *= (-1);
					}

				}
			}
		}
	}
}

//capture opponent with 1 liberty
void CaptureEnemy(int stone_array[9][9], int lib_flag[9][9], int &turn)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (lib_flag[i][j] == -1)
			{
				for (int m = -1; m < 2 && turn == 1; m++)
				{
					if (stone_array[i + m][j] == 0)
					{
						create_bitmap_white_stone("white_stone.png", i * 70 + 100, j * 70 + 100, 50, 50);
						stone_array[i + m][j] = 1;
						turn *= (-1);
					}
					else if (stone_array[i][j + m] == 0)
					{
						create_bitmap_white_stone("white_stone.png", i * 70 + 100, j * 70 + 100, 50, 50);
						stone_array[i][j + m] = 1;
						turn *= (-1);
					}

				}
			}
		}
	}
}

//the main function of one player
void computer_playing(int stone_array[9][9], int lib_flag[9][9], int &turn, int com_put_stone)
{
	SaveOwnGroup(stone_array, lib_flag, turn);
	CaptureEnemy(stone_array, lib_flag, turn);
	if (turn == 1)
	{
		for (int i = 0; i < 9; i += 2)
		{
			for (int j = 0; j < 9 && stone_array[i][j] == 0 && com_put_stone == 0; j++)
			{
				create_bitmap_white_stone("white_stone.png", i * 70 + 100, j * 70 + 100, 50, 50);
				stone_array[i][j] = 1;
				com_put_stone++;
				turn *= (-1);
			}
		}
	}
}

//counting points
int counting_points(int stone_array[9][9], int sw_point[9][9], float &white_point, float &black_point)
{
	float komi = 6.5;
	int k = 0, m = 0, n = 0, l = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (stone_array[i][j] == 1)
				white_point++;
			else if (stone_array[i][j] == -1)
				black_point++;
			else if (stone_array[i][j] == 0 && sw_point[i][j] == 0)
			{
				sw_point[i][j] = 1;
				for (k = i; k < 9 && stone_array[k][j] == 0; k++);
				for (m = i; m >= 0 && stone_array[k][j] == 0; m--);
				for (n = j; n < 9 && stone_array[k][j] == 0; n++);
				for (l = j; l >= 0 && stone_array[k][j] == 0; l--);
				if ((stone_array[k][j] == 1 || k >= 9) && (stone_array[m][j] == 1 || m < 0) && (stone_array[i][n] == 1 || n >= 9) && (stone_array[i][l] == 1 || l < 0))
					white_point += k - m + n - l - 1;
				else if ((stone_array[k][j] == -1 || k >= 9) && (stone_array[m][j] == -1 || m < 0) && (stone_array[i][n] == -1 || n >= 9) && (stone_array[i][l] == -1 || l < 0))
					black_point += k - m + n - l - 1;
			}
		}
	}
	printf("%d \n", k);
	white_point += komi;
	if (white_point > black_point)
		return 1;
	else
		return -1;
}
