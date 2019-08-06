/**
 * mapper.h
 *
 * Maps data from a given frame into physical locations & colorings
 * for use with the outputter, or renderer
 */

#ifndef __MAPPER_H__
#define __MAPPER_H__

#include "state.h"
#include "data.h"
#include "error.h"

void mapper_prepare_data(struct banter_state *state, struct banter_data *data);

void mapper_default_location_mapping(struct banter_data *data);
void mapper_default_color_mapping(struct banter_data *data);

#endif
