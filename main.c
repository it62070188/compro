#include <SDL.h> //
#include <SDL_image.h> //
#include <SDL_ttf.h>
#include <stdio.h>  //
#include <string.h>  //
#include <stdlib.h>  //
#include <ctype.h>  //
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <math.h>

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;

SDL_Surface* bg1_surface = NULL;
SDL_Texture* bg1_texture = NULL;

SDL_Surface* bg2_surface = NULL;
SDL_Texture* bg2_texture = NULL;

SDL_Surface* bg3_surface = NULL;
SDL_Texture* bg3_texture = NULL;

SDL_Surface* menu_bg_surface = NULL;
SDL_Texture* menu_bg_texture = NULL;

SDL_Surface* food1_surface = NULL;
SDL_Texture* food1_texture = NULL;

SDL_Surface* food2_surface = NULL;
SDL_Texture* food2_texture = NULL;

SDL_Surface* food3_surface = NULL;
SDL_Texture* food3_texture = NULL;

SDL_Surface* food4_surface = NULL;
SDL_Texture* food4_texture = NULL;

SDL_Surface* fail_surface = NULL;
SDL_Texture* fail_texture = NULL;

SDL_Surface* snake1_surface = NULL;
SDL_Texture* snake1_texture = NULL;

SDL_Surface* snake2_surface = NULL;
SDL_Texture* snake2_texture = NULL;

SDL_Surface* snake3_surface = NULL;
SDL_Texture* snake3_texture = NULL;

SDL_Surface* snake4_surface = NULL;
SDL_Texture* snake4_texture = NULL;

//Call Variable
int running;
int width = 1200, height = 700;    //Create width and height of program
long long frameTime = 0;    //Create frametime
int direction = 2;  //1 = ขึ้นบน 2 = ลงล่าง 3 = ซ้าย 4 = ขวา
int x[1000], y[1000];
int rest_x[1000], rest_y[1000];
int size = 3;
int keyboard_on = 0;
int speed = 250000;
int position_food_x , position_food_y;
int food_appear = 0;
int game_on = 1;
int bg_count = 0, bg_count2 = 0;
int point = 0;
int delay_time = 20000;
int game_start = 0;
int bg_delay = 0;
char score_text[20];

int main(int argc, char* args[]) {
	TTF_Init();                              //SDL_ttf init
	SDL_Init(SDL_INIT_EVERYTHING);           //SDL init
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow("Audition Quest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	running = 1;   //set running to true

	srand(time(NULL));

	TTF_Font* sans = TTF_OpenFont("font/HACKED.ttf", 100);   //Load font Hacked
	SDL_Color black = { 0, 0, 0 };   //Set black color
	SDL_Color white = { 255, 255, 255 };

	SDL_Surface* message_surface_start = TTF_RenderText_Solid(sans, "Press Enter To Start", black);   //Create Variable for turn text
	SDL_Texture* message_texture_start = SDL_CreateTextureFromSurface(renderer, message_surface_start);

	sprintf(score_text, "Score: %d", point);
	SDL_Surface* message_surface_score = TTF_RenderText_Solid(sans, score_text, white);   //Create Variable for turn text
	SDL_Texture* message_texture_score = SDL_CreateTextureFromSurface(renderer, message_surface_score);

	x[0] = 400, rest_x[0] = 400; //------------------------------------------------//
	y[0] = 400, rest_y[0] = 400; //------------------------------------------------//
	x[1] = 400, rest_x[1] = 400; //------------เปลี่ยนตามขนาดของแต่ละจุด -------------//
	y[1] = 350, rest_y[1] = 350; //------------If chang size 50 to 20 =========>>>>>
	x[2] = 400, rest_x[2] = 400; //==>>Point chang from 300,350,400 to 300,320,360 //
	y[2] = 300, rest_y[2] = 300; //------------------------------------------------//

	menu_bg_surface = IMG_Load("image/body.png");
	menu_bg_texture = SDL_CreateTextureFromSurface(renderer, menu_bg_surface);

	bg1_surface = IMG_Load("image/background/bg3.png");
	bg1_texture = SDL_CreateTextureFromSurface(renderer, bg1_surface);

	bg2_surface = IMG_Load("image/background/bg4.png");
	bg2_texture = SDL_CreateTextureFromSurface(renderer, bg2_surface);

	bg3_surface = IMG_Load("image/background/bg_sprite.png");
	bg3_texture = SDL_CreateTextureFromSurface(renderer, bg3_surface);

	food1_surface = IMG_Load("image/Food2.png");
	food1_texture = SDL_CreateTextureFromSurface(renderer, food1_surface);

	food2_surface = IMG_Load("image/Food3.png");
	food2_texture = SDL_CreateTextureFromSurface(renderer, food2_surface);

	food3_surface = IMG_Load("image/Food4.png");
	food3_texture = SDL_CreateTextureFromSurface(renderer, food3_surface);

	food4_surface = IMG_Load("image/Food5.png");
	food4_texture = SDL_CreateTextureFromSurface(renderer, food4_surface);

	fail_surface = IMG_Load("image/fail.png");
	fail_texture = SDL_CreateTextureFromSurface(renderer, fail_surface);

	snake1_surface = IMG_Load("image/Snake5.png");
	snake1_texture = SDL_CreateTextureFromSurface(renderer, snake1_surface);

	snake2_surface = IMG_Load("image/Snake2.png");
	snake2_texture = SDL_CreateTextureFromSurface(renderer, snake2_surface);

	snake3_surface = IMG_Load("image/Snake3.png");
	snake3_texture = SDL_CreateTextureFromSurface(renderer, snake3_surface);

	snake4_surface = IMG_Load("image/Snake4.png");
	snake4_texture = SDL_CreateTextureFromSurface(renderer, snake4_surface);

	while (running) {

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {   //If click close window turn off program
				running = 0;
			}
			else if (event.type == SDL_KEYDOWN) {    //Check Keyboard Event
				switch (event.key.keysym.sym){
				case SDLK_UP:    //Check button arrow up
					if (direction != 2 && keyboard_on == 0 && game_start){
						direction = 1;
						keyboard_on = 1;
					}
					break;
				case SDLK_DOWN:  //Check button arrow down
					if (direction != 1 && keyboard_on == 0 && game_start){
						direction = 2;
						keyboard_on = 1;
					}
					break;
				case SDLK_LEFT:  //Check button arrow left
					if (direction != 4 && keyboard_on == 0 && game_start){
						direction = 3;
						keyboard_on = 1;
					}
					break;
				case SDLK_RIGHT:  //Check button arrow right
					if (direction != 3 && keyboard_on == 0 && game_start){
						direction = 4;
						keyboard_on = 1;
					}
					break;
				case SDLK_RETURN:   //Check button ENTER and Restart at beginning point
					if (game_on == 0){
						game_on = 1;
						x[0] = 400, rest_x[0] = 400; //--
						y[0] = 400, rest_y[0] = 400; //--
						x[1] = 400, rest_x[1] = 400; //--
						y[1] = 350, rest_y[1] = 350; //--
						x[2] = 400, rest_x[2] = 400; //--
						y[2] = 300, rest_y[2] = 300; //--
						size = 3; //ขนาดเดิม
						direction = 2; //ทิศทางเดิม
						speed = 250000; //ความเร็วเดิม
						delay_time = 20000;
						game_start = 0;
					}
					else if (game_start == 0){
						game_start = 1;
						sprintf(score_text, "Score: %0d", point);
						message_surface_score = TTF_RenderText_Solid(sans, score_text, white);   //Create Variable for turn text
						message_texture_score = SDL_CreateTextureFromSurface(renderer, message_surface_score);
					}
					break;
				default:
					break;
				}
			}
		}

		frameTime++;

		if (game_on == 0){
			SDL_RenderClear(renderer);
			render_something(fail_texture, 0, 0, 1200, 700);
			SDL_RenderPresent(renderer);
			point = 0; // คะแนน
		}

		if(bg_count == 3){
			bg_count = 0;
		}
		if(bg_count2 >= bg_delay/2){
			bg_count++;
			bg_count2 = 0;
		}
		bg_count2++;

		if (game_on == 1){
			SDL_RenderClear(renderer);  //เคลียตัว renderer

			if (point >= 20){
				render_animation(bg3_texture, bg_count, 500, 263, 0, 0, 1200, 700); //ถ้าเป็น GIF ต้องใช้ rander_animation(bg_texture, bg_count, width, height, 0, 0, 1200ขนาดจอwidth, 700ขนาดจอheight);
			}
			else if (point >= 13){
				render_animation(bg2_texture, bg_count, 1200, 480, 0, 0, 1200, 700);
			}
			else if (point >= 5){
				render_animation(bg1_texture, bg_count, 1200, 480, 0, 0, 1200, 700);
			}
			else{
				render_animation(bg1_texture, bg_count, 1200, 480, 0, 0, 1200, 700);
			}

			while (food_appear == 0){ // เช็คว่างูกินอาหารหรือยัง
				food1_texture = SDL_CreateTextureFromSurface(renderer, food1_surface);
				position_food_x = 50 * (rand() % 24); // random แกน x ของอาหาร and size object * number point = size program
				position_food_y = 50 * (rand() % 14); // random แกน y ของอาหาร (translat line up) และขนาดของวัตถุ * จำนวนพิกัดทั้งหทด = ขนาดของจอโปรแกรม
				//----50 * 24 = 1200
				//----50 * 14 = 700
				food_appear = 1;

				/* เช็คว่าพิกัดของอาหารซํ้ากับตัวงูหรือไม่ */
				for (int i = 0; i < size; i++){
					if (position_food_x == x[i] && position_food_y == y[i]){
						food_appear = 0;
						break;
					}
				}
			}

			if(point >= 20){
				render_something(food4_texture, position_food_x, position_food_y, 50, 50);
			}
			else if (point >= 13){
				render_something(food3_texture, position_food_x, position_food_y, 50, 50);
			}
			else if (point >= 5){
				render_something(food2_texture, position_food_x, position_food_y, 50, 50);
			}
			else{
				render_something(food1_texture, position_food_x, position_food_y, 50, 50);
			}

			if(x[0] >= 1200 || x[0] < 0 || y[0] >= 700 || y[0] < 0){
				game_on = 0;
				continue;
			}

			for (int i = 0; i < size; i++){
				if(point >= 20){
					render_something(snake4_texture, x[i], y[i], 50, 50);
				}
				else if (point >= 13){
					render_something(snake3_texture, x[i], y[i], 50, 50);
				}
				else if (point >= 5){
					render_something(snake2_texture, x[i], y[i], 50, 50);
				}
				else{
					render_something(snake1_texture, x[i], y[i], 50, 50);
				}
			}

			if(game_start == 0){
				render_something(message_texture_start, 300, 300 , 600 ,80);
			}

			if (game_start == 1){
				switch(direction){
					case 1:
						y[0] -= 50; //Size of point
						break;
					case 2:
						y[0] += 50; //--
						break;
					case 3:
						x[0] -= 50; //--
						break;
					case 4:
						x[0] += 50; //--
						break;
					default:
						break;
				}

				if (x[0] == position_food_x && y[0] == position_food_y){ // ถ้าเก็บอาหารได้
					switch(direction){
						case 1:
							x[size] = x[size - 1];
							y[size] = y[size - 1] - 50;
							break;
						case 2:
							x[size] = x[size - 1];
							y[size] = y[size - 1] + 50;
							break;
						case 3:
							x[size] = x[size - 1] + 50;
							y[size] = y[size - 1];
								break;
						case 4:
							x[size] = x[size - 1] - 50;
							y[size] = y[size - 1];
							break;
						default:
							break;
					}
					size++; // ตัวแปรขนาด บวก 1
					point++; // ตัวแปรคะแนน บวก 1
					speed -= 5000;
					if (delay_time > 5000){
						delay_time -= 1000;
					}
					if (bg_delay < 15){
						bg_delay += 1;
					}
					food_appear = 0;
					sprintf(score_text, "Score: %0d", point);
					message_surface_score = TTF_RenderText_Solid(sans, score_text, white);   //Create Variable for turn text
					message_texture_score = SDL_CreateTextureFromSurface(renderer, message_surface_score);
					SDL_DestroyTexture(food1_texture); // ทําลาย texture อาหารเก่าทิ้ง
				}

				for (int i = 1; i < size; i++){
					if (x[0] == x[i] && y[0] == y[i]){ // ถ้างูชนตัวเอง
						game_on = 0;
						break;
					}
					x[i] = rest_x[i - 1];
					y[i] = rest_y[i - 1];
				}

				for (int i = 0; i < size; i++){
					rest_x[i] = x[i];
					rest_y[i] = y[i];
				}
				render_something(message_texture_score, 1000, 30, 150, 40);
			}
			keyboard_on = 0;
			SDL_RenderPresent(renderer);  //Render ตัว Renderer ออกมาทางหน้าจอ
			delay_function(delay_time);
		}
	}
	//zone ปิดโปรแกรม
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	return 0;
}

int render_animation(texture, count, srcrect_x, srcrect_y, pos_rect_x, pos_rect_y, rect_x, rect_y) {  //render แบบมี animation (texture, countของรูปภาพว่าอยู่ตำแหน่งไหน, ขนาดแกนxรูปภาพเดิม, ขนาดแกนyรูปภาพเดิม, ตำแหน่งx, ตำแหน่งy, ขนาดแนวนอน, ขนาดแนวตั้ง)
	int pos_x = count * srcrect_x;
	SDL_Rect animation_rect = { pos_rect_x, pos_rect_y, rect_x, rect_y };
	SDL_Rect animation_srcrect = { pos_x , 0, srcrect_x, srcrect_y };
	SDL_RenderCopy(renderer, texture, &animation_srcrect, &animation_rect);
}

int render_something(texture, pos_rect_x, pos_rect_y, rect_x, rect_y) {  //render แบบปกติ (texture, ตำแหน่งx, ตำแหน่งy, ขนาดแนวนอน, ขนาดแนวตั้ง)
	SDL_Rect something_rect = { pos_rect_x, pos_rect_y, rect_x, rect_y };
	SDL_RenderCopy(renderer, texture, NULL, &something_rect);
}

int delay_function(delay_diff) {  //เอาไว้ดีเล 10000 น่าจะ 1 วิ (มั้ง)
	int delay = delay_diff / 60 - SDL_GetTicks() + SDL_GetTicks();
	SDL_Delay(delay);
	return 0;
}

/*
เริ่มมาก็แตกไฟล์ MinGW.rar ไปแทนที่ MinGw ของตัวเองก่อน (จำเป็นมาก ใช้ในการ Complie)
(แนะนำว่าไว้ใน Drive C นะ)
ลอง cmd แล้วพิม mingw32-make ดูถ้าไม่ error แสดงว่าไม่มีปัญหา ถ้า error ก็ทักมานะจ้ะ
*/
