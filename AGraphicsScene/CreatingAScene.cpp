#include "pch.h"
#include <cControlGameEngine.h>

extern cControlGameEngine gameEngine;

void AddingAdditionalTextureContent()
{
    gameEngine.AdjustAlphaTransparency("Water", 0.3f);
}