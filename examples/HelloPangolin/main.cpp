#include <pangolin/display/display.h>
#include <pangolin/display/view.h>
#include <pangolin/handler/handler.h>
#include <pangolin/gl/gldraw.h>

#include <pangolin/display/display.h>
#include <pangolin/gl/glvbo.h>

// Here is an example of Pangolin being used *just* for windowing.
// We're using
void ClassicVBO()
{
    // Create a 500x500 pixel application window with an OpenGL Context
    // By default the window is double buffered if available.
    // Load any available OpenGL Extensions (through GLEW)
    pangolin::CreateWindowAndBind("Classic GL Triangle", 500, 500);

    // List coordinates of a triangle
    // These vertices will be relative to the coordinates of the window
    // which default in OpenGL to +/- 1.0 in X and Y (first two vertex ordinates)
    const float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // Create an OpenGL Buffer to store these coordinates
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // Set that buffer as the current GL buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Copy our host data into the currently bound OpenGL buffer
    // GL_STATIC_DRAW is a hint about how we'll use the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // We want the background to be purple
    glClearColor(0.64, 0.5, 0.81, 0.0);

    // We want our triangle to be a pleasant shade of blue!
    glColor3ub(73, 182, 255);

    // We keep rendering in a loop so that the triangle will keep showing
    // and get adjusted as the window is resized. Press Escape or close the
    // window to exit the Pangolin loop.
    while( !pangolin::ShouldQuit() )
    {
        // Clear the window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set our buffer as the current one for OpenGL
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        // This buffer contains floating point vertices with 3 dimensions.
        // They starts from the 0th element and are packed without padding.
        glVertexPointer(3, GL_FLOAT, 0, 0);

        // Use Them!
        glEnableClientState(GL_VERTEX_ARRAY);

        // Connect the first 3 of these vertices to form a triangle!
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Disable the stuff we enabled...
        glDisableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Process any windowing events and swap the back and front
        // OpenGL buffers if available.
        pangolin::FinishFrame();
    }

    // Deallocate the OpenGL buffer we made
    glDeleteBuffers(1, &VBO);
}

void PangolinVBO()
{
    pangolin::CreateWindowAndBind("Simple GL Triangle", 500, 500);

    pangolin::GlBuffer vbo(pangolin::GlArrayBuffer,
        std::vector<Eigen::Vector3f>{
           {-0.5f, -0.5f, 0.0f},
           { 0.5f, -0.5f, 0.0f },
           { 0.0f,  0.5f, 0.0f }
        }
    );

    glClearColor(0.64f, 0.5f, 0.81f, 0.0f);
    glColor3f(0.29f, 0.71f, 1.0f);

    while( !pangolin::ShouldQuit() )
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        pangolin::RenderVbo(vbo, GL_TRIANGLES);
        pangolin::FinishFrame();
    }
}


int main( int /*argc*/, char** /*argv*/ )
{
    PangolinVBO();

    return 0;
}
