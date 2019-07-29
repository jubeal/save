#include "unknow_project.h"

void			check_frame()
{
	static int		nb_frame = 0;
	static int		beginsecond = 0;
	int				frame_actual;
	static Uint32 	framestart;

	frame_actual = SDL_GetTicks();
	if (beginsecond == 0)
		beginsecond = frame_actual;
	if (frame_actual - beginsecond > 1000)
	{
		printf("nb_frame = %d\n", nb_frame);
		nb_frame = 0;
		beginsecond = 0;
	}
	else
		nb_frame++;
	/*if (1000 / FPS > frame_actual - framestart)
		SDL_Delay(1000 / FPS - (frame_actual - framestart));*/
	framestart = SDL_GetTicks();
}
