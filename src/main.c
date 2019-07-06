/*
//  main.c
//  Banter_Visualizer_C
//
//  Created by Benjamin Friedman on 10/18/18.
//  Copyright © 2018 Benjamin Friedman. All rights reserved.
*/

#include "libs.h"
#include "cli.h"
#include "data.h"
#include "core.h"
#include "outputter.h"

int main(int argc, char * argv[]) {

    /* TODO Pass cmdline args to the cli.cpp functions,
      these will return a 'banter_state' object, which will
      dictate later configurations we will be setting up.
      For the ids should add converters from char * to an
      id, and the ability to detect by ID (enum)
    */
    struct banter_state *state = cli_getstate_fromargs(argc, argv);
    
    /* construct banter data object */
    struct banter_data data;

    /* prepare our data object for reading */
    core_getdata_obj_withstate(state, &data);
    
    /* read one frame (for testing) */
    reader_get_data_frame(state, &data);

    /* results are then passed to the outputter */
    //outputter_writedata_withstate(&data, state);
    
    /* output for viewing, just to make sure it's all okay */
    // printf
    
    /* clear state */
    free(state);
    state = NULL;

    return 0;
}
