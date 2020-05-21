#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "ext/doctest.h"

#define NLL_MATH_DEFINITIONS
#include "../nll_math.h"

//============================================================================
//============================================================================

#define CHECK_VEC3_EQ(a, b) for (int i=0; i<3; i++) { CHECK(a[i] == b[i]); }
#define CHECK_M44_EQ(a, b) for (int i=0; i<16; i++) { CHECK(a[i] == b[i]); }

TEST_CASE("nllMat44Rotation") {

	const nllVec3 basis[3] = { {1,0,0}, {0,1,0}, {0,0,1} };
	const int X = 0, Y = 1, Z = 2;
	const float cosA = 0, sinA = 1;

	nllMat44 m;
	nllVec3 axis;

	nllMat44RotationX(m, cosA, sinA);
	nllVec3Transform(axis, m, basis[Y]);
	CHECK_VEC3_EQ(axis, basis[Z]);

	nllMat44RotationY(m, cosA, sinA);
	nllVec3Transform(axis, m, basis[Z]);
	CHECK_VEC3_EQ(axis, basis[X]);

	nllMat44RotationZ(m, cosA, sinA);
	nllVec3Transform(axis, m, basis[X]);
	CHECK_VEC3_EQ(axis, basis[Y]);
}

TEST_CASE("nllMat44RotationAxis") {

	nllMat44 mAxis, mRef;
	const float cosA = 0, sinA = 1;
	nllVec3 axis;

	nllMat44RotationAxis(mAxis, nllVec3Set(axis, 1, 0, 0), cosA, sinA);
	nllMat44RotationX(mRef, cosA, sinA);
	CHECK_M44_EQ(mAxis, mRef);

	nllMat44RotationAxis(mAxis, nllVec3Set(axis, 0, 1, 0), cosA, sinA);
	nllMat44RotationY(mRef, cosA, sinA);
	CHECK_M44_EQ(mAxis, mRef);

	nllMat44RotationAxis(mAxis, nllVec3Set(axis, 0, 0, 1), cosA, sinA);
	nllMat44RotationZ(mRef, cosA, sinA);
	CHECK_M44_EQ(mAxis, mRef);
}
