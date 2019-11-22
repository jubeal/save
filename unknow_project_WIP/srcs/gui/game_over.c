# include "unknow_project.h"

void	game_over(t_camera *main_camera, t_gui *gui, t_user_engine *user_engine)
{
	print_letter(main_camera, gui, "GAME OVER", create_t_rectangle(create_t_vector2(-0.12, 0.14), create_t_vector2(0.04, 0.12)));
}
