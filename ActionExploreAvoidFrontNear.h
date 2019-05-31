#ifndef ACTIONEXPLOREAVOIDFRONTNEAR
#define ACTIONEXPLOREAVOIDFRONTNEAR 
#include <Aria/Aria.h>

class ActionExploreAvoidFrontNear : public ArAction {
    public:
        ActionExploreAvoidFrontNear(double threshold);
        virtual ~ActionExploreAvoidFrontNear(void){};
        virtual ArActionDesired *fire(ArActionDesired currentDesired);
        virtual void setRobot(ArRobot *robot);
    protected:
        ArRangeDevice *mySonar;
        ArActionDesired myDesired;
        double myThreshold;
        int direction;
        double hypotenuseLength;
        double hypotenuseOffsetAngle;
        double leftOppositeOffsetAngle;
        double rightOppositeOffsetAngle;
        double oppositeLength;
        double oppositeOffsetAngle;
        double hypotenuseOppositeAngle;
        double leftOppositeLength;
        double rightOppositeLength;
};  
#endif
