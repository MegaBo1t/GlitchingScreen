#pragma once

class Shaders
{
public:
  unsigned int program;

  void shaderCreate(const char* Vsource, const char* Fsource)
  {
    int success;
    char log[512];

    unsigned int Vshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(Vshader, 1, &Vsource, NULL);
    glCompileShader(Vshader);

    glGetShaderiv(Vshader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(Vshader, 512, NULL, log);
      std::cout << "Vertex shader compilation fail:" << log << '\n';
    }

    unsigned int Fshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(Fshader, 1, &Fsource, NULL);
    glCompileShader(Fshader);

    glGetShaderiv(Fshader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(Fshader, 512, NULL, log);
      std::cout << "Frag shader compilation fail:" << log << '\n';
    }

    program = glCreateProgram();
    glAttachShader(program, Vshader);
    glAttachShader(program, Fshader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
      glGetProgramInfoLog(program, 512, NULL, log);
      std::cout << "Linking shaders failed:" << log << '\n';
      return;
    }

    glDeleteShader(Vshader);
    glDeleteShader(Fshader);
  }

  void useProgram()
  {
    glUseProgram(program);
  }
};
