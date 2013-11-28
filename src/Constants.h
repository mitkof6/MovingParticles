#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define WALL_COLLISION_PATH	"wall.dat"
#define BALL_COLLISION_PATH	"ball.dat"

//real velocity collision
#define BALL_COLLISION_REAL_MODE false

enum WallNorm {WALL_LEFT, WALL_RIGHT, WALL_FAR, WALL_NEAR, WALL_TOP, WALL_BOTTOM};

//box
#define BOX_SIZE 15

//particles
#define PARTICLES 50
#define MIN_X -BOX_SIZE/2.0f
#define MAX_X BOX_SIZE/2.0f
#define MIN_Y -BOX_SIZE/2.0f
#define MAX_Y BOX_SIZE/2.0f
#define MIN_Z -BOX_SIZE/2.0f
#define MAX_Z BOX_SIZE/2.0f
#define MIN_VX -200
#define MAX_VX 200
#define MIN_VY -200
#define MAX_VY 200
#define MIN_VZ -200
#define MAX_VZ 200
#define MIN_R 0.4
#define MAX_R 0.8
#define MIN_M 5
#define MAX_M 8


#define SLICES 10
#define STACKS 10

#define dt 0.001

//window
#define WINDOW_NAME "Viewer"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define WINDOW_X_POS 100
#define WINDOW_Y_POS 100

//camera
#define CAMERA_MOVE_SPEED 10
#define CAMERA_ROTATE_SPEED 0.03
#define CAM_POS_X 15
#define CAM_POS_Y 0
#define CAM_POS_Z 15
#define CAM_VIEW_X 0
#define CAM_VIEW_Y 0
#define CAM_VIEW_Z 0
#define CAM_UP_X 0
#define CAM_UP_Y 1
#define CAM_UP_Z 0


#endif