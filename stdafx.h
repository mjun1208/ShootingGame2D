#pragma once
#pragma comment (lib, "dsound.lib")
#include <iostream>
#include <algorithm>
#include <map>
#include <list>
#include <vector>
#include <time.h>
#include <string>
#include <fstream>
#include <iomanip>
#include "SDKsound.h"

using namespace std;

#define g_Device DXUTGetD3D9Device()
#define DX_Time DXUTGetElapsedTime()

#ifdef _DEBUG
#define DEBUG_LOG(log) cout << log << endl;
#else
#define DEBUG_LOG(log)
#endif // _DEBUG

using Vec2 = D3DXVECTOR2;
using Vec3 = D3DXVECTOR3;

const int WINSIZEX = 1280;
const int WINSIZEY = 720;

#include "cCameraManager.h"
#include "cSceneManager.h"
#include "cImageManager.h"
#include "cInputManager.h"

#include "cTexture.h"
#include "Utility.h"

///
#include "cMapManager.h"

#include "cButton.h"