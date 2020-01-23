/**
 * opengl_driver.c
 *
 */

#include "opengl_driver.h"

/* opengl state */
struct OpenGL_State opengl_state;

/* local holding for the banter state w/ opengl */
struct banter_state *opengl_banter_state;


void _opengl_driver_mac_setup_state();


/* TODO demonstrative... */
void
output(char *text)
{
  char *p;
  for (p = text; *p; p++)
    glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
}


/* display for mac */
void _opengl_driver_mac_display() {
	/* TODO setup */
	static GLfloat amb[] =
  {0.4, 0.4, 0.4, 0.0};
  static GLfloat dif[] =
  {1.0, 1.0, 1.0, 0.0};

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective( /* field of view in degree */ 90.0,
  /* aspect ratio */ 1.0,
    /* Z near */ 0.1, /* Z far */ 1000.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(
    -10.0, 0.0, 0.0,  /* eye */
    0.0, 0.0, 0.0,   /* center */
    0.0, 1.0, 0.    /* up is in positive Y direction */
  );

  glTranslatef(0.0, opengl_state.eyeY, opengl_state.eyeX);

  glRotatef( (GLfloat)opengl_state.rotateY, 0., 1., 0. );
  glRotatef( (GLfloat)opengl_state.rotateX, 1., 0., 0. );

  //if( Scale < MINSCALE )
  //    Scale = MINSCALE;
  glScalef( (GLfloat)opengl_state.scale, (GLfloat)opengl_state.scale, (GLfloat)opengl_state.scale);

  // TODO lighting may be unnecessary...
  GLfloat light0_ambient[] =
  {0.2, 0.2, 0.2, 1.0};
  GLfloat light0_diffuse[] =
  {0.0, 0.0, 0.0, 1.0};
  /*
  GLfloat light1_diffuse[] =
  {1.0, 0.0, 0.0, 1.0};
  GLfloat light1_position[] =
  {1.0, 1.0, 1.0, 0.0};
  GLfloat light2_diffuse[] =
  {0.0, 1.0, 0.0, 1.0};
  GLfloat light2_position[] =
  {-1.0, -1.0, 1.0, 0.0};
  float s = 0.0;
  GLfloat angle1 = 0.0, angle2 = 0.0;
*/
/*
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
  */
  /*
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
  glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
  glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
  */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_LINE_SMOOTH);
  glLineWidth(2.0);
  /*
*/
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  /*
  glEnable(GL_LIGHT1);
  glDisable(GL_LIGHT2);
  amb[3] = dif[3] = cos(s) / 2.0 + 0.5;
  glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);

  glPushMatrix();
  glTranslatef(-0.3, -0.3, 0.0);
  glRotatef(angle1, 1.0, 5.0, 0.0);
  glutSolidIcosahedron();
  */        /* render ico display list */
  /*
  glPopMatrix();

  glClear(GL_DEPTH_BUFFER_BIT);
  glEnable(GL_LIGHT2);
  glDisable(GL_LIGHT1);
  amb[3] = dif[3] = 0.5 - cos(s * .95) / 2.0;
  glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);

  glPushMatrix();
  glTranslatef(0.3, 0.3, 0.0);
  glRotatef(angle2, 1.0, 0.0, 5.0);
  glutSolidIcosahedron();
  */        /* render ico display list */
  /*glPopMatrix(); */
  glPushMatrix();
  glScalef(0.05, 0.05, 0.05);
  glBegin(opengl_state.drawMode);
  for(int x = 0; x < opengl_banter_state->data->count; x++) {
    glColor3f(
      opengl_banter_state->data->rColors[x],
      opengl_banter_state->data->gColors[x],
      opengl_banter_state->data->bColors[x]
    );

    //xLocations
    glVertex3f(
      opengl_banter_state->data->xLocations[x],
      opengl_banter_state->data->yLocations[x],
      opengl_banter_state->data->zLocations[x]
    );
  }
  glEnd();

  /* Draw Axis for debugging */
  glBegin(GL_LINES);
  /* along x */
  glColor3f(1,0,0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(10.0, 0.0, 0.0);
  /* along y */
  glColor3f(0,1,0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, 10.0, 0.0);
  /* along z */
  glColor3f(0,0,1);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, 0.0, 10.0);
  glEnd();


  /* draw summary info text */
  glColor3f(1,1,1);
  glPushAttrib(GL_ENABLE_BIT);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  int maxOrthoScreenSize = 5000;
  gluOrtho2D(0, maxOrthoScreenSize, 0, maxOrthoScreenSize); //1500
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  /* draw target */
  glPushMatrix();
  glTranslatef(50, 50, 0);
  char dtd[200] = {0};

  output(opengl_banter_state->in_target);

  /* draw total file size */
  // pos: 1000/100000 bytes
  sprintf(dtd, " pos: %d/%d \0", opengl_banter_state->offset, opengl_banter_state->data->resourceSize);
  output(dtd);

  /* draw offset */
  // offset step: 16
  sprintf(dtd, "step: %d \0", opengl_state.offsetStep);
  output(dtd);

  /* show scale (stride) */
  // scale: 1:1
  sprintf(dtd, "scale: %d:1 \0", opengl_banter_state->scale);
  output(dtd);

  glPopMatrix();

  /* draw position tracker */
  glPushMatrix();
  glLoadIdentity();

  glBegin(GL_LINES);
  glTranslatef(100, 300, 0);
  /* draw baseline */
  glVertex2f(100, 300);
  glVertex2f(100, maxOrthoScreenSize / 2 + 300);

  /* draw bottom cap */
  glVertex2f(50, 300);
  glVertex2f(150, 300);

  /* draw top cap */
  glVertex2f(50, maxOrthoScreenSize / 2 + 300);
  glVertex2f(150, maxOrthoScreenSize / 2 + 300);

  glEnd();

  /* draw (blue) tracking line */
  glColor3f(0,1,1);
  glBegin(GL_LINE_STRIP);
  glVertex2f(50, (maxOrthoScreenSize / 2) - (maxOrthoScreenSize / 2) * opengl_banter_state->offset / opengl_banter_state->data->resourceSize + 300);
  glVertex2f(150, (maxOrthoScreenSize / 2) - (maxOrthoScreenSize / 2) * opengl_banter_state->offset / opengl_banter_state->data->resourceSize + 300);
  glEnd();

  glPopMatrix();

  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glPopAttrib();
  glMatrixMode(GL_MODELVIEW);

  glutSwapBuffers();
}


/* idle func for mac opengl driver */
void _opengl_driver_mac_idle() {
	glutPostRedisplay();
}


/* opengl driver mac visible func */
void _opengl_driver_mac_visible(int visible) {
	if(visible == GLUT_VISIBLE) {
		/* set idle func */
		glutIdleFunc(_opengl_driver_mac_idle);
    glutSetWindow(opengl_state.window);
    glutPostRedisplay();

	} else {
		/* clear idle func */
		glutIdleFunc(NULL);

	}
}


/* Handles the user resizing the window */
void _opengl_driver_mac_reshape(int w, int h) {
  /* soft handle, window size will be rechecked in display */
  glutSetWindow(opengl_state.window);
  glutPostRedisplay();

}


/* Resets the renderer components */
void _opengl_driver_mac_reset() {
  _opengl_driver_mac_setup_state();
  /*opengl_banter_state->stride = 1000;*/
  opengl_banter_state->offset = 0;
  /* opengl_banter_state->scale = 1; */
}


/* Handles a keyboard key that has been pressed */
void _opengl_driver_mac_keyboard(unsigned char c, int x, int y) {

  switch(c) {
    case 'r':
      /* RESET */
      _opengl_driver_mac_reset();
      core_update_banter_state(opengl_banter_state);
      break;

    /* offset cases */
    case 'J':
    case 'j':
      /* pan offset backwards */
      if(opengl_banter_state->offset == 0) {
        /* do nothing */
        return;
      }

      opengl_banter_state->offset-=(opengl_state.offsetStep * opengl_banter_state->scale);

      if(opengl_banter_state->offset < 0) {
        opengl_banter_state->offset = 0;
      }

      core_update_banter_state(opengl_banter_state);
      break;

    case 'L':
    case 'l':
      /* pan offset forwards */
      if(opengl_banter_state->offset == opengl_banter_state->data->resourceSize - 1) {
        /* do nothing */
        return;
      }

      opengl_banter_state->offset+=(opengl_state.offsetStep * opengl_banter_state->scale);

      if(opengl_banter_state->offset > (opengl_banter_state->data->resourceSize - 1)) {
        opengl_banter_state->offset = opengl_banter_state->data->resourceSize - 1;
      }

      core_update_banter_state(opengl_banter_state);
      break;

    case '-':
      /* scale down */
      if(opengl_banter_state->scale > 1) {
        opengl_banter_state->scale/=2;
        core_update_banter_state(opengl_banter_state);
      }
      break;

    case '=':
    case '+':
      /* scale up */
      opengl_banter_state->scale*=2;
      core_update_banter_state(opengl_banter_state);
      break;

    /* shutdown cases */
    case 'q':
    case 'Q':
    /* escape keycode */
    case 0x1b:
      /* quit */
      opengl_driver_teardown();
      break;

    default:
      printf("got the key '%c' & %d %d\n", c, x, y);
      break;
  }
}


/* Called when mouse button changes, down/up */
void _opengl_driver_mac_mouse_button(int button, int state, int x, int y) {

  /* bit mask */
  int bCode = 0;

  switch(button) {
    case GLUT_LEFT_BUTTON:
      bCode = 1;
      break;

    case GLUT_MIDDLE_BUTTON:
      bCode = 2;
      break;

    default:
      bCode = 0;
      printf("Unknown mouse button pressed: %d\n", button);
  }

  if(state == GLUT_DOWN) {
    /* button down, set */
    opengl_state.mouseX = x;
    opengl_state.mouseY = y;
    opengl_state.mouseButton |= bCode;

  } else {
    /* button up, clear bit */
    opengl_state.mouseButton &= ~bCode;

  }
}


/* Called when the mouse moves */
void _opengl_driver_mac_mouse_motion(int x, int y) {
  // get change in x & y
  int dx = x - opengl_state.mouseX;
  int dy = y - opengl_state.mouseY;

  if((opengl_state.mouseButton & 1) != 0) {
    /* left button */
    opengl_state.rotateX += (dy * 1.0);
    opengl_state.rotateY += (dx * 1.0);

  }

  if((opengl_state.mouseButton & 2) != 0) {
    /* middle button */
    opengl_state.scale += (0.005f) * (dx - dy);

    /* keep above min */
    if(opengl_state.scale < 0.05f) {
      opengl_state.scale = 0.05f;
    }
  }

  /* update current position */
  opengl_state.mouseX = x;
  opengl_state.mouseY = y;

  glutSetWindow(opengl_state.window);
  glutPostRedisplay();

}


/* Handles special keys (like left/right/up/down) */
void _opengl_driver_mac_special(int key, int x, int y) {
  switch(key) {
    case GLUT_KEY_LEFT:
      opengl_state.eyeX--;
      break;
    case GLUT_KEY_RIGHT:
      opengl_state.eyeX++;
      break;
    case GLUT_KEY_DOWN:
      opengl_state.eyeY--;
      break;
    case GLUT_KEY_UP:
      opengl_state.eyeY++;
      break;
  }
}


/* Registers callbacks for opengl */
void _opengl_driver_mac_setup_callbacks() {
  // Complements of Prof. Mike Bailey @ OSU
  // DisplayFunc -- redraw the window
  // ReshapeFunc -- handle the user resizing the window
  // KeyboardFunc -- handle a keyboard input
  // MouseFunc -- handle the mouse button going down or up
  // MotionFunc -- handle the mouse moving with a button down
  // PassiveMotionFunc -- handle the mouse moving with a button up
  // VisibilityFunc -- handle a change in window visibility
  // EntryFunc	-- handle the cursor entering or leaving the window
  // SpecialFunc -- handle special keys on the keyboard
  // SpaceballMotionFunc -- handle spaceball translation
  // SpaceballRotateFunc -- handle spaceball rotation
  // SpaceballButtonFunc -- handle spaceball button hits
  // ButtonBoxFunc -- handle button box hits
  // DialsFunc -- handle dial rotations
  // TabletMotionFunc -- handle digitizing tablet motion
  // TabletButtonFunc -- handle digitizing tablet button hits
  // MenuStateFunc -- declare when a pop-up menu is in use
  // TimerFunc -- trigger something to happen a certain time from now
  // IdleFunc -- what to do when nothing else is going on

  /* callback funcs */
	glutDisplayFunc(_opengl_driver_mac_display);
  glutReshapeFunc(_opengl_driver_mac_reshape);
  glutKeyboardFunc(_opengl_driver_mac_keyboard);
  glutMouseFunc(_opengl_driver_mac_mouse_button);
  glutMotionFunc(_opengl_driver_mac_mouse_motion);
  glutPassiveMotionFunc( NULL );
  glutVisibilityFunc(_opengl_driver_mac_visible);
  glutEntryFunc( NULL );
  glutSpecialFunc(_opengl_driver_mac_special);
  glutSpaceballMotionFunc( NULL );
  glutSpaceballRotateFunc( NULL );
  glutSpaceballButtonFunc( NULL );
  glutButtonBoxFunc( NULL );
  glutDialsFunc( NULL );
  glutTabletMotionFunc( NULL );
  glutTabletButtonFunc( NULL );
  glutMenuStateFunc( NULL );
  glutTimerFunc( -1, NULL, 0 );
  glutIdleFunc(_opengl_driver_mac_idle);
}


/* test menu */
void _opengl_driver_mac_menu(int id) {

  switch(id) {
    case 0:
      /* QUIT */
      opengl_driver_teardown();
      break;

    default:
      printf("Unknown menu id of '%d'\n", id);
  }

  glutSetWindow(opengl_state.window);
	glutPostRedisplay();

}


/* Handles the offset being adjusted */
void _opengl_driver_mac_offset_menu(int id) {
  /* set the updated offset step */
  opengl_state.offsetStep = id;

  glutSetWindow(opengl_state.window);
	glutPostRedisplay();

}


/* changes the draw state of the program */
void _opengl_driver_mac_drawmode_menu(int id) {
  switch(id) {
    case 0:
      opengl_state.drawMode = GL_POINTS;
      break;
    case 1:
      opengl_state.drawMode = GL_LINES;
      break;
    case 2:
      opengl_state.drawMode = GL_LINE_STRIP;
      break;
    case 3:
      opengl_state.drawMode = GL_TRIANGLES;
      break;
    case 4:
      opengl_state.drawMode = GL_TRIANGLE_STRIP;
      break;
    case 5:
      opengl_state.drawMode = GL_POLYGON;
      break;
    default:
      printf("Unrecognized draw state entered '%d'\n", id);
  }
}


/* used for selecting the current location mapping */
void _opengl_driver_mac_locmap_menu(int id) {
  strcpy(
    opengl_banter_state->mapping_location_id,
    opengl_banter_state->location_mappings[id].name
  );

  core_update_banter_state(opengl_banter_state);

  glutSetWindow(opengl_state.window);
	glutPostRedisplay();
}


/* used for selecting the current color mapping */
void _opengl_driver_mac_colmap_menu(int id) {
  strcpy(
    opengl_banter_state->mapping_color_id,
    opengl_banter_state->color_mappings[id].name
  );

  core_update_banter_state(opengl_banter_state);

  glutSetWindow(opengl_state.window);
	glutPostRedisplay();
}


/* sets up various menus for mac */
void _opengl_driver_mac_setup_menus() {
  /* TODO setup actual menus */
  glutSetWindow(opengl_state.window);

  /* menu for selecting offsets */
  int offsetMenu = glutCreateMenu(_opengl_driver_mac_offset_menu);
  glutAddMenuEntry("1", 1);
  glutAddMenuEntry("2", 2);
  glutAddMenuEntry("4", 4);
  glutAddMenuEntry("8", 8);
  glutAddMenuEntry("16", 16);
  glutAddMenuEntry("32", 32);
  glutAddMenuEntry("64", 64);
  glutAddMenuEntry("128", 128);
  glutAddMenuEntry("256", 256);
  glutAddMenuEntry("512", 512);
  glutAddMenuEntry("1024", 1024);
  glutAddMenuEntry("2048", 2048);
  glutAddMenuEntry("4096", 4096);
  glutAddMenuEntry("8192", 8192);
  glutAddMenuEntry("16384", 16384);

  /* menu for selecting draw mode */
  int drawModeMenu = glutCreateMenu(_opengl_driver_mac_drawmode_menu);
  glutAddMenuEntry("Points", 0);
  glutAddMenuEntry("Lines", 1);
  glutAddMenuEntry("Line Strip", 2);
  glutAddMenuEntry("Triangles", 3);
  glutAddMenuEntry("Triangle Strip", 4);
  glutAddMenuEntry("Polygon", 5);

  /* menu for selecting location mapping */
  int locationMappingMenu = glutCreateMenu(_opengl_driver_mac_locmap_menu);
  for(int x = 0; x < opengl_banter_state->location_mappings_count; x++) {
    glutAddMenuEntry(opengl_banter_state->location_mappings[x].name, x);
  }

  /* menu for selecting color mapping */
  int colorMappingMenu = glutCreateMenu(_opengl_driver_mac_colmap_menu);
  for(x = 0; x < opengl_banter_state->color_mappings_count; x++) {
    glutAddMenuEntry(opengl_banter_state->color_mappings[x].name, x);
  }

  int mainMenu = glutCreateMenu(_opengl_driver_mac_menu);
  glutAddSubMenu("Step Size", offsetMenu);
  glutAddSubMenu("Draw Mode", drawModeMenu);
  glutAddSubMenu("Location Mapping", locationMappingMenu);
  glutAddSubMenu("Color Mapping", colorMappingMenu);
  glutAddMenuEntry("Quit", 0);

  // TODO setup sub menus later...
  //int mainmenu = glutCreateMenu();
  //glutAddSubMenu("Test Menu", testMenu);

  glutAttachMenu(GLUT_RIGHT_BUTTON);

}


/* sets up an initial state for rendering */
void _opengl_driver_mac_setup_state() {
  opengl_state.mouseButton = 0;
  opengl_state.mouseX     = 0;
  opengl_state.mouseY     = 0;
  opengl_state.rotateX    = 0.0;
  opengl_state.rotateY    = 0.0;
  opengl_state.scale      = 1.0;
  opengl_state.offsetStep = 1;
  /* set default eye position */
  opengl_state.eyeX = 0.0;
  opengl_state.eyeY = 0.0;
  /* set draw mode to points by default */
  opengl_state.drawMode = GL_POINTS;
}


/* opengl driver setup for mac */
void _opengl_driver_mac_setup() {

  _opengl_driver_mac_setup_state();

	/* init */
	glutInit(&(opengl_banter_state->argc), opengl_banter_state->argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  /* window size & position */
  glutInitWindowPosition(0,0);
  glutInitWindowSize(1200,1200);

	opengl_state.window = glutCreateWindow(BANTER_NAME);
  glutSetWindowTitle(BANTER_NAME);

  /* setup callbacks */
  _opengl_driver_mac_setup_callbacks();

  /* init glew (a window must be open to do this): */
  /* TODO properly shift this around as needed, likely into a WINDOWS driver */
#ifdef WIN32
	GLenum err = glewInit( );
	if( err != GLEW_OK )
	{
		fprintf( stderr, "glewInit Error\n" );
	}
	else
		fprintf( stderr, "GLEW initialized OK\n" );
	fprintf( stderr, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
#endif

  /* seup menus */
  _opengl_driver_mac_setup_menus();

  /* fire off the render thread from here */
  /* enters the GLUT event processing loop */
  /* does not return until done */
  glutSetWindow(opengl_state.window);
  glutMainLoop();

}

/* opengl setup */
void opengl_driver_start(struct banter_state *state) {

  /* hold the banter state */
  opengl_banter_state = state;

	_opengl_driver_mac_setup();
	/*
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	*/
}

/* opengl teardown */
void opengl_driver_teardown() {
  glutSetWindow(opengl_state.window);
  glFinish();
  glutDestroyWindow(opengl_state.window);

  /* TODO CLEANUP THE STATE */
  state_clear_state(opengl_banter_state);
  free(opengl_banter_state);
  opengl_banter_state = NULL;
  /* Will need to maintain a global state for this to work
  * but shouldn't be too bad...
  */
  exit(0);
}
