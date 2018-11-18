#include "Shader.hpp"

char		*ReadShader(char* filename)
{
	char	buf[1000];
	char	*ret;
	FILE	*ptr;
	int		i;

	ret = (char*)calloc(1000, 1);
	ptr = fopen(filename, "r");

	if (!ptr){
		cout << "The file " << filename << " does not exist :(\n";
		exit(-1);
	}

	i = 0;
	while (fgets(buf, 999, ptr))
	{
		ret = (char*)realloc(ret, strlen(ret) + strlen(buf) + 1);
		strcpy(ret + i, buf);
		i += strlen(buf);
	}
	fclose(ptr);
	return (ret);
}

Shader::Shader(char* v, char* f){
	char* vertStr = ReadShader(v);
	char* fragStr = ReadShader(f);
	vert = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert, 1, &vertStr, NULL);
	glCompileShader(vert);
	int  tmp;
	char infoLog[512];
	glGetShaderiv(vert, GL_COMPILE_STATUS, &tmp);
	if(!tmp){
		glGetShaderInfoLog(vert, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		exit(-1);
	}
	unsigned int frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag, 1, &fragStr, NULL);
	glCompileShader(frag);
	glGetShaderiv(frag, GL_COMPILE_STATUS, &tmp);
	if(!tmp){
		glGetShaderInfoLog(frag, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAG::COMPILATION_FAILED\n" << infoLog << std::endl;
		exit(-1);
	}
	program = glCreateProgram();
	glAttachShader(program, vert);
	glAttachShader(program, frag);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &tmp);
	if(!tmp){
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROG::COMPILATION_FAILED\n" << infoLog << std::endl;
		exit(-1);
	}
	free(vertStr);
	free(fragStr);
	glDeleteShader(vert);
	glDeleteShader(frag); 
}

Shader::~Shader(){}