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
CND_PLATFORM=Cygwin64_4.x-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/AllTests.o \
	${OBJECTDIR}/CustomCuTest.o \
	${OBJECTDIR}/CustomHelperFunctions.o \
	${OBJECTDIR}/MiscTestSuite.o \
	${OBJECTDIR}/SettersTestSuite.o \
	${OBJECTDIR}/UpdatersTestSuite.o \
	${OBJECTDIR}/cutest-1.5/CuTest.o


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
LDLIBSOPTIONS=../../ide/netbeans/dist/Release_x64/Cygwin64_4.x-Windows/libLinkAPI.dll

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/linkapitestrunner.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/linkapitestrunner.exe: ../../ide/netbeans/dist/Release_x64/Cygwin64_4.x-Windows/libLinkAPI.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/linkapitestrunner.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/linkapitestrunner ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/AllTests.o: AllTests.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Icutest-1.5 -I../../src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AllTests.o AllTests.c

${OBJECTDIR}/CustomCuTest.o: CustomCuTest.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Icutest-1.5 -I../../src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CustomCuTest.o CustomCuTest.c

${OBJECTDIR}/CustomHelperFunctions.o: CustomHelperFunctions.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Icutest-1.5 -I../../src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CustomHelperFunctions.o CustomHelperFunctions.c

${OBJECTDIR}/MiscTestSuite.o: MiscTestSuite.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Icutest-1.5 -I../../src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MiscTestSuite.o MiscTestSuite.c

${OBJECTDIR}/SettersTestSuite.o: SettersTestSuite.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Icutest-1.5 -I../../src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SettersTestSuite.o SettersTestSuite.c

${OBJECTDIR}/UpdatersTestSuite.o: UpdatersTestSuite.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Icutest-1.5 -I../../src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/UpdatersTestSuite.o UpdatersTestSuite.c

${OBJECTDIR}/cutest-1.5/CuTest.o: cutest-1.5/CuTest.c 
	${MKDIR} -p ${OBJECTDIR}/cutest-1.5
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Icutest-1.5 -I../../src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cutest-1.5/CuTest.o cutest-1.5/CuTest.c

# Subprojects
.build-subprojects:
	cd ../../ide/netbeans && ${MAKE}  -f Makefile CONF=Release_x64

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/linkapitestrunner.exe

# Subprojects
.clean-subprojects:
	cd ../../ide/netbeans && ${MAKE}  -f Makefile CONF=Release_x64 clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
