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
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-framework OpenGL -framework GLUT ../../dist/Debug/GNU-MacOSX/librendere_git.a ../../lib/osx/libz.a ../../lib/osx/libxerces-c.a ../../lib/osx/libpng12.a ../../lib/osx/libGLEW.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hello_triangle

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hello_triangle: ../../dist/Debug/GNU-MacOSX/librendere_git.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hello_triangle: ../../lib/osx/libz.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hello_triangle: ../../lib/osx/libxerces-c.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hello_triangle: ../../lib/osx/libpng12.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hello_triangle: ../../lib/osx/libGLEW.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hello_triangle: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hello_triangle ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: main.cc 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I/project/cpp_tools/glm-0.9.1.1 -I../../src -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cc

# Subprojects
.build-subprojects:
	cd ../.. && ${MAKE}  -f Makefile CONF=Debug
	cd ../.. && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hello_triangle

# Subprojects
.clean-subprojects:
	cd ../.. && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../.. && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
