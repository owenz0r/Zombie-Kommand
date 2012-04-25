// modified version from -
// http://www.friedspace.com/cprogramming/SDLTest.c
static void setPixel(SDL_Surface *screen, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
	if( x < 0 || y < 0 )
		return;

	Uint32 *pixmem32;
    Uint32 colour;  
 
    colour = SDL_MapRGB( screen->format, r, g, b );
  
    pixmem32 = (Uint32*) screen->pixels  + (y*SCREEN_WIDTH) + x;
    *pixmem32 = colour;
}

// Simplified Bresenham algorithm
// http://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
static void drawLine(SDL_Surface *screen, int x0, int y0, int x1, int y1, int offsetx=0, int offsety=0){

	std::vector<v2f> *result = new std::vector<v2f>();

	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);

	int sx, sy;
	sx = x0 < x1 ? 1 : -1;
	sy = y0 < y1 ? 1 : -1;
	int err = dx - dy;

	result->push_back(v2f(x0,y0));
	while( x0 != x1 || y0 != y1 ){
		int e2 = err * 2;
		
		if( e2 > -dy ){
			err -= dy;
			x0 += sx;
		}

		if( e2 < dx ){
			err += dx;
			y0 += sy;
		}
		result->push_back(v2f(x0,y0));
	}
	//return *result;

	for(int i=0; i < result->size(); i++)
		setPixel( screen, result->at(i)[0] - offsetx, result->at(i)[1] - offsety, 0, 255, 0);
}

static float cross2d(v2f &first, v2f &second){
	return first[0]*second[1] - first[1]*second[0];
}

// stolen from stackoverflow -
// http://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
static v2f* intersectionTest(v2f &p1, v2f &p2, v2f &p3, v2f &p4){
	
	float err = 0.0000001f;
	
	v2f r = p2 - p1;
	v2f s = p4 - p3;

	float cp = cross2d(r,s);

	// parallel
	if( abs(cp) < err )
		return NULL;

	v2f tmp = p3 - p1;
	float num = cross2d(tmp, s);
	float denom = cross2d(r,s);
	float t = num/denom;

	// not on line1
	if( t > 1.0f || t < 0.0f )
		return NULL;

	num = cross2d(tmp, r);
	float u = num / denom;
	
	// not on line2
	if( u > 1.0f || u < 0.0f )
		return NULL;

	v2f result = p3 + (u * s);
	return &result;

}