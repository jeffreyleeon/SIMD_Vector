// Testing.cpp : Testing methods for library
//	DEBUG: check functionality
//	RELEASE: check speed
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "gtest\gtest.h"
#include "..\Math\simdmath.h"

#ifdef _DEBUG

/************************************
Functionality test
*************************************/

TEST(Vector, Normalization)
{
	SIMDVector3 v(0.0f, 3.0f, 4.0f);
	v.Normalize();
	EXPECT_NEAR(0.8f, v.GetZ(), 0.01f);
}

TEST(Vector, DotProduct)
{
	SIMDVector3 v(2.0f, 4.0f, 6.0f);
	EXPECT_NEAR(56.0f, v.DotProduct(v), 0.01f);
}

TEST(Vector, Addition)
{
	SIMDVector3 v1(1.0f, 2.0f, 3.0f);
	SIMDVector3 v2(2.0f, 4.0f, 6.0f);
	v1.Add(v2);
	EXPECT_NEAR(9.0f, v1.GetZ(), 0.01f);
}

TEST(Vector, Sibstraction)
{
	SIMDVector3 v1(1.0f, 2.0f, 3.0f);
	SIMDVector3 v2(2.0f, 4.0f, 6.0f);
	v1.Substract(v2);
	EXPECT_NEAR(-3.0f, v1.GetZ(), 0.01f);
}

TEST(Vector, SquaredLength)
{
	SIMDVector3 v(3.0f, 1.0f, 4.0f);
	EXPECT_NEAR(26.0f, v.LengthSquared(), 0.01f);
}

TEST(Vector, Length)
{
	SIMDVector3 v(3.0f, 0.0f, 4.0f);
	EXPECT_NEAR(5.0f, v.Length(), 0.01f);
}

TEST(Vector, CrossProduct)
{
	SIMDVector3 v1(3.0f, 2.0f, 5.0f);
	SIMDVector3 v2(4.0f, 6.0f, 1.0f);
	SIMDVector3 v3 = CrossProduct(v1, v2);
	EXPECT_NEAR(10.0f, v3.GetZ(), 0.01f);
}

TEST(Vector, LERP)
{
	SIMDVector3 v1(1.0f, 10.0f, 100.0f);
	SIMDVector3 v2(0.0f, 0.0f, 0.0f);
	SIMDVector3 v3 = Lerp(v1, v2, 0.75f);
	EXPECT_NEAR(25.0f, v3.GetZ(), 0.01f);
}

TEST(Vector, Multiplication)
{
	SIMDVector3 v(1.0f, 1.0f, 1.0f);
	v.Multiply(3.0f);
	EXPECT_NEAR(3.0f, v.GetZ(), 0.01f);
}

TEST(Vector, Blend)
{
	SIMDVector3 v1(1.0f, 1.0f, 1.0f);
	SIMDVector3 v2(4.0f, 4.0f, 4.0f);
	SIMDVector3 v3(8.0f, 8.0f, 8.0f);
	SIMDVector3 v4(16.0f, 16.0f, 16.0f);

	SIMDVector3 vBlendResult = Blend(v1, v2, v3, v4, 0.25f, 0.25f, 0.25f);
	EXPECT_NEAR(7.25f, vBlendResult.GetZ(), 0.01f);
}

TEST(Quaternion, Multiplcation)
{
	SIMDVector3 axis(1.0f, 0.0f, 0.0f);
	SIMDQuaternion q(axis, PI / 4.0f);
	SIMDQuaternion p(axis, PI / 4.0f);

	q.Multiply(p);
	EXPECT_NEAR(0.707f, q.GetX(), 0.01f);
}

#endif
#ifdef NDEBUG

/************************************
Speed test
*************************************/

void TEST_SPEED_QUAT_MUL()
{
	LARGE_INTEGER freq, perf_start, perf_end;
	float freqms;
	QueryPerformanceFrequency(&freq);
	freqms = freq.QuadPart / 1000.0f;

	// SIMD
	std::cout << "Testing multiplication of quaternion" << std::endl;
	QueryPerformanceCounter(&perf_start);
	SIMDVector3 SIMDqv(1.0f, 2.0f, 3.0f);
	SIMDQuaternion SIMDq1(SIMDqv, 3);
	for (int i = 0; i < 10000; i++)
	{
		SIMDqv.Multiply(i);
		SIMDQuaternion SIMDq2(SIMDqv, 3);
		SIMDq1.Multiply(SIMDq2);
	}
	QueryPerformanceCounter(&perf_end);
	float elapsedSIMD = (perf_end.QuadPart - perf_start.QuadPart) / freqms;
	std::cout << "SSE SIMD multiplication\n";
	std::cout << "Total duration for 10000 = " << elapsedSIMD << "ms\n";
	std::cout << "Average duration = " << elapsedSIMD / 10000.0f << "ms\n";

	// DirectX
	QueryPerformanceCounter(&perf_start);
	SIMDVector3 DXqv(1.0f, 2.0f, 3.0f);
	SIMDQuaternion DXq1(DXqv, 3);
	for (int i = 0; i < 10000; i++)
	{
		DXqv.Multiply(i);
		SIMDQuaternion DXq2(DXqv, 3);
		DXq1.MultiplyDX(DXq2);
	}
	QueryPerformanceCounter(&perf_end);

	float elapsedDX = (perf_end.QuadPart - perf_start.QuadPart) / freqms;
	std::cout << "DirectX::XMQuaternionMultiply\n";
	std::cout << "Total duration for 10000 = " << elapsedDX << "ms\n";
	std::cout << "Average duration = " << elapsedDX / 10000.0f << "ms\n";

}

int _tmain(int argc, _TCHAR* argv[])
{
	// Quaternion
	TEST_SPEED_QUAT_MUL();

	std::cin.getline(new char, 1);
}

#endif