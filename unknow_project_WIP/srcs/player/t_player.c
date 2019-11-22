#include "unknow_project.h"

t_player		create_t_player(t_camera *cam)
{
	t_player 	result;

	result.camera = cam;
	result.shoot_time = 10;
	result.speed = 1.0;
	return (result);
}

t_player			*initialize_t_player(t_camera *cam)
{
	t_player *result;

	if (!(result = (t_player *)malloc(sizeof(t_player))))
		error_exit(-13, "Can't create a t_player array");
	*result = create_t_player(cam);
	return(result);
}

t_weapon		create_t_weapons(int index, int ammo, int total_ammo)
{
	t_weapon	result[5];

	result[0].name = "pistol";
	result[0].ammo = ammo;
	result[0].mag_size = 15;
	result[0].max_ammo = result[0].mag_size * MAX_MAGS;
	result[0].total_ammo = total_ammo;
	result[0].dmg = 10;
	result[0].tick_shoot = 1;
	result[0].tick_reload = 2;

	result[1].name = "ar";
	result[1].ammo = ammo;
	result[1].mag_size = 30;
	result[1].max_ammo = result[1].mag_size * MAX_MAGS;
	result[1].total_ammo = total_ammo;
	result[1].dmg = 25;
	result[1].tick_shoot = 1;
	result[1].tick_reload = 2;

	result[2].name = "rifle";
	result[2].ammo = ammo;
	result[2].mag_size = 10;
	result[2].max_ammo = result[2].mag_size * MAX_MAGS;
	result[2].total_ammo = total_ammo;
	result[2].dmg = 50;
	result[2].tick_shoot = 2;
	result[2].tick_reload = 3;

	result[3].name = "shotgun";
	result[3].ammo = ammo;
	result[3].mag_size = 8;
	result[3].max_ammo = result[3].mag_size * MAX_MAGS;
	result[3].total_ammo = total_ammo;
	result[3].dmg = 120;
	result[3].tick_shoot = 2;
	result[3].tick_reload = 3;

	result[4].name = "rpg";
	result[4].ammo = ammo;
	result[4].mag_size = 1;
	result[4].max_ammo = result[4].mag_size * MAX_MAGS;
	result[4].total_ammo = total_ammo;
	result[4].dmg = 200000;
	result[4].tick_shoot = 1;
	result[4].tick_reload = 4;

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
	else if (get_key_state(p_keyboard, p_keyboard->key[SDL_SCANCODE_5]) == 1)
		index = 4;
	player->current_weapon = &player->weapons[index];
}

void			reload_weapon(t_camera *camera, t_engine *engine)
{
	int to_fill;

	to_fill = engine->user_engine->player->current_weapon->mag_size - engine->user_engine->player->current_weapon->ammo;
	if (engine->tick - engine->user_engine->player->reload_time == engine->user_engine->player->current_weapon->tick_reload)
	{
		while (to_fill > 0 && engine->user_engine->player->current_weapon->ammo < engine->user_engine->player->current_weapon->mag_size && engine->user_engine->player->current_weapon->total_ammo > 0)
		{
			engine->user_engine->player->current_weapon->ammo++;
			engine->user_engine->player->current_weapon->total_ammo--;
			to_fill--;
			if (ft_strcmp(engine->user_engine->player->current_weapon->name, "pistol") == 0 && engine->user_engine->player->current_weapon->ammo == engine->user_engine->player->current_weapon->mag_size)
				engine->user_engine->player->current_weapon->total_ammo = 15;

		}
		camera->r_press = 0;
	}
}

void			shoot_weapon(t_engine *engine)
{
	t_mesh	*target;
	float	dist;
	static int	i = 0;

	dist = 0.0;
	if (t_mouse_state(engine->user_engine->mouse) == 1 && engine->tick % engine->user_engine->player->current_weapon->tick_shoot == 0)
	{
		if (engine->user_engine->player->current_weapon->ammo > 0)
		{
			target = cast_ray(engine, t_camera_list_get(engine->visual_engine->camera_list, 0)->pos, t_camera_list_get(engine->visual_engine->camera_list, 0)->forward, "Player");
			if (target != NULL && target->hp > 0)
			{
				if (ft_strcmp(engine->user_engine->player->current_weapon->name, "shotgun") == 0)
					dist = calc_dist_vector4_to_vector4(engine->user_engine->player->hitbox.pos, target->pos);
				if (engine->user_engine->player->current_weapon->dmg - dist * 4 >= 0)
					target->hp -= engine->user_engine->player->current_weapon->dmg - dist * 4;
				if (target->hp <= 0)
				{
					if (ft_strcmp(target->name, "wall_script") == 0)
						t_mesh_activate_gravity(engine->user_engine->player->camera->body, 0.0f);
					if (ft_strcmp(target->name, "Enemy") == 0)
						t_mesh_set_name(target, "Dead_enemy");
					t_mesh_set_visibility(target, BOOL_FALSE);
					target->no_hitbox = 1;
				}
			}
			if (ft_strcmp(engine->user_engine->player->current_weapon->name, "ar") == 0)
				engine->user_engine->player->current_weapon->ammo -= 2;
			engine->user_engine->player->current_weapon->ammo--;
		}
		engine->user_engine->player->shoot_time = engine->tick;
	}
}

void			player_action(t_camera *camera, t_keyboard *p_keyboard, t_engine *engine)
{
	static t_mesh	*door = NULL;
	static t_mesh	*elevator = NULL;
	t_mesh			*target;
	int				i;

	if (get_key_state(p_keyboard, p_keyboard->key[SDL_SCANCODE_L]) == 1)
	{
		if (engine->user_engine->player->camera->body->kinetic != 0.0f)
			t_mesh_activate_gravity(engine->user_engine->player->camera->body, 0.0f);
		else
			t_mesh_activate_gravity(engine->user_engine->player->camera->body, 100.0f);
	}
	if (get_key_state(p_keyboard, p_keyboard->key[SDL_SCANCODE_R]) == 1 && camera->r_press == 0
		&& engine->user_engine->player->current_weapon->mag_size - engine->user_engine->player->current_weapon->ammo != 0
		&& engine->user_engine->player->current_weapon->total_ammo != 0)
	{
		camera->r_press = 1;
		engine->user_engine->player->reload_time = engine->tick;
	}
	if (get_key_state(p_keyboard, p_keyboard->key[SDL_SCANCODE_F]) == 1)
	{
		i = 0;
		while(i < engine->physic_engine->mesh_list->size && camera->f_press == 0)
		{
			target = t_mesh_list_get(engine->physic_engine->mesh_list, i);
			if (camera->body != target && target->bubble_radius + camera->body->bubble_radius >= calc_dist_vector4_to_vector4(camera->body->center, target->center) && (ft_strcmp(target->name, "door") == 0 || ft_strcmp(target->name, "door") == '_'))
			{
				if (ft_strcmp(target->name, "door") == 0 || (ft_strcmp(target->name, "door_red") == 0
				&& engine->user_engine->player->red_card == 1) || (ft_strcmp(target->name, "door_blue") == 0
				&& engine->user_engine->player->blue_card == 1) || (ft_strcmp(target->name, "door_green") == 0
				&& engine->user_engine->player->green_card == 1))
				{
					target->door.move = 1;
					door = target;
				}
			}
			if (camera->body != target && target->bubble_radius + camera->body->bubble_radius >= calc_dist_vector4_to_vector4(camera->body->center, target->center) && ft_strcmp(target->name, "elevator") == 0)
			{
				target->door.move = 1;
				elevator = target;
			}
			i++;
		}
		camera->f_press = 1;
	}
	else
		camera->f_press = 0;
	if (get_key_state(p_keyboard, p_keyboard->key[SDL_SCANCODE_B]) == 1)
		save_map(engine, 1);
	change_weapon(engine->user_engine->keyboard, engine->user_engine->player);
	if (door != NULL)
		t_mesh_move_door(door);
	if (elevator != NULL)
		t_mesh_move_elevator(elevator, camera);
	if (camera->r_press == 1)
		reload_weapon(camera, engine);
	if (engine->user_engine->player->shoot_time != engine->tick && camera->r_press != 1)
		shoot_weapon(engine);
	if (engine->user_engine->player->hp <= 0)
		engine->playing = -2;
}
