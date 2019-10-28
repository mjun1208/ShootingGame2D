#pragma once

#include "cTile.h"

enum Dirction {
	LEFT, RIGHT, TOP, BOTTOM, FOLLOW
};


template <typename T>
T Lerp(T start, T end, float s) {
    return start + (end - start) * s;
}