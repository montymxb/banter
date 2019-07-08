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
    
    // TODO next steps
    // 0. Initiate a loop where we can iteract via the cli
    //	- read forward by amount
    //	- read back by amount
    //	- change stride
    //	- change scale
    //	- change mode (invalidates current target if done...)
    //	- change target (must match current mode)
    //	- change mapping
    //	- change coloring
    //	- 
    // 1. read a frame (or skip if no change in reading position)
    //	- exception being if we should be updating for every frame (i.e realtime analysis)
    // 2. prepare that frame into x & y coordinate axes and colors via MAPPER
    // 3. send that data to the OUTPUTTER
    // 4. outputter will present that data out to a given medium, such as the RENDERER, which will use the underlying graphics API to prepare the data
    
    /* read one frame (for testing) */
    reader_get_data_frame(state, &data);
    /* results are then passed to the outputter */
    //outputter_writedata_withstate(&data, state);
    /* output for viewing, just to make sure it's all okay */
    printf("\n(%d)>>>%s\n",data.count, data.og_data);
    
    
    /* clear and free state */
    state_clear_state(state);
    free(state);
    state = NULL;
    
    /* clear data */
    data_clear_data(&data);

    return 0;
}
