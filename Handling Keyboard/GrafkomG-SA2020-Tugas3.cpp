#include <iostream>
#include <glut.h>
#include <vector>
#include<WinUser.h>

using namespace std;
vector<char> tty;
vector<char>::iterator stack;
void systemout(void);
int Mouse_x = 0, Mouse_y = 0;

void keyboardA(unsigned char key, int x, int y) {
	stack = find(tty.begin(), tty.end(), key);
	if (stack == tty.end()) tty.push_back(key);
	systemout();
}

void keyboardB(unsigned char key, int x, int y) {
	stack = find(tty.begin(), tty.end(), key);
	if (stack != tty.end()) {
		int index = distance(tty.begin(), stack);
		tty.erase(tty.begin() + index);
	} systemout();
}
void systemout() {
	system("cls");
	cout << "Mouse_x: " << Mouse_y << " | " << "Mouse_y: " << Mouse_y << endl;
	for (auto it : tty) cout << it << ' ';
	glutPostRedisplay();
}

void touchpad(int x, int y) {
	Mouse_x = x;
	Mouse_y = y;
	systemout();
}

void touchpadButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && (state == GLUT_DOWN || state == GLUT_UP)) {
		Mouse_x = x;
		Mouse_y = y;
		std::cout << "\t cursor at (" << Mouse_x << ", " <<
			Mouse_y << ")" << std::endl;
	}if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		float x_min = (-x + 500) / 512;
		float x_max = (x - 500) / 512;
		float y_min = (-y + 500) / 512;
		float y_max = (y - 500) / 512;
		gluOrtho2D(x_min, x_max, y_min, y_max);
		std::cerr << x << ", " << y << std::endl;
	}
	systemout();
}

void mydisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPopMatrix(); // done with stack
	glutSwapBuffers();
	glFlush();
}

void myinit() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1000, 0, 1000);
	Mouse_x = Mouse_y = 500; // middle of window
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(50, 50);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Loss Pokoke");
	glutDisplayFunc(mydisplay);
	glutPassiveMotionFunc(touchpad);
	glutMouseFunc(touchpadButton);			  
	glutKeyboardFunc(keyboardA);       
	glutKeyboardUpFunc(keyboardB);       
	myinit();
	glutMainLoop();
	return 0;
}