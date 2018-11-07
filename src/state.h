/**
 * state.h
 *
 * Holds program state as struct to setup the rest of the
 * program
 */

#ifndef __state__h_
#define __state__h_

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
  /* holds filename for mode = 0 */
  char *in_fileName;
  /* holds pid for mode = 1 */
  int in_pid;

  /* id to a registered physical mapping */
  int mapping_id;

  /* id to a registered color mapping */
  int color_id;

  /* reading frame in bytes */
  long stride;

  /* optional configuration option, jumps to a fixed
  index in the current input */
  long jumpto;

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

#endif