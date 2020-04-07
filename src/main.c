
#include "engine.h"
#include "platform.h"
#include "bitmap.c"
#include "file_platform.h"

#include "raycasting.c"
//#include "mipmaps.c"
#include "file_read.c"
#include "physics.c"
#include "dithering.c"
#include "drawing.c"
#include "map_streaming.c"
#include "setup_maps.c"
#include "rendering_quality.c"
#include "logo_state.c"
#include "menu_state.c"
#include "game_state.c"
#include "cutscene.c"


/*
docker run --rm \
-v ${PWD}:/work \
-v /path/to/extra/m68k-amigaos/lib:/tools/usr/lib \
-v /path/to/extra/m68k-amigaos/include:/tools/usr/include \
-it amigadev/crosstools:m68k-amigaos bash
*/


//****************************** CREATE
void InitEngine(void)
{
	engine.exitFlag = 0;

	engine.musicOn = 0;
	ReadModFile("data/verge.mod");
	InitScreen();
	InitInput();

	engine.paletteBitmap = LoadBitmapFile("data/plt", &engine.paletteHeader, engine.palettePalette, 1, 0);

	//process paletter from an image
	SetBitmapPalette(engine.palettePalette);
	// Load font
	engine.font = InitFont("data/ss.fnt");


	SetupMaps();


	engine.cutsceneDuration = 0;
	ResetTime();


	UnuseSystem();

	// //*********************************** SELECT HARDWARE ***********************************************
	engine.informationText = CreateBitmapFromText(engine.font, 
	"KEY 1 = 1 MB RAM   KEY 2 = MORE THAN 1 MB RAM"
	);
	DrawTextBitmap(engine.informationText, 50, PLANEHEIGHT/2, 3);
	
	VSyncAndDraw();

	engine.renderer.ditherTable1 = 0;

	while(engine.renderer.ditherTable1 == 0)
	{
		GetPlayerMemorySetting();
		
	}

	ClearBuffor();
	
	FillTextBitmap(engine.font, engine.informationText, 
	#ifdef AMIGA
	"KEY 3 = A500   KEY 4 = A1200   KEY 5 = A3000"
	#else
	"KEY 3 = ATARI ST   KEY 4 = ATARI FALCON OR TT"
	#endif
	);
	DrawTextBitmap(engine.informationText, 50, PLANEHEIGHT/2, 3);
	VSyncAndDraw();

	while(engine.renderer.renderingType == 0)
	{
		GetPlayerRendererSetting();
		
	}

	ClearBuffor();
	
	FillTextBitmap(engine.font, engine.informationText, 
	"INVERT Y AXIS?   KEY 9 = YES   KEY 0 = NO"
	);
	DrawTextBitmap(engine.informationText, 50, PLANEHEIGHT/2, 3);

	VSyncAndDraw();
	
	engine.yAxis = 0;

	while(engine.yAxis == 0)
	{
		GetYAxisSetting();
		
	}


	FreeTextBitmap(engine.informationText);
	InitLogoState();

	



}

//****************************** LOOP
void EngineLoop(void)
{


	ProcessJoystick();
	
	TimeStep();
	if (engine.currentState == State_Logo)   //turned off
	{
		RunLogoState();
		
		if (getKey(ESCAPE))
		{
			engine.exitFlag = 1;
			ExitGame();
		}
			
	}
	else if(engine.currentState == State_Menu)
	{
		RunMenuState();
	}
	else if(engine.currentState == State_Game)
	{
			
		RunGameState();
	}

	if (getKey(ESCAPE) || engine.exitFlag)
	{
		ExitGame();
		engine.exitFlag = 1;
	}


	engine.loopEndTime = getCurrentTime();
}

//****************************** DESTROY
void EngineDestroy(void)
{
	UseSystem();
	CloseJoystick();
	ViewOff();
	FreeView();
	StopSample(0);
	DestroyAudio();

	FreeTextBitmap(engine.pBitmapVelocity);
	FreeTextBitmap(engine.pBitmapScore);
	FreeTextBitmap(engine.pBitmapTime);
	FreeTextBitmap(engine.pBitmapHeight);

	FreeTextBitmap(engine.pBitmapVelocityLabel);
	FreeTextBitmap(engine.pBitmapScoreLabel);
	FreeTextBitmap(engine.pBitmapTimeLabel);
	FreeTextBitmap(engine.pBitmapHeightLabel);
	

	free(engine.font);
	free(engine.activeBitmap);
	free(engine.shipBitmap);
	free(engine.paletteBitmap);
	free(engine.landingBitmap);
	free(engine.takeoffBitmap);
	free(engine.explosionBitmap);
	free(engine.renderer.ditherTable1);
	free(engine.renderer.depthBuffer);
	free(engine.renderer.screenPatch);
	free(engine.renderer.rayCastX);
	free(engine.renderer.rayCastY);
	for(int i = 0; i < 10; ++i)
	{
		FreeTextBitmap(engine.pBitmapInfo[i]);
	}

}



	
	