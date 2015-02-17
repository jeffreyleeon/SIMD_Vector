#include "stdafx.h"
#include "simdmath.h"

// Matrix4 constant declaration
float identityMatrix[4][4] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
const SIMDMatrix4 SIMDMatrix4::Identity(identityMatrix);

// Vector3 constant declaration
const SIMDVector3 SIMDVector3::Zero(0.0f, 0.0f, 0.0f);
const SIMDVector3 SIMDVector3::UnitX(1.0f, 0.0f, 0.0f);
const SIMDVector3 SIMDVector3::UnitY(0.0f, 1.0f, 0.0f);
const SIMDVector3 SIMDVector3::UnitZ(0.0f, 0.0f, 1.0f);
const SIMDVector3 SIMDVector3::NegativeUnitX(-1.0f, 0.0f, 0.0f);
const SIMDVector3 SIMDVector3::NegativeUnitY(0.0f, -1.0f, 0.0f);
const SIMDVector3 SIMDVector3::NegativeUnitZ(0.0f, 0.0f, -1.0f);