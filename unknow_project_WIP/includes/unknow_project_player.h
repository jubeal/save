#ifndef UNKNOW_PROJECT_PLAYER_H
# define UNKNOW_PROJECT_PLAYER_H
# define MAX_MAGS 5

#include "unknow_project_camera.h"

typedef struct  s_knife
{
	int			ammo;
}               t_knife;

typedef struct  s_pistol
{
	int			ammo;
	int			mag_size;
}               t_pistol;

typedef struct  s_ar
{
	int			ammo;
	int			mag_size;
}               t_ar;

typedef struct  s_rifle
{
	int			ammo;
	int			mag_size;
}               t_rifle;

typedef struct  s_shotgun
{
	int			ammo;
	int			mag_size;
}               t_shotgun;

typedef struct  s_weapons
{
	t_knife		knife;
	t_pistol	pistol;
	t_ar		ar;
	t_rifle		rifle;
	t_shotgun	shotgun;
}               t_weapons;

typedef struct  s_ammo
{
	int			pistol_ammo;
	int			pistol_mags;
	int			ar_ammo;
	int			ar_mags;
	int			rifle_ammo;
	int			rifle_mags;
	int			shotgun_ammo;
	int			shotgun_mags;
}               t_ammo;

typedef struct  s_player
{
	t_camera	*camera;
	t_mesh		hitbox;
	int			hp;
	int			armor;
	float		speed;
	t_weapons	weapons;
	t_ammo		ammo;
}               t_player;

t_player		create_t_player(t_camera *cam);
t_player		*initialize_t_player(t_camera *cam);
t_ammo			create_t_ammo(void);
t_weapons		create_t_weapons(t_ammo ammo);

#endif