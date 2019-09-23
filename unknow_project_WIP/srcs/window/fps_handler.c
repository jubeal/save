#include "unknow_project.h"

void		check_frame(void)
{
	static int		nb_frame;
	static int		beginsecond;
	int				frame_actual;
	static Uint32	framestart;

	nb_frame = 0;
	beginsecond = 0;
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
	framestart = SDL_GetTicks();
}
