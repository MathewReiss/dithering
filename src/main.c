#include <pebble.h>
#include "dithered_rects.h"

Window *my_window;
Layer *custom_layer;

int x_center = 72, y_center = 84;

void draw_custom_layer(Layer *cell_layer, GContext *ctx){
	
	#ifdef PBL_COLOR
		//draw_gradient_rect(ctx, GRect(0,0,54,168), GColorDarkGray, GColorChromeYellow, RIGHT_TO_LEFT);
		//draw_transitioning_rect(ctx, GRect(54,0,90,168), GColorBlue, GColorIslamicGreen);
		//draw_dithered_circle(ctx, x_center, y_center, 40, GColorCobaltBlue, GColorLimerick, DITHER_20_PERCENT);	
		//draw_dithered_circle(ctx, x_center, y_center, 35, GColorCobaltBlue, GColorLimerick, DITHER_25_PERCENT);
		
		draw_random_gradient_rect(ctx, GRect(0,0,72,168), GColorCobaltBlue, GColorPictonBlue, TOP_TO_BOTTOM);
		draw_gradient_rect(ctx, GRect(72,0,72,168), GColorCobaltBlue, GColorPictonBlue, TOP_TO_BOTTOM);
	#else
		draw_dithered_circle(ctx, x_center, y_center, 40, GColorBlack, GColorWhite, DITHER_20_PERCENT);	
		draw_dithered_circle(ctx, x_center, y_center, 35, GColorBlack, GColorWhite, DITHER_25_PERCENT);
	#endif
}

bool moving_right = true;

void move_tick(){
	if(moving_right){
		if(x_center < 104) x_center+=2;
		else moving_right = false;
	}
	else{
		if(x_center > 40) x_center-=2;
		else moving_right = true;
	}
	layer_mark_dirty(custom_layer);
	app_timer_register(20, move_tick, NULL);
}

void init(void){
	my_window = window_create();
	window_set_fullscreen(my_window, true);
	
	init_rand();
	
	custom_layer = layer_create(GRect(0,0,144,168));
	layer_set_update_proc(custom_layer, draw_custom_layer);
	
	layer_add_child(window_get_root_layer(my_window), custom_layer);
	
	window_stack_push(my_window, true);
	
	light_enable(true);
	
	//app_timer_register(100, move_tick, NULL);
	
	//start_transitioning_rect(custom_layer, 100);
}

void deinit(void){
	//stop_transitioning_rect();
	
	window_destroy(my_window);
	layer_destroy(custom_layer);
}

int main(void){
	init();
	app_event_loop();
	deinit();
}