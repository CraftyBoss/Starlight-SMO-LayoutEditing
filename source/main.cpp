#include "al/LiveActor/LiveActor.h"
#include "al/util.hpp"
#include "al/layout/LayoutActor.h"
#include "game/StageScene.hpp"
#include "game/Layouts/CoinCounter.h"
#include "rs/util.hpp"
#include <cmath>
#include <stdio.h>

#include "sead/math/seadVector.h"
#include "sead/math/seadMatrix.h"
#include "sead/prim/seadSafeString.h"
#include "types.h"

#include "log.h"

#define RAD(deg) (deg * (M_PI / 180)) // converts Degrees to Radians
#define DEG(rad) (rad * (180 / M_PI)) // converts Radians to Degrees

sead::Vector3f QuatToEuler(sead::Quatf *quat) {

    f32 x = quat->z;
    f32 y = quat->y;
    f32 z = quat->x;
    f32 w = quat->w;

    f32 t0 = 2.0 * (w * x + y * z);
    f32 t1 = 1.0 - 2.0 * (x * x + y * y);
    f32 roll = atan2f(t0, t1);

    f32 t2 = 2.0 * (w * y - z * x);
    t2 = t2 > 1.0 ? 1.0 : t2;
    t2 = t2 < -1.0 ? -1.0 : t2;
    f32 pitch = asinf(t2);

    f32 t3 = 2.0 * (w * z + x * y);
    f32 t4 = 1.0 - 2.0 * (y * y + z * z);
    f32 yaw = atan2f(t3, t4);

    return sead::Vector3f(yaw, pitch, roll);
}

void stageSceneHook() {

    __asm ("MOV X19, X0");

    StageScene *stageScene;
    __asm ("MOV %[result], X0" : [result] "=r" (stageScene));

    al::PlayerHolder *pHolder = al::getScenePlayerHolder(stageScene);
    al::LiveActor *player = al::tryGetPlayerActor(pHolder, 0);

    sead::Vector3f *playerTrans = al::getTrans(player);
    sead::Vector3f *playerVel = al::getVelocity(player);
    sead::Vector2f *inputLeft = al::getLeftStick(-1);
    sead::Vector2f *inputRight = al::getRightStick(-1);
    sead::Quatf *playerQuat = al::getQuat(player);

    static bool showMenu = true;

    static int pageNum = 0;

    int totalPages = 2;

    if(al::isPadTriggerUp(-1)) {
        showMenu = !showMenu;
    }

    if(al::isPadTriggerLeft(-1)) {
        pageNum--;
        if(pageNum < 0) {
            pageNum = totalPages - 1;
        }
    }

    if(al::isPadTriggerRight(-1)) {
        pageNum++;
        if(pageNum >= totalPages) {
            pageNum = 0;
        }
    }

    if(showMenu) {

        // \nLeft Stick Input:\nX: %f\nY: %f\nRight Stick Input:\nX: %f\nY: %f  inputLeft->x, inputLeft->y, inputRight->x, inputRight->y

        sead::Vector3f eulerAngles = QuatToEuler(playerQuat);

        sead::Vector3f playerRot = sead::Vector3f(DEG(eulerAngles.x),DEG(eulerAngles.y),DEG(eulerAngles.z));

        switch (pageNum)
        {
        case 0:
            al::setPaneStringFormat(stageScene->stageSceneLayout->coinCounter, "TxtDebug", "Mario Pos:\nX: %f\nY: %f\nZ: %f\nMario Velocity:\nX: %f\nY: %f\nZ: %f\nMario Rotation:\nX: %f\nY: %f\nZ: %f", playerTrans->x, playerTrans->y, playerTrans->z, playerVel->x, playerVel->y, playerVel->z, playerRot.x, playerRot.y, playerRot.z);
            break;
        
        case 1:
            al::setPaneStringFormat(stageScene->stageSceneLayout->coinCounter, "TxtDebug", "\nLeft Stick Input:\nX: %f\nY: %f\nRight Stick Input:\nX: %f\nY: %f", inputLeft->x, inputLeft->y, inputRight->x, inputRight->y);
            break;
        default:
            al::setPaneStringFormat(stageScene->stageSceneLayout->coinCounter, "TxtDebug", "Unknown Page");
            break;
        }
    }else {
        al::setPaneStringFormat(stageScene->stageSceneLayout->coinCounter, "TxtDebug", " ");
    }

    __asm ("MOV X0, %[input]" : [input] "=r" (stageScene));
}
