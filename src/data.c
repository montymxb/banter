/**
 * data.h
 *
 * Holds the functionality for cleaning up data
 */

#include "data.h"

/* Used to clear existing data */
void data_clear_data(struct banter_data *data) {
	
	free(data->xLocations);
	free(data->yLocations);
	free(data->zLocations);
	
	free(data->rColors);
	free(data->gColors);
	free(data->bColors);
	
	free(data->og_data);
}