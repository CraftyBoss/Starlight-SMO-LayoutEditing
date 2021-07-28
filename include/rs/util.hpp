#pragma once

#include "sead/math/seadVector.h"
#include "al/util.hpp"

namespace rs
{
    al::LiveActor* getPlayerActor(const al::Scene *);

    void get2DAreaPos(sead::Vector3<f32> *, al::AreaObj const *);
}
