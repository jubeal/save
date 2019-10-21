#include "unknow_project.h"

static char	*read_shader(const char *p_path)
{
	char	*content;
	char	*line;
	int		fd;

	content = NULL;
	line = NULL;
	fd = open(p_path, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strlen(content) != 0)
			ft_stradd(&content, "\n");
		ft_stradd(&content, line);
		free(line);
	}
	close(fd);
	free(line);
	return (content);
}

static void	compile_shader(GLuint p_id, char const *p_source)
{
	GLint	result;

	result = GL_FALSE;
	glShaderSource(p_id, 1, &p_source, NULL);
	glCompileShader(p_id);
	glGetShaderiv(p_id, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE)
		error_exit(-2, "Error while compiling shader");
}

static void	compute_program(GLuint p_program_id, GLuint p_vertex_shader_id, GLuint p_fragment_shader_id)
{
	GLint	result;

	result = GL_FALSE;
	glAttachShader(p_program_id, p_vertex_shader_id);
	glAttachShader(p_program_id, p_fragment_shader_id);
	glLinkProgram(p_program_id);
	glGetProgramiv(p_program_id, GL_LINK_STATUS, &result);
	if (result != GL_TRUE)
		error_exit(-3, "Error while computing shader program");
	glDetachShader(p_program_id, p_vertex_shader_id);
	glDetachShader(p_program_id, p_fragment_shader_id);
	glDeleteShader(p_vertex_shader_id);
	glDeleteShader(p_fragment_shader_id);
}

GLuint		load_shaders(const char *p_vertex_file_path, const char *p_fragment_file_path)
{
	char	*vertex_content;
	char	*fragment_content;
	GLuint	vertex_shader_id;
	GLuint	fragment_shader_id;
	GLuint	program_id;

	program_id = glCreateProgram();
	fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	vertex_content = read_shader(p_vertex_file_path);
	fragment_content = read_shader(p_fragment_file_path);
	compile_shader(vertex_shader_id, vertex_content);
	compile_shader(fragment_shader_id, fragment_content);
	free(vertex_content);
	free(fragment_content);
	compute_program(program_id, vertex_shader_id, fragment_shader_id);
	return (program_id);
}
