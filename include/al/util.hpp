#pragma once

namespace al
{
    class LiveActor;

    class AreaObj {

    };

}

#include "sead/math/seadVector.h"
#include "sead/prim/seadSafeString.h"
#include "sead/heap/seadHeap.h"
#include "al/scene/Scene.h"
#include "al/PlayerHolder/PlayerHolder.h"
#include "al/audio/AudioKeeper.h"
#include "al/camera/Projection.h"
#include "al/layout/IUseLayout.h"

#include "nn/ui2d/Texture.h"

#include "types.h"

namespace al
{

    // General Input functions

    bool isPadTriggerLeft(int port);
    bool isPadTriggerRight(int port);
    bool isPadTriggerUp(int port);

    bool isPadHoldLeft(int port);
    bool isPadHoldRight(int port);
    bool isPadHoldUp(int port);

    sead::Vector2f *getLeftStick(int);
    sead::Vector2f *getRightStick(int);

    // getters
    
    sead::Vector3f *getTrans(al::LiveActor const *);

    sead::Vector3f *getGravity(al::LiveActor const *);

    sead::Vector3f *getUp(al::LiveActor const *);

    sead::Vector3f *getUpPtr(al::LiveActor *);

    sead::Vector3f *getFront(al::LiveActor const *);

    sead::Vector3f *getCameraUp(al::IUseCamera const *, int);

    sead::Vector3f *getScale(al::LiveActor *);

    float *getScaleX(al::LiveActor *);

    float *getScaleY(al::LiveActor *);

    float *getScaleZ(al::LiveActor *);

    al::PlayerHolder *getScenePlayerHolder(al::Scene const *);

    al::LiveActor *tryGetPlayerActor(al::PlayerHolder const *, int);

    sead::Heap *getCurrentHeap(void);

    al::Projection *getProjection(al::IUseCamera const *, int);

    int getSubActorNum(al::LiveActor const *);

    al::LiveActor *getSubActor(al::LiveActor const *, int);

    sead::Vector3f *getVelocity(al::LiveActor const *);

    sead::Quatf *getQuat(al::LiveActor const *);

    // setters

    void setTransY(al::LiveActor *, float);

    void setTrans(al::LiveActor *, sead::Vector3f const &);

    void setScaleAll(al::LiveActor *, float);

    void setGravity(al::LiveActor const *, sead::Vector3f const &);

    void setFront(al::LiveActor *, sead::Vector3f const &);

    void setPaneTexture(al::IUseLayout *, char const *, nn::ui2d::TextureInfo const *);

    //void setPaneString(al::IUseLayout *layout, char const *paneName, char16_t const *, ushort);

    void setPaneStringFormat(al::IUseLayout *layout, char const *paneName, char const *format,...);

    // misc

    bool isInAreaObj(al::LiveActor const *, const char *);

    al::AreaObj *tryFindAreaObj(al::LiveActor const *, const char *);

    void tryGetAreaObjArg(int *, al::AreaObj const *, const char *);
    void tryGetAreaObjArg(float *, al::AreaObj const *, const char *);
    void tryGetAreaObjArg(bool *, al::AreaObj const *, const char *);

    void tryGetAreaObjStringArg(const char **, al::AreaObj const *, const char *);

    void offCollide(al::LiveActor *);
    void onCollide(al::LiveActor *);

    void startAction(al::LiveActor *, char const *);

    bool tryStartSe(al::IUseAudioKeeper const *, sead::SafeStringBase<char> const &);

    void startSe(al::IUseAudioKeeper const *, sead::SafeStringBase<char> const &);

    void startHitReaction(al::LiveActor const *, char const*);

    bool isInDeathArea(al::LiveActor const *);

    void calcCameraUpDir(sead::Vector3f *, al::IUseCamera const*, int);
}
