#include <stdlib.>
#include <stdio.h>
#include <getopt.h>

  static struct option long_options[] = {
                   {"help",              required_argument, NULL,  '?' },
                   {"clockwise",         no_argument,       NULL,  'c'},
                   {"counterclockwise",  no_argument,       NULL,  'b' },
                   {"noOfsteps",         required_argument, NULL,  'n' },
                   {"velocity",          required_argument, NULL,  'v' },
                   {"halfstep",          no_argument,       NULL,  's' },
		   {"fullstep",          no_argument,       NULL,  'h' },
                   {NULL,                    0,             NULL,   0, }
               };
