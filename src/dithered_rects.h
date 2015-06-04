#include <pebble.h>
//From https://github.com/MathewReiss/dithering

typedef enum{
	TOP_TO_BOTTOM,
	BOTTOM_TO_TOP,
	LEFT_TO_RIGHT,
	RIGHT_TO_LEFT,
	TOP_LEFT_TO_BOTTOM_RIGHT,
	BOTTOM_RIGHT_TO_TOP_LEFT,
	TOP_RIGHT_TO_BOTTOM_LEFT,
	BOTTOM_LEFT_TO_TOP_RIGHT
} GradientDirection;

typedef enum{
	DITHER_0_PERCENT,
	DITHER_10_PERCENT,
	DITHER_20_PERCENT,
	DITHER_25_PERCENT,
	DITHER_30_PERCENT,
	DITHER_40_PERCENT,
	DITHER_50_PERCENT,
	DITHER_60_PERCENT,
	DITHER_70_PERCENT,
	DITHER_75_PERCENT,
	DITHER_80_PERCENT,
	DITHER_90_PERCENT,
	DITHER_100_PERCENT
} DitherPercentage;


//=========================================================================================================================
// CONVERSION
//=========================================================================================================================

DitherPercentage getDitherFromPercentage(int percentage){
	switch(percentage){
		case 0: return DITHER_0_PERCENT;
		case 10: return DITHER_10_PERCENT;
		case 20: return DITHER_20_PERCENT;
		case 25: return DITHER_25_PERCENT;
		case 30: return DITHER_30_PERCENT;
		case 40: return DITHER_40_PERCENT;
		case 50: return DITHER_50_PERCENT;
		case 60: return DITHER_60_PERCENT;
		case 70: return DITHER_70_PERCENT;
		case 75: return DITHER_75_PERCENT;
		case 80: return DITHER_80_PERCENT;
		case 90: return DITHER_90_PERCENT;
		case 100: return DITHER_100_PERCENT;
		default: return DITHER_0_PERCENT;
	}
}

int getPercentageFromDither(DitherPercentage dither){
	switch(dither){
	
		case DITHER_0_PERCENT: return 0;
		case DITHER_10_PERCENT: return 10;
		case DITHER_20_PERCENT: return 20;
		case DITHER_25_PERCENT: return 25;
		case DITHER_30_PERCENT: return 30;
		case DITHER_40_PERCENT: return 40;
		case DITHER_50_PERCENT: return 50;
		
		case DITHER_60_PERCENT: return 60;
		case DITHER_70_PERCENT: return 70;
		case DITHER_75_PERCENT: return 75;
		case DITHER_80_PERCENT: return 80;
		case DITHER_90_PERCENT: return 90;
		case DITHER_100_PERCENT: return 100;
		
		default: return 0;
	}
}

//=========================================================================================================================
// DITHERED RECTS
//=========================================================================================================================

void draw_zero_percent(GContext *ctx, GRect bounds, GColor first){
	graphics_context_set_fill_color(ctx, first);
	graphics_fill_rect(ctx, bounds, 0, GCornerNone);
}

void draw_ten_percent(GContext *ctx, int x_start, int y_start, int width, int height, GColor first, GColor second){
	for(int x = x_start; x < x_start+width; x++){
		for(int y = y_start; y < y_start+height; y++){	
			if((x%8 == 0 && y%4 == 0) || ((x+4)%8 == 0 && (y+2)%4 == 0)) graphics_context_set_stroke_color(ctx, second);
			else graphics_context_set_stroke_color(ctx, first);
			graphics_draw_pixel(ctx, GPoint(x, y));
		}
	}
}

void draw_twenty_percent(GContext *ctx, int x_start, int y_start, int width, int height, GColor first, GColor second){
	for(int x = x_start; x < x_start+width; x++){
		for(int y = y_start; y < y_start+height; y++){
			if((x%4 + y%4 == 0) || ((x+2)%4 + (y+2)%4 == 0)) graphics_context_set_stroke_color(ctx, second);
			else graphics_context_set_stroke_color(ctx, first);
			graphics_draw_pixel(ctx, GPoint(x, y));
		}
	}
}

void draw_twenty_five_percent(GContext *ctx, int x_start, int y_start, int width, int height, GColor first, GColor second){
	for(int x = x_start; x < x_start+width; x++){
		for(int y = y_start; y < y_start+height; y++){
			if((x%4 == 0 && y%2 == 0) || ((x+2)%4 == 0 && (y+1)%2 == 0)) graphics_context_set_stroke_color(ctx, second);
			else graphics_context_set_stroke_color(ctx, first);
			graphics_draw_pixel(ctx, GPoint(x, y));			
		}
	}
}

void draw_thirty_percent(GContext *ctx, int x_start, int y_start, int width, int height, GColor first, GColor second){
	for(int x = x_start; x < x_start+width; x++){
		for(int y = y_start; y < y_start+height; y++){
			if( (x+y)%2 == 0 && ( (x+y)%4 != 0 || ( (x+y)%4 == 0 && x%2 != 0 && y%2 != 0) ) ) graphics_context_set_stroke_color(ctx, second);
			else graphics_context_set_stroke_color(ctx, first);
			graphics_draw_pixel(ctx, GPoint(x, y));					
		}
	}
}

void draw_forty_percent(GContext *ctx, int x_start, int y_start, int width, int height, GColor first, GColor second){
	for(int x = x_start; x < x_start+width; x++){
		for(int y = y_start; y < y_start+height; y++){
			if( (x+y)%2 == 0 && ( (x+y)%8 != 0 || ( (x+y)%8 == 0 && x%4 != 1 && y%4 != 3 ) ) ) graphics_context_set_stroke_color(ctx, second);
			else graphics_context_set_stroke_color(ctx, first);
			graphics_draw_pixel(ctx, GPoint(x, y));					
		}
	}
}

void draw_fifty_percent(GContext *ctx, int x_start, int y_start, int width, int height, GColor first, GColor second){
	for(int x = x_start; x < x_start+width; x++){
		for(int y = y_start; y < y_start+height; y++){
			if((x+y)%2 == 0) graphics_context_set_stroke_color(ctx, second);
			else graphics_context_set_stroke_color(ctx, first);
			graphics_draw_pixel(ctx, GPoint(x, y));					
		}
	}
}

void draw_dithered_rect(GContext *ctx, GRect bounds, GColor first_color, GColor second_color, DitherPercentage percentage){
	switch(percentage){
	
		case DITHER_0_PERCENT: draw_zero_percent(ctx, bounds, first_color); break;
		case DITHER_10_PERCENT: draw_ten_percent(ctx, bounds.origin.x, bounds.origin.y, bounds.size.w, bounds.size.h, first_color, second_color); break;
		case DITHER_20_PERCENT: draw_twenty_percent(ctx, bounds.origin.x, bounds.origin.y, bounds.size.w, bounds.size.h, first_color, second_color); break;
		case DITHER_25_PERCENT: draw_twenty_five_percent(ctx, bounds.origin.x, bounds.origin.y, bounds.size.w, bounds.size.h, first_color, second_color); break;
		case DITHER_30_PERCENT: draw_thirty_percent(ctx, bounds.origin.x, bounds.origin.y, bounds.size.w, bounds.size.h, first_color, second_color); break;
		case DITHER_40_PERCENT: draw_forty_percent(ctx, bounds.origin.x, bounds.origin.y, bounds.size.w, bounds.size.h, first_color, second_color); break;
		case DITHER_50_PERCENT: draw_fifty_percent(ctx, bounds.origin.x, bounds.origin.y, bounds.size.w, bounds.size.h, first_color, second_color); break;
		
		case DITHER_60_PERCENT: draw_dithered_rect(ctx, bounds, second_color, first_color, DITHER_40_PERCENT); break;
		case DITHER_70_PERCENT: draw_dithered_rect(ctx, bounds, second_color, first_color, DITHER_30_PERCENT); break;
		case DITHER_75_PERCENT: draw_dithered_rect(ctx, bounds, second_color, first_color, DITHER_25_PERCENT); break;
		case DITHER_80_PERCENT: draw_dithered_rect(ctx, bounds, second_color, first_color, DITHER_20_PERCENT); break;
		case DITHER_90_PERCENT: draw_dithered_rect(ctx, bounds, second_color, first_color, DITHER_10_PERCENT); break;
		case DITHER_100_PERCENT: draw_dithered_rect(ctx, bounds, second_color, first_color, DITHER_0_PERCENT); break;
		
		default: break;
	}
}

//=========================================================================================================================
// RANDOM DITHERED RECTS
//=========================================================================================================================

void init_rand(){
	srand(time(NULL));
}

void draw_random_dithered_rect(GContext *ctx, GRect bounds, GColor first_color, GColor second_color, DitherPercentage dither){
	int x_start = bounds.origin.x;
	int y_start = bounds.origin.y;
	int width = bounds.size.w;
	int height = bounds.size.h;
	
	int probability = getPercentageFromDither(dither);
	
	for(int x = x_start; x < x_start + width; x++){
		for(int y = y_start; y < y_start + height; y++){
			if(rand()%100 < probability) graphics_context_set_stroke_color(ctx, second_color);
			else graphics_context_set_stroke_color(ctx, first_color);
			graphics_draw_pixel(ctx, GPoint(x, y));
		}
	}
}
//draw_dithered_rect(ctx, GRect(x_start+(i*width/110)-1, y_start, 1+width/11, height), first, second, getDitherFromPercentage(i));
void draw_random_gradient_rect(GContext *ctx, GRect bounds, GColor first_color, GColor second_color, GradientDirection gradient){
	int x_start = bounds.origin.x;
	int y_start = bounds.origin.y;
	int width = bounds.size.w;
	int height = bounds.size.h;

	if(gradient == TOP_TO_BOTTOM){
		if(height >= 55){
			for(int i = 0; i < 11; i++){
				draw_random_dithered_rect(ctx, GRect(x_start, y_start+(i*height/11)-1, width, 1+height/11), first_color, second_color, getDitherFromPercentage(i*10));
			}
		}
		else{
			for(int i = 0; i < 5; i++){
				draw_random_dithered_rect(ctx, GRect(x_start, y_start+(i*height/5)-1, width, 1+height/5), first_color, second_color, getDitherFromPercentage(i*25));
			}
		}	
	}
	else if(gradient == LEFT_TO_RIGHT){
		if(width >= 55){
			for(int i = 0; i < 11; i++){
				draw_random_dithered_rect(ctx, GRect(x_start+(i*width/11)-1, y_start, 1+width/11, height), first_color, second_color, getDitherFromPercentage(i*10));
			}
		}
		else{
			for(int i = 0; i < 5; i++){
				draw_random_dithered_rect(ctx, GRect(x_start+(i*width/5)-1, y_start, 1+width/5, height), first_color, second_color, getDitherFromPercentage(i*25));
			}
		}
	}
	else if(gradient == BOTTOM_TO_TOP) draw_random_gradient_rect(ctx, bounds, second_color, first_color, TOP_TO_BOTTOM);
	else if(gradient == RIGHT_TO_LEFT) draw_random_gradient_rect(ctx, bounds, second_color, first_color, LEFT_TO_RIGHT);
}

//=========================================================================================================================
// DITHERED CIRCLES
//=========================================================================================================================

void draw_zero_percent_circle(GContext *ctx, int x_center, int y_center, int radius, GColor first){
	graphics_context_set_fill_color(ctx, first);
	graphics_fill_circle(ctx, GPoint(x_center, y_center), radius);
}

void draw_ten_percent_circle(GContext *ctx, int x_center, int y_center, int radius, GColor first, GColor second){
	for(int x = x_center-radius; x < x_center+radius; x++){
		for(int y = y_center-radius; y < y_center+radius; y++){
			if( (x%4 + y%4 == 0) || ((x+2)%4 + (y+2)%4 == 0) ) graphics_context_set_stroke_color(ctx, second);
			else graphics_context_set_stroke_color(ctx, first);
			
			if((x-x_center) * (x-x_center) + (y-y_center) * (y-y_center) < radius * radius) graphics_draw_pixel(ctx, GPoint(x,y));
		}
	}	
}

void draw_twenty_percent_circle(GContext *ctx, int x_center, int y_center, int radius, GColor first, GColor second){
	for(int x = x_center-radius; x < x_center+radius; x++){
		for(int y = y_center-radius; y < y_center+radius; y++){
			if((x+y)%2 == 0) graphics_context_set_stroke_color(ctx, second);
			else graphics_context_set_stroke_color(ctx, first);
			
			if((x-x_center) * (x-x_center) + (y-y_center) * (y-y_center) < radius * radius) graphics_draw_pixel(ctx, GPoint(x,y));
		}
	}	
}

void draw_twenty_five_percent_circle(GContext *ctx, int x_center, int y_center, int radius, GColor first, GColor second){
	for(int x = x_center-radius; x < x_center+radius; x++){
		for(int y = y_center-radius; y < y_center+radius; y++){
			if( (x%4 == 0 && y%2 == 0) || ((x+2)%4 == 0 && (y+1)%2 == 0) ) graphics_context_set_stroke_color(ctx, second);
			else graphics_context_set_stroke_color(ctx, first);
			
			if((x-x_center) * (x-x_center) + (y-y_center) * (y-y_center) < radius * radius) graphics_draw_pixel(ctx, GPoint(x,y));
		}
	}	
}

void draw_thirty_percent_circle(GContext *ctx, int x_center, int y_center, int radius, GColor first, GColor second){
	for(int x = x_center-radius; x < x_center+radius; x++){
		for(int y = y_center-radius; y < y_center+radius; y++){
			if( (x+y)%2 == 0 && ( (x+y)%4 != 0 || ( (x+y)%4 == 0 && x%2 != 0 && y%2 != 0) ) ) graphics_context_set_stroke_color(ctx, second);
			else graphics_context_set_stroke_color(ctx, first);
			
			if((x-x_center) * (x-x_center) + (y-y_center) * (y-y_center) < radius * radius) graphics_draw_pixel(ctx, GPoint(x,y));
		}
	}	
}

void draw_forty_percent_circle(GContext *ctx, int x_center, int y_center, int radius, GColor first, GColor second){
	for(int x = x_center-radius; x < x_center+radius; x++){
		for(int y = y_center-radius; y < y_center+radius; y++){
			if( (x+y)%2 == 0 && ( (x+y)%8 != 0 || ( (x+y)%8 == 0 && x%4 != 1 && y%4 != 3 ) ) ) graphics_context_set_stroke_color(ctx, second);
			else graphics_context_set_stroke_color(ctx, first);
			
			if((x-x_center) * (x-x_center) + (y-y_center) * (y-y_center) < radius * radius) graphics_draw_pixel(ctx, GPoint(x,y));
		}
	}	
}

void draw_fifty_percent_circle(GContext *ctx, int x_center, int y_center, int radius, GColor first, GColor second){
	for(int x = x_center-radius; x < x_center+radius; x++){
		for(int y = y_center-radius; y < y_center+radius; y++){
			if((x+y)%2 == 0) graphics_context_set_stroke_color(ctx, second);
			else graphics_context_set_stroke_color(ctx, first);
			
			if((x-x_center) * (x-x_center) + (y-y_center) * (y-y_center) < radius * radius) graphics_draw_pixel(ctx, GPoint(x,y));
		}
	}
}

void draw_dithered_circle(GContext *ctx, int x_center, int y_center, int radius, GColor first_color, GColor second_color, DitherPercentage percentage){
	switch(percentage){
	
		case DITHER_0_PERCENT: draw_zero_percent_circle(ctx, x_center, y_center, radius, first_color); break;
		case DITHER_10_PERCENT: draw_ten_percent_circle(ctx, x_center, y_center, radius, first_color, second_color); break;
		case DITHER_20_PERCENT: draw_twenty_percent_circle(ctx, x_center, y_center, radius, first_color, second_color); break;
		case DITHER_25_PERCENT: draw_twenty_five_percent_circle(ctx, x_center, y_center, radius, first_color, second_color); break;
		case DITHER_30_PERCENT: draw_thirty_percent_circle(ctx, x_center, y_center, radius, first_color, second_color); break;
		case DITHER_40_PERCENT: draw_forty_percent_circle(ctx, x_center, y_center, radius, first_color, second_color); break;
		case DITHER_50_PERCENT: draw_fifty_percent_circle(ctx, x_center, y_center, radius, first_color, second_color); break;
		
		case DITHER_60_PERCENT: draw_dithered_circle(ctx, x_center, y_center, radius, second_color, first_color, DITHER_40_PERCENT); break;
		case DITHER_70_PERCENT: draw_dithered_circle(ctx, x_center, y_center, radius, second_color, first_color, DITHER_30_PERCENT); break;
		case DITHER_75_PERCENT: draw_dithered_circle(ctx, x_center, y_center, radius, second_color, first_color, DITHER_25_PERCENT); break;
		case DITHER_80_PERCENT: draw_dithered_circle(ctx, x_center, y_center, radius, second_color, first_color, DITHER_20_PERCENT); break;
		case DITHER_90_PERCENT: draw_dithered_circle(ctx, x_center, y_center, radius, second_color, first_color, DITHER_10_PERCENT); break;
		case DITHER_100_PERCENT: draw_dithered_circle(ctx, x_center, y_center, radius, second_color, first_color, DITHER_0_PERCENT); break;
		
		default: break;
	}
}

//=========================================================================================================================
// TRANSITIONS
//=========================================================================================================================

AppTimer *transition_timer;

Layer *custom_layer;

bool increasing = true;
DitherPercentage current_dither = DITHER_0_PERCENT;
int transition_delay = 500;
int transition_loops = 0;
int loop_count = 0;

void tick(){
	if(transition_loops == 0 || loop_count < transition_loops) {
		if(increasing){
			switch(current_dither){
				case DITHER_0_PERCENT: current_dither = DITHER_10_PERCENT; break;
				case DITHER_10_PERCENT: current_dither = DITHER_20_PERCENT; break;
				case DITHER_20_PERCENT: current_dither = DITHER_30_PERCENT; break;
				case DITHER_30_PERCENT: current_dither = DITHER_40_PERCENT; break;
				case DITHER_40_PERCENT: current_dither = DITHER_50_PERCENT; break;
				case DITHER_50_PERCENT: current_dither = DITHER_60_PERCENT; break;
				case DITHER_60_PERCENT: current_dither = DITHER_70_PERCENT; break;
				case DITHER_70_PERCENT: current_dither = DITHER_80_PERCENT; break;
				case DITHER_80_PERCENT: current_dither = DITHER_90_PERCENT; break;
				case DITHER_90_PERCENT: 
					current_dither = DITHER_100_PERCENT;
					loop_count++;
					break;
				case DITHER_100_PERCENT: increasing = false; current_dither = DITHER_90_PERCENT; break;
				default: break;
			}	
		}
		else{
			switch(current_dither){
				case DITHER_0_PERCENT: increasing = true; current_dither = DITHER_10_PERCENT; break;
				case DITHER_10_PERCENT: 
					current_dither = DITHER_0_PERCENT; 
					loop_count++;
					break;
				case DITHER_20_PERCENT: current_dither = DITHER_10_PERCENT; break;
				case DITHER_30_PERCENT: current_dither = DITHER_20_PERCENT; break;
				case DITHER_40_PERCENT: current_dither = DITHER_30_PERCENT; break;
				case DITHER_50_PERCENT: current_dither = DITHER_40_PERCENT; break;
				case DITHER_60_PERCENT: current_dither = DITHER_50_PERCENT; break;
				case DITHER_70_PERCENT: current_dither = DITHER_60_PERCENT; break;
				case DITHER_80_PERCENT: current_dither = DITHER_70_PERCENT; break;
				case DITHER_90_PERCENT: current_dither = DITHER_80_PERCENT; break;
				case DITHER_100_PERCENT: current_dither = DITHER_90_PERCENT; break;
				default: break;
			}			
		}
		layer_mark_dirty(custom_layer);
	
		transition_timer = app_timer_register(transition_delay, tick, NULL);
	} else {
		app_timer_cancel(transition_timer);
	}
}

void draw_transitioning_rect(GContext *ctx, GRect bounds, GColor first_color, GColor second_color){
	draw_dithered_rect(ctx, bounds, first_color, second_color, current_dither);
}

void start_transitioning_rect(Layer *layer, int delay, int loops){
	custom_layer = layer;
	
	transition_delay = delay;
	transition_loops = loops;
	transition_timer = app_timer_register(transition_delay, tick, NULL);
}

void stop_transitioning_rect(){
	app_timer_cancel(transition_timer);
}

//=========================================================================================================================
// GRADIENTS
//=========================================================================================================================

void draw_top_to_bottom(GContext *ctx, int x_start, int y_start, int width, int height, GColor first, GColor second){
	if(height >= 55){
		for(int i = 0; i < 110; i += 10){
			draw_dithered_rect(ctx, GRect(x_start, y_start+(i*height/110)-1, width, 1+height/11), first, second, getDitherFromPercentage(i));
		}
	}
	else{
		for(int i = 0; i < 125; i += 25){ 
			draw_dithered_rect(ctx, GRect(x_start, y_start+(i*height/125)-1, width, 1+height/5), first, second, getDitherFromPercentage(i));
		}
	}
}

void draw_left_to_right(GContext *ctx, int x_start, int y_start, int width, int height, GColor first, GColor second){
	if(width >= 55){
		for(int i = 0; i < 110; i += 10){
			draw_dithered_rect(ctx, GRect(x_start+(i*width/110)-1, y_start, 1+width/11, height), first, second, getDitherFromPercentage(i));
		}
	}
	else{
		for(int i = 0; i < 125; i += 25){
			draw_dithered_rect(ctx, GRect(x_start+(i*width/125)-1, y_start, 1+width/5, height), first, second, getDitherFromPercentage(i));
		}
	}
}

void draw_gradient_rect(GContext *ctx, GRect bounds, GColor first_color, GColor second_color, GradientDirection direction){
	switch(direction){
		
		case TOP_TO_BOTTOM: draw_top_to_bottom(ctx, bounds.origin.x, bounds.origin.y, bounds.size.w, bounds.size.h, first_color, second_color); break;
		case BOTTOM_TO_TOP: draw_gradient_rect(ctx, bounds, second_color, first_color, TOP_TO_BOTTOM); break;
		
		case LEFT_TO_RIGHT: draw_left_to_right(ctx, bounds.origin.x, bounds.origin.y, bounds.size.w, bounds.size.h, first_color, second_color); break;
		case RIGHT_TO_LEFT: draw_gradient_rect(ctx, bounds, second_color, first_color, LEFT_TO_RIGHT); break;
		
		//case TOP_LEFT_TO_BOTTOM_RIGHT: break;
		//case BOTTOM_RIGHT_TO_TOP_LEFT: draw_gradient_rect(ctx, bounds, second_color, first_color, TOP_LEFT_TO_BOTTOM_RIGHT); break;
		
		//case TOP_RIGHT_TO_BOTTOM_LEFT: break;
		//case BOTTOM_LEFT_TO_TOP_RIGHT: draw_gradient_rect(ctx, bounds, second_color, first_color, TOP_RIGHT_TO_BOTTOM_LEFT); break;
		
		default: break;
	}
}
