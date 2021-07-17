// Go.cpp : Defines the entry point for the console application.
//
#include "board.h"
#include "stone.h"
#include"menu.h"

//global variables ========================================================================================================================================
int save_root, save_stone;
int i = 0, j = 0;
enum color_stone { Empty, White, Black };

//show massages ============================================================================================================================================
int message_box(const char* message,
	const char* content_title,
	const char* title)
{
	switch (al_show_native_message_box(
		al_get_current_display(),
		title,
		content_title,
		message, NULL,
		ALLEGRO_MESSAGEBOX_WARN)
		)
	{
	case 0: return 0;                       // User pressed the Cancel button
	case 1: return 1;                       // User pressed the OK button
	}
}

//function of pass =========================================================================================================================================
void function_pass(bool &pass_Pl_1, bool &pass_Pl_2, int &turn)
{
	draw_pass_bottom_click();
	if (turn == 1)
	{
		pass_Pl_1 = true;
		turn *= (-1);
	}
	else if (turn == -1)
	{
		pass_Pl_2 = true;
		turn *= (-1);
	}
}

//finding the positon of mouse and putting stones and checking capturing ====================================================================================
void mouse_position(float cursor_x, float cursor_y, bool &pass_Pl_1, bool &pass_Pl_2, bool one_player, bool two_players, int &turn, int stone_array[9][9], vector<int> zeroLib, int white_num, int black_num)
{

	if (cursor_x >= 700 && cursor_x <= 790 && cursor_y >= 740 && cursor_y <= 790)
	{
		function_pass(pass_Pl_1, pass_Pl_2, turn);
	}
	else
	{
		for (i = 0; i < 9; i++)
		{
			int first_range_x = 90;
			int end_range_x = 160;
			first_range_x += i * 70;
			end_range_x += i * 70;

			if (cursor_x > first_range_x && cursor_x < end_range_x)
			{
				for (j = 0; j < 9; j++)
				{
					int first_range_y = 90;
					int end_range_y = 160;
					first_range_y += j * 70;
					end_range_y += j * 70;
					if (cursor_y > first_range_y && cursor_y < end_range_y && stone_array[i][j] == 0)
					{
						if (two_players)
						{
							if (turn == -1)
							{
								pass_Pl_2 = false;
								create_bitmap_black_stone("black.png", end_range_x - 60, end_range_y - 60, 50, 50);
								stone_array[i][j] = -1;
								turn *= (-1);
							}
							else if (turn == 1)
							{
								pass_Pl_1 = false;
								create_bitmap_white_stone("white_stone.png", end_range_x - 60, end_range_y - 60, 50, 50);
								stone_array[i][j] = 1;
								turn *= (-1);
							}
						}
						else if (one_player)
						{
							if (turn == -1)
							{
								pass_Pl_2 = false;
								create_bitmap_black_stone("black.png", end_range_x - 60, end_range_y - 60, 50, 50);
								stone_array[i][j] = -1;
								turn *= (-1);
							}
							if (turn == 1)
							{
								pass_Pl_1 = false;
								computer_playing(stone_array, lib_flag, turn, com_put_stone);
							}
						}
						for (int m = 0; m < 9; m++)
						{
							for (int n = 0; n < 9; n++)
							{
								count_lib(stone_array, lib, lib_flag, m, n);
							}
						}
						save_root = root[i * width_boarder + j];
						check_add_group(stone_array, root, save_root, sw_group, i, j);
						for (int m = 0; m < 9; m++)
						{
							for (int n = 0; n < 9; n++)
							{
								find_same_root(stone_array, root, sw_fsRoot, lib, m, n);
							}
						}
						for (int m = 0; m < 9; m++)
						{
							for (int n = 0; n < 9; n++)
							{
								if (lib[m * width_boarder + n] == 0 && stone_array[m][n] != 0)
								{
									zeroLib.push_back(m * width_boarder + n);
								}
							}
						}
						for (int m = 0; m < zeroLib.size(); m++)
						{
							stone_array[zeroLib[m] / width_boarder][zeroLib[m] % width_boarder] = 0;
							if (stone_array[zeroLib[m] / width_boarder][zeroLib[m] % width_boarder] == 1)
								white_num--;
							else if (stone_array[zeroLib[m] / width_boarder][zeroLib[m] % width_boarder] == -1)
								black_num--;
							draw_display(stone_array);
						}
						suicide(stone_array, i, j, turn);
					}
				}
			}
		}
	}
}

//finding the positon of mouse and putting stones and checking capturing
void key_enter(int pos_x, int pos_y, bool &pass_Pl_1, bool &pass_Pl_2, bool one_player, bool two_players, int &turn, int stone_array[9][9], vector<int> zeroLib, int white_num, int black_num)
{

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (pos_x == 125 + i * 70 && pos_y == 125 + j * 70 && stone_array[i][j] == 0)
			{
				if (two_players)
				{
					if (turn == -1)
					{
						pass_Pl_2 = false;
						create_bitmap_black_stone("black.png", pos_x - 25, pos_y - 25, 50, 50);
						stone_array[i][j] = -1;
						turn *= (-1);
					}
					else if (turn == 1)
					{
						pass_Pl_1 = false;
						create_bitmap_white_stone("white_stone.png", pos_x - 25, pos_y - 25, 50, 50);
						stone_array[i][j] = 1;
						turn *= (-1);
					}
				}
				else if (one_player)
				{
					if (turn == -1)
					{
						pass_Pl_2 = false;
						create_bitmap_black_stone("black.png", pos_x - 25, pos_y - 25, 50, 50);
						stone_array[i][j] = -1;
						turn *= (-1);
					}
					if (turn == 1)
					{
						pass_Pl_1 = false;
						computer_playing(stone_array, lib_flag, turn, com_put_stone);
					}
				}
				for (int m = 0; m < 9; m++)
				{
					for (int n = 0; n < 9; n++)
					{
						count_lib(stone_array, lib, lib_flag, m, n);
					}
				}
				save_root = root[i * width_boarder + j];
				check_add_group(stone_array, root, save_root, sw_group, i, j);
				for (int m = 0; m < 9; m++)
				{
					for (int n = 0; n < 9; n++)
					{
						find_same_root(stone_array, root, sw_fsRoot, lib, m, n);
					}
				}
				for (int m = 0; m < 9; m++)
				{
					for (int n = 0; n < 9; n++)
					{
						if (lib[m * width_boarder + n] == 0 && stone_array[m][n] != 0)
						{
							zeroLib.push_back(m * width_boarder + n);
						}
					}
				}
				for (int m = 0; m < zeroLib.size(); m++)
				{
					stone_array[zeroLib[m] / width_boarder][zeroLib[m] % width_boarder] = 0;
					if (stone_array[zeroLib[m] / width_boarder][zeroLib[m] % width_boarder] == 1)
						white_num--;
					else if (stone_array[zeroLib[m] / width_boarder][zeroLib[m] % width_boarder] == -1)
						black_num--;
					draw_display(stone_array);
				}
				suicide(stone_array, i, j, turn);
			}
		}
	}
}



int main()
{
	//boolian variable ==================
	bool done = false;
	bool redraw = true;
	bool pass_Pl_1 = false;
	bool pass_Pl_2 = false;
	bool one_player = false;
	bool two_players = false;
	bool music = false;
	bool end = false;
	bool menu = true;
	bool playing = false;

	//variable ==========================
	int pos_x = 125;
	int pos_y = 125;
	int turn = -1;
	int FPS = 30;
	int stone_x;
	int stone_y;
	int white_num = 40;
	int black_num = 41;
	int stone_array[9][9] = { 0 };
	float cursor_x = 0;
	float cursor_y = 0;
	board board_array[9] = { 0 };


	//init ==============================
	init_menu();
	al_init_primitives_addon();
	al_init_acodec_addon();
	al_init_font_addon();
	al_init_image_addon();
	al_init_native_dialog_addon();
	al_init_ttf_addon();
	//install ===========================
	al_install_keyboard();
	al_install_mouse();
	al_install_audio();

	al_reserve_samples(1);
	
	// allegro variable =========================================================
	ALLEGRO_SAMPLE *sample = al_load_sample(musName);
	ALLEGRO_SAMPLE_INSTANCE *sampleInstance = al_create_sample_instance(sample);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
	ALLEGRO_SAMPLE_ID id;
 
	al_set_sample_instance_playmode(sampleInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(sampleInstance, al_get_default_mixer());
//	al_play_sample_instance(sampleInstance);

	//al_register ================================================================================
	al_register_event_source(event_queue, al_get_display_event_source(al_get_current_display()));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	//menu
	sara(/*event_queue, one_player, two_players, done,music,sample, sampleInstance,id*/);



	vector<int> zeroLib;
	quantify_root(root);
	al_start_timer(timer);
	// events =======================================================================================
	while (!done)
	{
	 
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		ALLEGRO_EVENT ev2;
		al_wait_for_event(event_queue, &ev2);
		x = ev2.mouse.x;
		y = ev2.mouse.y;
		if (menu)
		{
			if (ev2.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				menu = false;
				done = true;
				break;
			}

			else if (ev2.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{

				if (x > 250 && x < 390 && y > 250 && y < 300)
				{
					menu = false;
					playing = true;
					one_player = true;
					draw_display(stone_array);
				}
				if (x > 400 && x < 550 && y > 250 && y < 280)
				{
					menu = false;
					playing = true;
					two_players = true;
					draw_display(stone_array);
				}
				if (x > 250 && x < 390 && y > 320 && y < 380)
				{
					music = true;
					// playing audio =============================================================================
					if (music)
					{
						al_play_sample(sample, 10, 0, 1, ALLEGRO_PLAYMODE_LOOP, &id);
					}

				}

				if (x > 400 && x < 550 && y > 325 && y < 360)
				{
					music = false;
					if (music == false) { al_stop_sample(&id); }
				}

				if (x > 250 && x < 550 && y > 500 && y <550)
				{
					exit(0);
				}
				printf("x=%d   y=%d \n", x, y);
			}
		}

		else if (playing)
		{
			//keyboard events ===============================================================
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_UP:
					pos_y -= 70;
					break;
				case ALLEGRO_KEY_DOWN:
					pos_y += 70;
					break;
				case ALLEGRO_KEY_RIGHT:
					pos_x += 70;
					break;
				case ALLEGRO_KEY_LEFT:
					pos_x -= 70;
					break;
				case ALLEGRO_KEY_ENTER:
					key_enter(pos_x, pos_y, pass_Pl_1, pass_Pl_2, one_player, two_players, turn, stone_array, zeroLib, white_num, black_num);
					draw_display(stone_array);
					break;
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				}
				if (pos_x >= 125 && pos_x <= 685 && pos_y >= 125 && pos_y <= 685)
				{
					create_bitmap_keyboard("AX.png", pos_x - 25, pos_y - 25, 50, 50);
				}
				else if (pos_x < 125 || pos_x > 685 || pos_y < 125 || pos_y > 685)
				{
					pos_x = 125;
					pos_y = 125;
					al_draw_filled_circle(pos_x, pos_y, 20, al_map_rgb(196, 196, 196));
				}
			}
			else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				done = true;
			}
			else if (ev.type == ALLEGRO_EVENT_TIMER)
			{
				redraw = true;
			}
			else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				cursor_x = ev.mouse.x;
				cursor_y = ev.mouse.y;

				//putting stones and check capturing ===========================================================
				mouse_position(cursor_x, cursor_y, pass_Pl_1, pass_Pl_2, one_player, two_players, turn, stone_array, zeroLib, white_num, black_num);
				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 9; j++)
					{
						find_same_root(stone_array, root, sw_fsRoot, lib, i, j);
					}
				}
				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 9; j++)
					{
						if (lib[i * width_boarder + j] == 0 && stone_array[i][j] != 0)
						{
							zeroLib.push_back(i * width_boarder + j);
						}
					}
				}
				for (int i = 0; i < zeroLib.size(); ++i)
				{
					stone_array[zeroLib[i] / width_boarder][zeroLib[i] % width_boarder] = 0;
					al_draw_filled_circle((zeroLib[i] / width_boarder) * 70 + 125, (zeroLib[i] % width_boarder) * 70 + 125, 25, al_map_rgb(196, 196, 196));
				}
			}
			else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{
				if (cursor_x >= 700 && cursor_x <= 790 && cursor_y >= 740 && cursor_y <= 790)
				{
					draw_pass_bottom();
					if (pass_Pl_1)
						message_box("Player1 passed", "warning", "warning");
					else if (pass_Pl_2)
						message_box("Player2 passed", "warning", "warning");
				}
				pass_Pl_1 = false;
				pass_Pl_2 = false;

				//debugging
				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 9; j++)
					{
						printf("%d ", lib[j * width_boarder + i]);
					}
					printf("\n");
				}
				printf("\n");
				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 9; j++)
					{
						printf("%d ", root[j * width_boarder + i]);
					}
					printf("\n");
				}
				printf("\n");
				zero_lib(lib);
				zero_array(sw_fsRoot);
				zero_array(sw_group);
			}
			if (redraw && al_is_event_queue_empty(event_queue))
			{
				redraw = false;
			}
		}
		al_flip_display();
	}
	//destroy objects ===================
	al_destroy_sample(sample);
	al_destroy_sample_instance(sampleInstance);
	al_destroy_event_queue(event_queue);

}

