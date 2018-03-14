//#include "game.h"
#include  <iostream>
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\keyboard.h>
#include <allegro5\allegro_font.h>

#define FPS 60

void sys_pause()
{
	std::cout << "Press Enter to continue ...";
	std::getchar();
}

//int main(int argc, int *argv[])
int main()
{
	bool is_running = true;
	bool can_put_text = false;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT event;
	ALLEGRO_TIMER *timer;
	ALLEGRO_FONT *font;

	al_init();

	al_install_keyboard();
	al_init_font_addon();
	al_init_primitives_addon();

	timer = al_create_timer(1.0 / FPS);
	event_queue = al_create_event_queue();
	display = al_create_display(640, 480);
	font = al_create_builtin_font();

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	char str[200] = "";
	float y = 1.0, x = 1.0, yt = 1.0, xt = 1;

	al_start_timer(timer);

	while (is_running) {


		if (can_put_text) {
			al_clear_to_color(al_map_rgb(0, 0 , 0));
			//std::cout << al_keycode_to_name(event.keyboard.keycode) << std::endl;
			al_draw_textf(font, al_map_rgb(0, 255, 0), xt, yt, 0, "%s", str);
			al_draw_pixel(640 / 2, 480 / 2 + y, al_map_rgb(255, 0, 255));
			al_flip_display();
			can_put_text = false;
		}

		al_wait_for_event(event_queue, &event);

		switch (event.type) {
		case ALLEGRO_EVENT_KEY_DOWN:
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) is_running = false;
			strcat_s(str, al_keycode_to_name(event.keyboard.keycode));
			//xt += 10;
			break;
		case ALLEGRO_EVENT_TIMER:
			//std::cout << al_get_timer_count(timer) << std::endl;
			if (al_is_event_queue_empty(event_queue))
				can_put_text = true;
			break;
		default:
			break;
		}

		//al_clear_to_color(al_map_rgb(0, 0 , 0));
	}


	sys_pause();
	return 0;
}
