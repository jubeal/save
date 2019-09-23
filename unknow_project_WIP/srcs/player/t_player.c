#include "unknow_project.h"

t_player		create_t_player(t_camera *cam)
{
	t_player 	result;

//CHANGER POS DE LA HITBOX PAR CAM->POS
	result.camera = cam;
	result.hitbox = create_primitive_cube(create_t_vector3(1.0, 20.0, 1.0), create_t_vector3(0.1, 0.1, 0.1), NULL, 0.0, "Player");;
	t_mesh_set_color(&result.hitbox, create_t_color(0.5, 0.6, 0.0 ,1.0));
	result.hp = 50;
	printf("Player hp at initialisation = %d\n", result.hp);
	result.armor = 0;
	result.speed = 1.0;
	result.ammo = create_t_ammo();
	result.weapons = create_t_weapons(result.ammo);
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

t_weapons		create_t_weapons(t_ammo ammo)
{
	t_weapons	result;

	result.pistol.mag_size = 15;
	result.ar.mag_size = 30;
	result.rifle.mag_size = 10;
	result.shotgun.mag_size = 8;
	return (result);
}

// void			set_t_weapons(t_player player, t_weapons weapons)
// {
// 	weapons.pistol.ammo = player.ammo.pistol + (weapons.pistol.mag_size * ammo.pistol.mags);
// 	weapons.ar.ammo = player.ammo.ar + (weapons.pistol.mag_size * ammo.ar.mags);
// 	weapons.rifle.ammo = player.ammo.rifle + (weapons.pistol.mag_size * ammo.rifle.mags);
// 	weapons.shotgun.ammo = player.ammo.shotgun + (weapons.pistol.mag_size * ammo.shotgun.mags);
// }

t_ammo			create_t_ammo(void)
{
	t_ammo		result;

	result.pistol_mags = 0;
	result.ar_mags = 0;
	result.rifle_mags = 0;
	result.shotgun_mags = 0;
	return (result);
}

// void			set_t_ammo(t_ammo ammo)
// {
// 	ammo.pistol_ammo =
// }
