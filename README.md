RenderE
====================================

Simple render engine for OpenGL

Note: RenderE is no longer maintained. Instead checkout :

* https://github.com/mortennobel/SimpleRenderEngine
* http://www.github.com/mortennobel/kick

## DESCRIPTION

The purpose of the render is to create a basic render engine for the OpenGL 3.0.

The goal of the project is:

* Simple code
* Avoid using any deprecated code for OpenGL
* Wrap OpenGL calls
* Create a simple scenegraph used in the rendering
* Comply with the Google C++ Style Guide
 
Dependencies:

* GLEW
* glm (OpenGL Mathematics)
* Xerces-C++
* libPNG (optional texture loader)
* zlib (optional - but required for libPNG)
* FBX SDK (optional - model loader)

## Features

* Shader based (GLSL)
* Component based scene graph
* Model loading (FBX, Collada)
* Scene descriptions in XML

## Todo

* View frustum culling
* Particle system
* Deferred shading
* Post processing effects (SSAO, Bloom
* Replace Xerces with TinyXml (http://www.grinninglizard.com/tinyxml/)

## INSTALLATION

[Todo create documentation]

## License

Copyright Morten Nobel-Joergensen (http://www.nobel-joergensen.com)

License lgpl 3.0 (http://www.gnu.org/licenses/lgpl-3.0.txt)

