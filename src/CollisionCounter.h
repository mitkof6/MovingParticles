#ifndef COLLISIONCOUNTER_H_
#define COLLISIONCOUNTER_H_

#include <vector>
#include <stdio.h>
#include <string>

#include "Constants.h"
#include "Renderable.h"
#include "GL/glut.h"

using namespace std;

/**
 * Implements histogram data representation for collisions
 */
class CollisionCounter : public Renderable{

public:
	CollisionCounter(void);
	~CollisionCounter(void);

	/**
	 * Increments time sequence
	 */
	void incTime();

	/**
	 * Increments collision counter
	 */
	void incCounter();

	/**
	 * Register data pair (time, collisions)
	 */
	void registerEvent();

	/**
	 * Clears data
	 */
	void clear();

	/**
	 * Render histogram
	 */
	void draw();

	/**
	 * Does nothing
	 */
	void update();

	/**
	 * Used for rendering title
	 *
	 * @param title name
	 */
	void setName(string n);

	/**
	 * Saves sequence to matlab dat format
	 *
	 * @param path
	 */
	void saveToMat(string path);

	/**
	 * Used for synchronizing multiple counters
	 */
	unsigned long getDifference();

	/**
	 * Used to add collision counter to this data
	 * for synchronizing multiple counters
	 *
	 * @param count to be added
	 */
	void add(unsigned long count);

private:
	/**
	 * Title
	 */
	string name;

	/**
	 * Time and collisions
	 */
	unsigned long time, counter;

	/**
	 * Tracks counter(t)-counter(t-1)
	 */
	short difference;

	/**
	 * Data sequence
	 */
	vector<unsigned long> timeSeq, counterSeq;

	/**
	 * Draw string on the screen
	 *
	 * @param (string, position x, position y,
	 * 		   color(red, green, blue, a), font)
	 */
	void drawString(const char *str, int x, int y,
			float color[4], void *font);
};

#endif

