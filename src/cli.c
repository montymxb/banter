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
 * cli_assign_outmode
 *
 * Sets up the output mode for the cli, the default mode is to render directly
 */
void cli_assign_outmode(struct banter_state *state, char *mode) {
	if(strcmp(mode, "file") == 0) {
    /* file */
    state->out_mode = 1;

  } else if(strcmp(mode, "pipe") == 0) {
    /* process */
    state->out_mode = 2;

  } else if(strcmp(mode, "render") == 0) {
    /* process */
    state->out_mode = 0;

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
void cli_assign_outfile(struct banter_state *state, char *arg) {
	state->out_target = arg;
}


/* Assigns the CLI stride */
void cli_assign_stride(struct banter_state *state, char *arg) {
	/* TODO implement */
}

void cli_assign_coloring(struct banter_state *state, char *arg) {
	/* TODO implement */
}

void cli_assign_mapping(struct banter_state *state, char *arg) {
	/* TODO implement */
}

void cli_assign_offset(struct banter_state *state, char *arg) {
	/* TODO implement */
}

void cli_assign_scale(struct banter_state *state, char *arg) {
	/* TODO implement */
}


/**
 * cli_get_fresh_state
 *
 * Creates, intializes and returns a fresh banter state
 */
struct banter_state *cli_get_fresh_state() {
  struct banter_state *state = (struct banter_state *)malloc(sizeof(struct banter_state));

  // default input mode is file
  state->in_mode = 0;
  // no valid default input target to render from
  state->in_target = NULL;
  // no valid output target to write to by default
  state->out_target= NULL;
  // no default mapping id
  state->mapping_id = -1;
  // no default color id
  state->color_id = -1;
  // default stride of 1 byte
  state->stride = 1;
  // default offset of 0 bytes
  state->offset = 0;
  // default scale of 1 point:1 byte
  state->scale = 1;
  // default out mode for 'render'
  state->out_mode = 0;
  // no default mapping id
  state->output_mapping_id = -1;

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
      /* output mode, such as stdout/file */
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
      state->in_target = argv[++x];
      hasTarget = 1;

    } else if(hasTarget == 0) {
      /* implicit target */
      state->in_target = argv[x];
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

  /* TODO verify ALL required params are set before continuing */

  return state;

}
