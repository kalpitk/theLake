#include<bits/stdc++.h>
#include <GL/glut.h>
#include  "../include/vec3f.h"
#include  "../include/terrain.h"
#include  "../include/imageloader.h"
#include  "../include/renderer.h"

Terrain* _terrain = new Terrain(-25);

int main(int argc, char** argv) {
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3D Map simulator");
	initRendering();
	
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);
	// glutSetCursor(GLUT_CURSOR_NONE);
	// glutPassiveMotionFunc(mouse);
	glutMouseFunc(mouse);
    glutMotionFunc(mouseMove);
	glutReshapeFunc(handleResize);
	
	glutMainLoop();
	return 0;
}
