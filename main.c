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

SDL_Surface* menu_bg_surface = NULL;
SDL_Texture* menu_bg_texture = NULL;

//Call Variable
int running;
int width = 1200, height = 720;    //Create width and height of program
long long frameTime = 0;    //Create frametime

int main(int argc, char* args[]) {
	TTF_Init();                              //SDL_ttf init
	SDL_Init(SDL_INIT_EVERYTHING);           //SDL init
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow("Audition Quest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	running = 1;   //set running to true
	menu_bg_surface = IMG_Load("picture/03.png");
	menu_bg_texture = SDL_CreateTextureFromSurface(renderer, menu_bg_surface);

	while (running) {

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {   //If click close window turn off program
				running = 0;
			}
			else if (event.type == SDL_KEYDOWN) {    //Check Keyboard Event
				switch (event.key.keysym.sym){
				case SDLK_UP:    //Check button arrow up
					break;
				case SDLK_DOWN:  //Check button arrow down
					break;
				case SDLK_LEFT:  //Check button arrow left
					break;
				case SDLK_RIGHT:  //Check button arrow right
					break;
				case SDLK_RETURN:   //Check button ENTER
					break;
				default:
					break;
				}
			}
		}

		frameTime++;

		if (frameTime % 35000 == 0) {  //render background and function in main menu
			SDL_RenderClear(renderer);  //เคลียตัว renderer

			render_something(menu_bg_texture, 0, 0, 1200, 720);

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
