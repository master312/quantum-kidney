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
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/game/cGame.o \
	${OBJECTDIR}/src/game/ingame/cCameraManager.o \
	${OBJECTDIR}/src/game/ingame/cEntityManager.o \
	${OBJECTDIR}/src/game/ingame/cPlayerDriver.o \
	${OBJECTDIR}/src/game/ingame/entities/cCharacter.o \
	${OBJECTDIR}/src/game/ingame/entities/cEntity.o \
	${OBJECTDIR}/src/game/ingame/entities/cNpc.o \
	${OBJECTDIR}/src/game/ingame/entities/cObject.o \
	${OBJECTDIR}/src/game/ingame/entities/cPawn.o \
	${OBJECTDIR}/src/game/ingame/map/cMapChunk.o \
	${OBJECTDIR}/src/game/ingame/map/cMapManager.o \
	${OBJECTDIR}/src/game/sCommon.o \
	${OBJECTDIR}/src/game/states/cStAnimGenerator.o \
	${OBJECTDIR}/src/game/states/cStInGame.o \
	${OBJECTDIR}/src/game/states/cStMainMenu.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/storm/cBinaryFile.o \
	${OBJECTDIR}/src/storm/cData.o \
	${OBJECTDIR}/src/storm/cFileParser.o \
	${OBJECTDIR}/src/storm/cStateManager.o \
	${OBJECTDIR}/src/storm/cStormState.o \
	${OBJECTDIR}/src/storm/cTimedCallbackManager.o \
	${OBJECTDIR}/src/storm/cTimer.o \
	${OBJECTDIR}/src/storm/cVector2d.o \
	${OBJECTDIR}/src/storm/engine.o \
	${OBJECTDIR}/src/storm/events/cEventManager.o \
	${OBJECTDIR}/src/storm/events/cInputSDL2.o \
	${OBJECTDIR}/src/storm/fLogs.o \
	${OBJECTDIR}/src/storm/graphics/cAnimation.o \
	${OBJECTDIR}/src/storm/graphics/cAnimationManager.o \
	${OBJECTDIR}/src/storm/graphics/cFontManager.o \
	${OBJECTDIR}/src/storm/graphics/cFontManagerOpenGL.o \
	${OBJECTDIR}/src/storm/graphics/cFontManagerSDL2.o \
	${OBJECTDIR}/src/storm/graphics/cGraphics.o \
	${OBJECTDIR}/src/storm/graphics/cGraphicsOpenGL.o \
	${OBJECTDIR}/src/storm/graphics/cGraphicsSDL2.o \
	${OBJECTDIR}/src/storm/graphics/cTextureManager.o \
	${OBJECTDIR}/src/storm/graphics/cTextureManagerOpenGL.o \
	${OBJECTDIR}/src/storm/graphics/cTextureManagerSDL2.o \
	${OBJECTDIR}/src/storm/gui/cGuiManager.o \
	${OBJECTDIR}/src/storm/gui/cGuiSkin.o \
	${OBJECTDIR}/src/storm/gui/cGuiWidget.o \
	${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetButton.o \
	${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetCheckBox.o \
	${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetComboBox.o \
	${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetContainer.o \
	${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetHorizontalSlider.o \
	${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetInput.o \
	${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetLabel.o \
	${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetList.o \
	${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetPictureBox.o \
	${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetRadioGroup.o \
	${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetTree.o \
	${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetVerticalSlider.o \
	${OBJECTDIR}/src/storm/sound/cMusic.o \
	${OBJECTDIR}/src/storm/sound/cMusicSDL2.o \
	${OBJECTDIR}/src/storm/sound/cSound.o \
	${OBJECTDIR}/src/storm/sound/cSoundManager.o \
	${OBJECTDIR}/src/storm/sound/cSoundManagerSDL2.o \
	${OBJECTDIR}/src/storm/sound/cSoundSDL2.o \
	${OBJECTDIR}/src/storm/storm.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/quantum-kidney

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/quantum-kidney: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/quantum-kidney ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/game/cGame.o: src/game/cGame.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/game
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/game/cGame.o src/game/cGame.cpp

${OBJECTDIR}/src/game/ingame/cCameraManager.o: src/game/ingame/cCameraManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/game/ingame
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/game/ingame/cCameraManager.o src/game/ingame/cCameraManager.cpp

${OBJECTDIR}/src/game/ingame/cEntityManager.o: src/game/ingame/cEntityManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/game/ingame
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/game/ingame/cEntityManager.o src/game/ingame/cEntityManager.cpp

${OBJECTDIR}/src/game/ingame/cPlayerDriver.o: src/game/ingame/cPlayerDriver.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/game/ingame
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/game/ingame/cPlayerDriver.o src/game/ingame/cPlayerDriver.cpp

${OBJECTDIR}/src/game/ingame/entities/cCharacter.o: src/game/ingame/entities/cCharacter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/game/ingame/entities
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/game/ingame/entities/cCharacter.o src/game/ingame/entities/cCharacter.cpp

${OBJECTDIR}/src/game/ingame/entities/cEntity.o: src/game/ingame/entities/cEntity.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/game/ingame/entities
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/game/ingame/entities/cEntity.o src/game/ingame/entities/cEntity.cpp

${OBJECTDIR}/src/game/ingame/entities/cNpc.o: src/game/ingame/entities/cNpc.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/game/ingame/entities
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/game/ingame/entities/cNpc.o src/game/ingame/entities/cNpc.cpp

${OBJECTDIR}/src/game/ingame/entities/cObject.o: src/game/ingame/entities/cObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/game/ingame/entities
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/game/ingame/entities/cObject.o src/game/ingame/entities/cObject.cpp

${OBJECTDIR}/src/game/ingame/entities/cPawn.o: src/game/ingame/entities/cPawn.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/game/ingame/entities
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/game/ingame/entities/cPawn.o src/game/ingame/entities/cPawn.cpp

${OBJECTDIR}/src/game/ingame/map/cMapChunk.o: src/game/ingame/map/cMapChunk.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/game/ingame/map
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/game/ingame/map/cMapChunk.o src/game/ingame/map/cMapChunk.cpp

${OBJECTDIR}/src/game/ingame/map/cMapManager.o: src/game/ingame/map/cMapManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/game/ingame/map
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/game/ingame/map/cMapManager.o src/game/ingame/map/cMapManager.cpp

${OBJECTDIR}/src/game/sCommon.o: src/game/sCommon.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/game
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/game/sCommon.o src/game/sCommon.cpp

${OBJECTDIR}/src/game/states/cStAnimGenerator.o: src/game/states/cStAnimGenerator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/game/states
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/game/states/cStAnimGenerator.o src/game/states/cStAnimGenerator.cpp

${OBJECTDIR}/src/game/states/cStInGame.o: src/game/states/cStInGame.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/game/states
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/game/states/cStInGame.o src/game/states/cStInGame.cpp

${OBJECTDIR}/src/game/states/cStMainMenu.o: src/game/states/cStMainMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/game/states
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/game/states/cStMainMenu.o src/game/states/cStMainMenu.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/storm/cBinaryFile.o: src/storm/cBinaryFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/cBinaryFile.o src/storm/cBinaryFile.cpp

${OBJECTDIR}/src/storm/cData.o: src/storm/cData.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/cData.o src/storm/cData.cpp

${OBJECTDIR}/src/storm/cFileParser.o: src/storm/cFileParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/cFileParser.o src/storm/cFileParser.cpp

${OBJECTDIR}/src/storm/cStateManager.o: src/storm/cStateManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/cStateManager.o src/storm/cStateManager.cpp

${OBJECTDIR}/src/storm/cStormState.o: src/storm/cStormState.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/cStormState.o src/storm/cStormState.cpp

${OBJECTDIR}/src/storm/cTimedCallbackManager.o: src/storm/cTimedCallbackManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/cTimedCallbackManager.o src/storm/cTimedCallbackManager.cpp

${OBJECTDIR}/src/storm/cTimer.o: src/storm/cTimer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/cTimer.o src/storm/cTimer.cpp

${OBJECTDIR}/src/storm/cVector2d.o: src/storm/cVector2d.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/cVector2d.o src/storm/cVector2d.cpp

${OBJECTDIR}/src/storm/engine.o: src/storm/engine.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/engine.o src/storm/engine.cpp

${OBJECTDIR}/src/storm/events/cEventManager.o: src/storm/events/cEventManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/events
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/events/cEventManager.o src/storm/events/cEventManager.cpp

${OBJECTDIR}/src/storm/events/cInputSDL2.o: src/storm/events/cInputSDL2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/events
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/events/cInputSDL2.o src/storm/events/cInputSDL2.cpp

${OBJECTDIR}/src/storm/fLogs.o: src/storm/fLogs.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/fLogs.o src/storm/fLogs.cpp

${OBJECTDIR}/src/storm/graphics/cAnimation.o: src/storm/graphics/cAnimation.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/graphics
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/graphics/cAnimation.o src/storm/graphics/cAnimation.cpp

${OBJECTDIR}/src/storm/graphics/cAnimationManager.o: src/storm/graphics/cAnimationManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/graphics
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/graphics/cAnimationManager.o src/storm/graphics/cAnimationManager.cpp

${OBJECTDIR}/src/storm/graphics/cFontManager.o: src/storm/graphics/cFontManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/graphics
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/graphics/cFontManager.o src/storm/graphics/cFontManager.cpp

${OBJECTDIR}/src/storm/graphics/cFontManagerOpenGL.o: src/storm/graphics/cFontManagerOpenGL.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/graphics
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/graphics/cFontManagerOpenGL.o src/storm/graphics/cFontManagerOpenGL.cpp

${OBJECTDIR}/src/storm/graphics/cFontManagerSDL2.o: src/storm/graphics/cFontManagerSDL2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/graphics
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/graphics/cFontManagerSDL2.o src/storm/graphics/cFontManagerSDL2.cpp

${OBJECTDIR}/src/storm/graphics/cGraphics.o: src/storm/graphics/cGraphics.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/graphics
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/graphics/cGraphics.o src/storm/graphics/cGraphics.cpp

${OBJECTDIR}/src/storm/graphics/cGraphicsOpenGL.o: src/storm/graphics/cGraphicsOpenGL.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/graphics
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/graphics/cGraphicsOpenGL.o src/storm/graphics/cGraphicsOpenGL.cpp

${OBJECTDIR}/src/storm/graphics/cGraphicsSDL2.o: src/storm/graphics/cGraphicsSDL2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/graphics
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/graphics/cGraphicsSDL2.o src/storm/graphics/cGraphicsSDL2.cpp

${OBJECTDIR}/src/storm/graphics/cTextureManager.o: src/storm/graphics/cTextureManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/graphics
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/graphics/cTextureManager.o src/storm/graphics/cTextureManager.cpp

${OBJECTDIR}/src/storm/graphics/cTextureManagerOpenGL.o: src/storm/graphics/cTextureManagerOpenGL.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/graphics
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/graphics/cTextureManagerOpenGL.o src/storm/graphics/cTextureManagerOpenGL.cpp

${OBJECTDIR}/src/storm/graphics/cTextureManagerSDL2.o: src/storm/graphics/cTextureManagerSDL2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/graphics
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/graphics/cTextureManagerSDL2.o src/storm/graphics/cTextureManagerSDL2.cpp

${OBJECTDIR}/src/storm/gui/cGuiManager.o: src/storm/gui/cGuiManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/gui
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/gui/cGuiManager.o src/storm/gui/cGuiManager.cpp

${OBJECTDIR}/src/storm/gui/cGuiSkin.o: src/storm/gui/cGuiSkin.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/gui
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/gui/cGuiSkin.o src/storm/gui/cGuiSkin.cpp

${OBJECTDIR}/src/storm/gui/cGuiWidget.o: src/storm/gui/cGuiWidget.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/gui
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/gui/cGuiWidget.o src/storm/gui/cGuiWidget.cpp

${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetButton.o: src/storm/gui/widgets/cGuiWidgetButton.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/gui/widgets
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetButton.o src/storm/gui/widgets/cGuiWidgetButton.cpp

${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetCheckBox.o: src/storm/gui/widgets/cGuiWidgetCheckBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/gui/widgets
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetCheckBox.o src/storm/gui/widgets/cGuiWidgetCheckBox.cpp

${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetComboBox.o: src/storm/gui/widgets/cGuiWidgetComboBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/gui/widgets
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetComboBox.o src/storm/gui/widgets/cGuiWidgetComboBox.cpp

${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetContainer.o: src/storm/gui/widgets/cGuiWidgetContainer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/gui/widgets
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetContainer.o src/storm/gui/widgets/cGuiWidgetContainer.cpp

${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetHorizontalSlider.o: src/storm/gui/widgets/cGuiWidgetHorizontalSlider.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/gui/widgets
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetHorizontalSlider.o src/storm/gui/widgets/cGuiWidgetHorizontalSlider.cpp

${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetInput.o: src/storm/gui/widgets/cGuiWidgetInput.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/gui/widgets
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetInput.o src/storm/gui/widgets/cGuiWidgetInput.cpp

${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetLabel.o: src/storm/gui/widgets/cGuiWidgetLabel.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/gui/widgets
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetLabel.o src/storm/gui/widgets/cGuiWidgetLabel.cpp

${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetList.o: src/storm/gui/widgets/cGuiWidgetList.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/gui/widgets
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetList.o src/storm/gui/widgets/cGuiWidgetList.cpp

${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetPictureBox.o: src/storm/gui/widgets/cGuiWidgetPictureBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/gui/widgets
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetPictureBox.o src/storm/gui/widgets/cGuiWidgetPictureBox.cpp

${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetRadioGroup.o: src/storm/gui/widgets/cGuiWidgetRadioGroup.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/gui/widgets
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetRadioGroup.o src/storm/gui/widgets/cGuiWidgetRadioGroup.cpp

${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetTree.o: src/storm/gui/widgets/cGuiWidgetTree.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/gui/widgets
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetTree.o src/storm/gui/widgets/cGuiWidgetTree.cpp

${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetVerticalSlider.o: src/storm/gui/widgets/cGuiWidgetVerticalSlider.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/gui/widgets
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/gui/widgets/cGuiWidgetVerticalSlider.o src/storm/gui/widgets/cGuiWidgetVerticalSlider.cpp

${OBJECTDIR}/src/storm/sound/cMusic.o: src/storm/sound/cMusic.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/sound
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/sound/cMusic.o src/storm/sound/cMusic.cpp

${OBJECTDIR}/src/storm/sound/cMusicSDL2.o: src/storm/sound/cMusicSDL2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/sound
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/sound/cMusicSDL2.o src/storm/sound/cMusicSDL2.cpp

${OBJECTDIR}/src/storm/sound/cSound.o: src/storm/sound/cSound.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/sound
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/sound/cSound.o src/storm/sound/cSound.cpp

${OBJECTDIR}/src/storm/sound/cSoundManager.o: src/storm/sound/cSoundManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/sound
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/sound/cSoundManager.o src/storm/sound/cSoundManager.cpp

${OBJECTDIR}/src/storm/sound/cSoundManagerSDL2.o: src/storm/sound/cSoundManagerSDL2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/sound
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/sound/cSoundManagerSDL2.o src/storm/sound/cSoundManagerSDL2.cpp

${OBJECTDIR}/src/storm/sound/cSoundSDL2.o: src/storm/sound/cSoundSDL2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm/sound
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/sound/cSoundSDL2.o src/storm/sound/cSoundSDL2.cpp

${OBJECTDIR}/src/storm/storm.o: src/storm/storm.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/storm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/storm/storm.o src/storm/storm.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/quantum-kidney

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
