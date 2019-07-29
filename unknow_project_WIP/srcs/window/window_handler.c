#include "unknow_project.h"

void			start_sdl()
{
	unsigned int seed = 1493368;
	//initialisation SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//version d'OpenGL utiliser par SDL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); //major version, chiffre avant la virgule
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1); //minor version, chiffre apres la virgule

	//utilisation de la carte graphique
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	//Limitation de l'utilisation d'OpenGL (decrepated functions)
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//doublebuffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//profondeur du buffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

	//initialisation du ramdom et du TTF
	srand(seed);

}

t_window		*initialize_t_window(char *p_name, int p_size_x, int p_size_y)
{
	t_window	*win;
	t_vector3	tmp_coord;
	t_color		tmp_color;
	int			i;

	if (!(win = (t_window *)malloc(sizeof(t_window))))
		error_exit(-6, "Can't malloc a t_window");

	// creation de la fenetre
	win->window = SDL_CreateWindow(p_name, // nom de la fenetre
					0, 0, // position de la fentre sur l'ecran
					p_size_x, p_size_y, // taille de la fenetre
					SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL); //parametre de la fenetre

	// stockage de la taille de la fenetre dans win->size_x et win->size_y
	SDL_GetWindowSize(win->window, &win->size_x, &win->size_y);

	// creation du context
	win->context = SDL_GL_CreateContext(win->window);

	// generation du VAO (vertex array object)
	glGenVertexArrays(1, &win->vertex_array);

	// bind le VAO
	glBindVertexArray(win->vertex_array);

	// generation des VBO (vertex buffer object)
	glGenBuffers(1, &win->vertex_buffer);
	glGenBuffers(1, &win->vertex_fixed_buffer);
	glGenBuffers(1, &win->color_buffer);
	glGenBuffers(1, &win->color_fixed_buffer);
	glGenBuffers(1, &win->texture_buffer);
	glGenBuffers(1, &win->alpha_buffer);

	// initialisation du multi_thread
	i = 0;
	while (i < NB_THREAD_MAX)
	{
		win->data[i] = create_t_void_list();
		i++;
	}

	// create shader program
	win->program_color = load_shaders("ressources/shader/color_shader.vert", "ressources/shader/color_shader.frag");
	win->program_texture = load_shaders("ressources/shader/texture_shader.vert", "ressources/shader/texture_shader.frag");

	// gere l'alpha
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// gere la profondeur
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);
	SDL_GL_SetSwapInterval(0);

	if (!(win->vertex_data = (t_vector3 *)malloc(sizeof(t_vector3) * win->size_x * win->size_y)))
		error_exit(-456, "Can't malloc a t_vector3 array properly");

	if (!(win->color_data = (t_color *)malloc(sizeof(t_color) * win->size_x * win->size_y)))
		error_exit(-456, "Can't malloc a t_color array properly");

	tmp_color = create_t_color_from_int(255, 255, 255, 0);

	for (i = 0; i < win->size_x; i++)
	{
		for (int j = 0; j < win->size_y; j++)
		{
			tmp_coord.x = i;
			tmp_coord.y = j;
			tmp_coord.z = 0.0f;

			win->vertex_data[i + j * win->size_x].x = tmp_coord.x / ((float)(win->size_x) / 2.0) - 1.0f;
			win->vertex_data[i + j * win->size_x].y = -(tmp_coord.y / ((float)(win->size_y) / 2.0) - 1.0f);
			win->vertex_data[i + j * win->size_x].z = tmp_coord.z;
		}
	}
	glBindVertexArray(win->vertex_array);

	// bind vertex_buffer
	glBindBuffer(GL_ARRAY_BUFFER, win->vertex_fixed_buffer);
	// donne a vertex_buffer vertex_buffer_data
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * win->size_x * win->size_y * 3, win->vertex_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, win->color_fixed_buffer);
	// donne a color_buffer color_buffer_data
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * win->size_x * win->size_y * 4, NULL, GL_DYNAMIC_DRAW);

	// win->color_data = (t_color *)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);

	return (win);
}

void 				clear_buffers(t_window *win)
{
	for (int i = 0; i < win->size_x * win->size_y; i++)
	{
		win->color_data[i].a = 0;
	}
}

void				prepare_screen(t_window *p_win, t_color color)
{
	//Set background color
	glClearColor((GLclampf)color.r, (GLclampf)color.g, (GLclampf)color.b, 1.0f);

	clear_buffers(p_win);

	//Clear la profondeur et la couleur du buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void				render_screen(t_window *p_win)
{
	check_frame();

	draw_buffer_opengl(p_win, p_win->color_data);

	//Swap le buffer et l'ecran (Ca affiche la nouvelle image)
	SDL_GL_SwapWindow(p_win->window);
}


int 		is_point_in_screen(t_window *p_win, t_vector3 p_point)
{
	if (p_point.x < 0 || p_point.x >= p_win->size_x ||
		p_point.y < 0 || p_point.y >= p_win->size_y)
		return (0);
	return (1);
}

int			is_t_triangle_in_screen(t_window *p_win, t_triangle *p_triangle)
{
	int nb_left;
	int nb_up;
	int nb_right;
	int nb_down;

	if (p_triangle->a.x < 0 && p_triangle->b.x < 0 && p_triangle->c.x < 0)
		return (0);
	if (p_triangle->a.x >= p_win->size_x && p_triangle->b.x >= p_win->size_x && p_triangle->c.x >= p_win->size_x)
		return (0);

	if (p_triangle->a.y < 0 && p_triangle->b.y < 0 && p_triangle->c.y < 0)
		return (0);
	if (p_triangle->a.y >= p_win->size_y && p_triangle->b.y >= p_win->size_y && p_triangle->c.y >= p_win->size_y)
		return (0);

	return (1);
}
