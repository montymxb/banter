/**
 * reader.c
 *
 * Holds functionality for reading data from the given state into a data object
 */
 

#include "reader.h"

/* reader_get_data_frame
 *
 * If the data to be read is smaller than the provided stride size, the smaller actual read size
 * will be used instead of the stride.
 */
void reader_get_data_frame(struct banter_state *state, struct banter_data *data) {
    if(state->in_mode == 0) {
        /* from file */
        _reader_get_from_file(state, data);
        
    } else if(state->in_mode == 1) {
        /* from process */
        _reader_get_from_process(state, data);
        
    } else if(state->in_mode == 2) {
        /* from folder */
        _reader_get_from_folder(state, data);
        
    } else {
        /* unrecognized input mode */
        printf("\n[error] Unrecognized mode to read from, '%d'\n", state->in_mode);
        exit(1);
        
    }
}

/* read from file */
void _reader_get_from_file(struct banter_state *state, struct banter_data *data) {
	/* open file for reading */
	if(state->resource == NULL) {
		state->resource = fopen(state->in_target, "r");
	
		if(state->resource == NULL) {
			/* handle non-existant file */
			printf("\n[error] Could not find file to open, '%s'\n", state->in_target);
			exit(1);
		
		}
    }
    
    /* free existing data */
    free(data->og_data);
    
    /* setup new data at desired size */
    data->og_data = (char *)malloc(sizeof(char) * state->stride);
    
    /* Set offset position */
    if(fseek(state->resource, state->offset, SEEK_SET) != 0) {
    	/* Unable to seek, just mark we haven't read anything?? */
    	/* TODO handle this case... */
    }
    
    /* Read data, hold the count as well */
    data->count = fread(data->og_data, sizeof(char), state->stride, state->resource);
    
}

/* read from process */
void _reader_get_from_process(struct banter_state *state, struct banter_data *data) {
    /* TODO SETUP */
}

/* read from folder */
void _reader_get_from_folder(struct banter_state *state, struct banter_data *data) {
    /* TODO SETUP */
}
