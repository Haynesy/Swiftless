/*
    File:       Window-001.cpp
    Author:     Adam Haynes
    Date:       08-11-2010
*/

/*
    OpenGL - Open source Graphics Library
    
    GLUT ( OpenGL Utility Toolkit ) - Allows for simple window setup and is 
        cross platform
    
    GLEW ( OpenGL Extension Wrangler ) - Allows for easy to call 
        OpenGL extensions

Install -
    FreeGLUT – http://freeglut.sourceforge.net/
    GLEW – http://glew.sourceforge.net/

    Win32 Console application
    Add "glew32.lib" and "freeglut.lib" as linker libraries
    
*/

// Setup Header files
// #include // GLEW
// #include // GLUT

void display(void);

/*
    Function: Main entry point ( Application main )

    Flow:
        - Init GLUT
        - Setup Window Buffers ( Single buffer only )
        - Setup Window Width/Height X, Y Position
        - Create Window with title
        - Point GLUT to display function
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

    // Set up a basic buffer (only single buffered for now)
    glutInitDisplayMode(GLUT_SINGLE);

    // Set width ,height, X Pos and Y pos of window
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(windowXPos, windowYPos);

    // Create window with title
    glutCreateWindow("Basic Window!");
    
    // Set display function ( Will be run on every refresh )
    glutDisplayFunc(display);
    
    // Run the main loop which will handle closing of the application
    glutMainLoop();
}

/*
    Funciton: Runs the application display
    Flow:
        - Set Clear color ( RED in this case )
        - Clear the color buffer ( Using GL_COLOR_BUFFER_BIT )
            Other buffers will be later
        - Load the Identity Matrix ( Poorly named me thinks )
            to reset our drawing locations
        - Flush all calls from OpenGL to the window
    
    End State:
        Rendering of picture to the the window of the application
        
*/
void display(void)
{
    // Clear color is set to RED
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Reset Identity Matrix
    glLoadIdentity();

    // Flush all commands to the window
    glFlush();
}