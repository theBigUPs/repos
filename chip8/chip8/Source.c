#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#pragma warning(disable:4996)

typedef enum bool
{
	true = 1,
	false = 0
}bool;



typedef struct chip8
{
	uint8_t v[16]; //16 8 bit long data registers
	uint16_t instruction_pointer;
	uint16_t adress_register_I;// I is 12 bits wide
	uint16_t stack_pointer;
	uint16_t program_counter;
	uint8_t delay_timer;
	uint8_t sound_timer;
	uint8_t memory[0x1000];//4kb ram
}chip8state;


int *file_to_arr(FILE *f) 
{
	fseek(f, 0, SEEK_END); // seek to end of file
	int sizeoffile = ftell(f); // get current file pointer
	fseek(f, 0, SEEK_SET); // seek back to beginning of file
	printf("%d\n\n", sizeoffile);


	int *arr = (int *)malloc(sizeoffile * sizeof(int));


	if (f == NULL) {
		return 1;
	}
	int to = 0;
	int from = sizeoffile;
	int i, j, c=12;

	for (i = 0; i <= from && c != EOF; i++)
	{


		// Get the characters
		c = fgetc(f);
		*(arr+i) = c;
		//printf("%d\n", arr[i]);
	}

	return arr;
}


void display_clear(SDL_Renderer* renderer)
{
	for (size_t i = 0; i < 640; i++)
	{
		for (size_t j = 0; j < 320; i++)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderDrawPoint(renderer, i, j);
		}
	}
}

void return_from_subroutine()
{
	printf("return_from_subroutine");
}

void jump(uint16_t two_byte_machine_code,chip8state *c8)
{
	c8->program_counter = two_byte_machine_code & 0x0fff; //jumps to adress 0xnnn
}


void call_subroutine(uint16_t two_byte_machine_code, chip8state *c8)
{
	printf("call subroutine");
}


uint8_t random_8_bit_num()
{
	uint8_t num = (rand() % 256);
	return num;
}


void draw(uint8_t vx, uint8_t vy, uint8_t n)
{
	//Draws a sprite at coordinate(VX, VY) that has a width of 8 pixels and a height of N pixels.
	//Each row of 8 pixels is read as bit - coded starting from memory location I; I value does not change after the execution of this instruction.
	//As described above, VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn, and to 0 if that does not happen.

	printf("draw");
}



void reg_dump(chip8state *c8)
{
	for (size_t i = 0; i < 16; i++)
	{
		c8->memory[c8->adress_register_I + i] = c8->v[i];

	}
}


void reg_load(chip8state *c8)
{
	for (size_t i = 0; i < 16; i++)
	{
		c8->v[i] = c8->memory[c8->adress_register_I + i];

	}
}


void set_BCD(chip8state *c8,uint8_t vx )
{
	c8->memory[c8->adress_register_I] = (vx / 100);
	c8->memory[c8->adress_register_I + 1] = (vx % 100) / 10;
	c8->memory[c8->adress_register_I + 2] = (vx % 10);
	
}

uint8_t getkey()
{
	int a = getch();
	return a;
}

void opcodes(uint16_t two_byte_machine_code,chip8state *c8, SDL_Renderer* renderer)
{

	int upper_byte = two_byte_machine_code >>8; // upper byte is something like 0x12 of 0x1256
	int lower_byte = two_byte_machine_code & 0xff; // lower byte is something like 0x56 of 0x1256
	switch (upper_byte>>4)// gets the upper nibble of the upper byte
	{
		case 0x00: 
			switch (lower_byte)
			{
				case 0xe0: display_clear(renderer); break;
				case 0xee: return_from_subroutine(); break;
				default:
					break;
			};
			break;

		case 0x01: jump(two_byte_machine_code, c8); break;

		case 0x02: call_subroutine(two_byte_machine_code, c8); break;

		case 0x03: //if (Vx == NN) pc+1
			if (c8->v[upper_byte & 0x0f]==lower_byte)
			{
				c8->program_counter +=2;//this might be 2 or 1
			}
			;break;

		case 0x04://if (Vx != NN) pc+1
			if (c8->v[upper_byte & 0x0f] != lower_byte)
			{
				c8->program_counter += 2;//this might be 2 or 1
			}
			; break;

		case 0x05: //if (Vx == Vy) pc+1
			if (c8->v[upper_byte & 0x0f] == c8->v[lower_byte >> 4])
			{
				c8->program_counter += 2;//this might be 2 or 1
			}
			; break;

		case 0x06: c8->v[upper_byte & 0x0f] = lower_byte ; break;//Vx = NN

		case 0x07: c8->v[upper_byte & 0x0f] += lower_byte; break;//Vx += NN

		case 0x08:		
			switch (lower_byte & 0x0f)
			{
				case 0x00:    c8->v[upper_byte & 0x0f] = c8->v[lower_byte >> 4]; break; //Vx = Vy

				case 0x01:    c8->v[upper_byte & 0x0f] |= c8->v[lower_byte >> 4]; break; //Vx |= Vy

				case 0x02:    c8->v[upper_byte & 0x0f] &= c8->v[lower_byte >> 4]; break; //Vx &= Vy

				case 0x03:    c8->v[upper_byte & 0x0f] ^= c8->v[lower_byte >> 4]; break; //Vx &= Vy

				case 0x04:    c8->v[upper_byte & 0x0f] += c8->v[lower_byte >> 4]; break; //Vx += Vy

				case 0x05:    c8->v[upper_byte & 0x0f] -= c8->v[lower_byte >> 4]; break; //Vx -= Vy

				case 0x06: //Vx >>= 1					
					c8->v[0xf] =  (c8->v[upper_byte & 0x0f]) & 0x01 ;
					c8->v[upper_byte & 0x0f] = c8->v[upper_byte & 0x0f] >> 1;
					break;

				case 0x07:    c8->v[upper_byte & 0x0f] = c8->v[lower_byte >> 4] - c8->v[upper_byte & 0x0f]; break; //Vx = Vy - Vx

				case 0x0e: //Vx <<= 1
					c8->v[0xf] = (c8->v[upper_byte & 0x0f]) & 0x01;
					c8->v[upper_byte & 0x0f] = c8->v[upper_byte & 0x0f] << 1;
					break;

				default:
					break;
			}			
			; break;


		case 0x09:  //if (Vx != Vy) then skip one instruction			
			if (c8->v[upper_byte & 0x0f] != c8->v[lower_byte >> 4])
			{
				c8->program_counter += 2;//this might be 2 or 1
			}
			break;

		case 0x0a: c8->adress_register_I = two_byte_machine_code & 0x0fff; break; //I = NNN	

		case 0x0b: c8->program_counter = c8->v[0] + two_byte_machine_code & 0x0fff; break; //PC = V0 + NNN

		case 0x0c: //Vx = rand() & NN
			c8->v[upper_byte & 0x0f] = random_8_bit_num() & lower_byte ;
			break;

		case 0x0d: draw(c8->v[upper_byte & 0x0f], c8->v[lower_byte >> 4], lower_byte & 0xf) ; break;

		case 0x0e: 		
			switch (lower_byte)
			{
				case 0x9e: //if (key() == Vx)	Skips the next instruction if the key stored in VX is pressed
					if (getkey() == c8->v[upper_byte & 0x0f])
					{
						c8->program_counter += 2;
					}
					break; 

				case 0xa1://if (key() != Vx)	Skips the next instruction if the key stored in VX is not pressed					
					if (getkey() != c8->v[upper_byte & 0x0f])
					{
						c8->program_counter += 2;
					}
					break;
					
				default:
					break;
			}	
			break;

		case 0x0f: 						
			switch (lower_byte)
			{
				case 0x07: c8->v[upper_byte & 0x0f] = c8->delay_timer ; break;  //Vx = get_delay()
				case 0x0a: c8->v[upper_byte & 0x0f] = getkey()  ; break;  //Vx = get_key() A key press is awaited, and then stored in VX (blocking operation, all instruction halted until next key event).

				case 0x15: c8->delay_timer = c8->v[upper_byte & 0x0f]; break;  //delay_timer(Vx)

				case 0x18: c8->sound_timer = c8->v[upper_byte & 0x0f]; break;  //sound_timer(Vx)

				case 0x1e: c8->adress_register_I += c8->v[upper_byte & 0x0f]; break;  //I += Vx

				case 0x29:; break;//I = sprite_addr[Vx] Sets I to the location of the sprite for the character in VX. Characters 0-F in hexadecimal are represented by a 4x5 font.
				case 0x33:set_BCD(c8, c8->v[upper_byte & 0x0f]); break;//set_BCD(Vx)*(I + 0) = BCD(3);*(I + 1) = BCD(2);*(I + 2) = BCD(1);
				case 0x55:reg_dump(c8); break;//reg_dump(Vx, &I)
				case 0x66:reg_load(c8, c8->v[upper_byte & 0x0f]); break;//reg_load(Vx, &I)
				default:
					break;
			}			
			break;

		default:
			break;
	}

}



void draw_test(SDL_Renderer* renderer,int x,int y)
{
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	SDL_RenderDrawPoint(renderer, x, y);
}



int main()
{
	time_t t;
	srand((unsigned)time(&t));
	FILE* fptr1;
	//chip8state *c8 =  malloc(sizeof(chip8state)); //(struct chip8state*)

	fptr1 = fopen("Fishie.ch8", "rb");
	//c8->memory[5] = 12;
	//uint8_t *arr;
	//arr = file_to_arr(fptr1);
	
	//unsigned char memory[0x1000];

	//printf("%d", sizeof(memory));
	//uint16_t k = 0x1456;
	//int a = getch();
	//printf("%d",a);

	fclose(fptr1);

	
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	window = SDL_CreateWindow("chip 8 emulator hopefully",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640, 320,0);
	SDL_Surface *window_surface = SDL_GetWindowSurface(window);
	SDL_UpdateWindowSurface(window);
	//SDL_Delay(1000);
	renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED);



	
	//SDL_Quit();

	bool keep_window_open = true;
	while (keep_window_open)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e) > 0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				keep_window_open = false;
				break;
			}

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderClear(renderer);


			//SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
			//SDL_RenderDrawPoint(renderer, 120, 120);
			
			for (size_t i = 0; i < 100; i++)
			{
				draw_test(renderer, i, i);
			}
			
			//SDL_UpdateWindowSurface(window);
			SDL_RenderPresent(renderer);


			//SDL_UpdateWindowSurface(window);
		}
	}

	return 0;
}