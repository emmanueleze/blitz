#ifndef BLITZ_INCLUDE_BLITZ_E64GL_WINDOW_HPP
#define BLITZ_INCLUDE_BLITZ_E64GL_WINDOW_HPP

#include "e64gl.hpp"

namespace e64gl {

enum class Profile {
  Core = GLFW_OPENGL_CORE_PROFILE,
  Any = GLFW_OPENGL_ANY_PROFILE,
  Compat = GLFW_OPENGL_COMPAT_PROFILE
};

class Window {
public:
  Window();
  Window(GLuint _version_major = 3, GLuint _version_minor = 3);
  Window(GLuint _version_major = 3, GLuint _version_minor = 3,
         Profile _profile = Profile::Core);
  ~Window();

public:
  void setProfile(Profile _profile);
  void setVersion(GLuint _version_major, GLuint _version_minor);
  static int run(int argc, char *argv[]);

private:
  GLFWwindow *window;
  GLuint m_version_maj;
  GLuint m_version_min;
};
} // namespace stragl

#endif