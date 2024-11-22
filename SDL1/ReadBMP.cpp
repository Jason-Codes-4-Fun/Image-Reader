
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <SDL.h>
#include <cmath>
#include <string>
inline std::vector<int> GetCOlor8Bit(int c) {
	std::vector<int> RGB;
	switch (c) {
	case 0:
		//black
		RGB = { 0,0,0 };
		break;
	case 1:
		RGB = { 255,0,0 };
		break;
	case 2:
		//white
		RGB = { 255, 255, 255 };
		break;
	case 3:
		RGB = { 255, 255, 0 };
		break;
	case 4:
		RGB = { 0, 0, 128 };
		break;
	case 5:
		RGB = { 225, 0, 225 };
		break;
	case 6:
		RGB = { 0, 255, 255 };
		break;
	case 7:
		//white
		RGB = { 255, 255, 255};
		break;
	case 8:
		RGB = { 255, 255, 0 };
		break;
	case 9:
		RGB = { 50, 205, 50 };
		break;
	case 10:
		RGB = { 0, 128, 128 };
		break;
	case 11:
		RGB = { 173, 216, 230 };
		break;
	case 12:
		//grey
		RGB = { 192, 192, 192 };
		break;
	case 13:
		RGB = { 255, 105, 180 };
		break;
	case 14:
		RGB = { 128, 128, 128 };
		break;
	case 15:
		RGB = { 211, 211, 211 };
		break;

	}return RGB;
}

inline void Read(std::string file_name){
	uint32_t filesize;

	uint8_t rgb[3];
	std::fstream fout;

	

	fout.open(file_name, std::ios::in | std::ios::binary);
	if (fout) {

		//seeks the file size off the header, it teats the reference address for a uint32 as a pointer address for a char
		fout.seekg(2);
		//the cast 
		fout.read(reinterpret_cast<char*>(&filesize), 4);

		//seek the width off the header
		int32_t width;
		fout.seekg(18);
		fout.read(reinterpret_cast<char*>(&width), 4);

		//seeks the height off the header
		int32_t height;
		fout.seekg(22);
		fout.read(reinterpret_cast<char*>(&height), 4);
		
		SDL_Window* window;
		SDL_Renderer* renderer;

		SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		int y = height;
		int x = 0;
		// allows you to set the bit reading mode, the data can be obtained from the header but by default ill set it to 24
		int bits = 24;

		//case where we set it to 24 bits
		if (bits == 24) {
			//the modulus adds the appropriate padding to the bytes based on the width of the file
			int padding = width % 4;
			for (int pix = 0; (pix / 3) <= (width * height); pix = pix + 3) {
				x++;

				fout.seekg(54 + pix);
				fout.read(reinterpret_cast<char*>(rgb), 3);
				if (x == width && x != 0) {

					y--;
					x = 0;
					pix += padding;

				}
				SDL_SetRenderDrawColor(renderer, int(rgb[2]), int(rgb[1]), int(rgb[0]), 255);
				SDL_RenderDrawPoint(renderer, x, y);


			}
			
		}
		else {
			uint8_t BYTE;
			uint8_t BYTE2;
			std::vector<int> rgb;
			for (int byte = 118; byte <= 900*900; byte++) {
				fout.seekg( byte);
	
				if (x == 730) {

					y--;
					x = 0;
					byte += 3;


				}
				else {
					
				}
				fout.read(reinterpret_cast<char*>(&BYTE), 1);
				




				rgb = GetCOlor8Bit(int(BYTE >> 4));
				//std::cout << rgb[0] << " " << rgb[1] << " " << rgb[2] << std::endl;
				SDL_SetRenderDrawColor(renderer, rgb[0], rgb[1], rgb[2], 255);
				SDL_RenderDrawPoint(renderer, x, y);
				BYTE2 = (BYTE << 4);

				rgb = GetCOlor8Bit(int(BYTE2 >> 4));
				SDL_SetRenderDrawColor(renderer, rgb[0], rgb[1], rgb[2], 255);
				SDL_RenderDrawPoint(renderer, x+1, y);
				x += 2;
				//std::cout << (BYTE2>>4) <<std::endl;
			
				//std::cout << int(BYTE << 4 >>4) << std::endl;
				//std::cout << (BYTE>> 4);

				//


			}
		}
		bool running = true;
		while (running) {
			SDL_RenderPresent(renderer);
			SDL_Event event;
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					running = false;
				}
			}
		}

		

		
		fout.close();
	}
}


