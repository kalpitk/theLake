#include<bits/stdc++.h>
#include <GL/glut.h>
#include  "../include/vec3f.hpp"
#include  "../include/terrain.hpp"
#include  "../include/lake.hpp"
#include  "../include/imageloader.hpp"
#include  "../include/renderer.hpp"

Terrain* _terrain = new Terrain(-25);
Lake* _lake = new Lake(-26);

int main(int argc, char** argv) {
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Interactive Lake");
	initRendering();

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(keyboard);

	glutMouseFunc(mouse);
    glutMotionFunc(mouseMove);

	glutTimerFunc(50, timer, 0);
	glutReshapeFunc(handleResize);

	glutMainLoop();
	return 0;
}
