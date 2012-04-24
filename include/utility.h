
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