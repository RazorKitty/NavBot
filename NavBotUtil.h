#ifndef NAVBOTUTIL
#define NAVBOTUTIL 
#include <math.h>

namespace utils {
    double upperBoundClamp(double val, double max);
    double getOppositeAngle(double hypotenuseLength, double oppositeLength, double hypotenuseOppositeAngle);
    double getHypotenuseLength(double oppositeLength, double hypotenuseOppositeAngle);
}
#endif
