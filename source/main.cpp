#include "al/LiveActor/LiveActor.h"
#include "al/util.hpp"
#include "al/layout/LayoutActor.h"
#include "game/StageScene/StageScene.h"
#include "game/Layouts/CoinCounter.h"
#include "rs/util.hpp"
#include <cmath>
#include <stdio.h>

#include "debugMenu.hpp"

void stageSceneHook() {

    __asm ("MOV X19, X0");

    StageScene *stageScene;
    __asm ("MOV %[result], X0" : [result] "=r" (stageScene));

    isInGame = true;

    if(al::isPadTriggerUp(-1)) {
        showMenu = !showMenu;
    }

    __asm ("MOV X0, %[input]" : [input] "=r" (stageScene));
}
