/**
 * state.c
 *
 * Holds state teardown functionality
 */
 
#include "state.h"

void state_clear_state(struct banter_state *state) {
	if(state->resource != NULL) {
		fclose(state->resource);
	}
}
