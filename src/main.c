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

int main(int argc, char * argv[]) {

    /* TODO Pass cmdline args to the cli.cpp functions,
    these will return a 'banter_state' object, which will
    dictate later configurations we will be setting up.
    For the ids should add converters from char * to an
    id, and the ability to detect by ID (enum)
     */
     struct banter_state *state = cli_getstate_fromargs(argc, argv);

     /* pass the state to the core, which will control
     how the reader & mapper are interacted with */
     struct banter_data *data = core_getdata_withstate(state);

     /* results are then passed to the outputter */
     outputter_writedata_withstate(data, state);

    return 0;
}
