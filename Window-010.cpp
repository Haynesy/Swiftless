/*
    File:       Window-010.cpp
    Author:     Adam Haynes
    Date:       16-11-2010
*/

/*
    OpenGL Scaling
        

    Compile:
        g++ Window-010.cpp -lglut -lGLU -o Window
*/

// Setup Header files
#include "GL/glut.h"
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
    
    // Objects
    void renderPrimitive(void);
    
// Global Variables
    bool* keyStates         = new bool[256]; // Hold 256 ASCII characters
    bool* keySpecialStates  = new bool[256]; // Hold 256 Special characters
    
    bool movingUp           = false;
    float yLocation         = 0.0f;
    float yRotationAngle    = 0.0f;
GLfloat angle = 0.0;
/*
    Function: Main entry point ( Application main )

    Flow:
        - Init GLUT
        - Setup Window Buffers ( Double render buffer as well as support 
            for Alpha)
        - Setup Window Width, Height, X, Y Position
        - Create Window with title
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

    // Clear keyboard state
    initKeyboardState();

    // Set up a basic buffer (only single buffered for now)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    // Set width ,height, X Pos and Y pos of window
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(windowXPos, windowYPos);

    // Create window with title
    glutCreateWindow("Basic Window!");

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
        - Enable blending, Set up how objects blend
        - Load the Identity Matrix ( Poorly named me thinks )
            to reset our drawing locations
        - Move the scene back 5 units as the camera is located at ( 0, 0, 0 )
        - Render object to screen ( Will render at location: 0, 0, -5 )
        - Flush all calls from OpenGL to the window
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
    glClearColor(0.0f, 0.0f, 0.5f, 1.0f);

    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Enable blending in OpenGL
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Reset Identity Matrix
    glLoadIdentity();

    gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    renderPrimitive();
    glutSwapBuffers();
    angle ++;
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
    if ( keyStates['a'] ){
        // Do stuff
    }
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
    Flow:       Create objects
    End State:  Object rendered to viewport and is visible to the user
*/
void renderPrimitive(void)
{
	/*
    glColor3f(0.0f, 0.0f, 1.0f); // Set the colour of the square to blue

    glBegin(GL_QUADS);
        glVertex3f(-1.0f,   -1.0f,  0.0f); // Bottom left corner
        glVertex3f(-1.0f,   1.0f,   0.0f); // Top left corner
        glVertex3f(1.0f,    1.0f,   0.0f); // Top right corner
        glVertex3f(1.0f,    -1.0f,  0.0f); // Bottom right corner
    glEnd();
    */
	glScalef(2, 0.5, 1);
	glRotatef(angle, 1.0, 0.0, 0.0);
    	glRotatef(angle, 0.0, 1.0, 0.0);
    	glRotatef(angle, 0.0, 0.0, 1.0);
    	glColor4f(1.0, 0.0, 0.0, 0.2); 
	//set the color and alpha of the cube
    	glutSolidCube(2);
    	glColor4f(0.0, 1.0, 0.0, 0.5); 
	//set the color and alpha of the cube
    	glutSolidCube(1);
}
