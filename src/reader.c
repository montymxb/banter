/**
 * reader.c
 *
 * Holds functionality for reading data from the given state into a data object
 */

/* reader_get_data_frame
 *
 * If the data to be read is smaller than the provided stride size, the smaller actual read size
 * will be used instead of the stride.
 */
void reader_get_data_frame(struct banter_state *state, struct banter_data *data) {
    if(state->in_mode == 0) {
        /* from file */
        
        
    } else if(state->in_mode == 1) {
        /* from process */
        
        
    } else if(state->in_mode == 2) {
        /* from folder */
        
        
    } else {
        /* unrecognized input mode */
        printf("\n[error] Unrecognized mode to read from, '%d'\n", state->in_mode);
        exit(1);
        
    }
}

/* read from file */
void _reader_get_from_file(struct banter_state *state, struct banter_data *data) {
    FILE *handle = fopen(state->in_target, "r");
    
    // todo continue from here...
    
}

/* read from process */
void _reader_get_from_process(struct banter_state *state, struct banter_data *data) {
    /* TODO SETUP */
}

/* read from folder */
void _reader_get_from_folder(struct banter_state *state, struct banter_data *data) {
    /* TODO SETUP */
}
