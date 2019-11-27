#pragma once

#include "cTile.h"

enum Dirction {
	LEFT, RIGHT, TOP, BOTTOM, FOLLOW
};


template <typename T>
T Lerp(T start, T end, float s) {
    return start + (end - start) * s;
}

enum EnemyKind { e_NONE, TEST };

struct EnemyDumy {
	EnemyKind EnemyState;
	Vec2 vPos;
	Vec2 vMatrix;
	cTexture * m_Image;

	EnemyDumy(Vec2 Pos, Vec2 Matrix, EnemyKind State) : vPos(Pos), vMatrix(Matrix), EnemyState(State) {};
};