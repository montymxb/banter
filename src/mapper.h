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

/* pi constant */
#define PI 3.14159265

#define MAPPINGS_COUNT 9
#define COLORINGS_COUNT 9

#define LOC_MAP_EXTRUDE_Z "Extrude Along Z"
#define LOC_MAP_SPHERICAL_2D "Spherical 2D"
#define LOC_MAP_SPHERICAL_3D "Spherical 3D"
#define LOC_MAP_CUBE "Cube"
#define LOC_MAP_CUBE_4D "Cube 4D"
#define LOC_MAP_SPHERICAL_SHELLS "Spherical Shells"
#define LOC_CHAIN "Chain"
#define LOC_HILBERT_2D "Hilbert 2D"
#define LOC_HILBERT_3D "Hilbert 3D"

#define COL_MAP_VALUE "Value"
#define COL_MAP_3D_VALUE "3D Value"
#define COL_MAP_POSITIONAL "Positional"
#define COL_MAP_ENTROPY "Entropy"
#define COL_MAP_SEQUENCE "By Sequence"
#define COL_MAP_UPPER "Upper ASCII"
#define COL_MAP_LOWER "Lower ASCII"
#define COL_MAP_READABLE "Readable ASCII"
#define COL_MAP_SLOPE "Byte Slope"


void mapper_prepare_data(struct banter_state *state, struct banter_data *data);

/* Location Mappings */
void mapper_extrude_z_location_mapping(struct banter_data *data);
void mapper_spherical_2d_location_mapping(struct banter_data *data);
void mapper_spherical_3d_location_mapping(struct banter_data *data);
void mapper_cube_location_mapping(struct banter_data *data);
void mapper_cube_4d_location_mapping(struct banter_data *data);
void mapper_spherical_shells_location_mapping(struct banter_data *data);
void mapper_chain_location_mapping(struct banter_data *data);
void mapper_hilbert_curve_2d_location_mapping(struct banter_data *data);
void mapper_hilbert_curve_3d_location_mapping(struct banter_data *data);

/* Color Mappings */
void mapper_value_color_mapping(struct banter_data *data);
void mapper_positional_color_mapping(struct banter_data *data);
void mapper_entropy_color_mapping(struct banter_data *data);
void mapper_3d_value_color_mapping(struct banter_data *data);
void mapper_sequence_color_mapping(struct banter_data *data);
void mapper_upper_color_mapping(struct banter_data *data);
void mapper_lower_color_mapping(struct banter_data *data);
void mapper_readable_color_mapping(struct banter_data *data);
void mapper_slope_color_mapping(struct banter_data *data);

#endif
