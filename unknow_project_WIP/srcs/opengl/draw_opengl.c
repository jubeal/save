#include "unknow_project.h"

// void draw_pixel_opengl(t_window *p_win, t_vector3 *p_coord, t_color *p_color)
// {
// 	GLfloat vertex_buffer_data[] = {
// 		p_coord->x, p_coord->y, 0.0f
// 	};
//
// 	GLfloat color_buffer_data[] = {
// 		p_color->r,  p_color->g,  p_color->b, p_color->a
// 	};
//
// 	// bind VAO
// 	glBindVertexArray(p_win->vertex_array);
//
// 	// bind vertex_buffer
// 	glBindBuffer(GL_ARRAY_BUFFER, p_win->vertex_buffer);
// 	// donne a vertex_buffer vertex_buffer_data
// 	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
//
// 	// bind color_buffer
// 	glBindBuffer(GL_ARRAY_BUFFER, p_win->color_buffer);
// 	// donne a color_buffer color_buffer_data
// 	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
//
// 	// indique le shader a utiliser
// 	glUseProgram(p_win->program_color);
//
// 	// indique la location du shader utiliser
// 	glEnableVertexAttribArray(0);
// 	// quelle est le buffer a utiliser
// 	glBindBuffer(GL_ARRAY_BUFFER, p_win->vertex_buffer);
// 	// comment utiliser le buffer
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//
// 	glEnableVertexAttribArray(1);
// 	glBindBuffer(GL_ARRAY_BUFFER, p_win->color_buffer);
// 	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
//
// 	// dessine un point
// 	glDrawArrays( GL_POINTS, 0, 1);
// }
//
// void draw_point_opengl(t_window *p_win, t_vector2 *p_point, t_color *p_color, int size)
// {
// 	GLfloat vertex_buffer_data[3];
// 	GLfloat color_buffer_data[4];
//
// 	glPointSize(size);
//
// 	vertex_buffer_data[0] = p_point->x;
// 	vertex_buffer_data[1] = p_point->y;
// 	vertex_buffer_data[2] = 0.0f;
//
// 	color_buffer_data[0] = p_color->r;
// 	color_buffer_data[1] = p_color->g;
// 	color_buffer_data[2] = p_color->b;
// 	color_buffer_data[3] = p_color->a;
//
// 	// bind VAO
// 	glBindVertexArray(p_win->vertex_array);
//
// 	// bind vertex_buffer
// 	glBindBuffer(GL_ARRAY_BUFFER, p_win->vertex_buffer);
// 	// donne a vertex_buffer vertex_buffer_data
// 	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
//
// 	// bind color_buffer
// 	glBindBuffer(GL_ARRAY_BUFFER, p_win->color_buffer);
// 	// donne a color_buffer color_buffer_data
// 	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
//
// 	// indique le shader a utiliser
// 	glUseProgram(p_win->program_color);
//
// 	// indique la location du shader utiliser
// 	glEnableVertexAttribArray(0);
// 	// quelle est le buffer a utiliser
// 	glBindBuffer(GL_ARRAY_BUFFER, p_win->vertex_buffer);
// 	// comment utiliser le buffer
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//
// 	glEnableVertexAttribArray(1);
// 	glBindBuffer(GL_ARRAY_BUFFER, p_win->color_buffer);
// 	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
//
// 	// dessine un point
// 	glDrawArrays( GL_POINTS, 0, 1);
// 	glPointSize(1);
// }
//
// void draw_line_color_opengl(t_window *p_win, t_line *p_line, t_color *p_color)
// {
// 	GLfloat vertex_buffer_data[] = {
// 		p_line->a.x, p_line->a.y, 0.0f,
// 		p_line->b.x, p_line->b.y, 0.0f,
// 	};
//
// 	GLfloat color_buffer_data[] = {
// 		p_color->r,  p_color->g,  p_color->b, p_color->a,
// 		p_color->r,  p_color->g,  p_color->b, p_color->a,
// 	};
//
// 	// bind VAO
// 	glBindVertexArray(p_win->vertex_array);
//
// 	// bind vertex_buffer
// 	glBindBuffer(GL_ARRAY_BUFFER, p_win->vertex_buffer);
// 	// donne a vertex_buffer vertex_buffer_data
// 	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
//
// 	// bind color_buffer
// 	glBindBuffer(GL_ARRAY_BUFFER, p_win->color_buffer);
// 	// donne a color_buffer color_buffer_data
// 	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
//
// 	// indique le shader a utiliser
// 	glUseProgram(p_win->program_color);
//
// 	// indique la location du shader utiliser
// 	glEnableVertexAttribArray(0);
// 	// quelle est le buffer a utiliser
// 	glBindBuffer(GL_ARRAY_BUFFER, p_win->vertex_buffer);
// 	// comment utiliser le buffer
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//
// 	glEnableVertexAttribArray(1);
// 	glBindBuffer(GL_ARRAY_BUFFER, p_win->color_buffer);
// 	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
//
// 	// dessine un triangle
// 	glDrawArrays(GL_LINES, 0, 2);
// }
//
void draw_triangle_color_opengl(t_window *p_win, t_triangle *p_triangle, t_color *p_color)
{
	GLfloat vertex_buffer_data[] = {
		p_triangle->a.x, p_triangle->a.y, 0.0f,
		p_triangle->b.x, p_triangle->b.y, 0.0f,
		p_triangle->c.x, p_triangle->c.y, 0.0f,
	};

	GLfloat color_buffer_data[] = {
		p_color->r,  p_color->g,  p_color->b, p_color->a,
		p_color->r,  p_color->g,  p_color->b, p_color->a,
		p_color->r,  p_color->g,  p_color->b, p_color->a,
	};

	// bind VAO
	glBindVertexArray(p_win->vertex_array);

	// bind vertex_buffer
	glBindBuffer(GL_ARRAY_BUFFER, p_win->vertex_buffer);
	// donne a vertex_buffer vertex_buffer_data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

	// bind color_buffer
	glBindBuffer(GL_ARRAY_BUFFER, p_win->color_buffer);
	// donne a color_buffer color_buffer_data
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	// indique le shader a utiliser
	glUseProgram(p_win->program_color);

	// indique la location du shader utiliser
	glEnableVertexAttribArray(0);
	// quelle est le buffer a utiliser
	glBindBuffer(GL_ARRAY_BUFFER, p_win->vertex_buffer);
	// comment utiliser le buffer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, p_win->color_buffer);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);

	// dessine un triangle
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
//
// void			draw_triangle_texture_opengl(t_window *p_win, t_triangle *p_triangle_screen, t_uv *uv)
// {
// 	GLfloat vertex_buffer_data[] = {
// 		p_triangle_screen->a.x, p_triangle_screen->a.y, 0.0f,
// 		p_triangle_screen->b.x, p_triangle_screen->b.y, 0.0f,
// 		p_triangle_screen->c.x, p_triangle_screen->c.y, 0.0f,
// 	};
//
// 	GLfloat uv_buffer_data[] = {
// 		uv->uv->a.x,  uv->uv->a.y,
// 		uv->uv->b.x,  uv->uv->b.y,
// 		uv->uv->c.x,  uv->uv->c.y,
// 	};
//
// 	GLfloat alpha_buffer_data[] = {
// 		uv->alpha,
// 		uv->alpha,
// 		uv->alpha,
// 	};
//
// 	glBindTexture(GL_TEXTURE_2D, uv->image->id);
//
// 	glBindVertexArray(p_win->vertex_array);
//
// 	glBindBuffer(GL_ARRAY_BUFFER, p_win->vertex_buffer);
// 	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_DYNAMIC_DRAW);
//
// 	glBindBuffer(GL_ARRAY_BUFFER, p_win->texture_buffer);
// 	glBufferData(GL_ARRAY_BUFFER, sizeof(uv_buffer_data), uv_buffer_data, GL_DYNAMIC_DRAW);
//
// 	glBindBuffer(GL_ARRAY_BUFFER, p_win->alpha_buffer);
// 	glBufferData(GL_ARRAY_BUFFER, sizeof(alpha_buffer_data), alpha_buffer_data, GL_DYNAMIC_DRAW);
//
// 	glUseProgram(p_win->program_texture);
//
// 	glEnableVertexAttribArray(0);
// 	glBindBuffer(GL_ARRAY_BUFFER, p_win->vertex_buffer);
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//
// 	glEnableVertexAttribArray(1);
// 	glBindBuffer(GL_ARRAY_BUFFER, p_win->texture_buffer);
// 	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
//
// 	glEnableVertexAttribArray(2);
// 	glBindBuffer(GL_ARRAY_BUFFER, p_win->alpha_buffer);
// 	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, NULL);
//
// 	glDrawArrays(GL_TRIANGLES, 0, 3);
//
// 	glBindTexture(GL_TEXTURE_2D, 0);
// }

void draw_buffer_opengl(t_window *p_win, t_color *color_data)
{
	int screen_len;

	screen_len = p_win->size_x * p_win->size_y;

	glBindVertexArray(p_win->vertex_array);

	glBindBuffer(GL_ARRAY_BUFFER, p_win->color_fixed_buffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 4 * screen_len, color_data);

	// indique le shader a utiliser
	glUseProgram(p_win->program_color);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, p_win->vertex_fixed_buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, p_win->color_fixed_buffer);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);

	// dessine un point
	glDrawArrays( GL_POINTS, 0, screen_len);
}
