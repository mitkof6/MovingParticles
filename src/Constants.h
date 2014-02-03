#ifndef CONSTANTS_H_
#define CONSTANTS_H_

//simulation
#define dt 0.05

//box
#define BOX_SIZE 30

//context
#define MOLECULE false
#define PARTICLE true

//# of particles
#define PARTICLES 30

//# of molecules
#define MOLECULES 20

//# of springs systems
#define SPRING_SYSTEMS 10

//real velocity collision
#define BALL_COLLISION_REAL_MODE true

//rendering setup
#define SMOOTH true
#define COLOR true
#define LIGHT true//BUG
#define WIRED false

//spring
#define MIN_REST_LENGTH 3
#define MAX_REST_LENGTH 6
#define MIN_SPRING_K 20
#define MAX_SPRING_K 40
#define MIN_SPRING_B 0.1
#define MAX_SPRING_B 0.2
#define G 9.8

//molecule
#define MOLECULE_ANGLE 90
#define MOLECULE_MASS_MIN 5
#define MOLECULE_MASS_MAX 10
#define MOLECULES_MAX 7//only 5, or 7

//angular velocity
#define MIN_WX -5
#define MAX_WX 5
#define MIN_WY -5
#define MAX_WY 5
#define MIN_WZ -5
#define MAX_WZ 5

//linear velocity
#define MIN_VX -10
#define MAX_VX 10
#define MIN_VY -10
#define MAX_VY 10
#define MIN_VZ -10
#define MAX_VZ 10

//particles
#define MASS_MIN 5
#define MASS_MAX 10

//volume
#define MIN_X -BOX_SIZE/2.0f
#define MAX_X BOX_SIZE/2.0f
#define MIN_Y -BOX_SIZE/2.0f
#define MAX_Y BOX_SIZE/2.0f
#define MIN_Z -BOX_SIZE/2.0f
#define MAX_Z BOX_SIZE/2.0f

//sphere
#define SLICES 13
#define STACKS 13

//Material
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
#define WINDOW_NAME "Simulation"
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

//path for dat files (matlab import)
#define WALL_COLLISION_PATH	"wall.dat"
#define BALL_COLLISION_PATH	"ball.dat"

#endif
