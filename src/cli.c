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
    printf("Unrecognized mode of '%s' provided!\n", mode);
    exit(1);

  }
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

void cli_assign_outfile(struct banter_state *state, char *arg) {
	/* TODO implement */
}

void cli_assign_outmode(struct banter_state *state, char *arg) {
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

  state->in_mode = -1;
  state->in_target = NULL;
  state->mapping_id = -1;
  state->color_id = -1;
  state->stride = -1;
  state->offset = -1;
  state->scale = -1;
  state->out_mode = -1;
  state->output_mapping_id = -1;

  return state;

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
      cli_assign_inmode(state, argv[x+1]);

    } else if(strcmp(argv[x], "--outmode") == 0 && x < argc-1) {
      /* output mode, such as stdout/file */
      cli_assign_outmode(state, argv[x+1]);

    } else if(strcmp(argv[x], "--output") == 0 && x < argc-1) {
      /* name of output file, if out mode is 'file' */
      cli_assign_outfile(state, argv[x+1]);

    } else if(strcmp(argv[x], "--loadmaps") == 0 && x < argc-1) {
      /* location of csv for mappings to load */
      /* TODO SET THIS UP */

    } else if(strcmp(argv[x], "--map") == 0 && x < argc-1) {
      /* mapping to use by keyword */
      cli_assign_mapping(state, argv[x+1]);

    } else if(strcmp(argv[x], "--color") == 0 && x < argc-1) {
      /* coloring to use by keyword */
      cli_assign_coloring(state, argv[x+1]);

    } else if(strcmp(argv[x], "--stride") == 0 && x < argc-1) {
      /* # of bytes to show in each viewing pane */
      cli_assign_stride(state, argv[x+1]);

    } else if(strcmp(argv[x], "--offset") == 0 && x < argc-1) {
      /* offset to start reading from */
      cli_assign_offset(state, argv[x+1]);

    } else if(strcmp(argv[x], "--scale") == 0 && x < argc-1) {
      /* ratio of bytes used per point calculated */
      cli_assign_scale(state, argv[x+1]);

    } else if(strcmp(argv[x], "--target") == 0 && x < argc-1) {
      /* explicit target */
      state->in_target = argv[x+1];
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

  /* TODO verify ALL required params are set before continuing */

  return state;

}
