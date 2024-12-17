#pragma once

#include <map>
#include <string>

struct game_desc
{
	/* callbacks */
	void (*load_cb)(void);
	void (*cleanup_cb)(void);
	void (*update_cb)(float);
	void (*draw_cb)(void);
	void (*gui_cb)(void);

	/* mouse */
	void (*mouse_moved_cb)(float, float, float, float);
	void (*mouse_pressed_cb)(float, float, int);
	void (*mouse_released_cb)(float, float, int);

	/* keyboard */
	void (*keyboard_keypressed_cb)(int, bool);
	void (*keyboard_keyreleased_cb)(int);

	struct
	{
		bool console;
		struct
		{
			int width;
			int height;
			const char *title;
		} window;
	} config;
};

/* user-provided functions */
/* FIXME: can this be a namespace */
extern game_desc game_main(int argv, char *argc[]);

namespace engine
{
	struct module_t
	{
		struct
		{
			float x;
			float y;
			bool is_down;
		} mouse;

		struct
		{
			int width;
			int height;
		} graphics;
	};
}