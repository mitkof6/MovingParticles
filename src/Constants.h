#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define WALL_COLLISION_PATH	"wall.dat"
#define BALL_COLLISION_PATH	"ball.dat"

//molecule
#define MOLECULE true
#define MOL_TH 90
#define MAX_MOL 4

//real velocity collision
#define BALL_COLLISION_REAL_MODE true

//rendering setup
#define SMOTH true
#define COLOR true
#define LIGHT true
#define WIRED false

//box
#define BOX_SIZE 40

//particles
#define PARTICLES 100
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
#define MAX_M 10

#define SLICES 15
#define STACKS 15

//simulation
#define dt 0.002

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

//camera
#define CAMERA_MOVE_SPEED 8
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