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
CCC=x86_64-w64-mingw32-g++
CXX=x86_64-w64-mingw32-g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=Cygwin64_4.x-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug_x64
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1445274692/LinkAPI.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-mno-cygwin
CXXFLAGS=-mno-cygwin

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=/cygdrive/C/cygwin/lib/gcc/x86_64-w64-mingw32/4.5.3/libstdc++.a /cygdrive/C/cygwin/lib/gcc/x86_64-w64-mingw32/4.5.3/libgcc.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${TESTDIR}/TestFiles/f1

${TESTDIR}/TestFiles/f1: /cygdrive/C/cygwin/lib/gcc/x86_64-w64-mingw32/4.5.3/libstdc++.a

${TESTDIR}/TestFiles/f1: /cygdrive/C/cygwin/lib/gcc/x86_64-w64-mingw32/4.5.3/libgcc.a

${TESTDIR}/TestFiles/f1: ${OBJECTFILES}
	${MKDIR} -p ${TESTDIR}/TestFiles
	x86_64-w64-mingw32-g++ -o ${TESTDIR}/TestFiles/f1 ${OBJECTFILES} ${LDLIBSOPTIONS} -shared

${OBJECTDIR}/_ext/1445274692/LinkAPI.o: ../../src/LinkAPI.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445274692
	${RM} "$@.d"
	$(COMPILE.c) -g -I. -I.  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1445274692/LinkAPI.o ../../src/LinkAPI.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${TESTDIR}/TestFiles/f1

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
