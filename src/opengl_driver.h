/**
 * opengl_driver.h
 *
 * Driver for rendering via opengl
 */

#include "data.h"
#include "strings.h"
#include "state.h"

#ifdef __APPLE__
/* apple headers */
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else
/* unix headers */
#include <GL/gl.h>
#include <GL/glut.h>

#endif

/* holds OpenGL related state */
struct OpenGL_State {
  /* holds current window ref */
  GLint window;
  /* indicates current button pressed */
  int mouseButton;
  /* holds X & Y of mouse position, from pressing */
  int mouseX;
  int mouseY;
  /* scale & rotate for mouse operations */
  float rotateX;
  float rotateY;
  float scale;
  /* offset increment amount */
  int offsetStep;
  /* eye offsets */
  float eyeX;
  float eyeY;
  /* current draw mode */
  GLenum drawMode;
};

void opengl_driver_start(struct banter_state *state);
void opengl_driver_teardown();
