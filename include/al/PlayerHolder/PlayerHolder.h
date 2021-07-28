#pragma once

#include "sead/math/seadVector.h"
#include "al/scene/Scene.h"
#include "al/PlayerHolder/PlayerHolder.h"
#include "types.h"

namespace al {
    class PlayerHolder {
        public:
            PlayerHolder(int);
            al::LiveActor *getPlayer(int);
            
    };
}