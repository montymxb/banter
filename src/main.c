/*
//  main.c
//  Banter_Visualizer_C
//
//  Created by Benjamin Friedman on 10/18/18.
//  Copyright © 2018 Benjamin Friedman. All rights reserved.
*/

#include "libs.h"
#include "cli.h"

int main(int argc, char * argv[]) {

    /* TODO Pass cmdline args to the cli.cpp functions,
      these will return a 'banter_state' object, which will
      dictate later configurations we will be setting up.
      For the ids should add converters from char * to an
      id, and the ability to detect by ID (enum)
    */
    struct banter_state *state = cli_getstate_fromargs(argc, argv);

    /* set argc & argv */
    state->argc = argc;
    state->argv = argv;

    /* prepare our data object for reading */
    core_getdata_obj_withstate(state, state->data);

    /* start CLI loop */
    cli_ui_loop(state, state->data);


    if(state != NULL) {
      /* clear and free state */
      state_clear_state(state);
      free(state);
      state = NULL;

    }

    return 0;
}
