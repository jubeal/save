#include "unknow_project.h"

int		heal(t_player *player)
{
	int to_heal;

	to_heal = 20;
	if (player->hp < 100)
	{
		while (player->hp < 100 && to_heal-- > 0)
			player->hp += 1;
		return (BOOL_TRUE);
	}
	return (BOOL_FALSE);
}

int		refill_pistol(t_player *player)
{
	int	to_fill;

	to_fill = player->weapons[0].mag_size;
	if (player->weapons[0].total_ammo < player->weapons[0].max_ammo)
	{
		while (to_fill-- > 0 && player->weapons[0].total_ammo < player->weapons[0].max_ammo)
			player->weapons[0].total_ammo++;
		return (BOOL_TRUE);
	}
	else
		return (BOOL_FALSE);
}

int		refill_ar(t_player *player)
{
	int	to_fill;

	to_fill = player->weapons[1].mag_size;
	if (player->weapons[1].total_ammo < player->weapons[1].max_ammo)
	{
		while (to_fill-- > 0 && player->weapons[1].total_ammo < player->weapons[1].max_ammo)
			player->weapons[1].total_ammo++;
		return (BOOL_TRUE);
	}
	else
		return (BOOL_FALSE);
}

int		refill_rifle(t_player *player)
{
	int	to_fill;

	to_fill = player->weapons[2].mag_size;
	if (player->weapons[2].total_ammo < player->weapons[2].max_ammo)
	{
		while (to_fill-- > 0 && player->weapons[2].total_ammo < player->weapons[2].max_ammo)
			player->weapons[2].total_ammo++;
		return (BOOL_TRUE);
	}
	else
		return (BOOL_FALSE);
}

int		refill_shotgun(t_player *player)
{
	int	to_fill;

	to_fill = player->weapons[3].mag_size;
	if (player->weapons[3].total_ammo < player->weapons[3].max_ammo)
	{
		while (to_fill-- > 0 && player->weapons[3].total_ammo < player->weapons[3].max_ammo)
			player->weapons[3].total_ammo++;
		return (BOOL_TRUE);
	}
	else
		return (BOOL_FALSE);
}

int		protect(t_player *player)
{
	int to_protect;

	to_protect = 20;
	if (player->armor < 100)
	{
		while (player->armor < 100 && to_protect-- > 0)
			player->armor += 1;
		return (BOOL_TRUE);
	}
	return (BOOL_FALSE);
}

t_item		create_health_pack(t_vector3 pos, t_engine *engine)
{
	static int	num = 1;
	t_item		item;
	t_mesh		result;
	char 		*str;
	char 		*tmp;

	tmp = ft_itoa(num++);
	str = ft_strnew(ft_strlen("Health Pack ") + ft_strlen(tmp));
	str = ft_strcpy(str, "Health Pack ");
	str = ft_strcat(str, tmp);
	item.name = str;
	free(tmp);
	result = create_primitive_cube(pos, create_t_vector3(0.2, 0.05, 0.2), NULL, 0.0);
	t_mesh_set_name(&result, item.name);
	t_mesh_rotate(&result, create_t_vector3(0.0, 0.0, 0.0));
	t_mesh_set_color(&result, create_t_color(0.8, 0.0, 0.0 ,1.0));
	result.collectible = BOOL_TRUE;
	item.mesh = &result;
	item.pf = heal;
	item.picked_up = 0;
	t_engine_add_mesh(engine, result);
	return (item);
}

t_item		create_ammo_pack(t_vector3 pos, t_engine *engine, int type)
{
	static int	num = 1;
	t_item		item;
	t_mesh		result;
	char 		*str;
	char 		*tmp;

	tmp = ft_itoa(num++);
	str = ft_strnew(ft_strlen("Ammo Pack ") + ft_strlen(tmp));
	str = ft_strcpy(str, "Ammo Pack ");
	str = ft_strcat(str, tmp);
	item.name = str;
	free(tmp);
	result = create_primitive_cube(pos, create_t_vector3(0.2, 0.05, 0.2), NULL, 0.0);
	t_mesh_set_name(&result, item.name);
	t_mesh_rotate(&result, create_t_vector3(0.0, 0.0, 0.0));
	if (type == 1)
		t_mesh_set_color(&result, create_t_color(0.3, 0.3, 0.3 ,1.0));
	else if (type == 2)
		t_mesh_set_color(&result, create_t_color(0.0, 0.8, 0.0 ,1.0));
	else if (type == 3)
		t_mesh_set_color(&result, create_t_color(0.8, 0.8, 0.0 ,1.0));
	else if (type == 4)
		t_mesh_set_color(&result, create_t_color(0.4, 0.0, 0.0 ,1.0));
	result.collectible = BOOL_TRUE;
	item.mesh = &result;
	if (type == 1)
		item.pf = refill_pistol;
	else if (type == 2)
		item.pf = refill_ar;
	else if (type == 3)
		item.pf = refill_rifle;
	else if (type == 4)
		item.pf = refill_shotgun;
	item.picked_up = 0;
	t_engine_add_mesh(engine, result);
	return (item);
}

t_item		create_armor_pack(t_vector3 pos, t_engine *engine)
{
	static int	num = 1;
	t_item		item;
	t_mesh		result;
	char 		*str;
	char 		*tmp;

	tmp = ft_itoa(num++);
	str = ft_strnew(ft_strlen("Armor Pack ") + ft_strlen(tmp));
	str = ft_strcpy(str, "Armor Pack ");
	str = ft_strcat(str, tmp);
	item.name = str;
	free(tmp);
	result = create_primitive_cube(pos, create_t_vector3(0.2, 0.05, 0.2), NULL, 0.0);
	t_mesh_set_name(&result, item.name);
	t_mesh_rotate(&result, create_t_vector3(0.0, 0.0, 0.0));
	t_mesh_set_color(&result, create_t_color(0.0, 0.0, 0.8 ,1.0));
	result.collectible = BOOL_TRUE;
	item.mesh = &result;
	item.pf = protect;
	item.picked_up = 0;
	t_engine_add_mesh(engine, result);
	return (item);
}
