#ifndef ACTOINEXPLORENAVIGATENEAR
#define ACTOINEXPLORENAVIGATENEAR 
#include <Aria/Aria.h>

class ActionExploreNavigateNear : public ArAction {
    public:
        ActionExploreNavigateNear(double threshold);
        virtual ~ActionExploreNavigateNear(void){};
        virtual ArActionDesired *fire(ArActionDesired currentDesired);
        virtual void setRobot(ArRobot *robot);
    protected:
        ArRangeDevice *mySonar;
        ArActionDesired myDesired;
        double myThreshold;
        int direction;
        double leftOppositeOffsetAngle;
        double leftOppositeLength;
        double rightOppositeOffsetAngle;
        double rightOppositeLength;
        double oppositeLength;
        double oppositeOffsetAngle;
        double hypotenuseLength;
        double hypotenuseOffsetAngle;
        double hypotenuseOppositeAngle;
        double oppositeAjdacentAngle;
};
#endif 
