#ifndef ACTOINEXPLORENAVIGATENEAR
#define ACTOINEXPLORENAVIGATENEAR 
#include "Aria.h"

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
};
#endif 
