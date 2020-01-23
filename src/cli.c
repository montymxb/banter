/**
 * cli.c
 *
 * Holds functionality for parsing cmdline args into
 * a workable struct
 */

#include "cli.h"


/**
 * cli_assign_inmode
 *
 * Attempts to assign the appropriate input mode to the state
 */
void cli_assign_inmode(struct banter_state *state, char *mode) {
  if(strcmp(mode, "file") == 0) {
    /* file */
    state->in_mode = 0;

  } else if(strcmp(mode, "process") == 0) {
    /* process */
    state->in_mode = 1;

  } else if(strcmp(mode, "dir") == 0) {
    /* directory */
    state->in_mode = 2;

  } else {
    /* unrecognized state, return an error */
    printf("Unrecognized input mode of '%s' provided!\n", mode);
    exit(1);

  }
}


/**
 * cli_assign_target
 *
 * Assigns a new target to the current state
 */
void cli_assign_target(struct banter_state *state, char *target) {
  if(strlen(target) < BANTER_TARGET_SIZE) {
    strncpy(state->in_target, target, strlen(target));

  } else {
    error_report_with_message("target exceeds allotted size");

  }
}


/**
 * cli_assign_outmode
 *
 * Sets up the output mode for the cli, the default mode is to render directly
 */
void cli_assign_outmode(struct banter_state *state, char *mode) {
	if(strcmp(mode, "stdout") == 0) {
    /* stdout */
    state->out_mode = 1;

  } else if(strcmp(mode, "stream") == 0) {
    /* stream */
    state->out_mode = 2;

  } else if(strcmp(mode, "render") == 0) {
    /* process */
    state->out_mode = 0;

    /* setup the current renderer */
    #ifdef _WIN32
    /* setup for Windows */

    #else
    /* setup for Unix */
    state->renderer.start     = opengl_driver_start;
    state->renderer.teardown  = opengl_driver_teardown;
    #endif

  } else {
    /* unrecognized state, return an error */
    printf("Unrecognized out mode of '%s' provided!\n", mode);
    exit(1);

  }
}


/**
 * cli_assign_outfile
 *
 * Assigns a file to write out to (only used when the output mode is to file)
 */
void cli_assign_outfile(struct banter_state *state, char *target) {
	if(strlen(target) < BANTER_OUT_TARGET_SIZE) {
    strncpy(state->out_target, target, strlen(target));

  } else {
    error_report_with_message("out target exceeds allotted size");

  }
}


/* Assigns the CLI stride */
void cli_assign_stride(struct banter_state *state, char *arg) {
	state->stride = atoi(arg);
	if(state->stride < 0) {
		printf("\n[error] Cannot set a stride less than 0!\n");
		exit(1);

	}

}


/* Assigns the CLI coloring */
void cli_assign_coloring(struct banter_state *state, char *arg) {
	if(strlen(arg) < BANTER_COLOR_ID_SIZE) {
    strncpy(state->mapping_color_id, arg, strlen(arg));

  } else {
    error_report_with_message("unable to assign color id of too long size");

  }
}


/* Assigns the CLI mapping */
void cli_assign_mapping(struct banter_state *state, char *arg) {
  if(strlen(arg) < BANTER_MAPPING_ID_SIZE) {
    strncpy(state->mapping_location_id, arg, strlen(arg));

  } else {
    error_report_with_message("unable to assign mapping of too long size");

  }
}


/* Assigns the CLI offset */
void cli_assign_offset(struct banter_state *state, char *arg) {
	state->offset = atoi(arg);
	if(state->offset < 0) {
		printf("\n[error] Cannot set an offset less than 0!\n");
		state->offset = 0;

	}
}


void cli_assign_scale(struct banter_state *state, char *arg) {
	state->scale = atoi(arg);
	if(state->scale < 0) {
		printf("\n[error] Cannot set a scale less than 0!\n");
		exit(1);

	}
}


/**
 * cli_get_fresh_state
 *
 * Creates, intializes and returns a fresh banter state
 */
struct banter_state *cli_get_fresh_state() {
  struct banter_state *state = (struct banter_state *)malloc(sizeof(struct banter_state));

  /* default input mode is file */
  state->in_mode = 0;
  /* no valid default input target to render from */
  state->in_target[0] = '\0';
  /* set default resource of NULL (no file) */
  state->resource = NULL;
  /* no valid output target to write to by default */
  state->out_target[0] = '\0';
  /* default mapping id */
  strcpy(state->mapping_location_id, LOC_MAP_CUBE);
  /* default color id */
  strcpy(state->mapping_color_id, COL_MAP_3D_VALUE);
  /* default stride of 1 byte */
  state->stride = 1;
  /* default offset of 0 bytes */
  state->offset = 0;
  /* default scale of 1 point:1 byte */
  state->scale = 1;
  /* set defaults for renderer, which will be set if used */
  state->renderer.is_ready = 0;
  cli_assign_outmode(state, "render");

  /* setup location mapping for defaults */
  state->location_mappings_count = MAPPINGS_COUNT;
  int index = 0;
  state_add_location_mapping(index++, LOC_MAP_EXTRUDE_Z, &mapper_extrude_z_location_mapping, state);
  state_add_location_mapping(index++, LOC_MAP_SPHERICAL_2D, &mapper_spherical_2d_location_mapping, state);
  state_add_location_mapping(index++, LOC_MAP_SPHERICAL_3D, &mapper_spherical_3d_location_mapping, state);
  state_add_location_mapping(index++, LOC_MAP_CUBE, &mapper_cube_location_mapping, state);
  state_add_location_mapping(index++, LOC_MAP_CUBE_4D, &mapper_cube_4d_location_mapping, state);
  state_add_location_mapping(index++, LOC_MAP_SPHERICAL_SHELLS, &mapper_spherical_shells_location_mapping, state);
  state_add_location_mapping(index++, LOC_CHAIN, &mapper_chain_location_mapping, state);
  state_add_location_mapping(index++, LOC_HILBERT_2D, &mapper_hilbert_curve_2d_location_mapping, state);
  state_add_location_mapping(index++, LOC_HILBERT_3D, &mapper_hilbert_curve_3d_location_mapping, state);

  /* setup color mapping for defaults */
  state->color_mappings_count = COLORINGS_COUNT;
  index = 0;
  state_add_color_mapping(index++, COL_MAP_VALUE, &mapper_value_color_mapping, state);
  state_add_color_mapping(index++, COL_MAP_3D_VALUE, &mapper_3d_value_color_mapping, state);
  state_add_color_mapping(index++, COL_MAP_POSITIONAL, &mapper_positional_color_mapping, state);
  state_add_color_mapping(index++, COL_MAP_ENTROPY, &mapper_entropy_color_mapping, state);

  /* generate fresh data */
  state->data = (struct banter_data*)malloc(sizeof(struct banter_data));

  return state;

}

/**
 * cli_print_usage_info
 *
 * Prints the usage info for banter
 */
void cli_print_usage_info() {
	printf("\nbanter ([--target file.txt/folder/PID/program_name] OR [file.txt/folder/PID/program_name]) [--mode file/folder/memory] [--outmode stdout/file] [--output out.txt] [--loaddatamaps dm.csv] [--loadcolormaps cm.csv] [--datamap polar] [--colormap byorder] [--stride 1000] [--offset 0] [--scale 2]\n\n");
	printf("--target <explicit target program/file/folder to analyze>\n");
	printf("--mode <read from, file/folder/memory>\n");
	printf("--outmode <stdout/file, default is none and results are rendered directly>\n");
	printf("--output <name of file to write results out to when --outmode is 'file'>\n");
	printf("--loaddatamaps <csv of data mapping file to load>\n");
	printf("--loadcolormaps <csv of data mapping file to load>\n");
	printf("--datamap <name of data mapping to use for rendering>\n");
	printf("--colormap <name of color mapping to use for rendering>\n");
	printf("--stride <# of bytes to show in each viewing pane>\n");
	printf("--offset <offset in bytes to start reading from>\n");
	printf("--scale <ratio of bytes used per point calculated, zoom>\n");
	printf("\n");

}


/**
 * cli_verify_state
 *
 * Verifies the given banter state
 */
void cli_verify_state(struct banter_state *state) {
  if(state->in_mode == -1) {
    printf("State missing an input mode!\n");
    exit(1);
    /* TODO ACTUALLY ADD IN PROPER ERROR HANDLING, AND FINISH/ADD THIS */
  }
}


/* Returns a banter state struct from given args */
struct banter_state *cli_getstate_fromargs(int argc, char *argv[]) {
  int x;
  /* get key/value pairs for each arg, or ERROR out */
  int hasTarget = 0;
  /* retrieve a fresh state */
  struct banter_state *state = cli_get_fresh_state();

  for(x = 1; x < argc; x++) {
    if(strcmp(argv[x], "--mode") == 0 && x < argc-1) {
      /* mode */
      cli_assign_inmode(state, argv[++x]);

    } else if(strcmp(argv[x], "--outmode") == 0 && x < argc-1) {
      /* output mode, such as renderer/stdout/stream */
      cli_assign_outmode(state, argv[++x]);

    } else if(strcmp(argv[x], "--output") == 0 && x < argc-1) {
      /* name of output file, if out mode is 'file' */
      cli_assign_outfile(state, argv[++x]);

    } else if(strcmp(argv[x], "--loaddatamaps") == 0 && x < argc-1) {
      /* location of csv for data mappings to load */
      /* TODO SET THIS UP */

    } else if(strcmp(argv[x], "--loadcolormaps") == 0 && x < argc-1) {
      /* location of csv for color mappings to load */
      /* TODO SET THIS UP */

    } else if(strcmp(argv[x], "--datamap") == 0 && x < argc-1) {
      /* data mapping to use by keyword */
      cli_assign_mapping(state, argv[++x]);

    } else if(strcmp(argv[x], "--colormap") == 0 && x < argc-1) {
      /* color mapping to use by keyword */
      cli_assign_coloring(state, argv[++x]);

    } else if(strcmp(argv[x], "--stride") == 0 && x < argc-1) {
      /* # of bytes to show in each viewing pane */
      cli_assign_stride(state, argv[++x]);

    } else if(strcmp(argv[x], "--offset") == 0 && x < argc-1) {
      /* offset to start reading from */
      cli_assign_offset(state, argv[++x]);

    } else if(strcmp(argv[x], "--scale") == 0 && x < argc-1) {
      /* ratio of bytes used per point calculated */
      cli_assign_scale(state, argv[++x]);

    } else if(strcmp(argv[x], "--target") == 0 && x < argc-1) {
      /* explicit target */
      cli_assign_target(state, argv[++x]);
      hasTarget = 1;

    } else if(hasTarget == 0) {
      /* implicit target */
      cli_assign_target(state, argv[x]);
      hasTarget = 1;

    } else {
      /* not a valid command line arg! */
      printf("Unrecognized command line argument '%s'!\n", argv[x]);
      exit(1);

    }
  }

  if(argc == 1) {
  	/* no arguments, print usage info */
  	cli_print_usage_info();

  }

  return state;

}


/* CLI user interface loop */
void cli_ui_loop(struct banter_state *state, struct banter_data *data) {

    int result;
    char input[255];

    for(;;) {

        /*
        // TODO next steps
        //  -
        // 1. read a frame (or skip if no change in reading position)
        //  - exception being if we should be updating for every frame (i.e realtime analysis)
        // 2. prepare that frame into x & y coordinate axes and colors via MAPPER
        // 3. send that data to the OUTPUTTER
        // 4. outputter will present that data out to a given medium, such as the RENDERER, which will use the underlying graphics API to prepare the data
        */

        /* read one frame (for testing) */
        reader_get_data_frame(state, data);

        /* map this data */
        mapper_prepare_data(state, data);

        /* results are then passed to the outputter */
        outputter_forwarddata_withstate(state);

        /* TODO output for viewing, just to make sure it's all okay */
        printf("\n(%d)>>>%s\n",data->count, data->og_data);

        result = scanf(" %[^\n]", input);

        /* Check for EOF */
        if(result == EOF) {
            break;
        }

        /* Eat up any leftovers */
        /* result = scanf("%*c"); */

        /* Check for EOF again */
        /*
        //if(result == EOF) {
        //    break;
        //}
        */

        /*
        // recognized commands
        //	- read forward by amount (+100)
        //	- read back by amount (-98)
        //	- change stride (*2)
        //	- change scale (@50)
        //	- change mode (invalidates current target if done...) (mDESIRED_MODE_NAME)
        //	- change target (must match current mode) (tNEW_TARGET)
        //	- change mapping (pNEW_MAPPING)
        //	- change coloring (cNEW_COLORING)
        */

        if(input[0] == '+' || input[0] == '-') {
            /* read forward/backward an amount (offset) */
            state->offset+=atoi(input);
            if(state->offset < 0) {
                /* never go below zero for offset */
                state->offset = 0;
            }
            printf("~ offset is %d\n", state->offset);

        } else if(input[0] == '*') {
            /* change stride */
            cli_assign_stride(state, (&input)+1);
            printf("~ stride is %d\n", state->stride);

        } else if(input[0] == '@') {
            /* change scale */
            cli_assign_scale(state, (&input)+1);
            printf("~ scale is %d\n", state->scale);

        } else if(input[0] == 'm') {
            /* new mode */
            cli_assign_inmode(state, (&input)+1);
            printf("~ input mode is %d\n", state->in_mode);

        } else if(input[0] == 't') {
            /* new target */
            cli_assign_target(state, (&input)+1);
            printf("~ target is '%s'\n", state->in_target);

        } else if(input[0] == 'p') {
            /* new mapping */
            cli_assign_mapping(state, (&input)+1);
            printf("~ mapping is '%s'\n", state->mapping_location_id);

        } else if(input[0] == 'c') {
            /* new coloring */
            cli_assign_coloring(state, (&input)+1);
            printf("~ coloring is '%s'\n", state->mapping_color_id);

        } else if(input[0] == 'q') {
            /* quit, exit the program */
            printf("~ quitting\n");
            break;

        } else {
            /* unrecognized command */
            printf("[error] Unrecognized command sequence '%s'\n", input);

        }

    }
}
