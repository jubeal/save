#include "unknow_project.h"

int main(int argc, char **argv)
{
	TTF_Font	*police;
	SDL_Surface	*font = NULL;
	SDL_Color	color = {0, 0, 0};

	if (argc != 1)
		error_exit(-1, "Bad argument");

	Mix_Init(MIX_INIT_OGG);
	printf("%s\n", Mix_GetError());
	start_sdl(); //initialisation de la SDL

	t_window *win;
	win = initialize_t_window(argv[0], WIN_X, WIN_Y);	//creation et initialisation de la window

	t_texture *texture2[4];
	texture2[0] = png_load("ressources/assets/texture/pistol_ammo.png");
	texture2[1] = png_load("ressources/assets/texture/ar_ammo.png");
	texture2[2] = png_load("ressources/assets/texture/rifle_ammo.png");
	texture2[3] = png_load("ressources/assets/texture/shotgun_ammo.png");
	t_texture *texture = png_load("ressources/assets/texture/cube_test.png");
	t_texture *skybox = png_load("ressources/assets/texture/skybox.png");

	t_engine	*engine;
	t_gui		*gui;

	engine = initialize_t_engine(win);
	gui = initialize_t_gui(0.10, 30);

	load_menu(gui);
	TTF_Init();
	set_t_gui_texte(gui);
	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 1, 1024) == -1)
		printf("%s\n", Mix_GetError());

	t_mesh		mesh;
	t_camera	*main_camera;
	Mix_Music	*musique;

	musique = Mix_LoadMUS("ressources/assets/sound/mega_man_test.ogg");
	main_camera = t_camera_list_get(engine->visual_engine->camera_list, 0);
	t_engine_place_camera(engine, 0, create_t_vector3(5.0, 5.0, 0.0));
	t_camera_look_at_point(main_camera, create_t_vector3(0, 0, 0));
	t_engine_add_camera(engine, create_t_camera(win, create_t_vector3(0.0, 0.0, 0.0), 70, create_t_vector2(NEAR, FAR)));
	resize_t_view_port(t_camera_list_get(engine->visual_engine->camera_list, 1)->view_port, create_t_vector2_int(300, 240));
	move_t_view_port(t_camera_list_get(engine->visual_engine->camera_list, 1)->view_port, create_t_vector2_int(WIN_X - 300, 0));
	t_engine_add_camera(engine, create_t_camera(win, create_t_vector3(0.0, 0.0, 0.0), 70, create_t_vector2(NEAR, FAR)));
	resize_t_view_port(t_camera_list_get(engine->visual_engine->camera_list, 2)->view_port, create_t_vector2_int(300, 240));
	move_t_view_port(t_camera_list_get(engine->visual_engine->camera_list, 2)->view_port, create_t_vector2_int(300, 0));

	//resize_t_view_port(t_camera_list_get(engine->visual_engine->camera_list, 0)->view_port, create_t_vector2_int(2, 2));

	mesh = create_primitive_cube(create_t_vector3(2.0, 2.0, 2.0), create_t_vector3(0.3, 0.5, 0.3), NULL, 0.0);
	t_mesh_set_name(&mesh, "Player");
	t_mesh_set_color(&mesh, create_t_color(1.5, 0.4, 1.5, 1.0));

	engine->user_engine->player = initialize_t_player(main_camera, mesh);
	t_engine_add_mesh(engine, engine->user_engine->player->hitbox);
	link_t_camera_to_t_mesh(main_camera, t_engine_get_mesh(engine, 0), 100);

	// mesh = create_primitive_cube(create_t_vector3(1.0, 0.0, 2.0), create_t_vector3(1.0, 1.0, 1.0), texture, 0.0);
	// t_mesh_set_name(&mesh, "cube texture");
	// t_mesh_rotate(&mesh, create_t_vector3(0.0, 0.0, 0.0));
	// t_mesh_set_color(&mesh, create_t_color(0.5, 0.6, 0.8 ,1.0));
	// t_engine_add_mesh(engine, mesh);

	mesh = create_primitive_cube(create_t_vector3(1.0, 0.0, 5.0), create_t_vector3(2.0, 2.0, 2), NULL, 0.0);
	t_mesh_set_name(&mesh, "Enemy");
	t_mesh_rotate(&mesh, create_t_vector3(0.0, 90.0, 0.0));
	t_mesh_set_color(&mesh, create_t_color(0.0, 0.0, 0.0 ,1.0));
	t_engine_add_mesh(engine, mesh);

	t_mesh_list *meshs = read_map_file("ressources/map/fichier_map.map");

	int i = 0;
	while (i < meshs->size)
	{
		t_engine_add_mesh(engine, t_mesh_list_at(meshs, i));
		i++;
	}

	t_rectangle rec = create_t_rectangle(create_t_vector2(-1, 1), create_t_vector2(2, -2));

	t_item_list	*item_list = initialize_t_item_list();

	t_item health_pack = create_health_pack(create_t_vector3(0.0, 0.0, 0.0), engine);
	t_item_list_push_back(item_list, health_pack);

	t_item ammo_pack = create_ammo_pack(create_t_vector3(1.0, 0.0, 0.0), engine, 1);
	t_item_list_push_back(item_list, ammo_pack);
	ammo_pack = create_ammo_pack(create_t_vector3(2.0, 0.0, 0.0), engine, 2);
	t_item_list_push_back(item_list, ammo_pack);
	ammo_pack = create_ammo_pack(create_t_vector3(3.0, 0.0, 0.0), engine, 3);
	t_item_list_push_back(item_list, ammo_pack);
	ammo_pack = create_ammo_pack(create_t_vector3(4.0, 0.0, 0.0), engine, 4);
	t_item_list_push_back(item_list, ammo_pack);

	t_item armor_pack = create_armor_pack(create_t_vector3(-1.0, 0.0, 0.0), engine);
	t_item_list_push_back(item_list, armor_pack);

	armor_pack = create_armor_pack(create_t_vector3(-2.0, 0.0, 0.0), engine);
	t_item_list_push_back(item_list, armor_pack);
	engine->physic_engine->item_list = item_list;

	mesh = create_primitive_skybox(main_camera->pos, create_t_vector3(1.0, 1.0, 1.0), skybox);
	engine->playing = 1;
	Mix_VolumeMusic(MIX_MAX_VOLUME);
	Mix_PlayMusic(musique, -1);
	while (engine->playing != 0)
	{
		prepare_screen(win, create_t_color(0.2f, 0.2f, 0.2f, 1.0f));
		t_engine_prepare_camera(engine);

		if (engine->playing <= -1)
		{
			t_engine_draw_mesh(engine);
			t_engine_render_camera(engine);
			drawing_front_pause(main_camera, gui);
		}
		if (engine->playing == 2)
		{
			draw_rectangle_texture_cpu(main_camera->view_port, rec, gui->menu[0]);
		}
		if (engine->playing == 3)
		{
			draw_rectangle_texture_cpu(main_camera->view_port, rec, gui->menu[1]);
		}
		if (engine->playing == 4)
		{
			draw_rectangle_texture_cpu(main_camera->view_port, rec, gui->menu[2]);
		}
		if (engine->playing == 5)
		{
			draw_rectangle_texture_cpu(main_camera->view_port, rec, gui->menu[4]);
		}
		if (engine->playing == 6)
		{
			draw_rectangle_texture_cpu(main_camera->view_port, rec, gui->menu[3]);
		}
		if (engine->playing == 1)
		{
			mesh.pos = main_camera->pos;

			// draw_skybox(win, main_camera, &mesh); // skybox
			// t_engine_render_camera(engine);
			
			t_engine_apply_physic(engine);

			t_engine_handle_camera(engine);
			t_engine_prepare_camera(engine);

			t_engine_draw_mesh(engine);

			t_engine_render_camera(engine);
			change_weapon(engine->user_engine->keyboard, engine->user_engine->player);
			reload_weapon(engine->user_engine->keyboard, engine->user_engine->player);
			shoot_weapon(engine);
			// drawing_front_hp(main_camera, engine);
			// drawing_front_mun(main_camera, gui, texture2, engine->user_engine->player);
			draw_minimap(main_camera, engine, win);
			print_info_bar(main_camera, engine->user_engine->player, gui);
	
		}
		t_engine_handle_event(main_camera, gui, engine);
		render_screen(win); // affiche la fenetre
	}
	Mix_FreeMusic(musique);
	Mix_CloseAudio();
	TTF_Quit();
	return (0);
}
