#include "blitz/blitz.hpp"
#include "blitz/e64gl/window.hpp"

e64gl::Window::Window() {}

e64gl::Window::Window(GLuint _version_major, GLuint _version_minor)
    : m_version_maj(_version_major), m_version_min(_version_minor) {

  // Initiallize GLFW and configure window with glfwWindowHint
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // Create window object
  window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
  // if (window == NULL) {
  //   std::cout << "Failed to create GLFW Window" << std::endl;
  //   glfwTerminate();
  //   return NULL;
  // }

  // make context of window the main context on the current thread.
  glfwMakeContextCurrent(window);
}

int e64gl::Window::run(int argc, char *argv[]) {
  auto window = e64gl::initialize_window();
  if (!window) {
    return -1;
  }
  int nrAttributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
  e64gl::render_loop(window);
  return 0;
}

GLFWwindow *e64gl::initialize_window() {

  // Initiallize GLFW and configure window with glfwWindowHint
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // Create window object
  GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW Window" << std::endl;
    glfwTerminate();
    return NULL;
  }

  // make context of window the main context on the current thread.
  glfwMakeContextCurrent(window);

  // Initialize GLAD to manage function pointers.
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return NULL;
  }

  glViewport(0, 0, 800, 600); //  tell opengl the size of the rendering window

  // register callback (e64gl::framebuffer_size_callback) to get called anytime
  // the window is resized to adjust the viewport.
  glfwSetFramebufferSizeCallback(window, e64gl::framebuffer_size_callback);

  return window;
}

void e64gl::framebuffer_size_callback(GLFWwindow *window, int width,
                                      int height) {
  // std::cout << "WIDTH: " << width<<";"<<"HEIGHT: "<<height<< std::endl;
  glViewport(0, 0, width, height);
}

void e64gl::render_loop(GLFWwindow *window) {

  // Input vertex data (normalized device coordinates)
  GLfloat vertices[] = {-0.5f, -0.5f, 0.0f, 
                        0.5f, -0.5f,  0.0f,
                        0.0f,  0.5f, 0.0f };

  const char *vertexShaderSource =
      "#version 330 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "out vec4 vertexColor;\n"
      "void main(){\n"
      "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "vertexColor = vec4(0.835f, 0.0f, 0.0, 1.0f);\n"
      "}\n\0";

  const char *fragmentShaderSource = "#version 330 core\n"
                                     "out vec4 FragColor;\n"
                                     "in vec4 vertexColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "FragColor = vertexColor;\n"
                                     "}\n\0";

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // Create the shader
  // Attach source code to the shader object and compile it
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);

  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  GLuint VAO, VBO;

  glGenVertexArrays(1, &VAO);

  // Create memory to store vertex data
  glGenBuffers(1, &VBO);
  //  Bind newly created buffer to the GL_ARRAY_BUFFER target
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBindVertexArray(VAO);
  // Copies the previously defined vertex data into the currently bound buffer
  // memory
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // Render loop
  while (!glfwWindowShouldClose(window)) {

    process_input(window);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat timeValue = glfwGetTime();
    GLfloat greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    GLint vertexLocation = glGetUniformLocation(shaderProgram, "ourC0olor");
    glUseProgram(shaderProgram);
    glUniform4f(vertexLocation, 0.0f, greenValue, 0.0f, 1.0f);
    glBindVertexArray(VAO);
    //  Hint what kind of render types to be formed with the data
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window); //  swap the buffers
    glfwPollEvents();        // checks if any events are triggered
  }
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);

  glfwDestroyWindow(window);
  // Terminate GLFW to free up allocated resources
  glfwTerminate();
}

void e64gl::process_input(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void e64gl::transient_green_triangle(GLuint program, const char *str) {
  GLfloat timeValue = glfwGetTime();
  GLfloat greenValue = (cos(timeValue - 8) / 8.0f) + 5.5f;
  GLint vertexLocation = glGetUniformLocation(program, str);
  glUseProgram(program);
  glUniform4f(vertexLocation, 0.0f, greenValue, 0.0f, 1.0f);
}

int e64gl::windowing() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  auto window = glfwCreateWindow(0,0, "OpenGLX", NULL, NULL);
  if(window == NULL){
    perror("Unable to create window");
    glfwTerminate();
  }

  glfwMakeContextCurrent(window);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
      perror("Failed to init glad");
      exit(1);
    }

  while(!glfwWindowShouldClose(window)){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwPollEvents();
    glfwSwapBuffers(window);
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
