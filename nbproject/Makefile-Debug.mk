#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as
PROC=proc

# Macros
CND_PLATFORM=GNU-MacOSX
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/render_e/Component.o \
	${OBJECTDIR}/src/render_e/math/Vector4.o \
	${OBJECTDIR}/src/render_e/shaders/Shader.o \
	${OBJECTDIR}/src/render_e/Camera.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/render_e/math/Vector2.o \
	${OBJECTDIR}/src/render_e/RenderBase.o \
	${OBJECTDIR}/src/render_e/shaders/ShaderFileDataSource.o \
	${OBJECTDIR}/src/render_e/Mesh.o \
	${OBJECTDIR}/src/render_e/MeshComponent.o \
	${OBJECTDIR}/src/render_e/math/Mathf.o \
	${OBJECTDIR}/src/render_e/FBXLoader.o \
	${OBJECTDIR}/src/render_e/SceneObject.o \
	${OBJECTDIR}/src/render_e/shaders/DefaultShaders.o \
	${OBJECTDIR}/src/render_e/textures/PNGFileTextureDataSource.o \
	${OBJECTDIR}/src/render_e/Transform.o \
	${OBJECTDIR}/src/render_e/SceneXMLParser.o \
	${OBJECTDIR}/src/render_e/Material.o \
	${OBJECTDIR}/src/render_e/Light.o \
	${OBJECTDIR}/src/render_e/textures/Texture2D.o \
	${OBJECTDIR}/src/render_e/textures/CubeTexture.o \
	${OBJECTDIR}/src/render_e/textures/TextureDataSource.o \
	${OBJECTDIR}/src/render_e/math/Quaternion.o \
	${OBJECTDIR}/src/render_e/math/Matrix44.o \
	${OBJECTDIR}/src/render_e/textures/TextureBase.o \
	${OBJECTDIR}/src/render_e/math/Vector3.o \
	${OBJECTDIR}/src/render_e/MeshFactory.o \
	${OBJECTDIR}/src/render_e/shaders/ShaderDataSource.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f3 \
	${TESTDIR}/TestFiles/f1

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64
CXXFLAGS=-m64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=lib/osx/libGLEW.a lib/osx/libpng12.a lib/osx/libz.a /Applications/Autodesk/FBXSDK20113_1/lib/libfbxsdk_gcc4_ubd.a lib/osx/libxerces-c.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rendere

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rendere: lib/osx/libGLEW.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rendere: lib/osx/libpng12.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rendere: lib/osx/libz.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rendere: /Applications/Autodesk/FBXSDK20113_1/lib/libfbxsdk_gcc4_ubd.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rendere: lib/osx/libxerces-c.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rendere: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -framework GLUT -framework OPENGL -lm -lstdc++ -liconv -fexceptions -lz -framework Carbon -framework SystemConfiguration -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rendere ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/render_e/Component.o: src/render_e/Component.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/Component.o src/render_e/Component.cpp

${OBJECTDIR}/src/render_e/math/Vector4.o: src/render_e/math/Vector4.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/math
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/math/Vector4.o src/render_e/math/Vector4.cpp

${OBJECTDIR}/src/render_e/shaders/Shader.o: src/render_e/shaders/Shader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/shaders
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/shaders/Shader.o src/render_e/shaders/Shader.cpp

${OBJECTDIR}/src/render_e/Camera.o: src/render_e/Camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/Camera.o src/render_e/Camera.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/render_e/math/Vector2.o: src/render_e/math/Vector2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/math
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/math/Vector2.o src/render_e/math/Vector2.cpp

${OBJECTDIR}/src/render_e/RenderBase.o: src/render_e/RenderBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/RenderBase.o src/render_e/RenderBase.cpp

${OBJECTDIR}/src/render_e/shaders/ShaderFileDataSource.o: src/render_e/shaders/ShaderFileDataSource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/shaders
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/shaders/ShaderFileDataSource.o src/render_e/shaders/ShaderFileDataSource.cpp

${OBJECTDIR}/src/render_e/Mesh.o: src/render_e/Mesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/Mesh.o src/render_e/Mesh.cpp

${OBJECTDIR}/src/render_e/MeshComponent.o: src/render_e/MeshComponent.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/MeshComponent.o src/render_e/MeshComponent.cpp

${OBJECTDIR}/src/render_e/math/Mathf.o: src/render_e/math/Mathf.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/math
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/math/Mathf.o src/render_e/math/Mathf.cpp

${OBJECTDIR}/src/render_e/FBXLoader.o: src/render_e/FBXLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/FBXLoader.o src/render_e/FBXLoader.cpp

${OBJECTDIR}/src/render_e/SceneObject.o: src/render_e/SceneObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/SceneObject.o src/render_e/SceneObject.cpp

${OBJECTDIR}/src/render_e/shaders/DefaultShaders.o: src/render_e/shaders/DefaultShaders.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/shaders
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/shaders/DefaultShaders.o src/render_e/shaders/DefaultShaders.cpp

${OBJECTDIR}/src/render_e/textures/PNGFileTextureDataSource.o: src/render_e/textures/PNGFileTextureDataSource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/textures
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/textures/PNGFileTextureDataSource.o src/render_e/textures/PNGFileTextureDataSource.cpp

${OBJECTDIR}/src/render_e/Transform.o: src/render_e/Transform.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/Transform.o src/render_e/Transform.cpp

${OBJECTDIR}/src/render_e/SceneXMLParser.o: src/render_e/SceneXMLParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/SceneXMLParser.o src/render_e/SceneXMLParser.cpp

${OBJECTDIR}/src/render_e/Material.o: src/render_e/Material.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/Material.o src/render_e/Material.cpp

${OBJECTDIR}/src/render_e/Light.o: src/render_e/Light.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/Light.o src/render_e/Light.cpp

${OBJECTDIR}/src/render_e/textures/Texture2D.o: src/render_e/textures/Texture2D.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/textures
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/textures/Texture2D.o src/render_e/textures/Texture2D.cpp

${OBJECTDIR}/src/render_e/textures/CubeTexture.o: src/render_e/textures/CubeTexture.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/textures
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/textures/CubeTexture.o src/render_e/textures/CubeTexture.cpp

${OBJECTDIR}/src/render_e/textures/TextureDataSource.o: src/render_e/textures/TextureDataSource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/textures
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/textures/TextureDataSource.o src/render_e/textures/TextureDataSource.cpp

${OBJECTDIR}/src/render_e/math/Quaternion.o: src/render_e/math/Quaternion.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/math
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/math/Quaternion.o src/render_e/math/Quaternion.cpp

${OBJECTDIR}/src/render_e/math/Matrix44.o: src/render_e/math/Matrix44.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/math
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/math/Matrix44.o src/render_e/math/Matrix44.cpp

${OBJECTDIR}/src/render_e/textures/TextureBase.o: src/render_e/textures/TextureBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/textures
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/textures/TextureBase.o src/render_e/textures/TextureBase.cpp

${OBJECTDIR}/src/render_e/math/Vector3.o: src/render_e/math/Vector3.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/math
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/math/Vector3.o src/render_e/math/Vector3.cpp

${OBJECTDIR}/src/render_e/MeshFactory.o: src/render_e/MeshFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/MeshFactory.o src/render_e/MeshFactory.cpp

${OBJECTDIR}/src/render_e/shaders/ShaderDataSource.o: src/render_e/shaders/ShaderDataSource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/shaders
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/shaders/ShaderDataSource.o src/render_e/shaders/ShaderDataSource.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/newtestclass1.o ${TESTDIR}/tests/newtestrunner1.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/newsimpletest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/newtestclass.o ${TESTDIR}/tests/newtestrunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} lib/libGLEW.a 


${TESTDIR}/tests/newtestclass1.o: tests/newtestclass1.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/newtestclass1.o tests/newtestclass1.cpp


${TESTDIR}/tests/newtestrunner1.o: tests/newtestrunner1.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/newtestrunner1.o tests/newtestrunner1.cpp


${TESTDIR}/tests/newsimpletest.o: tests/newsimpletest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/newsimpletest.o tests/newsimpletest.cpp


${TESTDIR}/tests/newtestclass.o: tests/newtestclass.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -Ilib-include -I. -I. -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/newtestclass.o tests/newtestclass.cpp


${TESTDIR}/tests/newtestrunner.o: tests/newtestrunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -D_DEBUG -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -Ilib-include -I. -I. -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/newtestrunner.o tests/newtestrunner.cpp


${OBJECTDIR}/src/render_e/Component_nomain.o: ${OBJECTDIR}/src/render_e/Component.o src/render_e/Component.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/Component.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/Component_nomain.o src/render_e/Component.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/Component.o ${OBJECTDIR}/src/render_e/Component_nomain.o;\
	fi

${OBJECTDIR}/src/render_e/math/Vector4_nomain.o: ${OBJECTDIR}/src/render_e/math/Vector4.o src/render_e/math/Vector4.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/math
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/math/Vector4.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/math/Vector4_nomain.o src/render_e/math/Vector4.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/math/Vector4.o ${OBJECTDIR}/src/render_e/math/Vector4_nomain.o;\
	fi

${OBJECTDIR}/src/render_e/shaders/Shader_nomain.o: ${OBJECTDIR}/src/render_e/shaders/Shader.o src/render_e/shaders/Shader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/shaders
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/shaders/Shader.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/shaders/Shader_nomain.o src/render_e/shaders/Shader.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/shaders/Shader.o ${OBJECTDIR}/src/render_e/shaders/Shader_nomain.o;\
	fi

${OBJECTDIR}/src/render_e/Camera_nomain.o: ${OBJECTDIR}/src/render_e/Camera.o src/render_e/Camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/Camera.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/Camera_nomain.o src/render_e/Camera.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/Camera.o ${OBJECTDIR}/src/render_e/Camera_nomain.o;\
	fi

${OBJECTDIR}/src/main_nomain.o: ${OBJECTDIR}/src/main.o src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main_nomain.o src/main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/main_nomain.o;\
	fi

${OBJECTDIR}/src/render_e/math/Vector2_nomain.o: ${OBJECTDIR}/src/render_e/math/Vector2.o src/render_e/math/Vector2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/math
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/math/Vector2.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/math/Vector2_nomain.o src/render_e/math/Vector2.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/math/Vector2.o ${OBJECTDIR}/src/render_e/math/Vector2_nomain.o;\
	fi

${OBJECTDIR}/src/render_e/RenderBase_nomain.o: ${OBJECTDIR}/src/render_e/RenderBase.o src/render_e/RenderBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/RenderBase.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/RenderBase_nomain.o src/render_e/RenderBase.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/RenderBase.o ${OBJECTDIR}/src/render_e/RenderBase_nomain.o;\
	fi

${OBJECTDIR}/src/render_e/shaders/ShaderFileDataSource_nomain.o: ${OBJECTDIR}/src/render_e/shaders/ShaderFileDataSource.o src/render_e/shaders/ShaderFileDataSource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/shaders
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/shaders/ShaderFileDataSource.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/shaders/ShaderFileDataSource_nomain.o src/render_e/shaders/ShaderFileDataSource.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/shaders/ShaderFileDataSource.o ${OBJECTDIR}/src/render_e/shaders/ShaderFileDataSource_nomain.o;\
	fi

${OBJECTDIR}/src/render_e/Mesh_nomain.o: ${OBJECTDIR}/src/render_e/Mesh.o src/render_e/Mesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/Mesh.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/Mesh_nomain.o src/render_e/Mesh.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/Mesh.o ${OBJECTDIR}/src/render_e/Mesh_nomain.o;\
	fi

${OBJECTDIR}/src/render_e/MeshComponent_nomain.o: ${OBJECTDIR}/src/render_e/MeshComponent.o src/render_e/MeshComponent.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/MeshComponent.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/MeshComponent_nomain.o src/render_e/MeshComponent.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/MeshComponent.o ${OBJECTDIR}/src/render_e/MeshComponent_nomain.o;\
	fi

${OBJECTDIR}/src/render_e/math/Mathf_nomain.o: ${OBJECTDIR}/src/render_e/math/Mathf.o src/render_e/math/Mathf.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/math
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/math/Mathf.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/math/Mathf_nomain.o src/render_e/math/Mathf.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/math/Mathf.o ${OBJECTDIR}/src/render_e/math/Mathf_nomain.o;\
	fi

${OBJECTDIR}/src/render_e/FBXLoader_nomain.o: ${OBJECTDIR}/src/render_e/FBXLoader.o src/render_e/FBXLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/FBXLoader.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/FBXLoader_nomain.o src/render_e/FBXLoader.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/FBXLoader.o ${OBJECTDIR}/src/render_e/FBXLoader_nomain.o;\
	fi

${OBJECTDIR}/src/render_e/SceneObject_nomain.o: ${OBJECTDIR}/src/render_e/SceneObject.o src/render_e/SceneObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/SceneObject.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/SceneObject_nomain.o src/render_e/SceneObject.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/SceneObject.o ${OBJECTDIR}/src/render_e/SceneObject_nomain.o;\
	fi

${OBJECTDIR}/src/render_e/shaders/DefaultShaders_nomain.o: ${OBJECTDIR}/src/render_e/shaders/DefaultShaders.o src/render_e/shaders/DefaultShaders.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/shaders
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/shaders/DefaultShaders.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/shaders/DefaultShaders_nomain.o src/render_e/shaders/DefaultShaders.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/shaders/DefaultShaders.o ${OBJECTDIR}/src/render_e/shaders/DefaultShaders_nomain.o;\
	fi

${OBJECTDIR}/src/render_e/textures/PNGFileTextureDataSource_nomain.o: ${OBJECTDIR}/src/render_e/textures/PNGFileTextureDataSource.o src/render_e/textures/PNGFileTextureDataSource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/textures
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/textures/PNGFileTextureDataSource.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/textures/PNGFileTextureDataSource_nomain.o src/render_e/textures/PNGFileTextureDataSource.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/textures/PNGFileTextureDataSource.o ${OBJECTDIR}/src/render_e/textures/PNGFileTextureDataSource_nomain.o;\
	fi

${OBJECTDIR}/src/render_e/Transform_nomain.o: ${OBJECTDIR}/src/render_e/Transform.o src/render_e/Transform.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/Transform.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/Transform_nomain.o src/render_e/Transform.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/Transform.o ${OBJECTDIR}/src/render_e/Transform_nomain.o;\
	fi

${OBJECTDIR}/src/render_e/SceneXMLParser_nomain.o: ${OBJECTDIR}/src/render_e/SceneXMLParser.o src/render_e/SceneXMLParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/SceneXMLParser.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/SceneXMLParser_nomain.o src/render_e/SceneXMLParser.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/SceneXMLParser.o ${OBJECTDIR}/src/render_e/SceneXMLParser_nomain.o;\
	fi

${OBJECTDIR}/src/render_e/Material_nomain.o: ${OBJECTDIR}/src/render_e/Material.o src/render_e/Material.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/Material.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/Material_nomain.o src/render_e/Material.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/Material.o ${OBJECTDIR}/src/render_e/Material_nomain.o;\
	fi

${OBJECTDIR}/src/render_e/Light_nomain.o: ${OBJECTDIR}/src/render_e/Light.o src/render_e/Light.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/Light.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/Light_nomain.o src/render_e/Light.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/Light.o ${OBJECTDIR}/src/render_e/Light_nomain.o;\
	fi

${OBJECTDIR}/src/render_e/textures/Texture2D_nomain.o: ${OBJECTDIR}/src/render_e/textures/Texture2D.o src/render_e/textures/Texture2D.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/textures
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/textures/Texture2D.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/textures/Texture2D_nomain.o src/render_e/textures/Texture2D.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/textures/Texture2D.o ${OBJECTDIR}/src/render_e/textures/Texture2D_nomain.o;\
	fi

${OBJECTDIR}/src/render_e/textures/CubeTexture_nomain.o: ${OBJECTDIR}/src/render_e/textures/CubeTexture.o src/render_e/textures/CubeTexture.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/textures
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/textures/CubeTexture.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/textures/CubeTexture_nomain.o src/render_e/textures/CubeTexture.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/textures/CubeTexture.o ${OBJECTDIR}/src/render_e/textures/CubeTexture_nomain.o;\
	fi

${OBJECTDIR}/src/render_e/textures/TextureDataSource_nomain.o: ${OBJECTDIR}/src/render_e/textures/TextureDataSource.o src/render_e/textures/TextureDataSource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/textures
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/textures/TextureDataSource.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/textures/TextureDataSource_nomain.o src/render_e/textures/TextureDataSource.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/textures/TextureDataSource.o ${OBJECTDIR}/src/render_e/textures/TextureDataSource_nomain.o;\
	fi

${OBJECTDIR}/src/render_e/math/Quaternion_nomain.o: ${OBJECTDIR}/src/render_e/math/Quaternion.o src/render_e/math/Quaternion.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/math
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/math/Quaternion.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/math/Quaternion_nomain.o src/render_e/math/Quaternion.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/math/Quaternion.o ${OBJECTDIR}/src/render_e/math/Quaternion_nomain.o;\
	fi

${OBJECTDIR}/src/render_e/math/Matrix44_nomain.o: ${OBJECTDIR}/src/render_e/math/Matrix44.o src/render_e/math/Matrix44.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/math
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/math/Matrix44.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/math/Matrix44_nomain.o src/render_e/math/Matrix44.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/math/Matrix44.o ${OBJECTDIR}/src/render_e/math/Matrix44_nomain.o;\
	fi

${OBJECTDIR}/src/render_e/textures/TextureBase_nomain.o: ${OBJECTDIR}/src/render_e/textures/TextureBase.o src/render_e/textures/TextureBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/textures
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/textures/TextureBase.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/textures/TextureBase_nomain.o src/render_e/textures/TextureBase.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/textures/TextureBase.o ${OBJECTDIR}/src/render_e/textures/TextureBase_nomain.o;\
	fi

${OBJECTDIR}/src/render_e/math/Vector3_nomain.o: ${OBJECTDIR}/src/render_e/math/Vector3.o src/render_e/math/Vector3.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/math
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/math/Vector3.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/math/Vector3_nomain.o src/render_e/math/Vector3.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/math/Vector3.o ${OBJECTDIR}/src/render_e/math/Vector3_nomain.o;\
	fi

${OBJECTDIR}/src/render_e/MeshFactory_nomain.o: ${OBJECTDIR}/src/render_e/MeshFactory.o src/render_e/MeshFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/MeshFactory.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/MeshFactory_nomain.o src/render_e/MeshFactory.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/MeshFactory.o ${OBJECTDIR}/src/render_e/MeshFactory_nomain.o;\
	fi

${OBJECTDIR}/src/render_e/shaders/ShaderDataSource_nomain.o: ${OBJECTDIR}/src/render_e/shaders/ShaderDataSource.o src/render_e/shaders/ShaderDataSource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/render_e/shaders
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/render_e/shaders/ShaderDataSource.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -D_DEBUG -Ilib-include/osx -I/Applications/Autodesk/FBXSDK20113_1/include/ -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/render_e/shaders/ShaderDataSource_nomain.o src/render_e/shaders/ShaderDataSource.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/render_e/shaders/ShaderDataSource.o ${OBJECTDIR}/src/render_e/shaders/ShaderDataSource_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f3 || true; \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rendere

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
