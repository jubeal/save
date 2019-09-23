#include "unknow_project.h"

t_uv	create_t_uv(t_triangle p_triangle, t_texture *p_texture)
{
	t_uv	result;

	result.texture = p_texture;
	result.uv = p_triangle;
	return (result);
}

t_uv	*initialize_t_uv(t_triangle p_triangle, t_texture *p_texture)
{
	t_uv	*result;

	if (!(result = (t_uv *)malloc(sizeof(t_uv))))
		return (NULL);
	*result = create_t_uv(p_triangle, p_texture);
	return (result);
}

void	print_t_uv(t_uv uv, char *texture_name) // A SUPPRIMER
{
	printf("Texture : %s\n", texture_name);
	printf("Texture size : %d / %d\n", uv.texture->surface->w, uv.texture->surface->h);
	printf("Texture Internal Format : %d\n", uv.texture->surface->internalFormat);
	printf("UV coordinate :\n");
	print_t_vector3(uv.uv.a, "A : ");
	endl();
	print_t_vector3(uv.uv.b, "B : ");
	endl();
	print_t_vector3(uv.uv.c, "C : ");
	endl();
}
