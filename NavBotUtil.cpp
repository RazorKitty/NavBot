#include "NavBotUtil.h"
#include <math.h>

/* this returns the lower of two numbers */
namespace utils {
    double upperBoundClamp(double val, double max) {
        return (val < max)? val : max;
    }
    double getOppositeAngle(double hypotenuseLength, double oppositeLength) {
        return asin(sin(oppositeLength/hypotenuseLength))* 180.00/M_PI;
    }
    double getHypotenuseLength(double oppositeLength, double HypotenuseOppositeAngle) {
        return oppositeLength/(sin(HypotenuseOppositeAngle*M_PI/180.00));
    }
    double wrapAngle(double poseAngle, double offsetAngle) {
        double tmp = poseAngle + offsetAngle;
        if (tmp > 180.0) 
            return tmp - 360.0;
        else if (tmp < -180.0)
            return tmp + 360.0;
        return tmp;
    }
}
