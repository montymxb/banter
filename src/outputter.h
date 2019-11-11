/**
 * outputter.h
 *
 * Key components for sending data to where it should be going
 */

#ifndef __OUTPUTTER__H_
#define __OUTPUTTER__H_

#include "state.h"
#include "data.h"
#include "error.h"
#include <stdio.h>

/* Forwards data to the currently set output destination
   (ex. renderer, stream, etc.)
 */
void outputter_forwarddata_withstate(struct banter_state *state);

#endif
