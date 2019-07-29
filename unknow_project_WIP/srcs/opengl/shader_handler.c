#include "unknow_project.h"

// lit la totalite du fichier shader mis en parametre
static char			*read_shader(const char *p_path)
{
	char *content = NULL;
	char *line = NULL;
	int fd = open(p_path, O_RDONLY);

	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strlen(content) != 0)
			ft_stradd(&content, "\n");
		ft_stradd(&content, line);
	}

	return (content);
}

static void compile_shader(GLuint p_ID, char const *p_source)
{
	GLint	result = GL_FALSE;

	// indique que est le code source du shader
	glShaderSource(p_ID, 1, &p_source , NULL);
	// compile le shader
	glCompileShader(p_ID);

	// recupere l'etat du shader ( le stock dans result)
	glGetShaderiv(p_ID, GL_COMPILE_STATUS, &result);
	if ( result != GL_TRUE)
		error_exit(-2, "Error while compiling shader");
}

static void compute_program(GLuint p_program_ID, GLuint p_vertex_shader_ID, GLuint p_fragment_shader_ID)
{
	GLint	result = GL_FALSE;

	// lie le vertex et le fragment shader
	glAttachShader(p_program_ID, p_vertex_shader_ID);
	glAttachShader(p_program_ID, p_fragment_shader_ID);

	// compile le programe
	glLinkProgram(p_program_ID);

	// recupere l'etat du programe (le stock dans result)
	glGetProgramiv(p_program_ID, GL_LINK_STATUS, &result);

	if ( result != GL_TRUE)
		error_exit(-3, "Error while computing shader program");

	// detache les shader du programme
	glDetachShader(p_program_ID, p_vertex_shader_ID);
	glDetachShader(p_program_ID, p_fragment_shader_ID);

	// delete les shader
	glDeleteShader(p_vertex_shader_ID);
	glDeleteShader(p_fragment_shader_ID);
}

GLuint				load_shaders(const char * p_vertex_file_path, const char * p_fragment_file_path)
{
	char *vertex_content = read_shader(p_vertex_file_path);
	char *fragment_content = read_shader(p_fragment_file_path);

	// creer l'emplacement memoire pour un shader
	GLuint vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);

	compile_shader(vertex_shader_ID, vertex_content);
	compile_shader(fragment_shader_ID, fragment_content);

	// creer l'emplacement memoire pour un programme
	GLuint program_ID = glCreateProgram();

	compute_program(program_ID, vertex_shader_ID, fragment_shader_ID);

	return (program_ID);
}
