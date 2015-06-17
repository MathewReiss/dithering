#include <pebble.h>
#include "dithered_rects.h"

Window *my_window;
Layer *custom_layer;

int x_center = 72, y_center = 84;

int r_rand = 0, g_rand = 0, b_rand = 0;

void draw_custom_layer(Layer *cell_layer, GContext *ctx){
		
	#ifdef PBL_COLOR
		//int r_target = 25/*153*/, g_target = 71/*255*/, b_target = 25/*153*/;
		//GColor first = getFirstGColorFromRGB(r_target, g_target, b_target);
		//GColor second = getSecondGColorFromRGB(r_target, g_target, b_target);
		//DitherPercentage recommended = getRecommendedDitherPercentage(r_target, g_target, b_target, first, second);
	
		//draw_dithered_rect(ctx, GRect(0,0,144,168), first, second, recommended);
		
		draw_dithered_rect_from_RGB(ctx, GRect(0,0,144,168), r_rand, g_rand, b_rand);
		
		//draw_gradient_rect(ctx, GRect(0,0,144,168), GColorDarkGray, GColorClear, BOTTOM_TO_TOP);
		//draw_transitioning_rect(ctx, GRect(54,0,90,168), GColorBlue, GColorIslamicGreen);
		//draw_dithered_circle(ctx, x_center, y_center, 40, GColorCobaltBlue, GColorClear, DITHER_20_PERCENT);	
		//draw_dithered_circle(ctx, x_center, y_center, 35, GColorCobaltBlue, GColorLimerick, DITHER_25_PERCENT);
		
		//draw_random_gradient_rect(ctx, GRect(0,0,72,168), GColorCobaltBlue, GColorPictonBlue, TOP_TO_BOTTOM);
		//draw_gradient_rect(ctx, GRect(72,0,72,168), GColorCobaltBlue, GColorPictonBlue, TOP_TO_BOTTOM);
		
		//draw_dithered_rect(ctx, GRect(0,84,144,84), GColorBlack, GColorBlack, DITHER_0_PERCENT);
	
		//draw_dithered_rect(ctx, GRect(0,0,35,84), GColorBlack, GColorBlack, DITHER_0_PERCENT);
		//draw_dithered_rect(ctx, GRect(0,84,35,84), GColorWhite, GColorWhite, DITHER_0_PERCENT);
	
		//draw_dithered_rect(ctx, GRect(36,0,35,56), GColorBlack, GColorBlack, DITHER_0_PERCENT);
		//draw_dithered_rect(ctx, GRect(36,56,35,56), GColorBlack, GColorWhite, DITHER_50_PERCENT);
		//draw_dithered_rect(ctx, GRect(36,112,35,56), GColorWhite, GColorWhite, DITHER_0_PERCENT);
	
		//draw_dithered_rect(ctx, GRect(72,0,35,42), GColorBlack, GColorBlack, DITHER_0_PERCENT);
		//draw_dithered_rect(ctx, GRect(72,42,35,42), GColorDarkGray, GColorDarkGray, DITHER_0_PERCENT);
		//draw_dithered_rect(ctx, GRect(72,84,35,42), GColorLightGray, GColorLightGray, DITHER_0_PERCENT);
		//draw_dithered_rect(ctx, GRect(72,126,35,42), GColorWhite, GColorWhite, DITHER_0_PERCENT);
		
		//draw_dithered_rect(ctx, GRect(108,0,36,24), GColorBlack, GColorDarkGray, DITHER_0_PERCENT);
		//draw_dithered_rect(ctx, GRect(108,24,36,24), GColorBlack, GColorDarkGray, DITHER_50_PERCENT);
		//draw_dithered_rect(ctx, GRect(108,48,36,24), GColorDarkGray, GColorLightGray, DITHER_0_PERCENT);
		//draw_dithered_rect(ctx, GRect(108,72,36,24), GColorDarkGray, GColorLightGray, DITHER_50_PERCENT);
		//draw_dithered_rect(ctx, GRect(108,96,36,24), GColorLightGray, GColorWhite, DITHER_0_PERCENT);
		//draw_dithered_rect(ctx, GRect(108,120,36,24), GColorLightGray, GColorWhite, DITHER_50_PERCENT);
		//draw_dithered_rect(ctx, GRect(108,144,36,24), GColorWhite, GColorWhite, DITHER_0_PERCENT);
		
	#else
		//draw_gradient_rect(ctx, GRect(0,0,144,168), GColorBlack, GColorClear, BOTTOM_TO_TOP);
		//draw_dithered_rect(ctx, GRect(0,0,, GColor first_color, GColor second_color, DitherPercentage percentage)
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

void color_tick(){
	r_rand = rand()%255;
	g_rand = rand()%255;
	b_rand = rand()%255;
	
	APP_LOG(APP_LOG_LEVEL_DEBUG, "%03d,%03d,%03d", r_rand, g_rand, b_rand);
	
	layer_mark_dirty(custom_layer);
	
	app_timer_register(15000, color_tick, NULL);
}

void init(void){
	int seed = time(NULL);
	srand(seed);
	my_window = window_create();
	//window_set_fullscreen(my_window, true);
	
	//init_rand();
	
	custom_layer = layer_create(GRect(0,0,144,168));
	layer_set_update_proc(custom_layer, draw_custom_layer);
	
	layer_add_child(window_get_root_layer(my_window), custom_layer);
	
	window_stack_push(my_window, true);
	
	light_enable(true);
	
	color_tick();
	
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