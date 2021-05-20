#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(15); // Limit the speed of our program to 15 frames per second

	// We still want to draw on a black background, so we need to draw
	// the background before we do anything with the brush
	ofBackground(255, 255, 255);
	ofSetLineWidth(4);

	draw_flag = 0;
	load_flag = 0;
	dot_diameter = 20.0f;
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(127, 23, 31);  // Set the drawing color to brown

	// Draw shapes for ceiling and floor
	ofDrawRectangle(0, 0, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
	ofDrawRectangle(0, 728, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
	ofSetLineWidth(5);


	ofSetLineWidth(5);
	if (draw_flag) {

		for (int i = 0; i < num_of_line; i++)
		{
			ofDrawLine(lineseg[i].x1, lineseg[i].y1, lineseg[i].x2, lineseg[i].y2);
		}
		ofSetColor(0);
		for (int i = 0; i < num_of_dot; i++)
		{
			if (i == dot_index)
				ofSetColor(255, 0, 0, 255);
			ofDrawCircle(dot[i].x1, dot[i].y1, 10);
			if (i == dot_index)
				ofSetColor(0);
		}
		/* COMSIL1-TODO 3 : Draw the line segment and dot in which water starts to flow in the screen.
		 Note that after drawing line segment and dot, you have to make selected water start dot colored in red.
		 */



		 // 2nd week portion.
		ofSetLineWidth(2);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'v') {
		// HACK: only needed on windows, when using ofSetAutoBackground(false)
		glReadBuffer(GL_FRONT);
		ofSaveScreen("savedScreenshot_" + ofGetTimestampString() + ".png");
	}
	if (key == 'q' || key == 'Q') {
		// Reset flags
		draw_flag = 0;

		// Free the dynamically allocated memory exits.
		if (lineseg != NULL)
		{
			free(lineseg);
			lineseg = NULL;
		}
		if (dot != NULL)
		{
			free(dot);
			dot = NULL;
		}
		cout << "Dynamically allocated memory has been freed." << endl;

		_Exit(0);
	}
	if (key == 'd' || key == 'D') {
		if (!load_flag) return;

		/* COMSIL1-TODO 2: This is draw control part.
		You should draw only after when the key 'd' has been pressed.
		*/
		draw_flag = 1;
		//draw();
	}
	if (key == 's' || key == 'S') {
		// 2nd week portion.
	}
	if (key == 'e') {
		// 2nd week portion.
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (key == 'l' || key == 'L') {
		// Open the Open File Dialog
		ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a only txt for Waterfall");

		// Check whether the user opened a file
		if (openFileResult.bSuccess) {
			ofLogVerbose("User selected a file");

			// We have a file, so let's check it and process it
			processOpenFileSelection(openFileResult);
			load_flag = 1;
		}
	}

	/* COMSIL1-TODO 4: This is selection dot control part.
	 You can select dot in which water starts to flow by left, right direction key (<- , ->).
	 */

	if (key == OF_KEY_RIGHT) {
		if (dot_index == num_of_dot-1)
			dot_index = 0;
		else
			dot_index++;
		cout << "Selcted Dot Coordinate is (" << dot[dot_index].x1 << ", " << dot[dot_index].y1 << ")" << endl;
	}
	if (key == OF_KEY_LEFT) {
		if (dot_index == 0)
			dot_index = num_of_dot - 1;
		else
			dot_index--;
		cout << "Selcted Dot Coordinate is (" << dot[dot_index].x1 << ", " << dot[dot_index].y1 << ")" << endl;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult) {
	//Path to the comma delimited file
	//string fileName = "input.txt";

	string fileName = openFileResult.getName();
	ofFile file(fileName);

	if (!file.exists()) cout << "Target file does not exists." << endl;
	else cout << "We found the target file." << endl;

	ofBuffer buffer(file);

	/* This variable is for indicating which type of input is being received.
	 IF input_type == 0, then work of getting line input is in progress.
	 IF input_type == 1, then work of getting dot input is in progress.
	 */
	int input_type = 0;


	/* COMSIL1-TODO 1 : Below code is for getting the number of line and dot, getting coordinates.
	 You must maintain those information. But, currently below code is not complete.
	 Also, note that all of coordinate should not be out of screen size.
	 However, all of coordinate do not always turn out to be the case.
	 So, You have to develop some error handling code that can detect whether coordinate is out of screen size.
	*/
	int idx = 0;
	int count = 0;
	int mode;

	// Read file line by line
	for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
		string line = *it;
		break_flag = 0;
		// Split line into strings
		vector<string> words = ofSplitString(line, " ");

		if (words.size() == 1) {
			if (input_type == 0) { // Input for the number of lines.
				num_of_line = atoi(words[0].c_str());
				if (!lineseg)
				{
					lineseg = (Line*)malloc(sizeof(Line)*num_of_line);
				}
			}
			else { // Input for the number of dots.
				num_of_dot = atoi(words[0].c_str());
				if (!dot)
				{
					dot = (Dot*)malloc(sizeof(Dot)*num_of_dot);
				}
			}
		}
		else if (words.size() >= 2) {
			count++;
			if (input_type == 0) { // Input for actual information of lines
				for (int i = 0; i < 4; i++)
				{
					if (i % 2 == 0) // x ÁÂÇ¥
					{
						mode = 0;
					}
					else
					{
						mode = 1;
					}
					if(!isOnScreen(mode, atoi(words[i].c_str())))
					{
						break_flag = 1;
						break;
					}
				}

				if (!break_flag)
				{
					lineseg[idx].x1 = atoi(words[0].c_str());
					lineseg[idx].y1 = atoi(words[1].c_str());
					lineseg[idx].x2 = atoi(words[2].c_str());
					lineseg[idx].y2 = atoi(words[3].c_str());
					idx++;
				}
				if (num_of_line == count)
				{
					input_type = 1;
					if (idx != num_of_line)
					{
						num_of_line = idx;
						lineseg = (Line*)realloc(lineseg, sizeof(Line)*num_of_line);
					}
					idx = 0;
					count = 0;
				}
			}
			else { // Input for actual information of dots.
				for (int i = 0; i < 2; i++)
				{
					if (i % 2 == 0) // x ÁÂÇ¥
					{
						mode = 0;
					}
					else
					{
						mode = 1;
					}
					if (!isOnScreen(mode, atoi(words[i].c_str())))
					{
						break_flag = 1;
						break;
					}
				}
				if (!break_flag)
				{
					dot[idx].x1 = atoi(words[0].c_str());
					dot[idx].y1 = atoi(words[1].c_str());
					idx++;
				}
				
				if (count == num_of_dot)
				{
					input_type = 0;
					if (idx != num_of_dot)
					{
						num_of_dot = idx;
						dot = (Dot*)realloc(dot, sizeof(Dot)*num_of_dot);
					}
					idx = 0;
				}
			}
		} // End of else if.
		
	} // End of for-loop (Read file line by line).
	cout << "The number of line is: " << num_of_line << endl;
	cout << "The number of dot is: " << num_of_dot << endl;

	sortDot(dot);
	//debug print
	
	for (int i = 0; i < num_of_line; i++)
	{
		printf("%d %d %d %d\n", lineseg[i].x1, lineseg[i].y1, lineseg[i].x2, lineseg[i].y2);
	}
	for (int i = 0; i < num_of_dot; i++)
	{
		printf("%d %d\n", dot[i].x1, dot[i].y1);
	}
	dot_index = 0;
	//initializeWaterLines();
}

void ofApp::initializeWaterLines() {
	
}

void ofApp::sortDot(Dot* dot) {
	for (int i = 0; i < num_of_dot-1; i++)
	{
		for (int j = 0; j < num_of_dot - i - 1; j++)
		{
			if (dot[j].x1 > dot[j + 1].x1)
			{
				swapDot(dot, j);
			}
		}
	}
	return;
}

void ofApp::swapDot(Dot* dot, int n)
{
	int x = dot[n].x1;
	int y = dot[n].y1;
	dot[n].x1 = dot[n + 1].x1;
	dot[n].y1 = dot[n + 1].y1;
	dot[n + 1].x1 = x;
	dot[n + 1].y1 = y;
	return;
}

int ofApp::isOnScreen(int mode, int data)
{
	if (mode == 0) // x ÁÂÇ¥
	{
		if (data > 1024 || data < 0) return 0;
	}
	else // yÁÂÇ¥
	{
		if (data > 728 || data < 0) return 0;
	}
	return 1;
}