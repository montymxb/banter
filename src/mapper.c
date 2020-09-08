/**
 * mapper.c
 *
 * Handles mapping data for routing via the outputter
 */

#include "mapper.h"

/* map with an extrude along the z axis */
void mapper_extrude_z_location_mapping(struct banter_data *data) {
	long x;
	double yProg = 0.0;

	for(x = 0; x < data->count; x+=data->scale) {
		data->xLocations[x] = data->og_data[x];
		data->yLocations[x] = yProg-=0.1;
		if(x > 0) {
			/* use prior 'z' to set this up */
			data->zLocations[x] = data->og_data[x-1];
		} else {
			/* 1st entry, just 0 'z' */
			data->zLocations[x] = 0;
		}
	}
}


/* Maps to 2D spherical coordinates */
void mapper_spherical_2d_location_mapping(struct banter_data *data) {
	long x;
	double diameter = 0.0;
	for(x = 0; x < data->count; x+=data->scale) {
		float dataVal = (data->og_data[x] + 128.0) / 256.0;

		/* calculate x along shell */
		data->xLocations[x] = diameter * cos(dataVal * 2.0 * PI);

		/* calculate y along shell */
		data->yLocations[x] = diameter * sin(dataVal * 2.0 * PI);

		/* calculate z along shell */
		/* actually calculate this properly... */
		data->zLocations[x] = 0.0;

		diameter+=0.1;

	}
}

/* Maps to 3D spherical coordinates */
void mapper_spherical_3d_location_mapping(struct banter_data *data) {
	long x;
	double radius = 0.0;
	double twoPi = 2.0 * PI;
	double radiusIncrement = 0.1;

	for(x = 0; x < data->count; x+=data->scale) {

		/* calculate z along shell */
		if(x > 1) {
			/* 3 data points, place a point on the shell of sphere of radius 'radius' */

			/* calculate x & y off the 1st point */
			data->xLocations[x] = radius * cos(data->og_data[x] / 128.0 * twoPi);
			data->yLocations[x] = radius * sin(data->og_data[x] / 128.0 * twoPi);

			/* calculate z off of the 2nd point */
			double cosVal = cos(data->og_data[x-1] / 128.0 * twoPi);
			double sinVal = sin(data->og_data[x-1] / 128.0 * twoPi);

			/* use cos for calculating z location */
			data->zLocations[x] = radius * sinVal;

			/* use sin (inverse) to calculate how to adjust x & y for sphere */
			data->yLocations[x] = fabs(cosVal) * data->yLocations[x];
			data->xLocations[x] = fabs(cosVal) * data->xLocations[x];

			/* scale all off of 3rd point */
			double scale = (data->og_data[x-2] / 128.0 + 1.0) / 2.0;
			data->xLocations[x]*=scale;
			data->yLocations[x]*=scale;
			data->zLocations[x]*=scale;

		} else if(x > 0) {
			/* just x & y, 2 points, no z movement here */
			/* calculate x & y off the 1st point */
			data->xLocations[x] = radius * cos(data->og_data[x] / 128.0 * twoPi);
			data->yLocations[x] = radius * sin(data->og_data[x] / 128.0 * twoPi);

			/* calculate z off of the 2nd point */
			double cosVal = cos(data->og_data[x-1] / 128.0 * twoPi);
			double sinVal = sin(data->og_data[x-1] / 128.0 * twoPi);

			/* use cos for calculating z location */
			data->zLocations[x] = radius * sinVal;

			/* use sin (inverse) to calculate how to adjust x & y for sphere */
			data->yLocations[x] = fabs(cosVal) * data->yLocations[x];
			data->xLocations[x] = fabs(cosVal) * data->xLocations[x];

		} else {
			/* 1st point, put at center */
			/* calculate x & y off the 1st point */
			data->xLocations[x] = radius * cos(data->og_data[x] / 128.0 * twoPi);
			data->yLocations[x] = radius * sin(data->og_data[x] / 128.0 * twoPi);

			/* no z change */
			data->zLocations[x] = 0.0;

		}

		radius+=radiusIncrement;

	}
}


/* cube mapping */
void mapper_cube_location_mapping(struct banter_data *data) {
	for(int x = 0; x < data->count; x++) {
		if(x > 1) {
			/* rest of runs */
			data->xLocations[x] = data->og_data[x];
			data->yLocations[x] = data->og_data[x-1];
			data->zLocations[x] = data->og_data[x-2];

		} else if(x > 0) {
			/* second */
			data->xLocations[x] = data->og_data[x];
			data->yLocations[x] = data->og_data[x-1];
			data->zLocations[x] = 0.0;

		} else {
			/* initial */
			data->xLocations[x] = data->og_data[x];
			data->yLocations[x] = 0.0;
			data->zLocations[x] = 0.0;

		}
	}
}


/* 4d cube mapping */
void mapper_cube_4d_location_mapping(struct banter_data *data) {
	double offset = 0.0;
	for(int x = 0; x < data->count; x++) {
		if(x > 1) {
			/* rest of runs */
			data->xLocations[x] = data->og_data[x] + offset;
			data->yLocations[x] = data->og_data[x-1] + offset;
			data->zLocations[x] = data->og_data[x-2] + offset;

		} else if(x > 0) {
			/* second */
			data->xLocations[x] = data->og_data[x] + offset;
			data->yLocations[x] = data->og_data[x-1] + offset;
			data->zLocations[x] = offset;

		} else {
			/* initial */
			data->xLocations[x] = data->og_data[x] + offset;
			data->yLocations[x] = offset;
			data->zLocations[x] = offset;

		}
		offset+=0.01;
	}
}


/* maps locations into fixed spherical shells, without changing the radius over time */
void mapper_spherical_shells_location_mapping(struct banter_data *data) {
	long x;
	double radius = 100.0;
	double twoPi = 2.0 * PI;

	for(x = 0; x < data->count; x+=data->scale) {

		/* calculate z along shell */
		if(x > 1) {
			/* 3 data points, place a point on the shell of sphere of radius 'radius' */

			/* calculate x & y off the 1st point */
			data->xLocations[x] = radius * cos(data->og_data[x] / 128.0 * twoPi);
			data->yLocations[x] = radius * sin(data->og_data[x] / 128.0 * twoPi);

			/* calculate z off of the 2nd point */
			double cosVal = cos(data->og_data[x-1] / 128.0 * twoPi);
			double sinVal = sin(data->og_data[x-1] / 128.0 * twoPi);

			/* use cos for calculating z location */
			data->zLocations[x] = radius * sinVal;

			/* use sin (inverse) to calculate how to adjust x & y for sphere */
			data->yLocations[x] = fabs(cosVal) * data->yLocations[x];
			data->xLocations[x] = fabs(cosVal) * data->xLocations[x];

			/* scale all off of 3rd point */
			double scale = (data->og_data[x-2] / 128.0 + 1.0) / 2.0;
			data->xLocations[x]*=scale;
			data->yLocations[x]*=scale;
			data->zLocations[x]*=scale;

		} else if(x > 0) {
			/* just x & y, 2 points, no z movement here */
			/* calculate x & y off the 1st point */
			data->xLocations[x] = radius * cos(data->og_data[x] / 128.0 * twoPi);
			data->yLocations[x] = radius * sin(data->og_data[x] / 128.0 * twoPi);

			/* calculate z off of the 2nd point */
			double cosVal = cos(data->og_data[x-1] / 128.0 * twoPi);
			double sinVal = sin(data->og_data[x-1] / 128.0 * twoPi);

			/* use cos for calculating z location */
			data->zLocations[x] = radius * sinVal;

			/* use sin (inverse) to calculate how to adjust x & y for sphere */
			data->yLocations[x] = fabs(cosVal) * data->yLocations[x];
			data->xLocations[x] = fabs(cosVal) * data->xLocations[x];

		} else {
			/* 1st point, put at center */
			/* calculate x & y off the 1st point */
			data->xLocations[x] = radius * cos(data->og_data[x] / 128.0 * twoPi);
			data->yLocations[x] = radius * sin(data->og_data[x] / 128.0 * twoPi);

			/* no z change */
			data->zLocations[x] = 0.0;

		}

	}
}

long hilbert_index = 0;
/* 2D hilbert definition */
void __hilbert(double x, double y, double xi, double xj, double yi, double yj, int n, struct banter_data *data) {
	if(hilbert_index > data->count-1) {
		// no more calls from here
		return;

	}

	if(n <= 0) {
		data->xLocations[hilbert_index] = (x + (xi + yi)/2.0) * 255.0;
		data->zLocations[hilbert_index] = (y + (xj + yj)/2.0) * 255.0;
		data->yLocations[hilbert_index] = data->og_data[hilbert_index] / 32.0; // 32.0
		hilbert_index++;

	} else {
		__hilbert(x 									, y 									, yi/2.0	, yj/2.0	, xi/2.0	, xj/2.0	, n-1, data);
		__hilbert(x + xi/2.0					, y + xj/2.0					, xi/2.0	, xj/2.0	, yi/2.0	, yj/2.0	, n-1, data);
		__hilbert(x + xi/2.0 + yi/2.0	, y + xj/2.0 + yj/2.0	, xi/2.0	, xj/2.0	, yi/2.0	, yj/2.0	, n-1, data);
		__hilbert(x + xi/2.0 + yi			, y + xj/2.0 + yj			, -yi/2.0	, -yj/2.0	, -xi/2.0	, -xj/2.0	, n-1, data);

	}
}


/* 2D hilbert curve imaging */
void mapper_hilbert_curve_2d_location_mapping(struct banter_data *data) {
	// number of repetitions
	int n = 1;

	// zero out static hilbert index
	hilbert_index = 0;

	// advance hilbert count until it's enough
	while(pow(4,n) < data->count) {
		n++;
	}

	// start the hilbert curve
	__hilbert(
		-0.5,-0.5,	// starting X & Y bottom left
		1.0,0.0		// X unit vector
		,0.0,1.0	// Y unit vector
		,n,data	// number of iterations & data
	);
}


/* 3D hilbert definition*/
/* TODO fix this up later... */
void __hilbert3d(
	double x, double y, double z,
	double xi, double xj, double xk,
	double yi, double yj, double yk,
	double zi, double zj, double zk,
	int n, struct banter_data *data
) {

	if(hilbert_index > data->count-1) {
		// no more calls from here
		return;

	}

	if(n <= 0) {
		data->xLocations[hilbert_index] 	= (x + (xi + yi + zi)/2.0) * 255.0;
		data->yLocations[hilbert_index] 	= (y + (xj + yj + zj)/2.0) * 255.0;
		data->zLocations[hilbert_index++] = (z + (xk + yk + zk)/2.0) * 255.0;

	} else {

		/*
		glVertex3d(x-t,y-t,z); glVertex3d(x+t,y+t,z);
    glVertex3d(x+t,y-t,z); glVertex3d(x-t,y+t,z);

    glVertex3d(x,y-t,z-t); glVertex3d(x,y+t,z+t);
    glVertex3d(x,y-t,z+t); glVertex3d(x,y+t,z-t);

    glVertex3d(x-t,y,z-t); glVertex3d(x+t,y,z+t);
    glVertex3d(x+t,y,z-t); glVertex3d(x-t,y,z+t);
		*/

		// generate a small x/y noise to break up the moiré pattern
		double rx = (rand() % 100) / 10000.0;
		double ry = (rand() % 100) / 10000.0;

		x += rx;
		y += ry;

		// 1st 4 in regular Z coords
		__hilbert3d(
			x, y, z,
			yi/2.0, yj/2.0, yk/2.0,
			xi/2.0, xj/2.0, xk/2.0,
			zi/2.0, zj/2.0, zk/2.0,
			n-1, data
		);

		__hilbert3d(
			x + xi/2.0, y + xj/2.0, z, // + xk/2.0
			xi/2.0, xj/2.0, xk/2.0,
			yi/2.0, yj/2.0, yk/2.0,
			zi/2.0, zj/2.0, zk/2.0,
			n-1, data
		);

		__hilbert3d(
			x + xi/2.0 + yi/2.0, y + xj/2.0 + yj/2.0, z, // + xk/2.0 + yk/2.0 + zk/2.0
			xi/2.0, xj/2.0, xk/2.0,
			yi/2.0, yj/2.0, yk/2.0,
			zi/2.0, zj/2.0, zk/2.0,
			n-1, data
		);

		__hilbert3d(
			x + xi/2.0 + yi, y + xj/2.0 + yj, z, // + xk/2.0 + yk
			-yi/2.0, -yj/2.0, -yk/2.0,
			-xi/2.0, -xj/2.0, -xk/2.0,
			zi/2.0, zj/2.0, zk/2.0,
			n-1, data
		);

		// next 4 in adjusted Z coordinates
		__hilbert3d(
			x, y, z + zk/2.0,
			yi/2.0, yj/2.0, yk/2.0,
			xi/2.0, xj/2.0, xk/2.0,
			zi/2.0, zj/2.0, zk/2.0,
			n-1, data
		);

		__hilbert3d(
			x + xi/2.0, y + xj/2.0, z + zk/2.0, // + xk/2.0
			xi/2.0, xj/2.0, xk/2.0,
			yi/2.0, yj/2.0, yk/2.0,
			zi/2.0, zj/2.0, zk/2.0,
			n-1, data
		);

		__hilbert3d(
			x + xi/2.0 + yi/2.0, y + xj/2.0 + yj/2.0, z + zk/2.0, // + xk/2.0 + yk/2.0 + zk/2.0
			xi/2.0, xj/2.0, xk/2.0,
			yi/2.0, yj/2.0, yk/2.0,
			zi/2.0, zj/2.0, zk/2.0,
			n-1, data
		);

		__hilbert3d(
			x + xi/2.0 + yi, y + xj/2.0 + yj, z + zk/2.0, // + xk/2.0 + yk
			-yi/2.0, -yj/2.0, -yk/2.0,
			-xi/2.0, -xj/2.0, -xk/2.0,
			zi/2.0, zj/2.0, zk/2.0,
			n-1, data
		);

	}
}


/* 3D hilbert curve imaging */
void mapper_hilbert_curve_3d_location_mapping(struct banter_data *data) {
	// number of repetitions
	int n = 1;

	// zero out static hilbert index
	hilbert_index = 0;

	// advance hilbert count until it's enough
	while(pow(8,n) < data->count) {
		n++;
	}

	// start the hilbert curve
	__hilbert3d(
		-0.5,-0.5,-0.5,		// starting X,Y,Z at origin
		1.0, 0.0, 0.0,	// X unit vector
		0.0, 1.0, 0.0,	// Y unit vector
		0.0, 0.0, 1.0, 	// Z unit vector
		n,data					// number of iterations & data
	);

}


/* 3d chain mapping */
void mapper_chain_location_mapping(struct banter_data *data) {
	long x;

	/* zero out the 1st entry */
	data->xLocations[0] = 0.0;
	data->yLocations[0] = 0.0;
	data->zLocations[0] = 0.0;

	double xx,yy,zz;
	xx = yy = zz = 0.0;
	double offset = 0.01;

	for(x = 2; x < data->count; x+=data->scale) {
		// add new changes
		//xx += data->og_data[x];
		//yy += data->og_data[x-1];
		//zz += data->og_data[x-2];

		if(data->og_data[x] & 1) {
			xx += offset;
		}

		if(data->og_data[x] & 2) {
			yy += offset;
		}

		if(data->og_data[x] & 4) {
			zz += offset;
		}

		if(data->og_data[x] & 8) {
			xx -= offset;
		}

		if(data->og_data[x] & 16) {
			yy -= offset;
		}

		if(data->og_data[x] & 32) {
			zz -= offset;
		}

		if(data->og_data[x] & 64) {
			// do nothing?
		}

		if(data->og_data[x] & 128) {
			// do nothing?
		}

		// update locations
		data->xLocations[x] = xx;
		data->yLocations[x] = yy;
		data->zLocations[x] = zz;
	}
}


/* Color by value of a given byte */
void mapper_value_color_mapping(struct banter_data *data) {
	long x;
	for(x = 0; x < data->count; x+=data->scale) {
		/* color from val */
		float val = data->og_data[x];
		float colorVal = (val + 128.0) / 256.0;

		if(colorVal < 0.0 || colorVal > 1.0) {
			printf("Bad color Value '%d'!\n", colorVal);
			exit(1);

		}

		// shifting RGB color range
		// makes no assumptions about interpretation of underlying values
		if(colorVal < 0.333) {
			data->rColors[x] = 1.0 - colorVal * 3.333;
			data->gColors[x] = colorVal * 3.333;
			data->bColors[x] = 0.0;

		} else if(colorVal < 0.666) {
			data->rColors[x] = 0.0;
			data->gColors[x] = 1.0 - (colorVal - 0.333) * 3.333;
			data->bColors[x] = (colorVal - 0.333) * 3.333;

		} else {
			data->rColors[x] = (colorVal - 0.666) * 3.333;
			data->gColors[x] = 0.0;
			data->bColors[x] = 1.0 - (colorVal - 0.666) * 3.333;

		}

	}
}


/* Colors based on position */
void mapper_positional_color_mapping(struct banter_data *data) {
	long x;
	for(x = 0; x < data->count; x+=data->scale) {
		data->rColors[x] = (x*1.0) / data->count;
		data->gColors[x] = 1.0 - (x*1.0) / data->count;
		data->bColors[x] = 0.0;
	}
}


/* Colors based on variance in values (red = variance, green = homogenicity) */
void mapper_entropy_color_mapping(struct banter_data *data) {
	long x;
	double variance = 0.0;
	for(x = 0; x < data->count; x+=data->scale) {
		if(x > 0) {
			float colorVal1 = (data->og_data[x] + 128.0) / 256.0;
			float diff = fabs(variance - colorVal1);

			/* recalc variance */
			variance = (variance + colorVal1) / 2.0;

			/* more red, more variance */
			data->rColors[x] = diff * 2.0;
			/* more green, less variance */
			data->gColors[x] = 1.0 - diff * 2.0;
			data->bColors[x] = 0.0;

		} else {
			/* set baseline variance */
			variance = (data->og_data[x] + 128.0) / 256.0;
			data->rColors[x] = 0.0;
			data->gColors[x] = 1.0;
			data->bColors[x] = 0.0;
		}
	}
}


/* 3d color mapper */
void mapper_3d_value_color_mapping(struct banter_data *data) {
	for(int x = 0; x < data->count; x++) {
		if(x > 1) {
			/* rest of runs */
			data->rColors[x] = (data->og_data[x] + 128.0) / 320.0 + 0.2;
			data->gColors[x] = (data->og_data[x-1] + 128.0) / 320.0 + 0.2;
			data->bColors[x] = (data->og_data[x-2] + 128.0) / 320.0 + 0.2;

		} else {
			data->rColors[x] = 0.0;
			data->gColors[x] = 0.0;
			data->bColors[x] = 0.0;

		}
	}
}

/* Color drags by sequence, accounting for change (and lack there of, over time) */
void mapper_sequence_color_mapping(struct banter_data *data) {
	double c = 0.5;
	for(int x = 0; x < data->count; x++) {
		c += ((data->og_data[x] / 128.0)) * 0.1;

		// cap it off so we don't float out of bounds
		if(c < 0.0) {
			c = 0.0;
		} else if(c > 1.0) {
			c = 1.0;
		}

		data->rColors[x] = c;
		data->gColors[x] = c;
		data->bColors[x] = c;
	}
}

/* Highlights the upper ASCII range */
void mapper_upper_color_mapping(struct banter_data *data) {
	double c;
	for(int x = 0; x < data->count; x++) {
		if(data->og_data[x] >= 0.0) {
			c = 1.0;
		} else {
			c = 0.2;
		}

		data->rColors[x] = data->gColors[x] = data->bColors[x] = c;
	}
}

/* Highlights the lower ASCII range */
void mapper_lower_color_mapping(struct banter_data *data) {
	double c;
	for(int x = 0; x < data->count; x++) {
		if(data->og_data[x] >= 0.0) {
			c = 0.2;
		} else {
			c = 1.0;
		}

		data->rColors[x] = data->gColors[x] = data->bColors[x] = c;
	}
}

/* Highlights the readable ASCII range in blue */
void mapper_readable_color_mapping(struct banter_data *data) {
	double c;
	for(int x = 0; x < data->count; x++) {
		if(data->og_data[x] >= 32 && data->og_data[x] < 127) {
			c = 1.0;
		} else {
			c = 0.2;
		}

		data->rColors[x] = 0.0;
		data->gColors[x] = c;
		data->bColors[x] = c;
	}
}

/* Measures the slope between characters */
void mapper_slope_color_mapping(struct banter_data *data) {
	double slope = 0.0;
	for(int x = 0; x < data->count; x++) {
		if(x > 0) {
			slope = (data->og_data[x] - data->og_data[x-1]) / 128.0;
		}

		if(slope < 0.0) {
			data->rColors[x] = -slope;
			data->gColors[x] = 0.0;
			data->bColors[x] = 0.0;

		} else {
			data->rColors[x] = slope;
			data->gColors[x] = 0.0;
			data->bColors[x] = 0.0;

		}
	}
}


/**
 * mapper_prepare_data
 *
 * Prepares raw data with locations & colorings, ready for rendering
 */
void mapper_prepare_data(struct banter_state *state, struct banter_data *data) {
	int x;
	char matched = 0;

	/* if last count is less than current count (and not zero), reallocate */
	if(data->last_count > 0 && data->last_count < data->count) {
		/* free all */
		free(data->xLocations);
		free(data->yLocations);
		free(data->zLocations);
		free(data->rColors);
		free(data->gColors);
		free(data->bColors);

		/* so next if catches to allocate */
		data->xLocations = NULL;

	}

	/* if pointers are null, setup for the first time, adjust last count */
	if(data->xLocations == NULL) {
		data->xLocations = (double *)malloc(sizeof(double) * data->count);
		data->yLocations = (double *)malloc(sizeof(double) * data->count);
		data->zLocations = (double *)malloc(sizeof(double) * data->count);

		data->rColors = (double *)malloc(sizeof(double) * data->count);
		data->gColors = (double *)malloc(sizeof(double) * data->count);
		data->bColors = (double *)malloc(sizeof(double) * data->count);

		data->last_count = data->count;

	}

	/* set scale, so we show the appropriate offset */
	data->scale = state->scale;

	/* map locations */
	for(x = 0; x < state->location_mappings_count; x++) {
		if(strcmp(state->location_mappings[x].name, state->mapping_location_id) == 0) {
			/* apply this location mapping function */
			(*(state->location_mappings[x].mapping_func))(data);
			matched = matched | 1;
		}
	}

	/* map colors */
	for(x = 0; x < state->color_mappings_count; x++) {
		if(strcmp(state->color_mappings[x].name, state->mapping_color_id) == 0) {
			/* apply this color mapping function */
			(*(state->color_mappings[x].mapping_func))(data);
			matched = matched | 2;
		}
	}

	/* verify we matched everything */
	if(matched == 0) {
		error_report_with_message("Could not find color or location mapping to use");

	} else if(matched == 1) {
		error_report_with_message("Could not find color mapping to use");

	} else if(matched == 2) {
		error_report_with_message("Could not find location mapping to use");

	}
}
