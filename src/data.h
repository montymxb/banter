/**
 * data.h
 *
 * Holds the structure for defining output data
 */

#ifndef __DATA__H_
#define __DATA__H_

#include <stdlib.h>

/* holds data ready for output */
struct banter_data {
  /* indicates the # of datapoints present */
  long count;

  /* Physial mapping in 3d space */
  double *xLocations;
  double *yLocations;
  double *zLocations;

  /* Color mapping for each point */
  double *rColors;
  double *gColors;
  double *bColors;

  /* original data that mappings & colors were derived from */
  char *og_data;
};

/* Used to clear existing data */
void data_clear_data(struct banter_data *data);

#endif
