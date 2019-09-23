#include "unknow_project.h"

int main(int argc, char **argv)
{
	TTF_Font    *police;
	SDL_Surface *font = NULL;
	SDL_Color color = {0, 0, 0};

	if (argc != 1)
		error_exit(-1, "Bad argument");
	start_sdl(); //initialisation de la SDL

	t_window *win;
	win = initialize_t_window(argv[0], WIN_X, WIN_Y);	//creation et initialisation de la window

	t_texture *texture2 = png_load("ressources/assets/texture/ammo.png");
	t_texture *texture = png_load("ressources/assets/texture/cube_number.png");

	t_engine	*engine = initialize_t_engine(win);
	t_gui		*gui;

	gui = initialize_t_gui(0.10, 30);

	load_menu(gui);
	TTF_Init();
	set_t_gui_texte(gui);

	t_mesh mesh;
	t_camera *main_camera = t_camera_list_get(engine->visual_engine->camera_list, 0);

	t_engine_place_camera(engine, 0, create_t_vector3(5.0, 5.0, 0.0));
	t_camera_look_at_point(main_camera, create_t_vector3(0, 0, 0));
	t_engine_add_camera(engine, create_t_camera(win, create_t_vector3(0.0, 0.0, 0.0), 70, create_t_vector2(NEAR, FAR)));
	resize_t_view_port(t_camera_list_get(engine->visual_engine->camera_list, 1)->view_port, create_t_vector2_int(300, 240));
	move_t_view_port(t_camera_list_get(engine->visual_engine->camera_list, 1)->view_port, create_t_vector2_int(WIN_X - 300, 0));

	//resize_t_view_port(t_camera_list_get(engine->visual_engine->camera_list, 0)->view_port, create_t_vector2_int(2, 2));

	t_player *player = initialize_t_player(main_camera);
	t_engine_add_mesh(engine, player->hitbox);
	printf("Player hp after initialisation = %d\n", player->hp);
	link_t_camera_to_t_mesh(main_camera, t_engine_get_mesh(engine, 0), 100);

	// t_mesh mesh = read_obj_file("pawn.obj", create_t_vector3(2.9, 10.0, 2.9), create_t_vector3(0.1, 0.11, 0.1), 100.0);
	// t_mesh_set_color(&mesh, create_t_color(1.5, 0.4, 1.5, 1.0));
	// t_engine_add_mesh(engine, mesh);

	mesh = create_primitive_cube(create_t_vector3(-5.0, -1.0, -5.0), create_t_vector3(10.0, 1.0, 10.0), NULL, 0.0, "sol");
	// t_mesh_rotate(&mesh, create_t_vector3(45.0, 0.0, 0.0));
	t_mesh_set_color(&mesh, create_t_color(0.5, 0.5, 0.5, 1.0));
	t_engine_add_mesh(engine, mesh);



	// mesh = create_primitive_cube(create_t_vector3(5.0, 0.0, 5.0), create_t_vector3(1.0, 1.0, 1.0), NULL, 0.0, "cube texture");
	// t_mesh_rotate(&mesh, create_t_vector3(0.0, 0.0, 0.0));
	// t_mesh_set_color(&mesh, create_t_color(0.5, 0.6, 0.8 ,1.0));
	// t_engine_add_mesh(engine, mesh);

	mesh = create_primitive_cube(create_t_vector3(-5.0, 0.0, 5.0), create_t_vector3(10.0, 2.0, 0.1), texture, 0.0, "mur bleu");
	t_mesh_rotate(&mesh, create_t_vector3(0.0, 0.0, 0.0));
	t_mesh_set_color(&mesh, create_t_color(0.5, 0.6, 0.8 ,1.0));
	t_engine_add_mesh(engine, mesh);

	mesh = create_primitive_cube(create_t_vector3(-5.0, 0.0, -5.0), create_t_vector3(10.0, 2.0, 0.1), texture, 0.0, "mur rose");
	t_mesh_rotate(&mesh, create_t_vector3(0.0, 0.0, 0.0));
	t_mesh_set_color(&mesh, create_t_color(1.0, 0.6, 0.8 ,1.0));
	t_engine_add_mesh(engine, mesh);

	mesh = create_primitive_cube(create_t_vector3(-5.0, 0.0, 5.0), create_t_vector3(10.0, 2.0, 0.1), texture, 0.0, "mur violet");
	t_mesh_rotate(&mesh, create_t_vector3(0.0, 90.0, 0.0));
	t_mesh_set_color(&mesh, create_t_color(0.5, 0.0, 0.8 ,1.0));
	t_engine_add_mesh(engine, mesh);

	mesh = create_primitive_cube(create_t_vector3(5.0, 0.0, 5.0), create_t_vector3(10.0, 2.0, 0.1), texture, 0.0, "mur vert");
	t_mesh_rotate(&mesh, create_t_vector3(0.0, 90.0, 0.0));
	t_mesh_set_color(&mesh, create_t_color(0.5, 0.6, 0.0 ,1.0));
	t_engine_add_mesh(engine, mesh);

	mesh = create_primitive_cube(create_t_vector3(0.0, 0.0, 1.0), create_t_vector3(1.0, 1.0, 1.0), texture, 0.0, "test textures");
	t_mesh_rotate(&mesh, create_t_vector3(0.0, 90.0, 0.0));
	t_mesh_set_color(&mesh, create_t_color(0.5, 0.6, 0.0 ,1.0));
	t_engine_add_mesh(engine, mesh);

	// mesh = create_primitive_cube(create_t_vector3(0.0, 0.0, 0.0), create_t_vector3(5.0, 5.0, 5.0), NULL, 100.0);
	// t_mesh_rotate(&mesh, create_t_vector3(0.0, 0.0, 0.0));
	// t_mesh_set_color(&mesh, create_t_color(0.5, 0.6, 0.0 ,1.0));
	// t_engine_add_mesh(engine, mesh);


	t_rectangle rec = create_t_rectangle(create_t_vector2(-1, 1), create_t_vector2(2, -2));

	// mesh = read_obj_file("pawn.obj", create_t_vector3(-3.0, 1.0, 2.0), create_t_vector3(0.1, 0.11, 0.1), 10.0);
	// t_mesh_set_color(&mesh, create_t_color(0.3, 0.3, 1.0, 1.0));
	// t_engine_add_mesh(engine, mesh);

	t_item_list	*item_list = initialize_t_item_list();

	// t_item health_pack = create_health_pack(create_t_vector3(0.0, 0.0, 0.0), engine);
	// t_item_list_push_back(item_list, health_pack);
	// printf("item list 1 name = %s\n", item_list->item[0].name);

	// health_pack = create_health_pack(create_t_vector3(1.0, 0.0, 0.0), engine);
	// t_item_list_push_back(item_list, health_pack);
	// printf("item list 2 name = %s\n", item_list->item[1].name);

	// health_pack = create_health_pack(create_t_vector3(-1.0, 0.0, 0.0), engine);
	// t_item_list_push_back(item_list, health_pack);
	// printf("item list 3 name = %s\n", item_list->item[2].name);

	// t_engine_add_camera(engine, create_t_camera(win, create_t_vector3(3.5, 1.5, 0.25), 70, create_t_vector2(NEAR, FAR)));
	// resize_t_view_port(t_camera_list_get(engine->visual_engine->camera_list, 2)->view_port, create_t_vector2_int(400, 340));
	// move_t_view_port(t_camera_list_get(engine->visual_engine->camera_list, 2)->view_port, create_t_vector2_int(0, 0));
	// t_camera_look_at_point(t_camera_list_get(engine->visual_engine->camera_list, 2), create_t_vector3(0, 0, 0));

	t_mesh *target;
	// link_t_camera_to_t_mesh(main_camera, t_engine_get_mesh(engine, 0), 100);

	// t_item *target;
	// t_mesh *test;


	t_color color2 = create_t_color(1.0, 0.0, 1.0, 1.0);
	texture = png_load("ressources/assets/texture/skybox.png");


	mesh = create_primitive_skybox(main_camera->pos, create_t_vector3(1.0, 1.0, 1.0), texture);
	t_mesh_set_color(&mesh, create_t_color(0.0, 1.0, 0.0, 0.5));
	while (engine->playing != 0)
	{

				/*
		penser a faire un initialize t_item
		*/
		if ((target = cast_ray(engine, main_camera->pos, create_t_vector3(0.0, -1.0, 0.0))) != NULL)
		{
			if (target->collectible == 1)
			{
				int i = 0;
				while (i < item_list->size)
				{
					if (ft_strcmp(target->name, item_list->item[i].name) == 0)
					{
						item_list->item[i].pf(player);
						item_list->item[i].name = NULL;
					}
					i++;
				}
				t_mesh_set_visibility(target, 0);
				// delete_t_mesh(target);
			}
		}
		// target->mesh = cast_ray(engine, player.camera.pos ,create_t_vector3(0.0, -1.0, 0.0));
		// target->name = target->mesh->name;
		// if (ft_strcmp("Health Pack", target->name))
		// 	target->type = 0;
		// printf("target name = %s\n", target->name);
		// printf("target type = %d\n", target->type);
		// if ((target->type == 0 || target->type == 1 || target->type == 2))
		// {
		// 	//target->pf(player);
		// 	//t_mesh_set_visibility(target->mesh, 0);
		// 	//t_mesh_list_erase(engine->physic_engine->mesh_list, t_mesh_list_get_index(engine->physic_engine->mesh_list, target));
		// 	//printf("test\n");
		// }
		prepare_screen(win, create_t_color(0.2f, 0.2f, 0.2f, 1.0f));
		t_engine_prepare_camera(engine);
		engine->playing = 1;

		if (engine->playing <= -1)
		{
			t_engine_draw_mesh(engine);
			t_engine_render_camera(engine);
			drawing_front_pause(main_camera, gui);
		}
		else if (engine->playing == 2)
		{
			draw_rectangle_texture_cpu(main_camera->view_port, rec, gui->menu[0]);
		}
		else if (engine->playing == 3)
		{
			draw_rectangle_texture_cpu(main_camera->view_port, rec, gui->menu[1]);
		}
		else if (engine->playing == 4)
		{
			draw_rectangle_texture_cpu(main_camera->view_port, rec, gui->menu[2]);
		}
		else if (engine->playing == 5)
		{
			draw_rectangle_texture_cpu(main_camera->view_port, rec, gui->menu[4]);
		}
		else if (engine->playing == 6)
		{
			draw_rectangle_texture_cpu(main_camera->view_port, rec, gui->menu[3]);
		}
		else if (engine->playing == 1)
		{
			mesh.pos = main_camera->pos;

			draw_skybox(win, main_camera, &mesh);
			t_engine_render_camera(engine);

			t_engine_apply_physic(engine);

			t_engine_handle_camera(engine);

			t_engine_prepare_camera(engine);

			t_engine_draw_mesh(engine);

			t_engine_render_camera(engine);
			drawing_front_hp(main_camera, gui);
			drawing_front_mun(main_camera, gui, texture2);
			draw_minimap(main_camera, engine, win);
			print_info_bar(main_camera, gui);
		}

		t_engine_handle_event(main_camera, gui, engine);
		render_screen(win); // affiche la fenetre
	}
	TTF_Quit();
	return (0);
}
