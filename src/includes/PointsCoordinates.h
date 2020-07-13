#pragma once

#include "HLrobotconfig.h"
#include "MotionPlan.h"

//PosStruct A1P1, A1P2, A2P1, A2P2, PA, PB, PC, PD, A1P1Safe, A1P2Safe, A2P1Safe, A2P2Safe, PASafe, PBSafe, PCSafe, PDSafe, A1Safe, A0Safe, A2Safe;
const PosStruct A1P1(448.02, -282.356, 455.904, -90.989, 179.197, 135.938);
const PosStruct A1P2 = PosStruct(541.744, -280.623, 457.286, -90.989, 179.197, 135.938);
const PosStruct A2P1 = PosStruct(443.126, 291.95, 455.21, -136.493, 179.194, 91.668);
const PosStruct A2P2 = PosStruct(539.836, 296.944, 454.385, -136.493, 179.194, 91.668);
const PosStruct PA = PosStruct(486.058, -134.348, 453.503, -90.989, 179.197, 46.686);
const PosStruct PB = PosStruct(486.058, 150.235, 453.503, -90.989, 179.197, 46.686);
const PosStruct PC = PosStruct(360.338, 150.235, 453.503, -90.989, 179.197, 46.686);
const PosStruct PD = PosStruct(360.338, -134.348, 453.503, -90.989, 179.197, 46.686);
const PosStruct A1P1Safe = PosStruct(448.019, -282.356, 715, -90.989, 179.197, 135.938);
const PosStruct A1P2Safe = PosStruct(541.744, -280.623, 715, -90.989, 179.197, 135.938);
const PosStruct A2P1Safe = PosStruct(443.126, 291.95, 715, -136.493, 179.194, 91.668);
const PosStruct A2P2Safe = PosStruct(539.836, 296.944, 715, -136.493, 179.194, 91.668);
const PosStruct PASafe = PosStruct(486.058, -134.348, 715, -90.989, 179.197, 46.686);
const PosStruct PBSafe = PosStruct(486.058, 150.235, 715, -90.989, 179.197, 46.686);
const PosStruct PCSafe = PosStruct(360.338, 150.235, 715, -90.989, 179.197, 46.686);
const PosStruct PDSafe = PosStruct(360.338, -134.348, 715, -90.989, 179.197, 46.686);

const PosStruct A1Safe = PosStruct(445.537, -261.224, 715, -90.989, 179.197, 135.938);
const PosStruct A0Safe = PosStruct(400.537, -32.163, 715, -90.989, 179.197, 46.686);
const PosStruct A2Safe = PosStruct(477.908, 248.584, 715, -136.493, 179.194, 91.668);
