#include "Aria.h"
#include "ActionExploreVelocity.h"
#include "ActionExploreAvoid.h"

int main(int argc, char **argv) {
    Aria::init();
    ArArgumentParser argParser(&argc, argv);
    argParser.loadDefaultArguments();
    ArRobot robot;
    ArRobotConnector robotConnector(&argParser, &robot);
    ArLaserConnector laserConnector(&argParser, &robot, &robotConnector);

    if (!robotConnector.connectRobot()) {
        ArLog::log(ArLog::Terse, "Could not connect to the robot.");
        if (argParser.checkHelpAndWarnUnparsed()) {
            // -help not given, just exit.
            Aria::logOptions();
            Aria::exit(1);
            return 1;
        }
    }


    // Trigger argument parsing
    if (!Aria::parseArgs() || !argParser.checkHelpAndWarnUnparsed()) {
        Aria::logOptions();
        Aria::exit(1);
        return 1;
    }

    ArKeyHandler keyHandler;
    Aria::setKeyHandler(&keyHandler);
    robot.attachKeyHandler(&keyHandler);

    puts("This program will make the robot wander around. It uses some avoidance\n"
    "actions if obstacles are detected, otherwise it just has a\n"
    "constant forward velocity.\n\nPress CTRL-C or Escape to exit.");

    ArSonarDevice sonar;
    robot.addRangeDevice(&sonar);

    robot.runAsync(true);

    // turn on the motors, turn off amigobot sounds
    robot.enableMotors();
    robot.comInt(ArCommands::SOUNDTOG, 0);

    // add a set of actions that combine together to effect the wander behavior
    ArActionStallRecover recover;
    ArActionBumpers bumpers;
    //ArActionAvoidFront avoidFrontNear("Avoid Front Near", 225, 0);
    //ArActionAvoidFront avoidFrontFar;
    //ArActionConstantVelocity constantVelocity("Constant Velocity", 400);
    
    ActionExploreVelocity expVel(500, 1000);
    ActionExploreAvoid expAvd(2000, 3.6);
    
    robot.addAction(&recover, 100);
    robot.addAction(&bumpers, 75);
    //robot.addAction(&avoidFrontNear, 50);
    //robot.addAction(&avoidFrontFar, 49);
    //robot.addAction(&constantVelocity, 25);

    robot.addAction(&expAvd, 26);
    robot.addAction(&expVel, 25);
    // wait for robot task loop to end before exiting the program
    robot.waitForRunExit();

    Aria::exit(0);
    return 0;
}
