#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>

//angle of rotation
	float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, angle=0.0;

//positions of the cubes
	float positionz[10];
	float positionx[10];

// Mouse positions
	float lastx, lasty;

void cubepositions (void) 
{ //set the positions of the cubes

    for (int i=0;i<10;i++)
    {
    positionz[i] = rand()%5 + 5;
    positionx[i] = rand()%5 + 5;
    }
}

//draw the cube
void cube (void) 
{
   for (int i=0;i<10;i++)
	{
   	glPushMatrix();
		glTranslated(-positionx[i + 1] * 10, 0, -positionz[i + 1] * 10); //translate the cube
   	glTranslated(-positionx[i + 1] * 10, 0, -positionz[i + 1] * 10); //translate the cube
    	glutSolidCube(2); //draw the cube
      glPopMatrix();
    }
}

void mouseMovement(int x, int y) 
{
	int diffx=x-lastx; //check the difference between the current x and the last x position
	int diffy=y-lasty; //check the difference between the current y and the last y position
	lastx=x; //set lastx to the current x position
	lasty=y; //set lasty to the current y position
	xrot += (float) diffy; //set the xrot to xrot with the addition of the difference in the y position
	yrot += (float) diffx;// set the xrot to yrot with the addition of the difference in the x position
}

void init (void) 
{
	cubepositions();
}

void enable (void) 
{
    glEnable (GL_DEPTH_TEST); //enable the depth testing
    glEnable (GL_LIGHTING); //enable the lighting
    glEnable (GL_LIGHT0); //enable LIGHT0, our Diffuse Light
    glShadeModel (GL_SMOOTH); //set the shader to smooth shader

}

void camera (void) 
{
    glRotatef(xrot,1.0,0.0,0.0);  //rotate our camera on the x-axis (left and right)
    glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
    glTranslated(-xpos,-ypos,-zpos); //translate the screen to the position of our camera
}

void display (void) 
{
    glClearColor (0.0,0.0,0.0,1.0); //clear the screen to black
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
    glLoadIdentity();  
    camera();
    enable();
    cube(); //call the cube drawing function
    glutSwapBuffers(); //swap the buffers
    angle++; //increase the angle
}

void reshape (int w, int h) 
{
    glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
    glMatrixMode (GL_PROJECTION); //set the matrix to projection

    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0); //set the perspective (angle of sight, width, height, ,depth)
    glMatrixMode (GL_MODELVIEW); //set the matrix back to model

}

void keyboard (unsigned char key, int x, int y) 
{
    if (key=='q')
    {
	    xrot += 1;
   	 if (xrot >360) xrot -= 360;
    }
    if (key=='z')
    {
    	xrot -= 1;
    	if (xrot < -360) xrot += 360;
    }
    if (key=='w')
    {
    	float xrotrad, yrotrad;
    	yrotrad = (yrot / 180 * 3.141592654f);
    	xrotrad = (xrot / 180 * 3.141592654f); 
    	xpos += float(sin(yrotrad)) ;
    	zpos -= float(cos(yrotrad)) ;
    	ypos -= float(sin(xrotrad)) ;
    }
    if (key=='s')
    {
    	float xrotrad, yrotrad;
    	yrotrad = (yrot / 180 * 3.141592654f);
    	xrotrad = (xrot / 180 * 3.141592654f); 
    	xpos -= float(sin(yrotrad));
    	zpos += float(cos(yrotrad)) ;
    	ypos += float(sin(xrotrad));
    }
    if (key=='d')
    {
    	float yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xpos += float(cos(yrotrad)) * 0.2;
		zpos += float(sin(yrotrad)) * 0.2;	
    }
    if (key=='a')
    {
    	float yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xpos -= float(cos(yrotrad)) * 0.2;
		zpos -= float(sin(yrotrad)) * 0.2;	
    }
    if (key==27)
    {
    	exit(0);
    }
}

int main (int argc, char **argv) 
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH); //set the display to Double buffer, with depth
    glutInitWindowSize (500, 500); //set the window size glutInitWindowPosition (100, 100); //set the position of the window
    glutCreateWindow ("A basic OpenGL Window : Testing Camera"); //the caption of the window
    init (); //call the init function
    glutDisplayFunc (display); //use the display function to draw everything
    glutIdleFunc (display); //update any variables in display, display can be changed to anyhing, as long you move the 
	 //variables to be updated, in this case, angle++;
    glutReshapeFunc (reshape); //reshape the window accordingly
		glutPassiveMotionFunc(mouseMovement);
    glutKeyboardFunc (keyboard); //check the keyboard
    glutMainLoop (); //call the main loop
    return 0;
}
