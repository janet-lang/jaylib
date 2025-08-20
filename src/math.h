#include "raylib.h"
#include "raymath.h"

//----------------------------------------------------------------------------------
// Module Functions Definition - Utils math
//----------------------------------------------------------------------------------
static Janet cfun_Clamp(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  float value = janet_getnumber(argv, 0);
  float min = janet_getnumber(argv, 1);
  float max = janet_getnumber(argv, 2);

  return janet_wrap_number(Clamp(value, min, max));
}

static Janet cfun_Lerp(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  float start = janet_getnumber(argv, 0);
  float end = janet_getnumber(argv, 1);
  float amount = janet_getnumber(argv, 2);

  return janet_wrap_number(Lerp(start, end, amount));
}

static Janet cfun_Normalize(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  float value = janet_getnumber(argv, 0);
  float start = janet_getnumber(argv, 1);
  float end = janet_getnumber(argv, 2);

  return janet_wrap_number(Normalize(value, start, end));
}

static Janet cfun_Remap(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 5);
  float value = janet_getnumber(argv, 0);
  float inputStart = janet_getnumber(argv, 1);
  float inputEnd = janet_getnumber(argv, 2);
  float outputStart = janet_getnumber(argv, 3);
  float outputEnd = janet_getnumber(argv, 4);

  return janet_wrap_number(Remap(value, inputStart, inputEnd, outputStart, outputEnd));
}

static Janet cfun_Wrap(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  float value = janet_getnumber(argv, 0);
  float min = janet_getnumber(argv, 1);
  float max = janet_getnumber(argv, 2);

  return janet_wrap_number(Wrap(value, min, max));
}

static Janet cfun_FloatEquals(int32_t argc, Janet *argv) {
#if !defined(EPSILON)
#define EPSILON 0.000001f
#endif
  janet_fixarity(argc, 2);
  float x = janet_getnumber(argv, 0);
  float y = janet_getnumber(argv, 1);

  return janet_wrap_boolean(FloatEquals(x, y));
}

// Tries to replicate glm::angle
/* return acos(clamp(dot(x, y), T(-1), T(1))); */
static Janet cfun_Vector2AlignAngle(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v1 = jaylib_getvec2(argv, 0);
  Vector2 v2 = jaylib_getvec2(argv, 1);

  float dot = (v1.x * v2.x + v1.y * v2.y);

  float min = -1.0f;
  float max = 1.0f;
  float result = (dot < min) ? min : dot;

  if (result > max)
    result = max;
  result = acosf(result);

  return janet_wrap_number(result);
}

//----------------------------------------------------------------------------------
// Module Functions Definition - Vector2 math
//----------------------------------------------------------------------------------
static Janet cfun_Vector2Zero(int32_t argc, Janet *argv) {
  (void)argv;
  janet_fixarity(argc, 0);

  return jaylib_wrap_vec2(Vector2Zero());
}

static Janet cfun_Vector2One(int32_t argc, Janet *argv) {
  (void)argv;
  janet_fixarity(argc, 0);

  return jaylib_wrap_vec2(Vector2One());
}

static Janet cfun_Vector2Add(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v1 = jaylib_getvec2(argv, 0);
  Vector2 v2 = jaylib_getvec2(argv, 1);

  return jaylib_wrap_vec2(Vector2Add(v1, v2));
}

static Janet cfun_Vector2AddValue(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v = jaylib_getvec2(argv, 0);
  float add = (float)janet_getnumber(argv, 1);

  return jaylib_wrap_vec2(Vector2AddValue(v, add));
}

static Janet cfun_Vector2Subtract(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v1 = jaylib_getvec2(argv, 0);
  Vector2 v2 = jaylib_getvec2(argv, 1);

  return jaylib_wrap_vec2(Vector2Subtract(v1, v2));
}

static Janet cfun_Vector2SubtractValue(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v = jaylib_getvec2(argv, 0);
  float sub = janet_getnumber(argv, 1);

  return jaylib_wrap_vec2(Vector2SubtractValue(v, sub));
}
static Janet cfun_Vector2Length(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Vector2 v = jaylib_getvec2(argv, 0);

  return janet_wrap_number(Vector2Length(v));
}

static Janet cfun_Vector2LengthSqr(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Vector2 v = jaylib_getvec2(argv, 0);

  return janet_wrap_number(Vector2LengthSqr(v));
}

static Janet cfun_Vector2DotProduct(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v1 = jaylib_getvec2(argv, 0);
  Vector2 v2 = jaylib_getvec2(argv, 1);

  return janet_wrap_number(Vector2DotProduct(v1, v2));
}

static Janet cfun_Vector2Distance(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v1 = jaylib_getvec2(argv, 0);
  Vector2 v2 = jaylib_getvec2(argv, 1);

  return janet_wrap_number(Vector2Distance(v1, v2));
}

static Janet cfun_Vector2DistanceSqr(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v1 = jaylib_getvec2(argv, 0);
  Vector2 v2 = jaylib_getvec2(argv, 1);

  return janet_wrap_number(Vector2DistanceSqr(v1, v2));
}

// NOTE: Angle is calculated from origin point (0, 0)
static Janet cfun_Vector2Angle(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v1 = jaylib_getvec2(argv, 0);
  Vector2 v2 = jaylib_getvec2(argv, 1);

  return janet_wrap_number(Vector2Angle(v1, v2));
}

// NOTE: Parameters need to be normalized
// Current implementation should be aligned with glm::angle
static Janet cfun_Vector2LineAngle(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 start = jaylib_getvec2(argv, 0);
  Vector2 end = jaylib_getvec2(argv, 1);

  return janet_wrap_number(Vector2LineAngle(start, end));
}

static Janet cfun_Vector2Scale(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v = jaylib_getvec2(argv, 0);
  float scalar = janet_getnumber(argv, 1);

  return jaylib_wrap_vec2(Vector2Scale(v, scalar));
}

static Janet cfun_Vector2Multiply(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v1 = jaylib_getvec2(argv, 0);
  Vector2 v2 = jaylib_getvec2(argv, 1);

  return jaylib_wrap_vec2(Vector2Multiply(v1, v2));
}

static Janet cfun_Vector2Negate(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Vector2 v = jaylib_getvec2(argv, 0);
  Vector2 result = {-v.x, -v.y};

  return jaylib_wrap_vec2(result);
}

static Janet cfun_Vector2Divide(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v1 = jaylib_getvec2(argv, 0);
  Vector2 v2 = jaylib_getvec2(argv, 1);

  return jaylib_wrap_vec2(Vector2Divide(v1, v2));
}

static Janet cfun_Vector2Normalize(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Vector2 v = jaylib_getvec2(argv, 0);

  return jaylib_wrap_vec2(Vector2Normalize(v));
}

static Janet cfun_Vector2Transform(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v = jaylib_getvec2(argv, 0);
  Matrix mat = jaylib_getmatrix(argv, 1);

  return jaylib_wrap_vec2(Vector2Transform(v, mat));
}

static Janet cfun_Vector2Lerp(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Vector2 v1 = jaylib_getvec2(argv, 0);
  Vector2 v2 = jaylib_getvec2(argv, 1);
  float amount = janet_getnumber(argv, 2);

  return jaylib_wrap_vec2(Vector2Lerp(v1, v2, amount));
}

static Janet cfun_Vector2Reflect(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v = jaylib_getvec2(argv, 0);
  Vector2 normal = jaylib_getvec2(argv, 1);

  return jaylib_wrap_vec2(Vector2Reflect(v, normal));
}

static Janet cfun_Vector2Rotate(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v = jaylib_getvec2(argv, 0);
  float angle = janet_getnumber(argv, 1);

  return jaylib_wrap_vec2(Vector2Rotate(v, angle));
}

static Janet cfun_Vector2MoveTowards(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Vector2 v = jaylib_getvec2(argv, 0);
  Vector2 target = jaylib_getvec2(argv, 1);
  float maxDistance = janet_getnumber(argv, 2);

  return jaylib_wrap_vec2(Vector2MoveTowards(v, target, maxDistance));
}

static Janet cfun_Vector2Invert(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Vector2 v = jaylib_getvec2(argv, 0);

  return jaylib_wrap_vec2(Vector2Invert(v));
}

static Janet cfun_Vector2Clamp(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Vector2 v = jaylib_getvec2(argv, 0);
  Vector2 min = jaylib_getvec2(argv, 1);
  Vector2 max = jaylib_getvec2(argv, 2);

  return jaylib_wrap_vec2(Vector2Clamp(v, min, max));
}
static Janet cfun_Vector2ClampValue(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Vector2 v = jaylib_getvec2(argv, 0);
  float min = janet_getnumber(argv, 1);
  float max = janet_getnumber(argv, 2);

  return jaylib_wrap_vec2(Vector2ClampValue(v, min, max));
}
static Janet cfun_Vector2Equals(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 p = jaylib_getvec2(argv, 0);
  Vector2 q = jaylib_getvec2(argv, 1);

  return janet_wrap_boolean(Vector2Equals(p, q));
}

//----------------------------------------------------------------------------------
// Module Functions Definition - Vector3 math
//----------------------------------------------------------------------------------

static Janet cfun_Vector3Zero(int32_t argc, Janet *argv) {
  (void)argv;
  janet_fixarity(argc, 0);

  return jaylib_wrap_vec3(Vector3Zero());
}

static Janet cfun_Vector3One(int32_t argc, Janet *argv) {
  (void)argv;
  janet_fixarity(argc, 0);

  return jaylib_wrap_vec3(Vector3One());
}

static Janet cfun_Vector3Add(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);

  return jaylib_wrap_vec3(Vector3Add(v1, v2));
}

static Janet cfun_Vector3AddValue(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v = jaylib_getvec3(argv, 0);
  float add = janet_getnumber(argv, 1);

  return jaylib_wrap_vec3(Vector3AddValue(v, add));
}

static Janet cfun_Vector3Subtract(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);

  return jaylib_wrap_vec3(Vector3Subtract(v1, v2));
}

static Janet cfun_Vector3SubtractValue(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v = jaylib_getvec3(argv, 0);
  float sub = janet_getnumber(argv, 1);

  return jaylib_wrap_vec3(Vector3SubtractValue(v, sub));
}

static Janet cfun_Vector3Scale(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v = jaylib_getvec3(argv, 0);
  float scalar = janet_getnumber(argv, 1);

  return jaylib_wrap_vec3(Vector3Scale(v, scalar));
}

static Janet cfun_Vector3Multiply(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);

  return jaylib_wrap_vec3(Vector3Multiply(v1, v2));
}

static Janet cfun_Vector3CrossProduct(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);

  return jaylib_wrap_vec3(Vector3CrossProduct(v1, v2));
}

static Janet cfun_Vector3Perpendicular(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Vector3 v = jaylib_getvec3(argv, 0);

  return jaylib_wrap_vec3(Vector3Perpendicular(v));
}

static Janet cfun_Vector3Length(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Vector3 v = jaylib_getvec3(argv, 0);

  return janet_wrap_number(Vector3Length(v));
}

static Janet cfun_Vector3LengthSqr(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Vector3 v = jaylib_getvec3(argv, 0);

  return janet_wrap_number(Vector3LengthSqr(v));
}

static Janet cfun_Vector3DotProduct(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);

  return janet_wrap_number(Vector3DotProduct(v1, v2));
}

static Janet cfun_Vector3Distance(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);

  return janet_wrap_number(Vector3Distance(v1, v2));
}

static Janet cfun_Vector3DistanceSqr(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);

  return janet_wrap_number(Vector3DistanceSqr(v1, v2));
}

static Janet cfun_Vector3Angle(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);

  return janet_wrap_number(Vector3Angle(v1, v2));
}

static Janet cfun_Vector3Negate(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Vector3 v = jaylib_getvec3(argv, 0);

  return jaylib_wrap_vec3(Vector3Negate(v));
}

static Janet cfun_Vector3Divide(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);

  return jaylib_wrap_vec3(Vector3Divide(v1, v2));
}

static Janet cfun_Vector3Normalize(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Vector3 v = jaylib_getvec3(argv, 0);

  return jaylib_wrap_vec3(Vector3Normalize(v));
}

static Janet cfun_Vector3Project(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);

  return jaylib_wrap_vec3(Vector3Project(v1, v2));
}

static Janet cfun_Vector3Reject(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);

  return jaylib_wrap_vec3(Vector3Reject(v1, v2));
}

// TODO: This cannot be implemented the same way that it is in raymath.
// We could define one that returns a copy of the two Vector3,
// and another that takes in two mutable objects such as JanetArrays.
static Janet cfun_Vector3OrthoNormalize(int32_t argc, Janet *argv) {
  return janet_wrap_nil();
}

static Janet cfun_Vector3Transform(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v = jaylib_getvec3(argv, 0);
  Matrix mat = jaylib_getmatrix(argv, 1);

  return jaylib_wrap_vec3(Vector3Transform(v, mat));
}

static Janet cfun_Vector3RotateByQuaternion(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v = jaylib_getvec3(argv, 0);
  Quaternion q = jaylib_getvec4(argv, 1);

  return jaylib_wrap_vec3(Vector3RotateByQuaternion(v, q));
}

static Janet cfun_Vector3RotateByAxisAngle(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Vector3 v = jaylib_getvec3(argv, 0);
  Vector3 axis = jaylib_getvec3(argv, 1);
  float angle = janet_getnumber(argv, 2);

  return jaylib_wrap_vec3(Vector3RotateByAxisAngle(v, axis, angle));
}

static Janet cfun_Vector3Lerp(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);
  float amount = janet_getnumber(argv, 2);

  return jaylib_wrap_vec3(Vector3Lerp(v1, v2, amount));
}

static Janet cfun_Vector3Reflect(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v = jaylib_getvec3(argv, 0);
  Vector3 normal = jaylib_getvec3(argv, 1);

  return jaylib_wrap_vec3(Vector3Reflect(v, normal));
}

static Janet cfun_Vector3Min(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);

  return jaylib_wrap_vec3(Vector3Min(v1, v2));
}

static Janet cfun_Vector3Max(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);

  return jaylib_wrap_vec3(Vector3Max(v1, v2));
}

static Janet cfun_Vector3Barycenter(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 4);
  Vector3 p = jaylib_getvec3(argv, 0);
  Vector3 a = jaylib_getvec3(argv, 1);
  Vector3 b = jaylib_getvec3(argv, 2);
  Vector3 c = jaylib_getvec3(argv, 3);

  return jaylib_wrap_vec3(Vector3Barycenter(p, a, b, c));
}

static Janet cfun_Vector3Unproject(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Vector3 source = jaylib_getvec3(argv, 0);
  Matrix projection = jaylib_getmatrix(argv, 1);
  Matrix view = jaylib_getmatrix(argv, 2);

  return jaylib_wrap_vec3(Vector3Unproject(source, projection, view));
}

static Janet cfun_Vector3ToFloatV(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Vector3 v = jaylib_getvec3(argv, 0);
  JanetArray *arr = janet_array(3);
  janet_array_push(arr, janet_wrap_number(v.x));
  janet_array_push(arr, janet_wrap_number(v.y));
  janet_array_push(arr, janet_wrap_number(v.z));

  return janet_wrap_array(arr);
}

static Janet cfun_Vector3Invert(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Vector3 v = jaylib_getvec3(argv, 0);

  return jaylib_wrap_vec3(Vector3Invert(v));
}

static Janet cfun_Vector3Clamp(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Vector3 v = jaylib_getvec3(argv, 0);
  Vector3 min = jaylib_getvec3(argv, 1);
  Vector3 max = jaylib_getvec3(argv, 2);

  return jaylib_wrap_vec3(Vector3Clamp(v, min, max));
}
static Janet cfun_Vector3ClampValue(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Vector3 v = jaylib_getvec3(argv, 0);
  float min = janet_getnumber(argv, 1);
  float max = janet_getnumber(argv, 2);

  return jaylib_wrap_vec3(Vector3ClampValue(v, min, max));
}
static Janet cfun_Vector3Equals(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 p = jaylib_getvec3(argv, 0);
  Vector3 q = jaylib_getvec3(argv, 1);

  return janet_wrap_boolean(Vector3Equals(p, q));
}

static Janet cfun_Vector3Refract(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Vector3 v = jaylib_getvec3(argv, 0);
  Vector3 n = jaylib_getvec3(argv, 1);
  float r = janet_getnumber(argv, 2);

  return jaylib_wrap_vec3(Vector3Refract(v, n, r));
}

//----------------------------------------------------------------------------------
// Module Functions Definition - Matrix math
//----------------------------------------------------------------------------------

static Janet cfun_MatrixDeterminant(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Matrix mat = jaylib_getmatrix(argv, 0);

  return janet_wrap_number(MatrixDeterminant(mat));
}

static Janet cfun_MatrixTrace(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Matrix mat = jaylib_getmatrix(argv, 0);

  return janet_wrap_number(MatrixTrace(mat));
}

static Janet cfun_MatrixTranspose(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Matrix mat = jaylib_getmatrix(argv, 0);

  return jaylib_wrap_matrix(MatrixTranspose(mat));
}

static Janet cfun_MatrixInvert(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Matrix mat = jaylib_getmatrix(argv, 0);

  return jaylib_wrap_matrix(MatrixInvert(mat));
}

static Janet cfun_MatrixIdentity(int32_t argc, Janet *argv) {
  (void)argv;
  janet_fixarity(argc, 1);

  return jaylib_wrap_matrix(MatrixIdentity());
}

static Janet cfun_MatrixAdd(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Matrix left = jaylib_getmatrix(argv, 0);
  Matrix right = jaylib_getmatrix(argv, 1);

  return jaylib_wrap_matrix(MatrixAdd(left, right));
}

static Janet cfun_MatrixSubtract(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Matrix left = jaylib_getmatrix(argv, 0);
  Matrix right = jaylib_getmatrix(argv, 1);

  return jaylib_wrap_matrix(MatrixSubtract(left, right));
}

static Janet cfun_MatrixMultiply(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Matrix left = jaylib_getmatrix(argv, 0);
  Matrix right = jaylib_getmatrix(argv, 1);

  return jaylib_wrap_matrix(MatrixMultiply(left, right));
}

static Janet cfun_MatrixTranslate(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  float x = janet_getnumber(argv, 0);
  float y = janet_getnumber(argv, 1);
  float z = janet_getnumber(argv, 2);

  return jaylib_wrap_matrix(MatrixTranslate(x, y, z));
}

static Janet cfun_MatrixRotate(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 axis = jaylib_getvec3(argv, 0);
  float angle = janet_getnumber(argv, 1);

  return jaylib_wrap_matrix(MatrixRotate(axis, angle));
}
static Janet cfun_MatrixRotateX(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  float angle = janet_getnumber(argv, 0);

  return jaylib_wrap_matrix(MatrixRotateX(angle));
}

static Janet cfun_MatrixRotateY(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  float angle = janet_getnumber(argv, 0);

  return jaylib_wrap_matrix(MatrixRotateY(angle));
}

static Janet cfun_MatrixRotateZ(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  float angle = janet_getnumber(argv, 0);

  return jaylib_wrap_matrix(MatrixRotateZ(angle));
}

static Janet cfun_MatrixRotateXYZ(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Vector3 angle = jaylib_getvec3(argv, 0);

  return jaylib_wrap_matrix(MatrixRotateXYZ(angle));
}

static Janet cfun_MatrixRotateZYX(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Vector3 angle = jaylib_getvec3(argv, 0);

  return jaylib_wrap_matrix(MatrixRotateZYX(angle));
}

static Janet cfun_MatrixScale(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  float x = janet_getnumber(argv, 0);
  float y = janet_getnumber(argv, 1);
  float z = janet_getnumber(argv, 2);

  return jaylib_wrap_matrix(MatrixScale(x, y, z));
}

static Janet cfun_MatrixFrustum(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 6);
  double left = janet_getnumber(argv, 0);
  double right = janet_getnumber(argv, 1);
  double bottom = janet_getnumber(argv, 2);
  double top = janet_getnumber(argv, 3);
  double near = janet_getnumber(argv, 4);
  double far = janet_getnumber(argv, 5);

  return jaylib_wrap_matrix(MatrixFrustum(left, right, bottom, top, near, far));
}

static Janet cfun_MatrixPerspective(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 4);
  double fovY = janet_getnumber(argv, 0);
  double aspect = janet_getnumber(argv, 1);
  double nearPlane = janet_getnumber(argv, 2);
  double farPlane = janet_getnumber(argv, 3);

  return jaylib_wrap_matrix(MatrixPerspective(fovY, aspect, nearPlane, farPlane));
}

static Janet cfun_MatrixOrtho(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 6);
  double left = janet_getnumber(argv, 0);
  double right = janet_getnumber(argv, 1);
  double bottom = janet_getnumber(argv, 2);
  double top = janet_getnumber(argv, 3);
  double nearPlane = janet_getnumber(argv, 4);
  double farPlane = janet_getnumber(argv, 5);

  return jaylib_wrap_matrix(MatrixOrtho(left, right, bottom, top, nearPlane, farPlane));
}

static Janet cfun_MatrixLookAt(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Vector3 eye = jaylib_getvec3(argv, 0);
  Vector3 target = jaylib_getvec3(argv, 1);
  Vector3 up = jaylib_getvec3(argv, 2);

  return jaylib_wrap_matrix(MatrixLookAt(eye, target, up));
}

static Janet cfun_MatrixToFloatV(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Matrix mat = jaylib_getmatrix(argv, 0);
  JanetArray *arr = janet_array(3);
  janet_array_push(arr, janet_wrap_number(mat.m0));
  janet_array_push(arr, janet_wrap_number(mat.m1));
  janet_array_push(arr, janet_wrap_number(mat.m2));
  janet_array_push(arr, janet_wrap_number(mat.m3));
  janet_array_push(arr, janet_wrap_number(mat.m4));
  janet_array_push(arr, janet_wrap_number(mat.m5));
  janet_array_push(arr, janet_wrap_number(mat.m6));
  janet_array_push(arr, janet_wrap_number(mat.m7));
  janet_array_push(arr, janet_wrap_number(mat.m8));
  janet_array_push(arr, janet_wrap_number(mat.m9));
  janet_array_push(arr, janet_wrap_number(mat.m10));
  janet_array_push(arr, janet_wrap_number(mat.m11));
  janet_array_push(arr, janet_wrap_number(mat.m12));
  janet_array_push(arr, janet_wrap_number(mat.m13));
  janet_array_push(arr, janet_wrap_number(mat.m14));
  janet_array_push(arr, janet_wrap_number(mat.m15));

  return janet_wrap_array(arr);
}

static Janet cfun_QuaternionAdd(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Quaternion q1 = jaylib_getvec4(argv, 0);
  Quaternion q2 = jaylib_getvec4(argv, 1);

  return jaylib_wrap_vec4(QuaternionAdd(q1, q2));
}

static Janet cfun_QuaternionAddValue(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Quaternion q = jaylib_getvec4(argv, 0);
  float add = janet_getnumber(argv, 1);

  return jaylib_wrap_vec4(QuaternionAddValue(q, add));
}

static Janet cfun_QuaternionSubtract(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Quaternion q1 = jaylib_getvec4(argv, 0);
  Quaternion q2 = jaylib_getvec4(argv, 1);

  return jaylib_wrap_vec4(QuaternionSubtract(q1, q2));
}

static Janet cfun_QuaternionSubtractValue(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Quaternion q = jaylib_getvec4(argv, 0);
  float sub = janet_getnumber(argv, 1);

  return jaylib_wrap_vec4(QuaternionSubtractValue(q, sub));
}

static Janet cfun_QuaternionIdentity(int32_t argc, Janet *argv) {
  (void)argv;
  janet_fixarity(argc, 0);

  return jaylib_wrap_vec4(QuaternionIdentity());
}

static Janet cfun_QuaternionLength(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Quaternion q = jaylib_getvec4(argv, 0);

  return janet_wrap_number(QuaternionLength(q));
}

static Janet cfun_QuaternionNormalize(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Quaternion q = jaylib_getvec4(argv, 0);

  return jaylib_wrap_vec4(QuaternionNormalize(q));
}

static Janet cfun_QuaternionInvert(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Quaternion q = jaylib_getvec4(argv, 0);

  return jaylib_wrap_vec4(QuaternionInvert(q));
}

static Janet cfun_QuaternionMultiply(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Quaternion q1 = jaylib_getvec4(argv, 0);
  Quaternion q2 = jaylib_getvec4(argv, 1);

  return jaylib_wrap_vec4(QuaternionMultiply(q1, q2));
}

static Janet cfun_QuaternionScale(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Quaternion q = jaylib_getvec4(argv, 0);
  float scalar = janet_getnumber(argv, 1);

  return jaylib_wrap_vec4(QuaternionScale(q, scalar));
}

static Janet cfun_QuaternionDivide(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Quaternion q1 = jaylib_getvec4(argv, 0);
  Quaternion q2 = jaylib_getvec4(argv, 1);

  return jaylib_wrap_vec4(QuaternionDivide(q1, q2));
}

static Janet cfun_QuaternionLerp(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Quaternion q1 = jaylib_getvec4(argv, 0);
  Quaternion q2 = jaylib_getvec4(argv, 1);
  float amount = janet_getnumber(argv, 2);

  return jaylib_wrap_vec4(QuaternionLerp(q1, q2, amount));
}

static Janet cfun_QuaternionNlerp(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Quaternion q1 = jaylib_getvec4(argv, 0);
  Quaternion q2 = jaylib_getvec4(argv, 1);
  float amount = janet_getnumber(argv, 2);

  return jaylib_wrap_vec4(QuaternionNlerp(q1, q2, amount));
}

static Janet cfun_QuaternionSlerp(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Quaternion q1 = jaylib_getvec4(argv, 0);
  Quaternion q2 = jaylib_getvec4(argv, 1);
  float amount = janet_getnumber(argv, 2);

  return jaylib_wrap_vec4(QuaternionSlerp(q1, q2, amount));
}

static Janet cfun_QuaternionFromVector3ToVector3(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 from = jaylib_getvec3(argv, 0);
  Vector3 to = jaylib_getvec3(argv, 1);

  return jaylib_wrap_vec4(QuaternionFromVector3ToVector3(from, to));
}

static Janet cfun_QuaternionFromMatrix(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Matrix mat = jaylib_getmatrix(argv, 0);

  return jaylib_wrap_vec4(QuaternionFromMatrix(mat));
}

static Janet cfun_QuaternionToMatrix(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Quaternion q = jaylib_getvec4(argv, 0);

  return jaylib_wrap_matrix(QuaternionToMatrix(q));
}

static Janet cfun_QuaternionFromAxisAngle(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 axis = jaylib_getvec3(argv, 0);
  float angle = janet_getnumber(argv, 1);

  return jaylib_wrap_vec4(QuaternionFromAxisAngle(axis, angle));
}
// TODO: Implement me
static Janet cfun_QuaternionToAxisAngle(int32_t argc, Janet *argv) {
  return janet_wrap_nil();
}

static Janet cfun_QuaternionFromEuler(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  float pitch = janet_getnumber(argv, 0);
  float yaw = janet_getnumber(argv, 1);
  float roll = janet_getnumber(argv, 2);

  return jaylib_wrap_vec4(QuaternionFromEuler(pitch, yaw, roll));
}

static Janet cfun_QuaternionToEuler(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Quaternion q = jaylib_getvec4(argv, 0);

  return jaylib_wrap_vec3(QuaternionToEuler(q));
}

static Janet cfun_QuaternionTransform(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Quaternion q = jaylib_getvec4(argv, 0);
  Matrix mat = jaylib_getmatrix(argv, 1);

  return jaylib_wrap_vec4(QuaternionTransform(q, mat));
}

static Janet cfun_QuaternionEquals(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Quaternion p = jaylib_getvec4(argv, 0);
  Quaternion q = jaylib_getvec4(argv, 1);

  return janet_wrap_boolean(QuaternionEquals(p, q));
}
static const JanetReg math_cfuns[] = {
    // Utils
    {"utils/clamp", cfun_Clamp,
     "(utils/clamp x min max)\n\n"
     "Clamp x between min and max"},
    {"utils/lerp", cfun_Lerp,
     "(utils/lerp start end amount)\n\n"
     "Calculate linear interpolation between two numbers"},
    {"utils/normalize", cfun_Normalize,
     "(utils/normalize x start end)\n\n"
     "Normalize x within input range"},
    {"utils/remap", cfun_Remap,
     "(utils/remap x input-start input-end output-start output-end)\n\n"
     "Remap x within input range to output range"},
    {"utils/wrap", cfun_Wrap,
     "(utils/wrap x min max)\n\n"
     "Wrap x from min to max"},
    {"utils/float-equals", cfun_FloatEquals,
     "(utils/float-equals x y)\n\n"
     "Check whether two given numbers are almost equal"},

    // Custom helpers
    {"vector2-align-angle", cfun_Vector2AlignAngle,
     "(vector2-align-angle v1 v2)\n\n"
     "Returns the absolute angle between two vectors."},

    // Vector2
    {"vector2-zero", cfun_Vector2Zero,
     "(vector2-zero)\n\n"
     "Vector with components 0.0"},
    {"vector2-one", cfun_Vector2One,
     "(vector2-one)\n\n"
     "Vector with components 1.0"},
    {"vector2-add", cfun_Vector2Add,
     "(vector2-add v1 v2)\n\n"
     "Add two vectors (v1 + v2)"},
    {"vector2-add-val", cfun_Vector2AddValue,
     "(vector2-add-val v x)\n\n"
     "Add vector and x"},
    {"vector2-sub", cfun_Vector2Subtract,
     "(vector2-sub v1 v2)\n\n"
     "Subtract two vectors (v1 - v2)"},
    {"vector2-sub-val", cfun_Vector2SubtractValue,
     "(vector2-sub-val v x)\n\n"
     "Subtract vector by x"},
    {"vector2-length", cfun_Vector2Length,
     "(vector2-length v)\n\n"
     "Calculate vector length"},
    {"vector2-length-sqr", cfun_Vector2LengthSqr,
     "(vector2-length-sqr v)\n\n"
     "Calculate vector square length"},
    {"vector2-dot", cfun_Vector2DotProduct,
     "(vector2-dot v1 v2)\n\n"
     "Calculate the dot product of two vectors"},
    {"vector2-distance", cfun_Vector2Distance,
     "(vector2-distance v1 v2)\n\n"
     "Calculate distance between two vectors"},
    {"vector2-distance-sqr", cfun_Vector2DistanceSqr,
     "(vector2-distance-sqr v1 v2)\n\n"
     "Calculate square distance between two vectors"},
    {"vector2-angle", cfun_Vector2Angle,
     "(vector2-angle v1 v2)\n\n"
     "Calculate angle between two vectors"},
    {"vector2-line-angle", cfun_Vector2LineAngle,
     "(vector2-line-angle start end)\n\n"
     "Calculate angle defined by a two vector line"},
    {"vector2-scale", cfun_Vector2Scale,
     "(vector2-scale v scalar)\n\n"
     "Scale vector by scalar"},
    {"vector2-multiply", cfun_Vector2Multiply,
     "(vector2-multiply v1 v2)\n\n"
     "Multiply vector by vector"},
    {"vector2-negate", cfun_Vector2Negate,
     "(vector2-negate v)\n\n"
     "Negate vector"},
    {"vector2-divide", cfun_Vector2Divide,
     "(vector2-divide v1 v2)\n\n"
     "Divide vector by vector"},
    {"vector2-normalize", cfun_Vector2Normalize,
     "(vector2-normalize v)\n\n"
     "Normalize provided vector"},
    {"vector2-transform", cfun_Vector2Transform,
     "(vector2-transform v mat)\n\n"
     "Transform vector by matrix"},
    {"vector2-lerp", cfun_Vector2Lerp,
     "(vector2-lerp v1 v2 amount)\n\n"
     "Calculate linear interpolation between two vectors"},
    {"vector2-reflect", cfun_Vector2Reflect,
     "(vector2-reflect v normal)\n\n"
     "Calculate reflected vector to normal"},
    {"vector2-rotate", cfun_Vector2Rotate,
     "(vector2-rotate v angle)\n\n"
     "Rotate vector by angle"},
    {"vector2-move-towards", cfun_Vector2MoveTowards,
     "(vector2-move-towards v target max-distance)\n\n"
     "Move vector towards target"},
    {"vector2-invert", cfun_Vector2Invert,
     "(vector2-invert v)\n\n"
     "Invert vector"},
    {"vector2-clamp", cfun_Vector2Clamp,
     "(vector2-clamp v min max)\n\n"
     "Clamp the components of the vector between min and max values specified "
     "by the given vectors."},
    {"vector2-clamp-val", cfun_Vector2ClampValue,
     "(vector2-clamp-val v min max)\n\n"
     "Clamp the magnitude of the vector between two min and max values"},
    {"vector2-equals", cfun_Vector2Equals,
     "(vector2-equals p q)\n\n"
     "Check whether the two given vectors are almost equal"},

    // Vector3
    {"vector3-zero", cfun_Vector3Zero,
     "(vector3-zero)\n\n"
     "Vector with components 0.0"},
    {"vector3-one", cfun_Vector3One,
     "(vector3-one)\n\n"
     "Vector with components 1.0"},
    {"vector3-add", cfun_Vector3Add,
     "(vector3-add v1 v2)\n\n"
     "Add two vectors (v1 + v2)"},
    {"vector3-add-val", cfun_Vector3AddValue,
     "(vector3-add-val v x)\n\n"
     "Add vector and x"},
    {"vector3-sub", cfun_Vector3Subtract,
     "(vector3-sub v1 v2)\n\n"
     "Subtract two vectors (v1 - v2)"},
    {"vector3-sub-val", cfun_Vector3SubtractValue,
     "(vector3-sub-val v x)\n\n"
     "Subtract vector by x"},
    {"vector3-scale", cfun_Vector3Scale,
     "(vector3-scale v scalar)\n\n"
     "Scale vector by scalar"},
    {"vector3-multiply", cfun_Vector3Multiply,
     "(vector3-multiply v1 v2)\n\n"
     "Multiply vector by vector"},
    {"vector3-cross", cfun_Vector3CrossProduct,
     "(vector3-cross v1 v2)\n\n"
     "Calculate the cross product of two vectors"},
    {"vector3-perpendicular", cfun_Vector3Perpendicular,
     "(vector3-perpendicular v)\n\n"
     "Calculate a vector perpendicular to v"},
    {"vector3-length", cfun_Vector3Length,
     "(vector3-length v)\n\n"
     "Calculate vector length"},
    {"vector3-length-sqr", cfun_Vector3LengthSqr,
     "(vector3-length-sqr v)\n\n"
     "Calculate vector square length"},
    {"vector3-dot", cfun_Vector3DotProduct,
     "(vector3-dot v1 v2)\n\n"
     "Calculate the dot product of two vectors"},
    {"vector3-distance", cfun_Vector3Distance,
     "(vector3-distance v1 v2)\n\n"
     "Calculate distance between two vectors"},
    {"vector3-distance-sqr", cfun_Vector3DistanceSqr,
     "(vector3-distance-sqr v1 v2)\n\n"
     "Calculate square distance between two vectors"},
    {"vector3-angle", cfun_Vector3Angle,
     "(vector3-angle v1 v2)\n\n"
     "Calculate angle between two vectors"},
    {"vector3-negate", cfun_Vector3Negate,
     "(vector3-negate v)\n\n"
     "Negate vector"},
    {"vector3-divide", cfun_Vector3Divide,
     "(vector3-divide v1 v2)\n\n"
     "Divide vector by vector"},
    {"vector3-normalize", cfun_Vector3Normalize,
     "(vector3-normalize v)\n\n"
     "Normalize provided vector"},
    {"vector3-project", cfun_Vector3Project,
     "(vector3-project v1 v2)\n\n"
     "Calculate the projection of vector v1 to v2"},
    {"vector3-reject", cfun_Vector3Reject,
     "(vector3-reject v1 v2)\n\n"
     "Calculate the rejection of vector v1 to v2"},

    {"vector3-transform", cfun_Vector3Transform,
     "(vector3-transform v mat)\n\n"
     "Transform vector by matrix"},
    {"vector3-rotate-quat", cfun_Vector3RotateByQuaternion,
     "(vector3-rotate-quat v q)\n\n"
     "Transform by quaternion rotation"},
    {"vector3-rotate-axis", cfun_Vector3RotateByAxisAngle,
     "(vector3-rotate-axis v axis angle)\n\n"
     "Rotate vector around axis"},
    {"vector3-lerp", cfun_Vector3Lerp,
     "(vector3-lerp v1 v2 amount)\n\n"
     "Calculate linear interpolation between two vectors"},
    {"vector3-reflect", cfun_Vector3Reflect,
     "(vector3-reflect v normal)\n\n"
     "Calculate reflected vector to normal"},
    {"vector3-min", cfun_Vector3Min,
     "(vector3-min v)\n\n"
     "Get the minimum value for each pair of components"},
    {"vector3-max", cfun_Vector3Max,
     "(vector3-max v)\n\n"
     "Get the maximum value for each pair of components"},
    {"vector3-barycenter", cfun_Vector3Barycenter,
     "(vector3-barycenter p a b c)\n\n"
     "Compute barycenter coordinates (u, v, w) for point p with respect to "
     "triangle (a, b, c)"
     "\n"
     "Assumes P is on the plane of the triangle"},
    {"vector3-unproject", cfun_Vector3Unproject,
     "(vector3-unproject v proj view)\n\n"
     "Project v from screen space into object space"},
    {"vector3-to-array", cfun_Vector3ToFloatV,
     "(vector3-to-array v)\n\n"
     "Get v as an array of 3 numbers"},
    {"vector3-invert", cfun_Vector3Invert,
     "(vector3-invert v)\n\n"
     "Invert vector"},
    {"vector3-clamp", cfun_Vector3Clamp,
     "(vector3-clamp v min max)\n\n"
     "Clamp the components of the vector between min and max values specified "
     "by the given vectors."},
    {"vector3-clamp-val", cfun_Vector3ClampValue,
     "(vector3-clamp-val v min max)\n\n"
     "Clamp the magnitude of the vector between two min and max values"},
    {"vector3-equals", cfun_Vector3Equals,
     "(vector3-equals p q)\n\n"
     "Check whether the two given vectors are almost equal"},
    {"vector3-refract", cfun_Vector3Refract,
     "(vector3-refract v n r)\n\n"
     "Compute the direction of a refracted ray"
     "\n"
     "v: normalized direction of the incoming ray"
     "\n"
     "n: normalized normal vector of the interface of two optical media"
     "\n"
     "r: ratio of the refractive index of the medium from where the ray comes"
     "\n"
     "   to the refractive index of the medium on the other side of the "
     "surface"},

    // Matrix
    {"matrix-determinant", cfun_MatrixDeterminant,
     "(matrix-determinant m)\n\n"
     "Compute matrix determinant"},
    {"matrix-trace", cfun_MatrixTrace,
     "(matrix-trace m)\n\n"
     "Compute the sum of the values along the diagonal"},
    {"matrix-transpose", cfun_MatrixTranspose,
     "(matrix-transpose m)\n\n"
     "Tranpose provided matrix"},
    {"matrix-invert", cfun_MatrixInvert,
     "(matrix-invert m)\n\n"
     "Invert provided matrix"},
    {"matrix-identity", cfun_MatrixIdentity,
     "(matrix-identity)\n\n"
     "Get the identity matrix"},
    {"matrix-add", cfun_MatrixAdd,
     "(matrix-add m1 m2)\n\n"
     "Add two matrices"},
    {"matrix-sub", cfun_MatrixSubtract,
     "(matrix-sub m1 m2)\n\n"
     "Subtract two matrices"},
    {"matrix-multiply", cfun_MatrixMultiply,
     "(matrix-multiply m1 m2)\n\n"
     "Multiply two matrices"},
    {"matrix-translate", cfun_MatrixTranslate,
     "(matrix-translate x y z)\n\n"
     "Create translation matrix from coordinates"},
    {"matrix-rotate", cfun_MatrixRotate,
     "(matrix-rotate axis angle)\n\n"
     "Create rotation matrix from axis and angle"},
    {"matrix-rotate-x", cfun_MatrixRotateX,
     "(matrix-rotate-x angle)\n\n"
     "Get x-rotation matrix"
     "\n"
     "Angle must be provided in radians"},
    {"matrix-rotate-y", cfun_MatrixRotateY,
     "(matrix-rotate-y angle)\n\n"
     "Get y-rotation matrix"
     "\n"
     "Angle must be provided in radians"},
    {"matrix-rotate-z", cfun_MatrixRotateZ,
     "(matrix-rotate-z angle)\n\n"
     "Get z-rotation matrix"
     "\n"
     "Angle must be provided in radians"},
    {"matrix-rotate-xyz", cfun_MatrixRotateXYZ,
     "(matrix-rotate-xyz angle)\n\n"
     "Get xyz-rotation matrix"
     "\n"
     "Angle must be a Vector3 containing radians"},
    {"matrix-rotate-zyx", cfun_MatrixRotateZYX,
     "(matrix-rotate-zyx angle)\n\n"
     "Get zyx-rotation matrix"
     "\n"
     "Angle must be a Vector3 containing radians"},
    {"matrix-scale", cfun_MatrixScale,
     "(matrix-scale x y z)\n\n"
     "Get scaling matrix"},
    {"matrix-frustum", cfun_MatrixFrustum,
     "(matrix-frustum left right bottom top near far)\n\n"
     "Get frustum matrix"},
    {"matrix-perspective", cfun_MatrixPerspective,
     "(matrix-perspective fovy aspect near far)\n\n"
     "Get perspective projection matrix"
     "\n"
     "fovy angle must be provided in radians"},
    {"matrix-ortho", cfun_MatrixOrtho,
     "(matrix-ortho left right bottom top near far)\n\n"
     "Get orthographic projection matrix"},
    {"matrix-lookat", cfun_MatrixLookAt,
     "(matrix-lookat eye target up)\n\n"
     "Get camera look-at matrix (view matrix)"},
    {"matrix-to-array", cfun_MatrixToFloatV,
     "(matrix-lookat m)\n\n"
     "Get m as an array of 16 numbers"},

    // Quaternion
    {"quaternion-add", cfun_QuaternionAdd,
     "(quaternion-add q1 q2)\n\n"
     "Add two quaternions"},
    {"quaternion-add-val", cfun_QuaternionAddValue,
     "(quaternion-add-val q x)\n\n"
     "Add quaternion and number"},
    {"quaternion-sub", cfun_QuaternionSubtract,
     "(quaternion-sub q1 q2)\n\n"
     "Subtract two quaternions"},
    {"quaternion-sub-val", cfun_QuaternionSubtractValue,
     "(quaternion-sub-val q x)\n\n"
     "Subtract quaternion and number"},
    {"quaternion-identity", cfun_QuaternionIdentity,
     "(quaternion-identity)\n\n"
     "Get identity quaternion"},
    {"quaternion-length", cfun_QuaternionLength,
     "(quaternion-length q)\n\n"
     "Compute the length of quaternion"},
    {"quaternion-normalize", cfun_QuaternionNormalize,
     "(quaternion-normalize q)\n\n"
     "Normalize quaternion"},
    {"quaternion-invert", cfun_QuaternionInvert,
     "(quaternion-invert q)\n\n"
     "Invert quaternion"},
    {"quaternion-multiply", cfun_QuaternionMultiply,
     "(quaternion-multiply q1 q2)\n\n"
     "Multiply two quaternions"},
    {"quaternion-scale", cfun_QuaternionScale,
     "(quaternion-scale q scalar)\n\n"
     "Scale quaternion by scalar"},
    {"quaternion-divide", cfun_QuaternionDivide,
     "(quaternion-divide q1 q2)\n\n"
     "Divide two quaternions"},
    {"quaternion-lerp", cfun_QuaternionLerp,
     "(quaternion-lerp q1 q2 amount)\n\n"
     "Calculate linear interpolation between two quaternions"},
    {"quaternion-nlerp", cfun_QuaternionNlerp,
     "(quaternion-nlerp q1 q2 amount)\n\n"
     "Calculate slerp-optimzed interpolation between two quaternions"},
    {"quaternion-slerp", cfun_QuaternionSlerp,
     "(quaternion-slerp q1 q2 amount)\n\n"
     "Calculate spherical interpolation between two quaternions"},
    {"quaternion-from-vec3s", cfun_QuaternionFromVector3ToVector3,
     "(quaternion-from-vec3s v1 v2)\n\n"
     "Create quaternion based on the rotation from the rotation from one vector to another"},
    {"quaternion-from-matrix", cfun_QuaternionFromMatrix,
     "(quaternion-from-matrix m)\n\n"
     "Get a quaternion for a given rotation matrix"},
    {"quaternion-to-matrix", cfun_QuaternionToMatrix,
     "(quaternion-to-matrix q)\n\n"
     "Get a matrix for a given quaternion"},
    {"quaternion-from-axis", cfun_QuaternionFromAxisAngle,
     "(quaternion-from-axis axis angle)\n\n"
     "Get rotation quaternion for an angle and axis"
     "\n"
     "Angle must be provided in radians"},

    {"quaternion-from-euler", cfun_QuaternionFromEuler,
     "(quaternion-from-euler pitch yaw roll)\n\n"
     "Get a quaternion equivalent to Euler angles"
     "\n"
     "Rotation order is ZYX"},
    {"quaternion-to-euler", cfun_QuaternionToEuler,
     "(quaternion-to-euler q)\n\n"
     "Get a quaternion equivalent to Euler angles"
     "\n"
     "Angles are returned in a Vector3 in radians"},
    {"quaternion-transform", cfun_QuaternionTransform,
     "(quaternion-transform q m)\n\n"
     "Transform a quaternion given a transformation matrix"},
    {"quaternion-equals", cfun_QuaternionEquals,
     "(quaternion-equals p q)\n\n"
     "Check whether two given quaternions are almost equal"},
};
