#ifndef CONSTANTS_H_
#define CONSTANTS_H_

//octree
#define MAX_OCTREE_DEPTH 6
#define MIN_BALLS_PER_OCTREE 3
#define MAX_BALLS_PER_OCTREE 6

//box
#define BOX_SIZE 20

enum Wall {WALL_LEFT, WALL_RIGHT, WALL_FAR, WALL_NEAR, WALL_TOP, WALL_BOTTOM};

//particles
#define PARTICLES 7
#define MIN_X -BOX_SIZE/2.0f
#define MAX_X BOX_SIZE/2.0f
#define MIN_Y -BOX_SIZE/2.0f
#define MAX_Y BOX_SIZE/2.0f
#define MIN_Z -BOX_SIZE/2.0f
#define MAX_Z BOX_SIZE/2.0f
#define MIN_VX -2
#define MAX_VX 2
#define MIN_VY -2
#define MAX_VY 2
#define MIN_VZ -2
#define MAX_VZ 2
#define MIN_R 0.3
#define MAX_R 0.7
#define MIN_M 1
#define MAX_M 10


#define SLICES 40
#define STACKS 10

#define dt 0.01

//window
#define WINDOW_NAME "Viewer"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define WINDOW_X_POS 100
#define WINDOW_Y_POS 100

//camera
#define CAMERA_MOVE_SPEED 10
#define CAMERA_ROTATE_SPEED 0.03
#define CAM_POS_X 10
#define CAM_POS_Y 10
#define CAM_POS_Z 20
#define CAM_VIEW_X 0
#define CAM_VIEW_Y 0
#define CAM_VIEW_Z 0
#define CAM_UP_X 0
#define CAM_UP_Y 1
#define CAM_UP_Z 0


#endif