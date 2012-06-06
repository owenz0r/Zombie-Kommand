#ifndef GLOBALS_H
#define GLOBALS_H

#include "cml_config.h"
#include <cml/cml.h>
typedef cml::vector< float, cml::fixed<2> > v2f;

const int MAXSPRITES = 128;
const int MAXENTITIES = 128;
const int MAXCHARACTERS = 8;
const int TILESIZE = 20;

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;
static const int SCREEN_BPP = 32;

#endif
