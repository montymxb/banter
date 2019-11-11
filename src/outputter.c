/**
 * outputter.c
 *
 * Key components for writing out data to the visualizer
 */

#include "outputter.h"

/* Returns a data object for the current state */
void outputter_forwarddata_withstate(struct banter_state *state) {
	/* check the output mode */
	if(state->out_mode == 0) {
		/* send data to the renderer */
		if(state->renderer.is_ready != 1) {
			/* if not at state #1, start rendering from here on out */
			state->renderer.is_ready = 1;
			/* Will NOT return at this point... */
			state->renderer.start(state);

		}

		/* render data */
		/* TODO remove... */
		/* state->renderer.render(data); */

	} else if(state->out_mode == 1) {
		/* stdout */
		/* TODO implement stdout */
		error_report_with_message("'stdout' mode is currently not implemented");

	} else if(state->out_mode == 2) {
		/* stream (file,pipe,socket,etc.) */
		/* TODO implement stream */
		error_report_with_message("'stream' mode is currently not implemented");

	}
}
