/*
    File:       Window-001.cpp
    Author:     Adam Haynes
    Date:       08-11-2010
*/

/*
    Window Reshaping
    
    Projection Matrix ( 4x4 ):
        Used to map a 3D scene to a 2D plane ( Color Buffer )
        Requires    - Angle in degrees of our FOV ( Field of view )
                    - Aspect Ratio of our 2D rendering plane
                    - Near and Far planes that bound the render
    
    Model View Matrix ( Transformation Matrix ):
        Used to place geometry ( location and rotation ) at any given time.
        
    Texture Matrix:
        Used to position and rotatre textures in much the same was as the 
        Model View Matrix ( You usually wont touch it )
*/

// Setup Header files
// #include // GLEW
// #include // GLUT

// function headers
void display(void);
void reshape(int width, int height);

/*
    Function: Main entry point ( Application main )

    Flow:
        - Init GLUT
        - Setup Window Buffers ( Single buffer only )
        - Setup Window Width, Height, X, Y Position
        - Create Window with title
        - Point GLUT to display function for rendering
        - Point GLUT to reshape function for changing the size of the viewport
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
    //      and the reshping function
    glutDisplayFunc(display);
    glutReshapeFunc(reshape); 
    
    // Run the main loop which will handle closing of the application
    glutMainLoop();
}

/*
    Function: Runs the application display
    Flow:
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