#include "bear.h"
#include "visitor.h"

void Bear::accept(Visitor& visitor) {
    visitor.visit(*this);
}