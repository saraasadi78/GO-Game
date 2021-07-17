#pragma once
#include "stone.h"
#include "board.h"

const char image_name1[] = "background.png";
const char image_name2[] = "trad.jpg";
int x, y,x2,y2;

ALLEGRO_FONT*font1 = al_load_ttf_font("annifont.ttf", 20, 0);


int init_menu() {
	if (!al_init()) {
		al_show_native_message_box(al_get_current_display(),
			"Error",
			"Could not init",
			"Failed to initialize allegro!\n",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
	ALLEGRO_DISPLAY* menu = al_create_display(800, 800);
	al_set_window_position(menu, 500, 100);
	al_set_window_title(menu, "MENU");
	al_clear_to_color(al_map_rgb(226, 173, 50));
	al_flip_display();
	return 0;
}

void create_bitmap(const char image_name[], float x, float y, int width, int height) {
	ALLEGRO_BITMAP *image = NULL;
	image = al_load_bitmap(image_name);
	al_draw_scaled_bitmap(image,
		0, 0, // source origin
		al_get_bitmap_width(image), // source width
		al_get_bitmap_height(image), // source height
		x, y, // target origin
		width, height, // target dimensions
		0 // flags
	);
}


void sara(/*ALLEGRO_EVENT_QUEUE * event_queue, bool &one_player, bool &two_players, bool &done, bool &music, ALLEGRO_SAMPLE *sample, ALLEGRO_SAMPLE_INSTANCE *sampleInstance, ALLEGRO_SAMPLE_ID &id*/)
{
	ALLEGRO_FONT*font1 = al_load_ttf_font("annifont.ttf", 20, 0);
 

	create_bitmap(image_name1, 0, 0, 800, 800);

	al_draw_filled_rounded_rectangle(250, 150, 550, 200, 10, 10, al_map_rgb(0, 0, 0));
	al_draw_filled_rounded_rectangle(250, 250, 390, 300, 10, 10, al_map_rgb(0, 0, 0));
	al_draw_filled_rounded_rectangle(400, 250, 550, 300, 10, 10, al_map_rgb(0, 0, 0));
	al_draw_filled_rounded_rectangle(250, 350, 390, 400, 10, 10, al_map_rgb(0, 0, 0));
	al_draw_filled_rounded_rectangle(400, 350, 550, 400, 10, 10, al_map_rgb(0, 0, 0));
	al_draw_filled_rounded_rectangle(250, 450, 550, 500, 10, 10, al_map_rgb(0, 0, 0));
	al_draw_filled_rounded_rectangle(250, 550, 550, 600, 10, 10, al_map_rgb(0, 0, 0));

	al_draw_text(font1, al_map_rgb(255, 255, 255), 250, 150, 0, "    welcome to go game");
	al_draw_text(font1, al_map_rgb(255, 255, 255), 252, 250, 0, " one player");
	al_draw_text(font1, al_map_rgb(255, 255, 255), 400, 250, 0, " two players");
	al_draw_text(font1, al_map_rgb(255, 255, 255), 250, 350, 0, " music on");
	al_draw_text(font1, al_map_rgb(255, 255, 255), 400, 350, 0, " music off");
	al_draw_text(font1, al_map_rgb(255, 255, 255), 250, 450, 0, "   continue saved game");
	al_draw_text(font1, al_map_rgb(255, 255, 255), 355, 550, 0, " exit");
}
