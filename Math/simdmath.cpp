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

// Matrix4 methods
void SIMDMatrix4::CreateTranslation(const SIMDVector3& translation)
{
	_rows[0] = _mm_setr_ps(1.0f, 0.0f, 0.0f, translation.GetX());
	_rows[1] = _mm_setr_ps(0.0f, 1.0f, 0.0f, translation.GetY());
	_rows[2] = _mm_setr_ps(0.0f, 0.0f, 1.0f, translation.GetZ());
	_rows[3] = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
}

void SIMDMatrix4::CreateLookAt(const SIMDVector3& vEye, const SIMDVector3& vAt, const SIMDVector3& vUp)
{
	DirectX::XMMATRIX result = DirectX::XMMatrixLookAtLH(vEye._data, vAt._data, vUp._data);
	_rows[0] = result.r[0];
	_rows[1] = result.r[1];
	_rows[2] = result.r[2];
	_rows[3] = result.r[3];
	_MM_TRANSPOSE4_PS(_rows[0], _rows[1], _rows[2], _rows[3]);
}