#include "Pointer.h"

Pointer::Pointer(Engine *e, v2f *pos, std::vector<std::string> &sprites) : Drawable(sprites), Entity(e, (*pos)[0], (*pos)[1]) {

}

void Pointer::Update(Uint32 time){

}