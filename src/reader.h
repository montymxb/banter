/**
 * reader.h
 *
 * Holds functionality for reading data from the given state into a data object
 */

#ifndef __READER__H_
#define __READER__H_

#include "libs.h"
#include "state.h"
#include "data.h"

/* Reads one frame of data */
void reader_get_data_frame(struct banter_state *state, struct banter_data *data);

/* read from file */
void _reader_get_from_file(struct banter_state *state, struct banter_data *data);

/* read from process */
void _reader_get_from_process(struct banter_state *state, struct banter_data *data);

/* read from folder */
void _reader_get_from_folder(struct banter_state *state, struct banter_data *data);

#endif __READER_H_
