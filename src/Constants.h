#ifndef CONSTANTS_H_
#define CONSTANTS_H_

//path for dat files (matlab import)
#define WALL_COLLISION_PATH	"wall.dat"
#define BALL_COLLISION_PATH	"ball.dat"

//rigid body
#define RIGID_BODY true
#define MOL_TH 90
#define MOL_MASS_MIN 1
#define MOL_MASS_MAX 5
#define MOL_RADIUS 1
#define MAX_MOL 5
/*
#define WIDTH_MIN 2
#define WIDTH_MAX 4
#define LENGTH_MIN 2
#define LENGTH_MAX 4
#define HEIGHT_MIN 2
#define HEIGHT_MAX 4
*/
//real velocity collision
#define BALL_COLLISION_REAL_MODE true

//rendering setup
#define SMOOTH false
#define COLOR true
#define LIGHT true
#define WIRED false

//box
#define BOX_SIZE 13

//particles
#define PARTICLES 1
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
#define MIN_M 5
#define MAX_M 20

#define SLICES 13
#define STACKS 13

//simulation
#define dt 0.001

//metirial
#define AB_MIN 0
#define AB_MAX 0.2
#define DI_MIN 0.1
#define DI_MAX 0.6
#define SP_MIN 0.6
#define SP_MAX 1.0
#define SH_MIN 0
#define SH_MAX 128

enum WallNorm {WALL_LEFT, WALL_RIGHT, WALL_FAR,
	WALL_NEAR, WALL_TOP, WALL_BOTTOM};

//light
#define L_POS_X 20.0
#define L_POS_Y 50.0
#define L_POS_Z 50.0
#define L_POS_W 0.0

//window
#define WINDOW_NAME "Viewer"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define WINDOW_X_POS 100
#define WINDOW_Y_POS 100

//text
#define TEXT_WIDTH 8
#define TEXT_HEIGHT 12

//camera
#define CAMERA_MOVE_SPEED 4
#define CAMERA_ROTATE_SPEED 0.01
#define CAM_POS_X 0
#define CAM_POS_Y 0
#define CAM_POS_Z 25
#define CAM_VIEW_X 0
#define CAM_VIEW_Y 0
#define CAM_VIEW_Z 0
#define CAM_UP_X 0
#define CAM_UP_Y 1
#define CAM_UP_Z 0

//camera 3rd
#define OFFSET_X 15
#define OFFSET_Y 15
#define OFFSET_Z 15


#endif