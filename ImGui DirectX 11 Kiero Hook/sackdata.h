#include "includes.h"




class sackdata
{

public:
    char pad_0000[16]; //0x0000
    int32_t idx; //0x0010
    int32_t team; //0x0014
    char* name; //0x0018
    char* formatname; //0x001C
    int32_t clanid; //0x0020
    char pad_0024[4]; //0x0024
    int32_t health; //0x0028
    int32_t skinstate; //0x002C
    char pad_0030[4]; //0x0030
    Vector3 prevPos; //0x0034
    char pad_0040[4]; //0x0040
    Vector3 curPos; //0x0044
    Vector3 Pos; //0x0050
    char pad_0050[16];
    float nextFrame; //0x006C
    char pad_0070[16]; //0x0070
    float tM; //0x0080
    char ad_0020[4]; //0x0084// weapondata2.4000
    char pad_0088[8]; //0x0088
    int32_t currset; //0x0090
    char pad_0094[176]; //0x0094
    int32_t wstate; //0x0144
    int32_t bstate; //0x0148
    int32_t lf; //0x014C
    int32_t la; //0x0150
    float leg_limit; //0x0154
    char pad_0158[4]; //0x0158
    int32_t frameWaterSplash; //0x015C
    float tWaterSplash; //0x0160
    float yWaterSplash; //0x0164
    float speed; //0x0168
    float drawtime; //0x016C
    char pad_0170[12]; //0x0170
    int32_t exp; //0x017C
    char pad_0180[12]; //0x0180
    int32_t pexp; //0x018C
    char pad_0190[4]; //0x0190
    float spawntime; //0x0194
    bool spawnprotect; //0x0198
    char pad_0199[3]; //0x0199
    char(*cp)[10][4]; //0x019C
    Vector3 restoreHead; //0x01A0
    Vector3 restoreLArm; //0x01AC
    Vector3 restoreRArm; //0x01B8
    int32_t ipx; //0x01C4
    int32_t ipy; //0x01C8
    int32_t ipz; //0x01CC
    int32_t irx; //0x01D0
    int32_t iry; //0x01D4
    int32_t prevbstate; //0x01D8
    bool updatepos; //0x01DC
    bool updaterotx; //0x01DD
    bool updateroty; //0x01DE
    bool visible; //0x01DF
    char(*fragcount)[5][4]; //0x01E0
    char pad_01E4[28]; //0x01E4
    float tHeartBeat; //0x0200
    char pad_0204[4]; //0x0204


}; //Size: 0x0208