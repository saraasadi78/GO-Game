#pragma once
#include <iostream>
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

const int width = 800;
const int height = 800;
const char FONT_NAME[] = "ARIALI.TTF";
const char IMAGE_DROGON[] = "dragon_background.jpg";
const char musName[30] = "file_(donkool.com)-10-10.ogg";
const char pass[] = "Pass";
struct board
{
	int x;
	int y;
};

//initialize display =======================================================================================================================================
int init_display() {
	if (!al_init()) {
		al_show_native_message_box(al_get_current_display(),
			"Error",
			"Could not init",
			"Failed to initialize allegro!\n",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
	ALLEGRO_DISPLAY* display = al_create_display(width, height);
	al_set_window_position(display, 500, 100);
	al_clear_to_color(al_map_rgb(226, 173, 50));
	return 0;
}

//linking game board with array ============================================================================================================================
void BoardArray(board board_array[9])
{
	for (int i = 0; i < 9; i++)
	{
		board_array[i].x = 125 + i * 70;
		board_array[i].y = 125 + i * 70;
	}
}

//print text ===============================================================================================================================================
void print_text(const char text[], int x, int y, int R = 255, int G = 255, int B = 255, const char
	font_name[] = FONT_NAME) {
	ALLEGRO_FONT *font = al_load_ttf_font("ARIALI.TTF", 25, 5);
	al_draw_text(font, al_map_rgb(R, G, B), x, y, 0, text);
}

//bitmap for background ====================================================================================================================================
void create_bitmap_dragon(const char image_name[], float x, float y, int width, int height) {
	ALLEGRO_BITMAP *image = NULL;
	image = al_load_bitmap("dragon_background.jpg");
	al_draw_scaled_bitmap(image,
		0, 0,                             // source origin
		al_get_bitmap_width(image),       // source width
		al_get_bitmap_height(image),      // source height
		x, y,                             // target origin
		width, height,                    // target dimensions
		0                                 // flags
	);
}

//bitmap for white stone ===================================================================================================================================
int create_bitmap_white_stone(const char image_name[], float x, float y, int width, int height) {
	ALLEGRO_BITMAP *image = NULL;
	image = al_load_bitmap("white_stone.png");
	al_draw_scaled_bitmap(image,
		0, 0,                             // source origin
		al_get_bitmap_width(image),       // source width
		al_get_bitmap_height(image),      // source height
		x, y,                             // target origin
		width, height,                    // target dimensions
		0                                 // flags
	);
	return 0;
}

//bitmap for black stone ===================================================================================================================================
int create_bitmap_black_stone(const char image_name[], float x, float y, int width, int height) {
	ALLEGRO_BITMAP *image = NULL;
	image = al_load_bitmap("black.png");
	al_draw_scaled_bitmap(image,
		0, 0,                             // source origin
		al_get_bitmap_width(image),       // source width
		al_get_bitmap_height(image),      // source height
		x, y,                             // target origin
		width, height,                    // target dimensions
		0                                 // flags
	);
	return 0;
}

//drawing pass bottom ======================================================================================================================================
void draw_pass_bottom()
{
	al_draw_filled_rectangle(700, 740, 790, 790, al_map_rgb(226, 173, 50));
	print_text(pass, 720, 750, 0, 0, 0, "ARIALI.TTF");
}
void draw_pass_bottom_click()
{
	al_draw_filled_rectangle(700, 740, 790, 790, al_map_rgb(181, 133, 26));
	print_text(pass, 720, 750, 0, 0, 0, "ARIALI.TTF");
}

//draw save button
void draw_save_button()
{
	al_draw_filled_rectangle(10, 740, 100, 790, al_map_rgb(226, 173, 50));
	print_text("save", 30, 750, 0, 0, 0, "ARIALI.TTF");
}
void draw_save_button_click()
{
	al_draw_filled_rectangle(10, 740, 100, 790, al_map_rgb(181, 133, 26));
	print_text("save", 30, 750, 0, 0, 0, "ARIALI.TTF");
}

//drawing display for the first time =====================================================================================================================
void draw_display(int stone_array[9][9])
{
	//background
	create_bitmap_dragon("dragon_background.jpg", 0, 0, 800, 800);

	// draw chart ================================================================================
	for (int i = 0; i < 9; i++)
	{
		al_draw_line(125 + (i * 70), 125, 125 + (i * 70), 685, al_map_rgb(0, 0, 0), 3);
		al_draw_line(125, 125 + (i * 70), 685, 125 + (i * 70), al_map_rgb(0, 0, 0), 3);
	}
	// drawing circles ===========================================================================
	al_draw_filled_circle(265, 265, 7, al_map_rgb(0, 0, 0));
	al_draw_filled_circle(265, 545, 7, al_map_rgb(0, 0, 0));
	al_draw_filled_circle(405, 405, 7, al_map_rgb(0, 0, 0));
	al_draw_filled_circle(545, 265, 7, al_map_rgb(0, 0, 0));
	al_draw_filled_circle(545, 545, 7, al_map_rgb(0, 0, 0));

	// drawing borders ============================================================================
	al_draw_rectangle(125, 125, 685, 685, al_map_rgb(0, 0, 0), 6);

	//printing letters ============================================================================
	int aski = 64;
	for (int i = 0; i < 9; i++) {
		aski++;
		char temp = (char)aski;
		char javab[] = { temp,'\0' };
		print_text(javab, 115 + 70 * i, 50, 0, 0, 0, "ARIALI.TTF");
		print_text(javab, 115 + 70 * i, 735, 0, 0, 0, "ARIALI.TTF");
	}
	//printing numbers =============================================================================
	int num = 48;
	for (int i = 0; i < 9; i++)
	{
		num++;
		char NUM = (char)num;
		char javab1[] = { NUM ,'\0' };
		print_text(javab1, 50, 110 + 70 * i, 0, 0, 0, "SHOWG.TTF");
		print_text(javab1, 735, 110 + 70 * i, 0, 0, 0, "SHOWG.TTF");
	}
	//pass bottom
	draw_pass_bottom();
	draw_save_button();
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (stone_array[i][j] == 1)
				create_bitmap_white_stone("white_stone.png", i * 70 + 100, j * 70 + 100, 50, 50);
			else if (stone_array[i][j] == -1)
				create_bitmap_black_stone("black.png", i * 70 + 100, j * 70 + 100, 50, 50);
		}
	}
}


int create_bitmap_keyboard(const char image_name[], int x, int y, int width, int height) {
	ALLEGRO_BITMAP *image = NULL;
	image = al_load_bitmap("AX.png");
	al_draw_scaled_bitmap(image,
		0, 0,                             // source origin
		al_get_bitmap_width(image),       // source width
		al_get_bitmap_height(image),      // source height
		x, y,                             // target origin
		width, height,                    // target dimensions
		0                                 // flags
	);
	return 0;
}