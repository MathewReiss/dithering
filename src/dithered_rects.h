//From https://github.com/MathewReiss/dithering

#include <pebble.h>

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
// CONVERSION (Mathew Reiss)
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
// DITHERED RECTS (Mathew Reiss)
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
// RANDOM DITHERED RECTS (Mathew Reiss)
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
// DITHERED CIRCLES (Mathew Reiss)
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
// TRANSITIONS (Mathew Reiss, Thomas Hunsaker)
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
// RAW GRADIENTS (Mathew Reiss)
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

//=========================================================================================================================
// COLOR ARRAY FROM SINGLE RGB OR HEX VALUE (Mathew Reiss)
//=========================================================================================================================

#ifdef PBL_COLOR
int getNearestRGBInt(int c){
	if(c <= (85/2)) return 0;
	else if(c <= (85+85/2)) return 85;
	else if(c <= (170+85/2)) return 170;
	else return 255;
}	

int getUpperRGBInt(int c){
	if(c == 0) return 0;
	if(c <= 85) return 85;
	else if(c <= 170) return 170;
	else if(c <= 255) return 255;

	else return 255;
}

int getLowerRGBInt(int c){
	if(c == 255) return 255;
	if(c >= 170) return 170;
	else if(c >= 85) return 85;
	else if(c >= 0) return 0;
	
	else return 0;
}

int getUpperOrNearestRGBInt(int c){
	if(c >= 128) return getUpperRGBInt(c);
	else return getNearestRGBInt(c);
}

int getLowerOrNearestRGBInt(int c){
	if(c < 128) return getLowerRGBInt(c);
	return getNearestRGBInt(c);
}
	
GColor getFirstGColorFromRGB(int r, int g, int b){
	return GColorFromRGB(getUpperRGBInt(r), getUpperRGBInt(g), getUpperRGBInt(b));
}

GColor getSecondGColorFromRGB(int r, int g, int b){
	return GColorFromRGB(getLowerRGBInt(r), getLowerRGBInt(g), getLowerRGBInt(b));
}

DitherPercentage getRecommendedDitherPercentage(int r_0, int g_0, int b_0, GColor first, GColor second){
	int r_1 = 85*first.r;
	int g_1 = 85*first.g;
	int b_1 = 85*first.b;
	
	int r_2 = 85*second.r;
	int g_2 = 85*second.g;
	int b_2 = 85*second.b;
	
	int product_0 = r_0*r_0 + g_0*g_0 + b_0*b_0;
	int product_1 = r_1*r_1 + g_1*g_1 + b_1*b_1;
	int product_2 = r_2*r_2 + g_2*g_2 + b_2*b_2;
	
	int range = product_1 - product_2;
	int rel_val = product_0 - product_2;
	int tar_percent = abs( 10 * ( ( 10 * rel_val ) / range ) );
	
	return getDitherFromPercentage(tar_percent);
}

void draw_dithered_rect_from_RGB(GContext *ctx, GRect bounds, int r, int g, int b){
	GColor first = getFirstGColorFromRGB(r, g, b);
	GColor second = getSecondGColorFromRGB(r, g, b);
	DitherPercentage recommended = getRecommendedDitherPercentage(r, g, b, first, second);
	
	draw_dithered_rect(ctx, bounds, first, second, recommended);
}

void draw_dithered_rect_from_HEX(GContext *ctx, GRect bounds, int hex){
	int r_from_hex = ( ( hex >> 16 ) & 0xFF ) / 255;
	int g_from_hex = ( ( hex >> 8 ) & 0xFF ) / 255;
	int b_from_hex = ( ( hex ) & 0xFF ) / 255;
	
	draw_dithered_rect_from_RGB(ctx, bounds, r_from_hex, g_from_hex, b_from_hex);
}

//=========================================================================================================================
// DRAW MASKED DITHERED COLORS - INCLUDING TEXT (Yuriy Galanter)
//=========================================================================================================================

/*********************** UTILITY FUNCTIONS *********************/  

//Helper function that finds inverted color;  
GColor color_inverted(GColor source) {
  GColor inverted = source;
  if(gcolor_equal(source, GColorBlack)) 
    inverted= GColorWhite;
  if(gcolor_equal(source, GColorWhite))
    inverted= GColorBlack;
  if(!gcolor_equal(source, GColorClear)) //GColorClear should not change
      inverted.argb= source.argb ^ 0b00111111;
  return inverted;
}     
  
//Set pixel color at given coordinates 
void set_pixel(uint8_t *bitmap_data, int bytes_per_row, int y, int x, uint8_t color) {
   bitmap_data[y*bytes_per_row + x] = color; // in Basalt - simple set entire byte
}

//Get pixel color at given coordinates 
uint8_t get_pixel(uint8_t *bitmap_data, int bytes_per_row, int y, int x) {
   return bitmap_data[y*bytes_per_row + x]; // in Basalt - simple get entire byte
}


/*********************** Dithering Functions based on dithered_rects.h *********************/  

void draw_zero_percent_mask(uint8_t *bitmap_data, int bytes_per_row, int x_start, int y_start, int width, int height, GColor first, GColor mask){
  GColor temp_pixel;
  
	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
      
      temp_pixel = (GColor)get_pixel(bitmap_data, bytes_per_row, y + y_start, x + x_start);
      
      if (gcolor_equal(temp_pixel, mask)) {
        set_pixel(bitmap_data, bytes_per_row, y + y_start, x + x_start, first.argb);
      }
      
		}
	}  
}

void draw_ten_percent_mask(uint8_t *bitmap_data, int bytes_per_row, int x_start, int y_start, int width, int height, GColor first, GColor second, GColor mask){
  GColor temp_pixel;
  
	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
      
      temp_pixel = (GColor)get_pixel(bitmap_data, bytes_per_row, y + y_start, x + x_start);
      
      if (gcolor_equal(temp_pixel, mask)) {
  			if((x%8 == 0 && y%4 == 0) || ((x+4)%8 == 0 && (y+2)%4 == 0)) temp_pixel = second;
  			else temp_pixel = first;
  			
        set_pixel(bitmap_data, bytes_per_row, y + y_start, x + x_start, temp_pixel.argb);
      }
      
		}
	}  
}

void draw_twenty_percent_mask(uint8_t *bitmap_data, int bytes_per_row, int x_start, int y_start, int width, int height, GColor first, GColor second, GColor mask){
  GColor temp_pixel;
  
	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
      
      temp_pixel = (GColor)get_pixel(bitmap_data, bytes_per_row, y + y_start, x + x_start);
      
      if (gcolor_equal(temp_pixel, mask)) {
  			if((x%4 + y%4 == 0) || ((x+2)%4 + (y+2)%4 == 0)) temp_pixel = second;
  			else temp_pixel = first;
  			
        set_pixel(bitmap_data, bytes_per_row, y + y_start, x + x_start, temp_pixel.argb);
      }
      
		}
	}    
}

void draw_twenty_five_percent_mask(uint8_t *bitmap_data, int bytes_per_row, int x_start, int y_start, int width, int height, GColor first, GColor second, GColor mask){
  GColor temp_pixel;
  
	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
      
      temp_pixel = (GColor)get_pixel(bitmap_data, bytes_per_row, y + y_start, x + x_start);
      
      if (gcolor_equal(temp_pixel, mask)) {
  			if((x%4 == 0 && y%2 == 0) || ((x+2)%4 == 0 && (y+1)%2 == 0)) temp_pixel = second;
  			else temp_pixel = first;
  			
        set_pixel(bitmap_data, bytes_per_row, y + y_start, x + x_start, temp_pixel.argb);
      }
      
		}
	}      
}

void draw_thirty_percent_mask(uint8_t *bitmap_data, int bytes_per_row, int x_start, int y_start, int width, int height, GColor first, GColor second, GColor mask){

GColor temp_pixel;
  
	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
      
      temp_pixel = (GColor)get_pixel(bitmap_data, bytes_per_row, y + y_start, x + x_start);
      
      if (gcolor_equal(temp_pixel, mask)) {
  			if( (x+y)%2 == 0 && ( (x+y)%4 != 0 || ( (x+y)%4 == 0 && x%2 != 0 && y%2 != 0) ) ) temp_pixel = second;
  			else temp_pixel = first;
  			
        set_pixel(bitmap_data, bytes_per_row, y + y_start, x + x_start, temp_pixel.argb);
      }
      
		}
	}    
}

void draw_forty_percent_mask(uint8_t *bitmap_data, int bytes_per_row, int x_start, int y_start, int width, int height, GColor first, GColor second, GColor mask){
  GColor temp_pixel;
  
	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
      
      temp_pixel = (GColor)get_pixel(bitmap_data, bytes_per_row, y + y_start, x + x_start);
      
      if (gcolor_equal(temp_pixel, mask)) {
  			if( (x+y)%2 == 0 && ( (x+y)%8 != 0 || ( (x+y)%8 == 0 && x%4 != 1 && y%4 != 3 ) ) ) temp_pixel = second;
  			else temp_pixel = first;
  			
        set_pixel(bitmap_data, bytes_per_row, y + y_start, x + x_start, temp_pixel.argb);
      }
      
		}
	}
}

void draw_fifty_percent_mask(uint8_t *bitmap_data, int bytes_per_row, int x_start, int y_start, int width, int height, GColor first, GColor second, GColor mask){
  GColor temp_pixel;
  
	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
      
      temp_pixel = (GColor)get_pixel(bitmap_data, bytes_per_row, y + y_start, x + x_start);
      
      if (gcolor_equal(temp_pixel, mask)) {
  			if((x+y)%2 == 0) temp_pixel = second;
  			else temp_pixel = first;
  			
        set_pixel(bitmap_data, bytes_per_row, y + y_start, x + x_start, temp_pixel.argb);
      }
      
		}
	}
}

void draw_dithered_mask(uint8_t *bitmap_data, int bytes_per_row, GRect bounds, GColor first_color, GColor second_color, GColor mask_color, DitherPercentage percentage){
	switch(percentage){
	
		case DITHER_0_PERCENT: draw_zero_percent_mask(bitmap_data, bytes_per_row, bounds.origin.x, bounds.origin.y, bounds.size.w, bounds.size.h, first_color, mask_color); break;
		case DITHER_10_PERCENT: draw_ten_percent_mask(bitmap_data, bytes_per_row, bounds.origin.x, bounds.origin.y, bounds.size.w, bounds.size.h, first_color, second_color, mask_color); break;
		case DITHER_20_PERCENT: draw_twenty_percent_mask(bitmap_data, bytes_per_row, bounds.origin.x, bounds.origin.y, bounds.size.w, bounds.size.h, first_color, second_color, mask_color); break;
		case DITHER_25_PERCENT: draw_twenty_five_percent_mask(bitmap_data, bytes_per_row, bounds.origin.x, bounds.origin.y, bounds.size.w, bounds.size.h, first_color, second_color, mask_color); break;
		case DITHER_30_PERCENT: draw_thirty_percent_mask(bitmap_data, bytes_per_row, bounds.origin.x, bounds.origin.y, bounds.size.w, bounds.size.h, first_color, second_color, mask_color); break;
		case DITHER_40_PERCENT: draw_forty_percent_mask(bitmap_data, bytes_per_row, bounds.origin.x, bounds.origin.y, bounds.size.w, bounds.size.h, first_color, second_color, mask_color); break;
		case DITHER_50_PERCENT: draw_fifty_percent_mask(bitmap_data, bytes_per_row, bounds.origin.x, bounds.origin.y, bounds.size.w, bounds.size.h, first_color, second_color, mask_color); break;
		
		case DITHER_60_PERCENT: draw_dithered_mask(bitmap_data, bytes_per_row, bounds, second_color, first_color, mask_color, DITHER_40_PERCENT); break;
		case DITHER_70_PERCENT: draw_dithered_mask(bitmap_data, bytes_per_row, bounds, second_color, first_color, mask_color, DITHER_30_PERCENT); break;
		case DITHER_75_PERCENT: draw_dithered_mask(bitmap_data, bytes_per_row, bounds, second_color, first_color, mask_color, DITHER_25_PERCENT); break;
		case DITHER_80_PERCENT: draw_dithered_mask(bitmap_data, bytes_per_row, bounds, second_color, first_color, mask_color, DITHER_20_PERCENT); break;
		case DITHER_90_PERCENT: draw_dithered_mask(bitmap_data, bytes_per_row, bounds, second_color, first_color, mask_color, DITHER_10_PERCENT); break;
		case DITHER_100_PERCENT: draw_dithered_mask(bitmap_data, bytes_per_row, bounds, second_color, first_color, mask_color, DITHER_0_PERCENT); break;
		
		default: break;
	}
}

/*********************** Drawing dithered text *********************/ 

// draws dithered text  
// First 6 params same as for "graphics_draw_text"
// background color: pass color of the background
// first_color, second_color, percentage, same as for draw_dithered_rect
void draw_dithered_text(GContext *ctx, const char * text, GFont font, GRect bounds, GTextOverflowMode overflow_mode, GTextAlignment alignment, GTextLayoutCacheRef layout, 
                        GColor background_color, 
                        GColor first_color, GColor second_color, DitherPercentage percentage){
  
  // initially drawing text in inverted color
  GColor mask_color = color_inverted(background_color);
  graphics_context_set_text_color(ctx, mask_color);
  graphics_draw_text(ctx, text, font, bounds, overflow_mode, alignment, layout);
  
  //capturing framebuffer bitmap
  GBitmap *fb = graphics_capture_frame_buffer(ctx);
  uint8_t *bitmap_data =  gbitmap_get_data(fb);
  int bytes_per_row = gbitmap_get_bytes_per_row(fb);

  //drawing dithered mask over text 
  draw_dithered_mask(bitmap_data, bytes_per_row, bounds, first_color, second_color, mask_color, percentage);
  
  //releasing framebuffer
  graphics_release_frame_buffer(ctx, fb);
  
}  

// draws dithered text from RGB colors
// First 6 params same as for "graphics_draw_text"
// background color: pass color of the background
// r, g, b - colors to mix
void draw_dithered_text_from_RGB(GContext *ctx, const char * text, GFont font, GRect bounds, GTextOverflowMode overflow_mode, GTextAlignment alignment, GTextLayoutCacheRef layout, 
                                 GColor background_color, 
                                 int r, int g, int b){
	
  GColor first = getFirstGColorFromRGB(r, g, b);
	GColor second = getSecondGColorFromRGB(r, g, b);
	DitherPercentage recommended = getRecommendedDitherPercentage(r, g, b, first, second);
	
	draw_dithered_text(ctx, text, font, bounds, overflow_mode, alignment, layout, background_color, first, second, recommended);
}

#endif
	
//=========================================================================================================================
// SMOOTH GRADIENTS (Morris Timm)
//=========================================================================================================================
	
#ifdef PBL_PLATFORM_BASALT

#define CHANNEL_DISTANCE(X, Y) ((X)>(Y)?(X)-(Y):(Y)-(X))

// find the distance between the two colors by determining the distance for each channel separately and use the greatest
uint8_t get_color_distance(GColor first_color, GColor second_color) {
  uint8_t distance = 0;
  uint8_t dr = CHANNEL_DISTANCE(first_color.r, second_color.r);
  uint8_t dg = CHANNEL_DISTANCE(first_color.g, second_color.g);
  uint8_t db = CHANNEL_DISTANCE(first_color.b, second_color.b);
  if(dr > distance) distance = dr;
  if(dg > distance) distance = dg;
  if(db > distance) distance = db;
  
  // if the greatest distance is 2 and there is at least one distance 1, distance 3 looks better
  if(2 == distance) {
    if(1 == dr || 1 == dg || 1 == db) {
      distance = 3;
    }
  }
  return distance;
}

// get the value of a channel based for the current step
uint8_t get_channel_for_step(uint8_t first, uint8_t second, uint8_t step) {
  uint8_t channel = first;
  if(first > second) {
    switch(first-second) {
      case 1: channel = (1 == step ? first : second); break;
      case 2: channel = first - 1; break;
      case 3: channel = first - step; break;
    }
  } else
  if(first < second) {
    switch(second-first) {
      case 1: channel = (1 == step ? first : second); break;
      case 2: channel = first + 1; break;
      case 3: channel = first + step; break;
    }
  }
  return channel;
}

// draw one smooth gradient rect consisting of up to 3 gradient rects
// the gradient looks smoother (most of the time) by calculating up to two colors in between the two specified colors
// if the color distance is 1, the result ist the same as a normal gradient rect
void draw_smooth_gradient_rect(GContext *ctx, GRect bounds, GColor first_color, GColor second_color, GradientDirection direction) {
  uint8_t steps = get_color_distance(first_color, second_color);
  GColor gradient_colors[4] = {first_color, second_color, second_color, second_color};
  for(uint8_t i = 1; i < steps; ++i) {
    gradient_colors[i].r = get_channel_for_step(first_color.r, second_color.r, i);
    gradient_colors[i].g = get_channel_for_step(first_color.g, second_color.g, i);
    gradient_colors[i].b = get_channel_for_step(first_color.b, second_color.b, i);
  }
  
  switch(direction) {
    case TOP_TO_BOTTOM:
      for(uint8_t i = 0; i < steps; ++i) {
        draw_gradient_rect(ctx, GRect(bounds.origin.x, bounds.origin.y+((bounds.size.h/steps)*i), bounds.size.w, bounds.size.h/steps), gradient_colors[i], gradient_colors[i+1], TOP_TO_BOTTOM);
      }
      break;
    case BOTTOM_TO_TOP: draw_smooth_gradient_rect(ctx, bounds, second_color, first_color, TOP_TO_BOTTOM); break;
    
    case LEFT_TO_RIGHT:
      for(uint8_t i = 0; i < steps; ++i) {
        draw_gradient_rect(ctx, GRect(bounds.origin.x+((bounds.size.w/steps)*i), bounds.origin.y, bounds.size.w/steps, bounds.size.h), gradient_colors[i], gradient_colors[i+1], LEFT_TO_RIGHT);
      }
      break;
    case RIGHT_TO_LEFT: draw_smooth_gradient_rect(ctx, bounds, second_color, first_color, LEFT_TO_RIGHT); break;
    
    default: break;
  }
}

//=========================================================================================================================
// SMOOTH + RANDOM GRADIENTS (Mathew Reiss)
//=========================================================================================================================	
	
void draw_smooth_random_gradient_rect(GContext *ctx, GRect bounds, GColor first_color, GColor second_color, GradientDirection direction) {
  uint8_t steps = get_color_distance(first_color, second_color);
  GColor gradient_colors[4] = {first_color, second_color, second_color, second_color};
  for(uint8_t i = 1; i < steps; ++i) {
    gradient_colors[i].r = get_channel_for_step(first_color.r, second_color.r, i);
    gradient_colors[i].g = get_channel_for_step(first_color.g, second_color.g, i);
    gradient_colors[i].b = get_channel_for_step(first_color.b, second_color.b, i);
  }
  
  switch(direction) {
    case TOP_TO_BOTTOM:
      for(uint8_t i = 0; i < steps; ++i) {
        draw_random_gradient_rect(ctx, GRect(bounds.origin.x, bounds.origin.y+((bounds.size.h/steps)*i), bounds.size.w, bounds.size.h/steps), gradient_colors[i], gradient_colors[i+1], TOP_TO_BOTTOM);
      }
      break;
    case BOTTOM_TO_TOP: draw_smooth_gradient_rect(ctx, bounds, second_color, first_color, TOP_TO_BOTTOM); break;
    
    case LEFT_TO_RIGHT:
      for(uint8_t i = 0; i < steps; ++i) {
        draw_random_gradient_rect(ctx, GRect(bounds.origin.x+((bounds.size.w/steps)*i), bounds.origin.y, bounds.size.w/steps, bounds.size.h), gradient_colors[i], gradient_colors[i+1], LEFT_TO_RIGHT);
      }
      break;
    case RIGHT_TO_LEFT: draw_smooth_gradient_rect(ctx, bounds, second_color, first_color, LEFT_TO_RIGHT); break;
    
    default: break;
  }
}

#endif // PBL_PLATFORM_BASALT 
