/**
 * @file GameDataFunction.h
 * @brief Holds static functions for getting / storage save data.
 */

#pragma once

#include <al/LiveActor/LiveActor.h>
#include <game/GameDataHolderAccessor.h>

class GameDataFunction
{
public:
    // gets current save file's current world id
    static s32 getCurrentWorldId(GameDataHolderAccessor);

    static char* getCurrentStageName(GameDataHolderAccessor);

    static s32 getCurrentShineNum(GameDataHolderAccessor);

    // gets total moons collected on a specified save file (-1 for current save)
    static s32 getTotalShineNum(GameDataHolderAccessor, int);

    // gets the total amount of moons available in a kingdom
    static s32 getWorldTotalShineNum(GameDataHolderAccessor, int); 

    // checks save file if shine is collected in kingdom index
    static bool isGotShine(GameDataHolderAccessor, int, int);

    // checks save file if shine is collected by shine index only (0 through 725)
    static bool isGotShine(GameDataHolderAccessor, int);

    // Gets Index for X Kingdom
    static s32 getWorldIndexWaterfall(void);

};