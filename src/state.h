/**
 * state.h
 *
 * Holds program state as struct to setup the rest of the
 * program
 */

#ifndef __state__h_
#define __state__h_

#include "libs.h"
#include "data.h"

#define BANTER_TARGET_SIZE      1024
#define BANTER_OUT_TARGET_SIZE  1024
#define BANTER_MAPPING_ID_SIZE  1024
#define BANTER_COLOR_ID_SIZE    1024

#define BANTER_LOCATION_NAME    1024
#define BANTER_COLOR_NAME       1024

#define BANTER_MAPPING_COUNT    16 /* TODO, temporary */

/* holds position mapping functionality */
struct banter_location_mapping {
  char name[BANTER_LOCATION_NAME];
  void (*mapping_func)(struct banter_data *);
};

/* holds color mapping functionality */
struct banter_color_mapping {
  char name[BANTER_COLOR_NAME];
  void (*mapping_func)(struct banter_data *);
};

/*
  holds the current banter state,
  essentially holds configuration information for
  banter should be operating given what it's provided
 */
struct banter_state {
  /*
  Mode for reading input
  0 = file
  1 = process
  2 = ???(dir)
  */
  int in_mode;
  /* holds target file, process id or dir */
  char in_target[BANTER_TARGET_SIZE];
  
  /* Holds file resource, as needed */
  FILE *resource;
  
  /* holds output target, such as for writing results to a specific file */
  char out_target[BANTER_OUT_TARGET_SIZE];

  /* id to a registered physical mapping */
  char mapping_location_id[BANTER_MAPPING_ID_SIZE];

  /* id to a registered color mapping */
  char mapping_color_id[BANTER_COLOR_ID_SIZE];

  /* array of location mappings */
  struct banter_location_mapping location_mappings[BANTER_MAPPING_COUNT];
  int location_mappings_count;

  /* array of color mappings */
  struct banter_color_mapping color_mappings[BANTER_MAPPING_COUNT];
  int color_mappings_count;

  /* reading frame in bytes */
  long stride;

  /* optional configuration option, offset to read from
   in the current input */
  long offset;

  /* ratio of bytes shown per point,
  ex. 2:1, 2 bytes per point */
  int scale;

  /*
  Mode for sending output
  0 = stdout
  1 = file
  */
  int out_mode;

  /* id to a registered output mapping */
  int output_mapping_id;

};

void state_clear_state(struct banter_state *state);

#endif
