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

int		refill_rpg(t_player *player)
{
	int	to_fill;

	to_fill = player->weapons[4].mag_size;
	if (player->weapons[4].total_ammo < player->weapons[4].max_ammo)
	{
		while (to_fill-- > 0 && player->weapons[4].total_ammo < player->weapons[4].max_ammo)
			player->weapons[4].total_ammo++;
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

int		jetpack(t_player *player)
{
	int	to_fill;

	to_fill = 50;
	if (player->fuel < 300)
	{
		while (player->fuel < 300 && to_fill-- > 0)
			player->fuel += 1;
		return (BOOL_TRUE);
	}
	return (BOOL_FALSE);
}

int		red_card(t_player *player)
{
	player->red_card = 1;
	return (BOOL_TRUE);
}

int		blue_card(t_player *player)
{
	player->blue_card = 1;
	return (BOOL_TRUE);
}

int		green_card(t_player *player)
{
	player->green_card = 1;
	return (BOOL_TRUE);
}

t_item		create_health_pack(void)
{
	static int	num = 1;
	t_item		item;

	item.name = ft_strjoinf("Health_Pack_", ft_itoa(num), 2);
	num++;
	// t_mesh_set_color(&result, create_t_color(0.8, 0.0, 0.0 ,1.0));
	// result.collectible = BOOL_TRUE;
	item.pf = heal;
	return (item);
}

t_item		create_ammo_pack(int type)
{
	static int	num = 1;
	t_item		item;

	item.name = ft_strjoinf("Ammo_Pack_", ft_itoa(num), 2);
	num++;
	// if (type == 1)
	// 	t_mesh_set_color(&result, create_t_color(0.3, 0.3, 0.3 ,1.0));
	// else if (type == 2)
	// 	t_mesh_set_color(&result, create_t_color(0.0, 0.8, 0.0 ,1.0));
	// else if (type == 3)
	// 	t_mesh_set_color(&result, create_t_color(0.8, 0.8, 0.0 ,1.0));
	// else if (type == 4)
	// 	t_mesh_set_color(&result, create_t_color(0.4, 0.0, 0.0 ,1.0));
	// else if (type == 5)
	// 	t_mesh_set_color(&result, create_t_color(0.4, 0.0, 0.4 ,1.0));
	// result.collectible = BOOL_TRUE;
	if (type == 1)
		item.pf = refill_pistol;
	else if (type == 2)
		item.pf = refill_ar;
	else if (type == 3)
		item.pf = refill_rifle;
	else if (type == 4)
		item.pf = refill_shotgun;
	else if (type == 5)
		item.pf = refill_rpg;
	return (item);
}

t_item		create_armor_pack(void)
{
	static int	num = 1;
	t_item		item;

	item.name = ft_strjoinf("Armor_Pack_", ft_itoa(num), 2);
	num++;
	// t_mesh_set_color(&result, create_t_color(0.0, 0.0, 0.8 ,1.0));
	// result.collectible = BOOL_TRUE;
	item.pf = protect;
	return (item);
}

t_item		create_jet_pack(void)
{
	static int	num = 1;
	t_item		item;

	item.name = ft_strjoinf("Jet_Pack_", ft_itoa(num), 2);
	num++;
	// t_mesh_set_color(&result, create_t_color(0.8, 0.8, 0.5 ,1.0));
	// result.collectible = BOOL_TRUE;
	item.pf = jetpack;
	return (item);
}

t_item		create_color_card(int type)
{
	t_item		item;
	t_mesh		result;

	if (type == 1)
		item.name = ft_strjoin("Card_", "Red");
	else if (type == 2)
		item.name = ft_strjoin("Card_", "Blue");
	else if (type == 3)
		item.name = ft_strjoin("Card_", "Green");
	// if (type == 1)
	// 	t_mesh_set_color(&result, create_t_color(1.0, 0.2, 0.2 ,1.0));
	// else if (type == 2)
	// 	t_mesh_set_color(&result, create_t_color(0.2, 0.2, 1.0 ,1.0));
	// else if (type == 3)
	// 	t_mesh_set_color(&result, create_t_color(0.2, 1.0, 0.2 ,1.0));
	// result.collectible = BOOL_TRUE;
	if (type == 1)
		item.pf = red_card;
	else if (type == 2)
		item.pf = blue_card;
	else if (type == 3)
		item.pf = green_card;
	return (item);
}
