#include "vykhukhol.h"
#include "visitor.h"

void Vykhukhol::accept(Visitor& visitor) {
    visitor.visit(*this);
}