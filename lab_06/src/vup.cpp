#include "vup.h"
#include "visitor.h"

void Vup::accept(Visitor& visitor) {
    visitor.visit(*this);
}