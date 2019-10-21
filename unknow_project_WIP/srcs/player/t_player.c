#include "unknow_project.h"

t_player		create_t_player(t_camera *cam, t_mesh hitbox)
{
	t_player 	result;

	result.camera = cam;
	result.hitbox = hitbox;
	t_mesh_set_color(&result.hitbox, create_t_color(0.5, 0.6, 0.0 ,1.0));
	result.hp = 100;
	result.armor = 0;
	result.speed = 1.0;
	result.weapons[0] = create_t_weapons(0);
	result.weapons[1] = create_t_weapons(1);
	result.weapons[2] = create_t_weapons(2);
	result.weapons[3] = create_t_weapons(3);
	result.current_weapon = &result.weapons[0];
	return (result);
}

t_player			*initialize_t_player(t_camera *cam, t_mesh hitbox)
{
	t_player *result;

	if (!(result = (t_player *)malloc(sizeof(t_player))))
		error_exit(-13, "Can't create a t_player array");
	// printf("malloc t_player\n");

	*result = create_t_player(cam, hitbox);

	return(result);
}

t_weapon		create_t_weapons(int index)
{
	t_weapon	result[4];

	result[0].name = "pistol";
	result[0].ammo = 15;
	result[0].mag_size = 15;
	result[0].max_ammo = result[0].mag_size * MAX_MAGS;
	result[0].total_ammo = 0;

	result[1].name = "ar";
	result[1].ammo = 0;
	result[1].mag_size = 30;
	result[1].max_ammo = result[1].mag_size * MAX_MAGS;
	result[1].total_ammo = 0;

	result[2].name = "rifle";
	result[2].ammo = 0;
	result[2].mag_size = 10;
	result[2].max_ammo = result[2].mag_size * MAX_MAGS;
	result[2].total_ammo = 0;

	result[3].name = "shotgun";
	result[3].ammo = 0;
	result[3].mag_size = 8;
	result[3].max_ammo = result[3].mag_size * MAX_MAGS;
	result[3].total_ammo = 0;

	return (result[index]);
}


void			change_weapon(t_keyboard *p_keyboard, t_player *player)
{
	static int index = 0; //changer pour une union
	if (get_key_state(p_keyboard, p_keyboard->key[SDL_SCANCODE_1]) == 1)
		index = 0;
	else if (get_key_state(p_keyboard, p_keyboard->key[SDL_SCANCODE_2]) == 1)
		index = 1;
	else if (get_key_state(p_keyboard, p_keyboard->key[SDL_SCANCODE_3]) == 1)
		index = 2;
	else if (get_key_state(p_keyboard, p_keyboard->key[SDL_SCANCODE_4]) == 1)
		index = 3;
	player->current_weapon = &player->weapons[index];
}

void			reload_weapon(t_keyboard *p_keyboard, t_player *player)
{
	int to_fill;

	to_fill = player->current_weapon->mag_size - player->current_weapon->ammo;
	if (get_key_state(p_keyboard, p_keyboard->key[SDL_SCANCODE_R]) == 1)
	{
		while (to_fill > 0 && player->current_weapon->ammo < player->current_weapon->mag_size && player->current_weapon->total_ammo > 0)
		{
			player->current_weapon->ammo++;
			player->current_weapon->total_ammo--;
			to_fill--;
		}
	}
}

void			shoot_weapon(t_engine *engine)
{
	t_mesh	*target;

	if (t_mouse_state(engine->user_engine->mouse) == 1)
	{
		if (engine->user_engine->player->current_weapon->ammo > 0)
		{
			target = cast_ray(engine, t_camera_list_get(engine->visual_engine->camera_list, 0)->pos, t_camera_list_get(engine->visual_engine->camera_list, 0)->forward);
			if (target != NULL)
				// printf("\rTarget name = %s\n", target->name);
			// if (ft_strcmp(target->name, "Enemy") == 0)
			engine->user_engine->player->current_weapon->ammo--;
		}
	}
}
