#include "unknow_project.h"

t_vector4		convert_screen_to_opengl(t_view_port *p_view_port, t_vector4 source)
{
	t_vector4 result;

	result.x = source.x / ((float)(p_view_port->size.x) / 2.0) - 1.0f;
	result.y = -(source.y / ((float)(p_view_port->size.y) / 2.0) - 1.0f);
	result.z = source.z;
	return (result);
}

t_vector2		convert_vector2_to_opengl(t_view_port *p_view_port, t_vector2 source)
{
	t_vector2 result;

	result.x = source.x / ((float)(p_view_port->size.x) / 2.0) - 1.0f;
	result.y = -(source.y / ((float)(p_view_port->size.y) / 2.0) - 1.0f);
	return (result);
}

t_vector4		convert_opengl_to_vector4(t_view_port *p_view_port, t_vector4 source)
{
	t_vector4 result;

	result.x = (source.x + 1.0f) * ((float)(p_view_port->size.x) / 2.0);
	result.y = (-(source.y) + 1.0f) * ((float)(p_view_port->size.y) / 2.0);
	result.z = source.z;
	return (result);
}

t_vector2_int	convert_vector2_to_vector2_int(t_vector2 base)
{
	return (create_t_vector2_int((int)(base.x), (int)(base.y)));
}

t_vector4		convert_vector2_to_vector4(t_vector2 base)
{
	return (create_t_vector4(base.x, base.y, 0.0));
}

t_vector4_int	convert_vector4_to_vector4_int(t_vector4 base)
{
	return (create_t_vector4_int((int)(base.x), (int)(base.y), (int)(base.z)));
}

float			degree_to_radius(float angle)
{
	return ((float)(((float)angle) * M_PI / (float)180));
}

float			radius_to_degree(float radian)
{
	return ((float)((float)(radian * 180) / M_PI));
}

t_uv			convert_t_uv_to_texture(t_uv *source)
{
	t_uv		result;

	result = *source;
	result.uv.a.y = 1 - result.uv.a.y;
	result.uv.b.y = 1 - result.uv.b.y;
	result.uv.c.y = 1 - result.uv.c.y;
	return (result);
}
