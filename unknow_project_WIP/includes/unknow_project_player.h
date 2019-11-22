#ifndef UNKNOW_PROJECT_PLAYER_H
# define UNKNOW_PROJECT_PLAYER_H
# define MAX_MAGS 5

#include "unknow_project_camera.h"

typedef struct  s_weapon
{
	char		*name;
	int			ammo;
	int			mag_size;
	int			total_ammo;
	int			max_ammo;
	int			dmg;
	int			tick_shoot;
	int			tick_reload;
}               t_weapon;

typedef struct  s_player
{
	t_camera	*camera;
	t_mesh		hitbox;
	int			hp;
	int			armor;
	int			fuel;
	float		speed;
	t_weapon	weapons[5];
	t_weapon	*current_weapon;
	int			red_card;
	int			blue_card;
	int			green_card;
	int			shoot_time;
	int			reload_time;

}               t_player;

t_player		create_t_player(t_camera *cam);
t_player		*initialize_t_player(t_camera *cam);
t_player		*read_player(int fd, t_camera *main_camera);
t_weapon		create_t_weapons(int index, int ammo, int total_ammo);


#endif
