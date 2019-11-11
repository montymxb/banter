/**
 * state.c
 *
 * Holds state teardown functionality
 */

#include "state.h"

void state_clear_state(struct banter_state *state) {

  /* clear data, associated with state */
  data_clear_data(&(state->data));

	if(state->resource != NULL) {
		fclose(state->resource);
    state->resource = NULL;
	}

  /* cleanup data as well */
  if(state->data != NULL) {
    free(state->data);
    state->data = NULL;

  }

  /* TODO causes infinite loop, as teardown is called from renderer anyways
	//if(state->renderer.is_ready == 1) {
	//	state->renderer.teardown();
	//}
  */
}

/* attempts to add a location mapping */
void state_add_location_mapping(int index, char *name, void (*mapping_func)(struct banter_data *), struct banter_state *state) {

  if(index > state->location_mappings_count) {
    printf("[error] Attempted to add location mapping at %d beyond preset limit of %d mappings\n", index, state->location_mappings_count);
    exit(1);

  }

  strcpy(state->location_mappings[index].name, name);
  state->location_mappings[index].mapping_func = mapping_func;
}


/* attempts to add a color mapping */
void state_add_color_mapping(int index, char *name, void (*mapping_func)(struct banter_data *), struct banter_state *state) {

  if(index > state->color_mappings_count) {
    printf("[error] Attempted to add color mapping at %d beyond preset limit of %d mappings\n", index, state->location_mappings_count);
    exit(1);

  }

  strcpy(state->color_mappings[index].name, name);
  state->color_mappings[index].mapping_func = mapping_func;
}
