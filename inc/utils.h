#pragma once
#include "Types.h"

inline static bool isPageCrossed(WORD src, WORD dest){
    return (src ^ dest) >= PAGE_SIZE;
}