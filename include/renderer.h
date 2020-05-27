#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

void update(int value);
void drawScene();
void handleResize(int w, int h);
void initRendering();
void keyboard(unsigned char,int,int);
void keyboardSpecial(int,int,int);
void mouse(int,int,int,int);
void mouseMove(int,int);
void timer(int value);
void cleanup();

#endif