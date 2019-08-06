/**
 * mapper.c
 *
 * Handles mapping data for routing via the outputter
 */

#include "mapper.h"

/* default location mapper */
void mapper_default_location_mapping(struct banter_data *data) {
	long x;
	for(x = 0; x < data->count; x++) {
		data->xLocations[x] = data->og_data[x];
		data->yLocations[x] = data->og_data[x];
		data->zLocations[x] = x;
	}
}

/* default color mapper */
void mapper_default_color_mapping(struct banter_data *data) {
	long x;
	for(x = 0; x < data->count; x++) {
		data->rColors[x] = data->og_data[x] % 64;
		data->gColors[x] = data->og_data[x] % 128;
		data->bColors[x] = data->og_data[x];
	}
}

/**
 * mapper_prepare_data
 *
 * Prepares raw data with locations & colorings, ready for rendering
 */
void mapper_prepare_data(struct banter_state *state, struct banter_data *data) {
	int x;
	char matched = 0;

	/* TODO setup location & color data memory here */

	/* map locations */
	for(x = 0; x < state->location_mappings_count; x++) {
		if(strcmp(state->location_mappings[x].name, state->mapping_location_id) == 0) {
			(*(state->location_mappings[x].mapping_func))(data);
			matched = matched | 1;
			printf(">>>%d\n", matched);
		}
	}

	/* map colors */
	for(x = 0; x < state->color_mappings_count; x++) {
		if(strcmp(state->color_mappings[x].name, state->mapping_color_id) == 0) {
			(*(state->color_mappings[x].mapping_func))(data);
			matched = matched | 2;
			printf(">>>%d\n", matched);
		}
	}

	/* verify we matched everything */
	if(matched == 0) {
		error_report_with_message("Could not find color or location mapping to use");

	} else if(matched == 1) {
		error_report_with_message("Could not find color mapping to use");

	} else if(matched == 2) {
		error_report_with_message("Could not find location mapping to use");

	}
}
