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

SDL_Surface* bg_surface = NULL;
SDL_Texture* bg_texture = NULL;

SDL_Surface* menu_bg_surface = NULL;
SDL_Texture* menu_bg_texture = NULL;

SDL_Surface* food_surface = NULL;
SDL_Texture* food_texture = NULL;

SDL_Surface* radish_surface = NULL;
SDL_Texture* radish_texture = NULL;

SDL_Surface* fail_surface = NULL;
SDL_Texture* fail_texture = NULL;

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
int bg_count = 0;
int point = 0;


int main(int argc, char* args[]) {
	TTF_Init();                              //SDL_ttf init
	SDL_Init(SDL_INIT_EVERYTHING);           //SDL init
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow("Audition Quest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	running = 1;   //set running to true

	srand(time(NULL));

	x[0] = 400, rest_x[0] = 400; //------------------------------------------------//
	y[0] = 400, rest_y[0] = 400; //------------------------------------------------//
	x[1] = 400, rest_x[1] = 400; //------------เปลี่ยนตามขนาดของแต่ละจุด -------------//
	y[1] = 350, rest_y[1] = 350; //------------If chang size 50 to 20 =========>>>>>
	x[2] = 400, rest_x[2] = 400; //==>>Point chang from 300,350,400 to 300,320,360 //
	y[2] = 300, rest_y[2] = 300; //------------------------------------------------//

	menu_bg_surface = IMG_Load("image/body.png");
	menu_bg_texture = SDL_CreateTextureFromSurface(renderer, menu_bg_surface);

	bg_surface = IMG_Load("image/background/fang_sp.png");
	bg_texture = SDL_CreateTextureFromSurface(renderer, bg_surface);

	food_surface = IMG_Load("image/apple.png");
	food_texture = SDL_CreateTextureFromSurface(renderer, food_surface);

	fail_surface = IMG_Load("image/fail.png");
	fail_texture = SDL_CreateTextureFromSurface(renderer, fail_surface);

	radish_surface = IMG_Load("image/radish.png");
	radish_texture = SDL_CreateTextureFromSurface(renderer, radish_surface);

	while (running) {

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {   //If click close window turn off program
				running = 0;
			}
			else if (event.type == SDL_KEYDOWN) {    //Check Keyboard Event
				switch (event.key.keysym.sym){
				case SDLK_UP:    //Check button arrow up
					if (direction != 2 && keyboard_on == 0){
						direction = 1;
						keyboard_on = 1;
					}
					break;
				case SDLK_DOWN:  //Check button arrow down
					if (direction != 1 && keyboard_on == 0){
						direction = 2;
						keyboard_on = 1;
					}
					break;
				case SDLK_LEFT:  //Check button arrow left
					if (direction != 4 && keyboard_on == 0){
						direction = 3;
						keyboard_on = 1;
					}
					break;
				case SDLK_RIGHT:  //Check button arrow right
					if (direction != 3 && keyboard_on == 0){
						direction = 4;
						keyboard_on = 1;
					}
					break;
				case SDLK_RETURN:   //Check button ENTER and Restart at beginning point
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
					break;
				default:
					break;
				}
			}
		}

		frameTime++;

		if (frameTime % 100000 == 0 && game_on == 0){
			SDL_RenderClear(renderer);
			render_something(fail_texture, 0, 0, 1200, 700);
			SDL_RenderPresent(renderer);
			point = 0; // คะแนน
		}

		if (frameTime % speed == 0 && game_on) {  //render background and function in main menu
			SDL_RenderClear(renderer);  //เคลียตัว renderer

			if(bg_count == 4){
				bg_count = 0;
			}
			render_animation(bg_texture, bg_count, 1200, 480, 0, 0, 1200, 700); //ถ้าเป็น GIF ต้องใช้ rander_animation(bg_texture, bg_count, width, height, 0, 0, 1200ขนาดจอwidth, 700ขนาดจอheight);
			bg_count++;

			while (food_appear == 0){ // เช็คว่างูกินอาหารหรือยัง
				food_texture = SDL_CreateTextureFromSurface(renderer, food_surface);
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

			if (size % 2 == 0){
				render_something(radish_texture, position_food_x, position_food_y, 50, 50);
			}
			else{
				render_something(food_texture, position_food_x, position_food_y, 50, 50);
			}

			if(point >= 6){
				menu_bg_surface = IMG_Load("image/Snake4.png");
				menu_bg_texture = SDL_CreateTextureFromSurface(renderer, menu_bg_surface);
			}
			else{
				if(point >= 4){
					menu_bg_surface = IMG_Load("image/Snake3.png");
					menu_bg_texture = SDL_CreateTextureFromSurface(renderer, menu_bg_surface);
				}
				else{
					if(point >= 2){
						menu_bg_surface = IMG_Load("image/Snake2.png");
						menu_bg_texture = SDL_CreateTextureFromSurface(renderer, menu_bg_surface);
					}
					else{
						menu_bg_surface = IMG_Load("image/Snake1.png");
						menu_bg_texture = SDL_CreateTextureFromSurface(renderer, menu_bg_surface);
					}
				}
			}

			if(x[0] >= 1200 || x[0] < 0 || y[0] >= 700 || y[0] < 0){
				game_on = 0;
				continue;
			}

			for (int i = 0; i < size; i++){
                render_something(menu_bg_texture, x[i], y[i], 50, 50);
            }

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
                food_appear = 0;
				SDL_DestroyTexture(food_texture); // ทําลาย texture อาหารเก่าทิ้ง
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

			keyboard_on = 0;
			SDL_RenderPresent(renderer);  //Render ตัว Renderer ออกมาทางหน้าจอ
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
