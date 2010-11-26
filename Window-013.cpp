/*
    File:       Window-013.cpp
    Author:     Adam Haynes
    Date:       19-11-2010
*/

/*
    OpenGL Lighting types

    Compile:
        -E will give out additional compiling information
        g++ -E Window-013.cpp -lglut -lGLU -o Window
*/

// Setup Header files
    #ifdef __WIN32__
        #include <windows.h>
    #endif
    #ifdef __APPLE__
        #include "GLUT/glut.h"
    #else
        #include "GL/glut.h"
    #endif
    #include "GL/glu.h"
    #include "GL/gl.h"

// Function headers
    // Display Functions
    void display(void);
    void reshape(int width, int height);

    // Keyboard Functions
    void keyPressed(unsigned char key, int x, int y);
    void keyUp(unsigned char key, int x, int y);
    void initKeyboardState(void);
    void keyOperations(void);
    void keySpecialPressed (int key, int x, int y);
    void keySpecialUp (int key, int x, int y);
    void keySpecialOperations(void);

    // Lighting

        // Diffuse colour
        GLfloat diffuseLightRed             = 1.0;
        GLfloat diffuseLightGreen           = 1.0;
        GLfloat diffuseLightBlue            = 1.0;

        // Ambient colour
        GLfloat ambientLightRed             = 1.0;
        GLfloat ambientLightGreen           = 1.0;
        GLfloat ambientLightBlue            = 1.0;

        // Light position
        GLfloat lightX                      = 0.0;
        GLfloat lightY                      = 0.0;
        GLfloat lightZ                      = 1.0;
        GLfloat lightW                      = 0.0;

    void initLighting(void);
    void light(void);

    // Objects
    void renderPrimitive(void);

// Global Variables
    bool* keyStates         = new bool[256]; // Hold 256 ASCII characters
    bool* keySpecialStates  = new bool[256]; // Hold 256 Special characters

    bool movingUp           = false;
    float yLocation         = 0.0f;
    float yRotationAngle    = 0.0f;
GLfloat angle = 0.0;
GLfloat ViewPositionX = 0.0;
GLfloat ViewPositionZ = -5.0;
GLfloat ViewPositionY = 0.0;
/*
    Function: Main entry point ( Application main )

    Flow:
        - Init GLUT
        - Setup Window Buffers ( Double render buffer as well as support
            for Alpha, and Depth buffer)
        - Setup Window Width, Height, X, Y Position
        - Create Window with title
        - Setup Lighting
        - Set callback to display function for rendering
        - Set callback to reshape function for changing the size of the viewport
        - Set callback to keyPressed and keyUp to handle keyboard input
        - Tell GLUT to enter main loop
            E.g
                while( running ) {
                    doApplicationStuff();
                }
    End State:
        Creation and running of an application as well as closing and
        releasing all resources used by the application
*/
int main(int argc, char **argv)
{
    int windowWidth     = 500;
    int windowHeight    = 500;
    int windowXPos      = 100;
    int windowYPos      = 100;

    // Initialize GLUT with command line input
    glutInit(&argc, argv);

    // Set up a basic buffer (only single buffered for now)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

    // Set width ,height, X Pos and Y pos of window
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(windowXPos, windowYPos);

    // Create window with title
    glutCreateWindow("Basic Window with lighting!");

    // Clear keyboard state
    initKeyboardState();

    // Setup lighting
    initLighting();

    // Setup Idle and Display to both use the 'display' function,
    // set the reshape event to use the 'reshape' funciton
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);

    // Set keyboard callback function to handle key pressing and releasing
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);
    glutSpecialFunc(keySpecialPressed);
    glutSpecialUpFunc(keySpecialUp);

    // Run the main loop which will handle closing of the application
    glutMainLoop();
}

/*
    Function: Runs the application display
    Flow:
        - Check key operations as they may have adverse effects on the
            display state e.g may require the display matrix to move forward
        - Set Clear color ( RED in this case )
        - Clear the color buffer ( Using GL_COLOR_BUFFER_BIT )
            information in other buffers will come later
        - Load the Identity Matrix ( Poorly named me thinks )
            to reset our drawing locations
        - Move the camera to look in the required direction
        - Render object to screen ( Will render at location: 0, 0, -5 )
        - Swap buffers
        - Calcualte transofrmations for object
    End State:
        Rendering of picture to the the window of the application

*/
void display(void)
{
    /*
        Check any keyboard operations that may alter the display of the
        next frame
    */
    keyOperations();
    keySpecialOperations();

    // Clear color is set to RED
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

    // Set lights up
    GLfloat DiffuseLight[] = { diffuseLightRed, diffuseLightGreen, diffuseLightBlue };
    GLfloat AmbientLight[] = { ambientLightRed, ambientLightGreen, ambientLightBlue };
    glLightfv (GL_LIGHT0, GL_DIFFUSE, DiffuseLight); //change the light accordingly
    glLightfv (GL_LIGHT1, GL_AMBIENT, AmbientLight); //change the light accordingly

    // Set light position
    GLfloat LightPosition[] = {lightX, lightY, lightZ, lightW}; // lightW indicates if it is a point light
    glLightfv (GL_LIGHT0, GL_POSITION, LightPosition); //change the light accordingly

    // Reset Identity Matrix
    //glLoadIdentity();

    // Light the scene
    //light();

    // Look at a point
    gluLookAt (ViewPositionX, ViewPositionY, ViewPositionZ - 10.0, ViewPositionX, ViewPositionY, ViewPositionZ, 0.0, 1.0, 0.0);

    // Render objects
    renderPrimitive();

    // Swap the old buffer out for the new rendered image
    glutSwapBuffers();

    // Increase angle
    angle += 0.1;
}


/*
    Function: Reshapes the viewport when the window is resized
    Flow:
        - Reshape the viewport to the new width and height
        - Switch over to and reset the Projection Matrix
        - Update the Perspective for the new width and height
        - Switch matrix mode back to model view
    End State:
        The viewport should be reshaped to match the new window dimensions
        while making sure the rendering stays consistent
*/
void reshape(int width, int height)
{
    // Change the viewport to the size of the window
    // Note: 0, 0 corresponds to the bottom left corner
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    /*
        Switch to the projection matrix so that we can manipulate
        how our scene is viewed
    */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // Reset projection matrix so as not to cause artifacts

    int fieldOfView             = 60; // 30 degress left and 30 right
    GLfloat aspectRatio         = (GLfloat)width / (GLfloat)height;
    GLfloat nearClippingPlane   = 1.0f;
    GLfloat farClippingPlane    = 100.0f;

    // Set the projection perspective
    gluPerspective(fieldOfView, aspectRatio, nearClippingPlane, farClippingPlane);

    // Reset back to Model View Matrix
    glMatrixMode(GL_MODELVIEW);
}
/*
    Function:   Handles key pressing
    Flow:       Set keyState array at key position to true
    End State:  Specified key set to true in keyState array
*/
void keyPressed(unsigned char key, int x, int y)
{
    keyStates[key] = true; // Set the state of the current key to pressed
}

/*
    Function:   Handles key releasing
    Flow:       Set keyState array at key position to false
    End State:  Specified key set to false in keyState array
*/
void keyUp(unsigned char key, int x, int y)
{
    keyStates[key] = false; // Set the state of the current key to released
}

/*
    Function:   Reset keyState variable all to false
    Flow:       Cycle through entire keyState array and set all to false
    End State:  Entire ketStates array to be set to false
*/
void initKeyboardState(void)
{
    for(int i = 0; i < 256; i++)
        keyStates[i] = false;

    for(int i = 0; i < 256; i++)
        keySpecialStates[i] = false;
}

/*
    Function: Process keyPress or keyRelease operations
    Flow:
    End State:
*/
void keyOperations(void)
{
    // Light values
    if ( keyStates['r'] ) {
        diffuseLightRed 	= 1.0; //change light to red
        diffuseLightGreen 	= 0.0;
        diffuseLightBlue 	= 0.0;
    }
    if ( keyStates['g'] ) {
        diffuseLightRed 	= 0.0; //change light to green
        diffuseLightGreen	= 1.0;
        diffuseLightBlue 	= 0.0;
    }
    if ( keyStates['b'] ) {
        diffuseLightRed 	= 0.0; //change light to blue
        diffuseLightGreen 	= 0.0;
        diffuseLightBlue 	= 1.0;
    }

	// Viewer Position
	if ( keyStates['w'] )
		ViewPositionZ += 0.1;
	if ( keyStates['s'] )
		ViewPositionZ -= 0.1;
	if ( keyStates['a'] )
		ViewPositionX += 0.1;
	if ( keyStates['d'] )
		ViewPositionX -= 0.1;

    // Light Position
    if ( keyStates['i'] )
        lightY += 1.0; //move the light up

    if ( keyStates['k'] )
        lightY -= 1.0; //move the light down

    if ( keyStates['j'] )
        lightX -= 1.0; //move the light left

    if ( keyStates['l'] )
        lightX += 1.0; //move the light right

}

/*
    Function: Process keyPress or keyRelease operations for special characters
    Flow:
    End State:
*/
void keySpecialOperations(void)
{
    if (keySpecialStates[GLUT_KEY_LEFT]) {
        // If the left arrow key has been pressed
        // Perform left arrow key operations
    }
}

/*
    Function:   Handles special key pressing
    Flow:       Set keySpecialStates array at key position to true
    End State:  Specified key set to true in keySpecialStates array
*/
void keySpecialPressed (int key, int x, int y)
{
    keySpecialStates[key] = true; // Set the state of the current key to pressed
}

/*
    Function:   Handles special key releasing
    Flow:       Set keySpecialStates array at key position to false
    End State:  Specified key set to false in keySpecialStates array
*/
void keySpecialUp (int key, int x, int y)
{
    keySpecialStates[key] = false; // Set the state of the current key to released
}

/*
    Function:   Renders and object to the viewport ( Square in thsi case )
    Flow:       - Set rotation
                - Set Color of object
                - Create object
    End State:  Object created and positioned
*/
void renderPrimitive(void)
{

    glRotatef(angle, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glColor3f(0.0, 0.0, 1.00);
    glutSolidCube(2);
}

void initLighting(void)
{
    glEnable (GL_DEPTH_TEST); //enable the depth testing
    glEnable (GL_LIGHTING); //enable the lighting
    glEnable (GL_LIGHT0); //enable LIGHT0, our Diffuse Light
    glEnable (GL_LIGHT1); //enable LIGHT1, our Ambient Light
    glShadeModel (GL_SMOOTH); //set the shader to smooth shader
}

void light(void)
{
/*
glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);
*/
}
