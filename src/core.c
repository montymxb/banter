/**
 * core.c
 *
 * Holds the core components of banter
 */

#include "core.h"

/* Modifies a data object for the current state */
void core_getdata_obj_withstate(struct banter_state *state, struct banter_data *data) {
    
    /* set the count of elements (equal to stride) */
    data->count         = state->stride;
    data->last_count    = 0;
    
    /* clear pointers */
    data->xLocations = NULL;
    data->yLocations = NULL;
    data->zLocations = NULL;
    data->rColors    = NULL;
    data->gColors    = NULL;
    data->bColors    = NULL;
    data->og_data    = NULL;
    
}
