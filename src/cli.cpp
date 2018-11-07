/**
 * cli.cpp
 *
 * Holds functionality for parsing cmdline args into
 * a workable struct
 */

 #include "cli.h"

/* Returns a banter state struct from given args */
struct banter_state *cli_getstate_fromargs(int argc, char *argv[]) {
  int x;
  /* get key/value pairs for each arg, or ERROR out */

  for(x = 1; x < argc; x++) {

  }


  /* Verify we have sufficient args to proceed */
  /* Otherwise call an appropriate error function from error.cpp */
  /* Can wrap up error/stats for us in a nice way if we want */

}
