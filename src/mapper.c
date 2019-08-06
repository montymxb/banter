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

	/* if last count is less than current count (and not zero), reallocate */
	if(data->last_count > 0 && data->last_count < data->count) {
		/* free all */
		free(data->xLocations);
		free(data->yLocations);
		free(data->zLocations);
		free(data->rColors);
		free(data->gColors);
		free(data->bColors);

		/* so next if catches to allocate */
		data->xLocations = NULL;

	}

	/* if pointers are null, setup for the first time, adjust last count */
	if(data->xLocations == NULL) {
		data->xLocations = (double *)malloc(sizeof(double) * data->count);
		data->yLocations = (double *)malloc(sizeof(double) * data->count);
		data->zLocations = (double *)malloc(sizeof(double) * data->count);

		data->rColors = (double *)malloc(sizeof(double) * data->count);
		data->gColors = (double *)malloc(sizeof(double) * data->count);
		data->bColors = (double *)malloc(sizeof(double) * data->count);

		data->last_count = data->count;

	}

	/* map locations */
	for(x = 0; x < state->location_mappings_count; x++) {
		if(strcmp(state->location_mappings[x].name, state->mapping_location_id) == 0) {
			(*(state->location_mappings[x].mapping_func))(data);
			matched = matched | 1;
		}
	}

	/* map colors */
	for(x = 0; x < state->color_mappings_count; x++) {
		if(strcmp(state->color_mappings[x].name, state->mapping_color_id) == 0) {
			(*(state->color_mappings[x].mapping_func))(data);
			matched = matched | 2;
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
