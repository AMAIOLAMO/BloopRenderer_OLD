#include "CXCamera.h"

CXCamera::CXCamera(Vec3 _position, Vec3 _lookDirection) :
	position(_position), lookDirection(_lookDirection) {}

CXCamera::CXCamera(const CXCamera& other) :
	position(other.position), lookDirection(other.lookDirection) {}
