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


/* updates the banter state if new changes have been made
 * factors in things like stride, offset, scale, etc.
 * */
void core_update_banter_state(struct banter_state *state) {
  /* read one frame (for testing) */
  reader_get_data_frame(state, state->data);

  /* map this data */
  mapper_prepare_data(state, state->data);

  /* results are then passed to the outputter */
  outputter_forwarddata_withstate(state);

}
