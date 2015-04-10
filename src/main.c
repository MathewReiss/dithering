#include <pebble.h>
#include "dithered_rects.h"

Window *my_window;
Layer *custom_layer;

void draw_custom_layer(Layer *cell_layer, GContext *ctx){
	
	#ifdef PBL_COLOR
		draw_gradient_rect(ctx, GRect(0,0,54,168), GColorDarkGray, GColorChromeYellow, RIGHT_TO_LEFT);
		draw_transitioning_rect(ctx, GRect(54,0,90,168), GColorBlue, GColorIslamicGreen);
	#else
		draw_gradient_rect(ctx, GRect(0, 0, 144, 168), GColorBlack, GColorWhite, TOP_TO_BOTTOM);
	#endif
}

void init(void){
	my_window = window_create();
	window_set_fullscreen(my_window, true);
	
	custom_layer = layer_create(GRect(0,0,144,168));
	layer_set_update_proc(custom_layer, draw_custom_layer);
	
	layer_add_child(window_get_root_layer(my_window), custom_layer);
	
	window_stack_push(my_window, true);
	
	light_enable(true);
	
	start_transitioning_rect(custom_layer, 100);
}

void deinit(void){
	stop_transitioning_rect();
	
	window_destroy(my_window);
	layer_destroy(custom_layer);
}

int main(void){
	init();
	app_event_loop();
	deinit();
}