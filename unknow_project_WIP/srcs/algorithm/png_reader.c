#include "unknow_project.h"

t_surface *read_png_file(const char *filename)
{
	FILE		*fp;
	png_structp	png_ptr;
	png_infop	info_ptr;
	t_surface	*surface;

	int bit_depth;
	int color_type;

	if (!(surface = (t_surface *)malloc(sizeof(t_surface))))
		error_exit(-29, "Can't malloc a t_surface");

	fp = fopen (filename, "rb");		//ouverture du fichier .png. "rb" = read byte donc lecture uniquement et en byte.

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);	//fonction lib png pour creer une sorte de curseur que l'on appelle tete de lecture
	info_ptr = png_create_info_struct (png_ptr);	//lib png, cree une structure qui stock l'encodage de la couleur qu'il detecte

	png_init_io (png_ptr, fp);	//link tete de lecture et fichier

	png_read_info (png_ptr, info_ptr);	//lit le header du png pour y choper les infos et range dans infos ptr

	bit_depth = png_get_bit_depth (png_ptr, info_ptr); //definit la taille d'une couleur (8, 16 ou 32 bits)
	color_type = png_get_color_type (png_ptr, info_ptr);	//recupere le type (rgb, rgba)

	png_read_update_info (png_ptr, info_ptr);	//relink de ce qu'on a fais et indique fin de lecture du header

	png_get_IHDR (png_ptr, info_ptr,			//Prepare la lecture
              (png_uint_32*)(&surface->w),		//des pixels en
              (png_uint_32*)(&surface->h),		//rangeant bien
              &bit_depth, &color_type,			//les infos que
              NULL, NULL, NULL);				//l'on a recupere

	if (color_type == PNG_COLOR_TYPE_RGB)		//define lib png qui definit rgb simple
	{
		surface->format = GL_RGB;				//definit format comme rgb
		surface->internalFormat = 3;			//nombre d'infos par pixel
	}
	else if (color_type == PNG_COLOR_TYPE_RGB_ALPHA)	//pareil mais en rgba
	{
		surface->format = GL_RGBA;
		surface->internalFormat = 4;
	}
	else											//reste traite en erreur
	{
		error_exit(0, "XXX");
	}

	surface->pixels = (GLubyte *)malloc (sizeof (GLubyte) * surface->w * surface->h * surface->internalFormat);	//malloc d'un espace suffisant pour tous les pixels

	png_bytep *row_pointers;

	row_pointers = (png_bytep *)malloc (sizeof (png_bytep) * surface->h);	//maloc d'un espace suffisant pour une ligne de pixels

	int i = -1;
	while (++i < surface->h)
		row_pointers[i] = (png_bytep)(surface->pixels + ((surface->h - (i + 1)) * surface->w * surface->internalFormat));	//met dans ma ligne de pixels l'adresse des premiers pixels des lignes de surface

	png_read_image (png_ptr, row_pointers);	//lecture de l'image pour stockage dans row

	free (row_pointers);

	png_read_end (png_ptr, NULL);	//fin de lecture
	png_destroy_read_struct (&png_ptr, &info_ptr, NULL); //destruction de la structe du png

	fclose (fp);

	return (surface);
}

t_texture *png_load(char *path)
{
	t_texture *texture;
	SDL_Surface *tmp_surface;
	int internal_format;
	int format;

	if (!(texture = (t_texture *)malloc(sizeof(t_texture))))	//malloc du t_texture
		error_exit(-29, "Can't malloc a t_texture");			//sortie si probleme

	texture->surface = read_png_file(path);					//lecture du fichier .png

	tmp_surface = IMG_Load(path);							//chargement de l'image par SDL dans tmp_surface

	if (tmp_surface == NULL)
		error_exit(-32, "Can't load a sdl_tmp_surface");	//sort si sdl fais une erreure
	if (tmp_surface->format->BytesPerPixel == 3)			//Si on est en RGB
	{
		internal_format = GL_RGB;							//defini le format RGB
		if (tmp_surface->format->Rmask == 0xff)				//Rmask est le masque qui definit le format
			format = GL_RGB;								//si Rmask == 0xFF alors on est en RGB
		else
			format = GL_BGR;								//si Rmask == 0x0000FF alors on est en BGR
	}
	else if (tmp_surface->format->BytesPerPixel == 4)		//Si on est en RGBA
	{
		internal_format = GL_RGBA;							//defini le format RGBA
		if (tmp_surface->format->Rmask == 0xff)				//Rmask est le masque qui definit le format
			format = GL_RGBA;								//si Rmask == 0xFF alors on est en RGBA
		else
			format = GL_BGRA;								//si Rmask == 0x0000FF alors on est en BGRA
	}
	glGenTextures(1, &(texture->id));						//Creation d'une textures dans la carte graphique
	glBindTexture(GL_TEXTURE_2D, (texture->id));			//Indique a OpenGL la texture sur laquelle on travail

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	//Defini comment on comble les bordures de la texture en x
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	//en y
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	//definition de la facon dont on agrandi l'image
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	//definition de la facon dont on reduit l'image

	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, tmp_surface->w,	//Envoie la texture a opengl qui la range
				tmp_surface->h, 0, format,							//dans la carte graphique en prechargement
				GL_UNSIGNED_BYTE, tmp_surface->pixels);				//

	glBindTexture(GL_TEXTURE_2D, 0);		//on arrete de travailler dessu

	SDL_FreeSurface(tmp_surface);			//free surface

	return (texture);
}
