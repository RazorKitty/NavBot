#ifndef NAVBOTUTIL
#define NAVBOTUTIL 
#include <math.h>

namespace utils {
    double upperBoundClamp(double val, double max);
    double getOppositeAngle(double hypotenuseLength, double oppositeLength);
    double getHypotenuseLength(double oppositeLength, double hypotenuseOppositeAngle);
    double wrapAngle(double poseAngle, double offsetAngle);
}
#endif
