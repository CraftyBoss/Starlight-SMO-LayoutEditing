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

#include "helpers.hpp"

void stageSceneHook() {

    __asm ("MOV X19, X0");

    StageScene *stageScene;
    __asm ("MOV %[result], X0" : [result] "=r" (stageScene));

    al::PlayerHolder *pHolder = al::getScenePlayerHolder(stageScene);
    PlayerActorHakoniwa *player = al::tryGetPlayerActor(pHolder, 0);
    HackCap *cap = player->mHackCap;

    sead::Vector3f *playerTrans = al::getTrans(player);
    sead::Vector3f *capTrans = al::getTrans(cap);

    sead::Vector3f *playerVel = al::getVelocity(player);
    sead::Vector3f *capVel = al::getTrans(cap);

    sead::Vector2f *inputLeft = al::getLeftStick(-1);
    sead::Vector2f *inputRight = al::getRightStick(-1);

    sead::Quatf *playerQuat = al::getQuat(player);
    sead::Quatf *capQuat = al::getQuat(cap);

    sead::Vector3f *playerRecoveryPoint = player->mPlayerRecoverPoint->getSafetyPoint();

    const char *curAnimName = player->mPlayerAnimator->mAnimFrameCtrl->getActionName();

    float curAnimFrame = player->mPlayerAnimator->getAnimFrame();

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

        sead::Vector3f eulerAngles = QuatToEuler(playerQuat);

        sead::Vector3f capEuler = QuatToEuler(capQuat);

        sead::Vector3f playerRot = sead::Vector3f(DEG(eulerAngles.x),DEG(eulerAngles.y),DEG(eulerAngles.z));

        sead::Vector3f capRot = sead::Vector3f(DEG(capEuler.x),DEG(capEuler.y),DEG(capEuler.z));

        switch (pageNum)
        {
        case 0:
            al::setPaneStringFormat(stageScene->stageSceneLayout->coinCounter, 
                "TxtDebug", "Mario Pos:\nX: %f\nY: %f\nZ: %f\nMario Velocity:\nX: %f\nY: %f\nZ: %f\nMario Rotation:\nX: %f\nY: %f\nZ: %f\nHorizontal Speed: %f\nRecovery Point Location:\nX: %f\nY: %f\nZ: %f\n", 
                playerTrans->x, playerTrans->y, playerTrans->z, playerVel->x, playerVel->y, playerVel->z, playerRot.x, playerRot.y, playerRot.z, al::calcSpeedH(player), playerRecoveryPoint->x,playerRecoveryPoint->y, playerRecoveryPoint->z
            );
            break;
        
        case 1:
            al::setPaneStringFormat(stageScene->stageSceneLayout->coinCounter, "TxtDebug", 
                "\nLeft Stick Input:\nX: %f\nY: %f\nRight Stick Input:\nX: %f\nY: %f\nCurrent Animation Frame: %f\nCappy Position:\nX: %f\nY: %f\nZ: %f\nCappy Rotation:\nX: %f\nY: %f\nZ: %f\n", 
                inputLeft->x, inputLeft->y, inputRight->x, inputRight->y, curAnimFrame, capTrans->x, capTrans->y, capTrans->z, capRot.x, capRot.y, capRot.z
            );
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
