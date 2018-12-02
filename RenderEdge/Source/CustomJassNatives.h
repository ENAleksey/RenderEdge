#pragma once

#include "Utils.h"

void ClearExecuteTriggers();
void ExecuteKeyTriggers(int32 key, int32 state);
void ExecuteMouseTriggers(int32 button, int32 state);
void ExecuteWheelTriggers(int32 delta);
void ExecuteMouseMoveTriggers(int32 x, int32 y);
void ExecuteWindowResizeTriggers();
void ExecuteFrameUpdateTriggers();

void InitCustomNatives();