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
CND_PLATFORM=MinGW-Windows
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
	${OBJECTDIR}/_ext/a4ed2b29/INIReader.o \
	${OBJECTDIR}/_ext/a4ed2b29/ini.o \
	${OBJECTDIR}/enigma.o \
	${OBJECTDIR}/enigma_reader.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/plugboard.o \
	${OBJECTDIR}/rotor.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/rotate_tests.o \
	${TESTDIR}/tests/rotor_tests.o

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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/extended_enigma.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/extended_enigma.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/extended_enigma ${OBJECTFILES} ${LDLIBSOPTIONS} -static-libgcc -static-libstdc++

${OBJECTDIR}/_ext/a4ed2b29/INIReader.o: ../config_files/INIReader.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a4ed2b29
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a4ed2b29/INIReader.o ../config_files/INIReader.cpp

${OBJECTDIR}/_ext/a4ed2b29/ini.o: ../config_files/ini.c
	${MKDIR} -p ${OBJECTDIR}/_ext/a4ed2b29
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a4ed2b29/ini.o ../config_files/ini.c

${OBJECTDIR}/enigma.o: enigma.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/enigma.o enigma.cpp

${OBJECTDIR}/enigma_reader.o: enigma_reader.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/enigma_reader.o enigma_reader.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/plugboard.o: plugboard.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/plugboard.o plugboard.cpp

${OBJECTDIR}/rotor.o: rotor.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/rotor.o rotor.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/rotate_tests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} -static-libgcc -static-libstdc++  

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/rotor_tests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} -static-libgcc -static-libstdc++  


${TESTDIR}/tests/rotate_tests.o: tests/rotate_tests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/rotate_tests.o tests/rotate_tests.cpp


${TESTDIR}/tests/rotor_tests.o: tests/rotor_tests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/rotor_tests.o tests/rotor_tests.cpp


${OBJECTDIR}/_ext/a4ed2b29/INIReader_nomain.o: ${OBJECTDIR}/_ext/a4ed2b29/INIReader.o ../config_files/INIReader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/a4ed2b29
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/a4ed2b29/INIReader.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a4ed2b29/INIReader_nomain.o ../config_files/INIReader.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/a4ed2b29/INIReader.o ${OBJECTDIR}/_ext/a4ed2b29/INIReader_nomain.o;\
	fi

${OBJECTDIR}/_ext/a4ed2b29/ini_nomain.o: ${OBJECTDIR}/_ext/a4ed2b29/ini.o ../config_files/ini.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/a4ed2b29
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/a4ed2b29/ini.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a4ed2b29/ini_nomain.o ../config_files/ini.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/a4ed2b29/ini.o ${OBJECTDIR}/_ext/a4ed2b29/ini_nomain.o;\
	fi

${OBJECTDIR}/enigma_nomain.o: ${OBJECTDIR}/enigma.o enigma.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/enigma.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/enigma_nomain.o enigma.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/enigma.o ${OBJECTDIR}/enigma_nomain.o;\
	fi

${OBJECTDIR}/enigma_reader_nomain.o: ${OBJECTDIR}/enigma_reader.o enigma_reader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/enigma_reader.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/enigma_reader_nomain.o enigma_reader.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/enigma_reader.o ${OBJECTDIR}/enigma_reader_nomain.o;\
	fi

${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_nomain.o main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

${OBJECTDIR}/plugboard_nomain.o: ${OBJECTDIR}/plugboard.o plugboard.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/plugboard.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/plugboard_nomain.o plugboard.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/plugboard.o ${OBJECTDIR}/plugboard_nomain.o;\
	fi

${OBJECTDIR}/rotor_nomain.o: ${OBJECTDIR}/rotor.o rotor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/rotor.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/rotor_nomain.o rotor.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/rotor.o ${OBJECTDIR}/rotor_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
