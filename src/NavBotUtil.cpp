#include "NavBotUtil.h"
#include "math.h"

/* this returns the lower of two numbers */
namespace utils {
    double upperBoundClamp(double val, double max) {
        return (val < max)? val : max;
    }
    double getOppositeAngle(double hypotenuseLength, double oppositeLength, double hypotenuseOppositeAngle) {
        return asin(sin(oppositeLength/hypotenuseLength))* 180.00/M_PI;
    }
    double getHypotenuseLength(double oppositeLength, double HypotenuseOppositeAngle) {
        return oppositeLength/(sin(HypotenuseOppositeAngle*M_PI/180.00));
    }
}
