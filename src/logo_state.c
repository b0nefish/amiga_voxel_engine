#include "engine.h"

void InitLogoState()
{
	
    ResetTime();
	engine.currentState = State_Logo;
	for(int i = 0; i < 4; i++)
	{
		engine.logoState.fadeInStatus[i] = 1;
		engine.logoState.fadeOutStatus[i] = 0;
	}
	engine.logoState.screenIndex = 1;
	engine.logoState.screenDuration = LOGORUNTIME;
}

void RunLogoState()
{
	
    animateIntro();

    engine.logoState.screenDuration -= engine.deltaTime;

    if(engine.logoState.screenDuration > LOGORUNTIME)
    {
        engine.logoState.screenDuration = LOGORUNTIME;
        engine.logoState.screenIndex = (engine.logoState.screenIndex + 1) % 4;
        switchIntroScreen();
    }
    VSyncWait();

}

void switchIntroScreen()
{

	switch (engine.logoState.screenIndex)
	{
	case 2:
	{
        LoadBitmapToMemory("data/l2");
		
		ClearBuffor();
		DrawBitmap4bCenter(engine.activeBitmap, &engine.activeBitmapHeader);
		
        VSyncAndDraw();

		for(int i = 0; i < 4; i++)
		{
			engine.logoState.fadeInStatus[i] = 0;
			engine.logoState.fadeOutStatus[i] = 0;
		}
	}
	break;
	case 3:
	{
        LoadBitmapToMemory("data/l3");

		ClearBuffor();
		DrawBitmap4bCenter(engine.activeBitmap, &engine.activeBitmapHeader);
		
        VSyncAndDraw();

		for(int i = 0; i < 4; i++)
		{
			engine.logoState.fadeInStatus[i] = 0;
			engine.logoState.fadeOutStatus[i] = 0;
		}
	}
	break;
	default:
	{
		engine.currentState = State_Menu;
		engine.menuState.infoScreen = 0;
	} break;
	}
}

#ifdef AMIGA
#define PALETTE_SHIFT 4
#else
#define PALETTE_SHIFT 5
#endif 

void animateIntro()
{
	if(engine.logoState.screenDuration < 7400000 && !engine.logoState.fadeInStatus[3])
	{
		for (int i = 0; i < 16; i++)
		{
			engine.renderer.bitmapPalette[i] = ((((engine.activePalette[i * 4 + 2]/4) >> PALETTE_SHIFT) << 8) +
								(((engine.activePalette[i * 4 + 1]/4) >> PALETTE_SHIFT) << 4) + ((engine.activePalette[i * 4 + 0]/4) >> PALETTE_SHIFT));
		}
		SetPalette();
		engine.logoState.fadeInStatus[3] = 1;
	}
	if(engine.logoState.screenDuration < 7300000 && !engine.logoState.fadeInStatus[2])
	{
		for (int i = 0; i < 16; i++)
		{
			engine.renderer.bitmapPalette[i] = ((((engine.activePalette[i * 4 + 2]/2) >> PALETTE_SHIFT) << 8) +
								(((engine.activePalette[i * 4 + 1]/2) >> PALETTE_SHIFT) << 4) + ((engine.activePalette[i * 4 + 0]/2) >> PALETTE_SHIFT));
		}
		SetPalette();
		engine.logoState.fadeInStatus[2] = 1;
	}
	if(engine.logoState.screenDuration < 7200000 && !engine.logoState.fadeInStatus[1])
	{
		for (int i = 0; i < 16; i++)
		{
			engine.renderer.bitmapPalette[i] = ((((engine.activePalette[i * 4 + 2]*3/4) >> PALETTE_SHIFT) << 8) +
								(((engine.activePalette[i * 4 + 1]*3/4) >> PALETTE_SHIFT) << 4) + ((engine.activePalette[i * 4 + 0]*3/4) >> PALETTE_SHIFT));
		}
		SetPalette();
		engine.logoState.fadeInStatus[1] = 1;
	}
	if(engine.logoState.screenDuration < 7100000 && !engine.logoState.fadeInStatus[0])
	{
		for (int i = 0; i < 16; i++)
		{
			engine.renderer.bitmapPalette[i] = (((engine.activePalette[i * 4 + 2] >> PALETTE_SHIFT) << 8) +
								((engine.activePalette[i * 4 + 1] >> PALETTE_SHIFT) << 4) + (engine.activePalette[i * 4 + 0] >> PALETTE_SHIFT));
		}
		SetPalette();
		engine.logoState.fadeInStatus[0] = 1;
	}

	if(engine.logoState.screenDuration < 400000 && !engine.logoState.fadeOutStatus[0])
	{
		for (int i = 0; i < 16; i++)
		{
			engine.renderer.bitmapPalette[i] = ((((engine.activePalette[i * 4 + 2]*3/4) >> PALETTE_SHIFT) << 8) +
								(((engine.activePalette[i * 4 + 1]*3/4) >> PALETTE_SHIFT) << 4) + ((engine.activePalette[i * 4 + 0]*3/4) >> PALETTE_SHIFT));
		}
		SetPalette();
		engine.logoState.fadeOutStatus[0] = 1;
	}
	if(engine.logoState.screenDuration < 300000 && !engine.logoState.fadeOutStatus[1])
	{
		for (int i = 0; i < 16; i++)
		{
			engine.renderer.bitmapPalette[i] = ((((engine.activePalette[i * 4 + 2]/2) >> PALETTE_SHIFT) << 8) +
								(((engine.activePalette[i * 4 + 1]/2) >> PALETTE_SHIFT) << 4) + ((engine.activePalette[i * 4 + 0]/2) >> PALETTE_SHIFT));
		}
		SetPalette();
		engine.logoState.fadeOutStatus[1] = 1;
	}
	if(engine.logoState.screenDuration < 200000 && !engine.logoState.fadeOutStatus[2])
	{
		for (int i = 0; i < 16; i++)
		{
			engine.renderer.bitmapPalette[i] = ((((engine.activePalette[i * 4 + 2]/4) >> PALETTE_SHIFT) << 8) +
								(((engine.activePalette[i * 4 + 1]/4) >> PALETTE_SHIFT) << 4) + ((engine.activePalette[i * 4 + 0]/4) >> PALETTE_SHIFT));
		}
		SetPalette();
		engine.logoState.fadeOutStatus[2] = 1;
	}
	if(engine.logoState.screenDuration < 100000 && !engine.logoState.fadeOutStatus[3])
	{
		for (int i = 0; i < 16; i++)
		{
			engine.renderer.bitmapPalette[i] = 0;
		}
		SetPalette();
		engine.logoState.fadeOutStatus[3] = 1;
	}
}
