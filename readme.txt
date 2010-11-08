RenderE

Simple render engine for OpenGL 3.0/3.1

The purpose of the render is to create a basic render engine for the OpenGL 3.0.

The goal of the project is:
 - Simple and well documented code
 - Avoid using any deprecated code for OpenGL
 - No OpenGL exposed in headers (allowing ports to other platforms such as DirectX)
 - Create a simple scenegraph used in the rendering
 - Comply with the Google C++ Style Guide
 
Keep dependencies to a minimum:
 - GLEW
 - Boost
 - libPNG (optional texture loader)
 - zlib (optional - but required for libPNG)
 