#include <stdio.h>
#include <stdint.h>
#include <SDL.h>
#pragma warning(disable:4996)


typedef struct chip8
{
	uint8_t v[16]; //16 8 bit long data registers
	uint16_t instruction_pointer;
	uint16_t adress_register_I;//should technically be 12 bits wide can be and'ed with 0x0fff to achieve this length but not necessary
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


void display_clear()
{
	printf("display clear");
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
	return 5;
}


void draw(uint8_t vx, uint8_t vy, uint8_t n)
{
	//Draws a sprite at coordinate(VX, VY) that has a width of 8 pixels and a height of N pixels.
	//Each row of 8 pixels is read as bit - coded starting from memory location I; I value does not change after the execution of this instruction.
	//As described above, VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn, and to 0 if that does not happen.

	printf("draw");
}


void opcodes(uint16_t two_byte_machine_code,chip8state *c8)
{

	int upper_byte = two_byte_machine_code >>8; // upper byte is something like 0x12 of 0x1256
	int lower_byte = two_byte_machine_code & 0xff; // lower byte is something like 0x56 of 0x1256
	switch (upper_byte>>4)// gets the upper nibble of the upper byte
	{
		case 0x00: 
			switch (lower_byte)
			{
				case 0xe0: display_clear(); break;
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
				case 0x9e:; break; //if (key() == Vx)	Skips the next instruction if the key stored in VX is pressed
				case 0xa1:; break; //if (key() != Vx)	Skips the next instruction if the key stored in VX is not pressed
				default:
					break;
			}	
			break;

		case 0x0f: 						
			switch (lower_byte)
			{
				case 0x07:; break;  //Vx = get_delay()
				case 0x0a:; break;  //Vx = get_delay() A key press is awaited, and then stored in VX (blocking operation, all instruction halted until next key event).

				case 0x15: c8->delay_timer = c8->v[upper_byte & 0x0f]; break;  //delay_timer(Vx)

				case 0x18: c8->sound_timer = c8->v[upper_byte & 0x0f]; break;  //sound_timer(Vx)

				case 0x1e: c8->adress_register_I += c8->v[upper_byte & 0x0f]; break;  //I += Vx

				case 0x29:; break;//I = sprite_addr[Vx] Sets I to the location of the sprite for the character in VX. Characters 0-F in hexadecimal are represented by a 4x5 font.
				case 0x33:; break;//set_BCD(Vx)*(I + 0) = BCD(3);*(I + 1) = BCD(2);*(I + 2) = BCD(1);
				case 0x55:; break;//reg_dump(Vx, &I)
				case 0x66:; break;//reg_load(Vx, &I)
				default:
					break;
			}			
			break;

		default:
			break;
	}

}

int main()
{

	FILE* fptr1;


	fptr1 = fopen("Fishie.ch8", "rb");

	uint8_t *arr;
	//arr = file_to_arr(fptr1);
	
	//unsigned char memory[0x1000];

	//printf("%d", sizeof(memory));
	uint16_t k = 0x1456;

	printf("%x",k&0xff);



	fclose(fptr1);


	













	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;

		if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) == 0) {
			SDL_bool done = SDL_FALSE;

			while (!done) {
				SDL_Event event;

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(renderer);

				SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
				SDL_RenderDrawLine(renderer, 320, 200, 300, 240);
				SDL_RenderDrawLine(renderer, 300, 240, 340, 240);
				SDL_RenderDrawLine(renderer, 340, 240, 320, 200);
				SDL_RenderPresent(renderer);

				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						done = SDL_TRUE;
					}
				}
			}
		}

		if (renderer) {
			SDL_DestroyRenderer(renderer);
		}
		if (window) {
			SDL_DestroyWindow(window);
		}
	}
	SDL_Quit();


















	return 0;
}