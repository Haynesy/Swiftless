/*
    File:       Window-003.cpp
    Author:     Adam Haynes
    Date:       08-11-2010
*/

/*
    Keyboard input
        Key press amd key release as well as buffering.
    
    Compile:
        g++ Window-003.cpp -lglut -lGLU -o Window
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
    
// Global Variables
    bool* keyStates = new bool[256]; // Hold 256 ASCII characters
    bool* keySpecialStates = new bool[256]; // Hold 256 Special characters
/*
    Function: Main entry point ( Application main )

    Flow:
        - Init GLUT
        - Setup Window Buffers ( Single buffer only )
        - Setup Window Width, Height, X, Y Position
        - Create Window with title
        - Set callback to display function for rendering
        - Set callback to reshape function for changing the size of the viewport
        - Set callback to keyPressed and keyUp to handle keyboard input
        - Tell GLUT to enter main loop
            E.g
                while(true) {
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
    glutInitDisplayMode(GLUT_SINGLE);

    // Set width ,height, X Pos and Y pos of window
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(windowXPos, windowYPos);

    // Create window with title
    glutCreateWindow("Basic Window!");

    // Set display function ( Will be run on every refresh ) 
    //      and the reshping function
    glutDisplayFunc(display);
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
        - Flush all calls from OpenGL to the window
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
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Reset Identity Matrix
    glLoadIdentity();

    // Flush all commands to the window
    glFlush();
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
