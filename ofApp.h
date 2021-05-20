#pragma once

#include "ofMain.h"

typedef struct _LINE
{
	int x1, y1;
	int x2, y2;
}Line;

typedef struct _DOT {
	int x1, y1;
}Dot;

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	/* WaterFall-related member variables Regions */

	// flag variables
	int draw_flag;
	int load_flag;
	int break_flag;
	

	// Line segment and dot related variables
	int num_of_line, num_of_dot;
	float dot_diameter;
	Line* lineseg = NULL;
	Dot* dot = NULL;
	int dot_index;

	/* WaterFall-related member functions */

	void processOpenFileSelection(ofFileDialogResult openFileResult);
	void initializeWaterLines(); // 2nd week portion.
	int isOnScreen(int mode, int data);
	void sortDot(Dot* dot);
	void swapDot(Dot* dot, int n);
};
