#include "raylib.h"

//----------------------------------------------------------------------------------
// Module Functions Definition - Utils math
//----------------------------------------------------------------------------------
static Janet cfun_Clamp(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  float value = janet_getnumber(argv, 0);
  float min = janet_getnumber(argv, 1);
  float max = janet_getnumber(argv, 2);
  float result = (value < min) ? min : value;

  if (result > max)
    result = max;

  return janet_wrap_number(result);
}

static Janet cfun_Lerp(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  float start = janet_getnumber(argv, 0);
  float end = janet_getnumber(argv, 1);
  float amount = janet_getnumber(argv, 2);
  float result = start + amount * (end - start);

  return janet_wrap_number(result);
}

static Janet cfun_Normalize(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  float value = janet_getnumber(argv, 0);
  float start = janet_getnumber(argv, 1);
  float end = janet_getnumber(argv, 2);
  float result = (value - start) / (end - start);

  return janet_wrap_number(result);
}

static Janet cfun_Remap(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 5);
  float value = janet_getnumber(argv, 0);
  float inputStart = janet_getnumber(argv, 1);
  float inputEnd = janet_getnumber(argv, 2);
  float outputStart = janet_getnumber(argv, 3);
  float outputEnd = janet_getnumber(argv, 4);
  float result = (value - inputStart) / (inputEnd - inputStart) *
                     (outputEnd - outputStart) +
                 outputStart;

  return janet_wrap_number(result);
}

static Janet cfun_Wrap(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  float value = janet_getnumber(argv, 0);
  float min = janet_getnumber(argv, 1);
  float max = janet_getnumber(argv, 2);
  float result = value - (max - min) * floorf((value - min) / (max - min));

  return janet_wrap_number(result);
}

static Janet cfun_FloatEquals(int32_t argc, Janet *argv) {
#if !defined(EPSILON)
#define EPSILON 0.000001f
#endif
  janet_fixarity(argc, 2);
  float x = janet_getnumber(argv, 0);
  float y = janet_getnumber(argv, 1);

  int result =
      (fabsf(x - y)) <= (EPSILON * fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y))));

  return janet_wrap_boolean(result);
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
  Vector2 result = {0.0f, 0.0f};

  return jaylib_wrap_vec2(result);
}

static Janet cfun_Vector2One(int32_t argc, Janet *argv) {
  (void)argv;
  janet_fixarity(argc, 0);
  Vector2 result = {1.0f, 1.0f};

  return jaylib_wrap_vec2(result);
}

static Janet cfun_Vector2Add(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v1 = jaylib_getvec2(argv, 0);
  Vector2 v2 = jaylib_getvec2(argv, 1);
  Vector2 result = {v1.x + v2.x, v1.y + v2.y};

  return jaylib_wrap_vec2(result);
}

static Janet cfun_Vector2AddValue(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v = jaylib_getvec2(argv, 0);
  float add = (float)janet_getnumber(argv, 1);
  Vector2 result = {v.x + add, v.y + add};

  return jaylib_wrap_vec2(result);
}

static Janet cfun_Vector2Subtract(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v1 = jaylib_getvec2(argv, 0);
  Vector2 v2 = jaylib_getvec2(argv, 1);
  Vector2 result = {v1.x - v2.x, v1.y - v2.y};

  return jaylib_wrap_vec2(result);
}

static Janet cfun_Vector2SubtractValue(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v = jaylib_getvec2(argv, 0);
  float sub = janet_getnumber(argv, 1);
  Vector2 result = {v.x - sub, v.y - sub};

  return jaylib_wrap_vec2(result);
}
static Janet cfun_Vector2Length(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Vector2 v = jaylib_getvec2(argv, 0);
  float result = sqrtf((v.x * v.x) + (v.y * v.y));

  return janet_wrap_number(result);
}

static Janet cfun_Vector2LengthSqr(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Vector2 v = jaylib_getvec2(argv, 0);
  float result = (v.x * v.x) + (v.y * v.y);

  return janet_wrap_number(result);
}

static Janet cfun_Vector2DotProduct(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v1 = jaylib_getvec2(argv, 0);
  Vector2 v2 = jaylib_getvec2(argv, 1);
  float result = (v1.x * v2.x + v1.y * v2.y);

  return janet_wrap_number(result);
}

static Janet cfun_Vector2Distance(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v1 = jaylib_getvec2(argv, 0);
  Vector2 v2 = jaylib_getvec2(argv, 1);
  float result =
      sqrtf((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));

  return janet_wrap_number(result);
}

static Janet cfun_Vector2DistanceSqr(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v1 = jaylib_getvec2(argv, 0);
  Vector2 v2 = jaylib_getvec2(argv, 1);
  float result = (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y);

  return janet_wrap_number(result);
}

// NOTE: Angle is calculated from origin point (0, 0)
static Janet cfun_Vector2Angle(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v1 = jaylib_getvec2(argv, 0);
  Vector2 v2 = jaylib_getvec2(argv, 1);
  float dot = v1.x * v2.x + v1.y * v2.y;
  float det = v1.x * v2.y - v1.y * v2.x;
  float result = atan2f(det, dot);

  return janet_wrap_number(result);
}

// NOTE: Parameters need to be normalized
// Current implementation should be aligned with glm::angle
static Janet cfun_Vector2LineAngle(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 start = jaylib_getvec2(argv, 0);
  Vector2 end = jaylib_getvec2(argv, 1);
  // Angles move clockwise
  float result = -atan2f(end.y - start.y, end.x - start.x);

  return janet_wrap_number(result);
}

static Janet cfun_Vector2Scale(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v = jaylib_getvec2(argv, 0);
  float scalar = janet_getnumber(argv, 1);
  Vector2 result = {v.x * scalar, v.y * scalar};

  return jaylib_wrap_vec2(result);
}

static Janet cfun_Vector2Multiply(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v1 = jaylib_getvec2(argv, 0);
  Vector2 v2 = jaylib_getvec2(argv, 1);
  Vector2 result = {v1.x * v2.x, v1.y * v2.y};

  return jaylib_wrap_vec2(result);
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
  Vector2 result = {v1.x / v2.x, v1.y / v2.y};

  return jaylib_wrap_vec2(result);
}

static Janet cfun_Vector2Normalize(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Vector2 result = {0};
  Vector2 v = jaylib_getvec2(argv, 0);
  float length = sqrtf((v.x * v.x) + (v.y * v.y));
  if (length > 0) {
    float ilength = 1.0f / length;
    result.x = v.x * ilength;
    result.y = v.y * ilength;
  }

  return jaylib_wrap_vec2(result);
}

static Janet cfun_Vector2Transform(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v = jaylib_getvec2(argv, 0);
  Matrix mat = jaylib_getmatrix(argv, 1);

  Vector2 result = {0};
  float x = v.x;
  float y = v.y;
  float z = 0;

  result.x = mat.m0 * x + mat.m4 * y + mat.m8 * z + mat.m12;
  result.y = mat.m1 * x + mat.m5 * y + mat.m9 * z + mat.m13;

  return jaylib_wrap_vec2(result);
}

static Janet cfun_Vector2Lerp(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Vector2 v1 = jaylib_getvec2(argv, 0);
  Vector2 v2 = jaylib_getvec2(argv, 1);
  float amount = janet_getnumber(argv, 2);

  Vector2 result = {0};
  result.x = v1.x + amount * (v2.x - v1.x);
  result.y = v1.y + amount * (v2.y - v1.y);
  return jaylib_wrap_vec2(result);
}

static Janet cfun_Vector2Reflect(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v = jaylib_getvec2(argv, 0);
  Vector2 normal = jaylib_getvec2(argv, 1);

  Vector2 result = {0};
  float dotProduct = (v.x * normal.x + v.y * normal.y);
  result.x = v.x - (2.0f * normal.x) * dotProduct;
  result.y = v.y - (2.0f * normal.y) * dotProduct;

  return jaylib_wrap_vec2(result);
}

static Janet cfun_Vector2Rotate(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector2 v = jaylib_getvec2(argv, 0);
  float angle = janet_getnumber(argv, 1);

  float cosres = cosf(angle);
  float sinres = sinf(angle);

  Vector2 result = {0};

  result.x = v.x * cosres - v.y * sinres;
  result.y = v.x * sinres + v.y * cosres;

  return jaylib_wrap_vec2(result);
}

static Janet cfun_Vector2MoveTowards(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Vector2 v = jaylib_getvec2(argv, 0);
  Vector2 target = jaylib_getvec2(argv, 1);
  float maxDistance = janet_getnumber(argv, 2);

  Vector2 result = {0};

  float dx = target.x - v.x;
  float dy = target.y - v.y;
  float value = (dx * dx) + (dy * dy);

  if ((value == 0) ||
      ((maxDistance >= 0) && (value <= maxDistance * maxDistance)))
    return jaylib_wrap_vec2(target);

  float dist = sqrtf(value);

  result.x = v.x + dx / dist * maxDistance;
  result.y = v.y + dy / dist * maxDistance;

  return jaylib_wrap_vec2(result);
}

static Janet cfun_Vector2Invert(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Vector2 v = jaylib_getvec2(argv, 0);

  Vector2 result = {1.0f / v.x, 1.0f / v.y};

  return jaylib_wrap_vec2(result);
}

static Janet cfun_Vector2Clamp(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Vector2 v = jaylib_getvec2(argv, 0);
  Vector2 min = jaylib_getvec2(argv, 1);
  Vector2 max = jaylib_getvec2(argv, 2);

  Vector2 result = {0};

  result.x = fminf(max.x, fmaxf(min.x, v.x));
  result.y = fminf(max.y, fmaxf(min.y, v.y));

  return jaylib_wrap_vec2(result);
}
static Janet cfun_Vector2ClampValue(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Vector2 v = jaylib_getvec2(argv, 0);
  float min = janet_getnumber(argv, 1);
  float max = janet_getnumber(argv, 2);

  Vector2 result = v;

  float length = (v.x * v.x) + (v.y * v.y);
  if (length > 0.0f) {
    length = sqrtf(length);

    if (length < min) {
      float scalar = min / length;
      result.x = v.x * scalar;
      result.y = v.y * scalar;
    } else if (length > max) {
      float scalar = max / length;
      result.x = v.x * scalar;
      result.y = v.y * scalar;
    }
  }

  return jaylib_wrap_vec2(result);
}
static Janet cfun_Vector2Equals(int32_t argc, Janet *argv) {
#if !defined(EPSILON)
#define EPSILON 0.000001f
#endif
  janet_fixarity(argc, 2);
  Vector2 p = jaylib_getvec2(argv, 0);
  Vector2 q = jaylib_getvec2(argv, 1);

  int result = ((fabsf(p.x - q.x)) <=
                (EPSILON * fmaxf(1.0f, fmaxf(fabsf(p.x), fabsf(q.x))))) &&
               ((fabsf(p.y - q.y)) <=
                (EPSILON * fmaxf(1.0f, fmaxf(fabsf(p.y), fabsf(q.y)))));

  return janet_wrap_boolean(result);
}

//----------------------------------------------------------------------------------
// Module Functions Definition - Vector3 math
//----------------------------------------------------------------------------------

static Janet cfun_Vector3Zero(int32_t argc, Janet *argv) {
  (void)argv;
  janet_fixarity(argc, 0);
  Vector3 result = {0.0f, 0.0f, 0.0f};

  return jaylib_wrap_vec3(result);
}

static Janet cfun_Vector3One(int32_t argc, Janet *argv) {
  (void)argv;
  janet_fixarity(argc, 0);
  Vector3 result = {1.0f, 1.0f, 1.0f};

  return jaylib_wrap_vec3(result);
}

static Janet cfun_Vector3Add(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);
  Vector3 result = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};

  return jaylib_wrap_vec3(result);
}

static Janet cfun_Vector3AddValue(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v = jaylib_getvec3(argv, 0);
  float add = janet_getnumber(argv, 1);
  Vector3 result = {v.x + add, v.y + add, v.z + add};

  return jaylib_wrap_vec3(result);
}

static Janet cfun_Vector3Subtract(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);
  Vector3 result = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};

  return jaylib_wrap_vec3(result);
}

static Janet cfun_Vector3SubtractValue(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v = jaylib_getvec3(argv, 0);
  float sub = janet_getnumber(argv, 1);
  Vector3 result = {v.x - sub, v.y - sub, v.z - sub};

  return jaylib_wrap_vec3(result);
}

static Janet cfun_Vector3Scale(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v = jaylib_getvec3(argv, 0);
  float scalar = janet_getnumber(argv, 1);
  Vector3 result = {v.x * scalar, v.y * scalar, v.z * scalar};

  return jaylib_wrap_vec3(result);
}

static Janet cfun_Vector3Multiply(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);
  Vector3 result = {v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};

  return jaylib_wrap_vec3(result);
}

static Janet cfun_Vector3CrossProduct(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);
  Vector3 result = {v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
                    v1.x * v2.y - v1.y * v2.x};

  return jaylib_wrap_vec3(result);
}

static Janet cfun_Vector3Perpendicular(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Vector3 v = jaylib_getvec3(argv, 0);
  Vector3 result = {0};

  float min = (float)fabs(v.x);
  Vector3 cardinalAxis = {1.0f, 0.0f, 0.0f};

  if (fabsf(v.y) < min) {
    min = (float)fabs(v.y);
    Vector3 tmp = {0.0f, 1.0f, 0.0f};
    cardinalAxis = tmp;
  }

  if (fabsf(v.z) < min) {
    Vector3 tmp = {0.0f, 0.0f, 1.0f};
    cardinalAxis = tmp;
  }

  // Cross product between vectors
  result.x = v.y * cardinalAxis.z - v.z * cardinalAxis.y;
  result.y = v.z * cardinalAxis.x - v.x * cardinalAxis.z;
  result.z = v.x * cardinalAxis.y - v.y * cardinalAxis.x;

  return jaylib_wrap_vec3(result);
}

static Janet cfun_Vector3Length(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Vector3 v = jaylib_getvec3(argv, 0);
  float result = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);

  return janet_wrap_number(result);
}

static Janet cfun_Vector3LengthSqr(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Vector3 v = jaylib_getvec3(argv, 0);
  float result = v.x * v.x + v.y * v.y + v.z * v.z;

  return janet_wrap_number(result);
}

static Janet cfun_Vector3DotProduct(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);
  float result = (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);

  return janet_wrap_number(result);
}

static Janet cfun_Vector3Distance(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);
  float dx = v2.x - v1.x;
  float dy = v2.y - v1.y;
  float dz = v2.z - v1.z;
  float result = sqrtf(dx * dx + dy * dy + dz * dz);

  return janet_wrap_number(result);
}

static Janet cfun_Vector3DistanceSqr(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);
  float dx = v2.x - v1.x;
  float dy = v2.y - v1.y;
  float dz = v2.z - v1.z;
  float result = dx * dx + dy * dy + dz * dz;

  return janet_wrap_number(result);
}

static Janet cfun_Vector3Angle(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);
  Vector3 cross = {v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
                   v1.x * v2.y - v1.y * v2.x};
  float len = sqrtf(cross.x * cross.x + cross.y * cross.y + cross.z * cross.z);
  float dot = (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
  float result = atan2f(len, dot);

  return janet_wrap_number(result);
}

static Janet cfun_Vector3Negate(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Vector3 v = jaylib_getvec3(argv, 0);
  Vector3 result = {-v.x, -v.y, -v.z};

  return jaylib_wrap_vec3(result);
}

static Janet cfun_Vector3Divide(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);
  Vector3 result = {v1.x / v2.x, v1.y / v2.y, v1.z / v2.z};

  return jaylib_wrap_vec3(result);
}

static Janet cfun_Vector3Normalize(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Vector3 v = jaylib_getvec3(argv, 0);

  Vector3 result = v;
  float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
  if (length != 0.0f) {
    float ilength = 1.0f / length;

    result.x *= ilength;
    result.y *= ilength;
    result.z *= ilength;
  }

  return jaylib_wrap_vec3(result);
}

static Janet cfun_Vector3Project(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);
  Vector3 result = {0};

  float v1dv2 = (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
  float v2dv2 = (v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);

  float mag = v1dv2 / v2dv2;

  result.x = v2.x * mag;
  result.y = v2.y * mag;
  result.z = v2.z * mag;

  return jaylib_wrap_vec3(result);
}

static Janet cfun_Vector3Reject(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);
  Vector3 result = {0};

  float v1dv2 = (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
  float v2dv2 = (v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);

  float mag = v1dv2 / v2dv2;

  result.x = v1.x - (v2.x * mag);
  result.y = v1.y - (v2.y * mag);
  result.z = v1.z - (v2.z * mag);

  return jaylib_wrap_vec3(result);
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

  Vector3 result = {0};

  float x = v.x;
  float y = v.y;
  float z = v.z;

  result.x = mat.m0 * x + mat.m4 * y + mat.m8 * z + mat.m12;
  result.y = mat.m1 * x + mat.m5 * y + mat.m9 * z + mat.m13;
  result.z = mat.m2 * x + mat.m6 * y + mat.m10 * z + mat.m14;

  return jaylib_wrap_vec3(result);
}

static Janet cfun_Vector3RotateByQuaternion(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v = jaylib_getvec3(argv, 0);
  Quaternion q = jaylib_getvec4(argv, 1);

  Vector3 result = {0};

  result.x = v.x * (q.x * q.x + q.w * q.w - q.y * q.y - q.z * q.z) +
             v.y * (2 * q.x * q.y - 2 * q.w * q.z) +
             v.z * (2 * q.x * q.z + 2 * q.w * q.y);
  result.y = v.x * (2 * q.w * q.z + 2 * q.x * q.y) +
             v.y * (q.w * q.w - q.x * q.x + q.y * q.y - q.z * q.z) +
             v.z * (-2 * q.w * q.x + 2 * q.y * q.z);
  result.z = v.x * (-2 * q.w * q.y + 2 * q.x * q.z) +
             v.y * (2 * q.w * q.x + 2 * q.y * q.z) +
             v.z * (q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z);

  return jaylib_wrap_vec3(result);
}

static Janet cfun_Vector3RotateByAxisAngle(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Vector3 v = jaylib_getvec3(argv, 0);
  Vector3 axis = jaylib_getvec3(argv, 1);
  float angle = janet_getnumber(argv, 2);

  Vector3 result = v;

  // Vector3Normalize(axis);
  float length = sqrtf(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
  if (length == 0.0f)
    length = 1.0f;
  float ilength = 1.0f / length;
  axis.x *= ilength;
  axis.y *= ilength;
  axis.z *= ilength;

  angle /= 2.0f;
  float a = sinf(angle);
  float b = axis.x * a;
  float c = axis.y * a;
  float d = axis.z * a;
  a = cosf(angle);
  Vector3 w = {b, c, d};

  // Vector3CrossProduct(w, v)
  Vector3 wv = {w.y * v.z - w.z * v.y, w.z * v.x - w.x * v.z,
                w.x * v.y - w.y * v.x};

  // Vector3CrossProduct(w, wv)
  Vector3 wwv = {w.y * wv.z - w.z * wv.y, w.z * wv.x - w.x * wv.z,
                 w.x * wv.y - w.y * wv.x};

  // Vector3Scale(wv, 2*a)
  a *= 2;
  wv.x *= a;
  wv.y *= a;
  wv.z *= a;

  // Vector3Scale(wwv, 2)
  wwv.x *= 2;
  wwv.y *= 2;
  wwv.z *= 2;

  result.x += wv.x;
  result.y += wv.y;
  result.z += wv.z;

  result.x += wwv.x;
  result.y += wwv.y;
  result.z += wwv.z;

  return jaylib_wrap_vec3(result);
}

static Janet cfun_Vector3Lerp(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);
  float amount = janet_getnumber(argv, 2);

  Vector3 result = {0};

  result.x = v1.x + amount * (v2.x - v1.x);
  result.y = v1.y + amount * (v2.y - v1.y);
  result.z = v1.z + amount * (v2.z - v1.z);

  return jaylib_wrap_vec3(result);
}

static Janet cfun_Vector3Reflect(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v = jaylib_getvec3(argv, 0);
  Vector3 normal = jaylib_getvec3(argv, 1);

  Vector3 result = {0};
  float dotProduct = (v.x * normal.x + v.y * normal.y + v.z * normal.z);
  result.x = v.x - (2.0f * normal.x) * dotProduct;
  result.y = v.y - (2.0f * normal.y) * dotProduct;
  result.z = v.z - (2.0f * normal.z) * dotProduct;

  return jaylib_wrap_vec3(result);
}

static Janet cfun_Vector3Min(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);
  Vector3 result = {0};

  result.x = fminf(v1.x, v2.x);
  result.y = fminf(v1.y, v2.y);
  result.z = fminf(v1.z, v2.z);
  return jaylib_wrap_vec3(result);
}

static Janet cfun_Vector3Max(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 v1 = jaylib_getvec3(argv, 0);
  Vector3 v2 = jaylib_getvec3(argv, 1);
  Vector3 result = {0};

  result.x = fmaxf(v1.x, v2.x);
  result.y = fmaxf(v1.y, v2.y);
  result.z = fmaxf(v1.z, v2.z);

  return jaylib_wrap_vec3(result);
}

static Janet cfun_Vector3Barycenter(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 4);
  Vector3 p = jaylib_getvec3(argv, 0);
  Vector3 a = jaylib_getvec3(argv, 1);
  Vector3 b = jaylib_getvec3(argv, 2);
  Vector3 c = jaylib_getvec3(argv, 3);

  Vector3 result = {0};

  Vector3 v0 = {b.x - a.x, b.y - a.y, b.z - a.z}; // Vector3Subtract(b, a)
  Vector3 v1 = {c.x - a.x, c.y - a.y, c.z - a.z}; // Vector3Subtract(c, a)
  Vector3 v2 = {p.x - a.x, p.y - a.y, p.z - a.z}; // Vector3Subtract(p, a)
  float d00 =
      (v0.x * v0.x + v0.y * v0.y + v0.z * v0.z); // Vector3DotProduct(v0, v0)
  float d01 =
      (v0.x * v1.x + v0.y * v1.y + v0.z * v1.z); // Vector3DotProduct(v0, v1)
  float d11 =
      (v1.x * v1.x + v1.y * v1.y + v1.z * v1.z); // Vector3DotProduct(v1, v1)
  float d20 =
      (v2.x * v0.x + v2.y * v0.y + v2.z * v0.z); // Vector3DotProduct(v2, v0)
  float d21 =
      (v2.x * v1.x + v2.y * v1.y + v2.z * v1.z); // Vector3DotProduct(v2, v1)

  float denom = d00 * d11 - d01 * d01;

  result.y = (d11 * d20 - d01 * d21) / denom;
  result.z = (d00 * d21 - d01 * d20) / denom;
  result.x = 1.0f - (result.z + result.y);

  return jaylib_wrap_vec3(result);
}

static Janet cfun_Vector3Unproject(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Vector3 source = jaylib_getvec3(argv, 0);
  Matrix projection = jaylib_getmatrix(argv, 1);
  Matrix view = jaylib_getmatrix(argv, 2);
  Vector3 result = {0};

  // Calculate unprojected matrix (multiply view matrix by projection matrix)
  // and invert it
  Matrix matViewProj = {
      // MatrixMultiply(view, projection);
      view.m0 * projection.m0 + view.m1 * projection.m4 +
          view.m2 * projection.m8 + view.m3 * projection.m12,
      view.m0 * projection.m1 + view.m1 * projection.m5 +
          view.m2 * projection.m9 + view.m3 * projection.m13,
      view.m0 * projection.m2 + view.m1 * projection.m6 +
          view.m2 * projection.m10 + view.m3 * projection.m14,
      view.m0 * projection.m3 + view.m1 * projection.m7 +
          view.m2 * projection.m11 + view.m3 * projection.m15,
      view.m4 * projection.m0 + view.m5 * projection.m4 +
          view.m6 * projection.m8 + view.m7 * projection.m12,
      view.m4 * projection.m1 + view.m5 * projection.m5 +
          view.m6 * projection.m9 + view.m7 * projection.m13,
      view.m4 * projection.m2 + view.m5 * projection.m6 +
          view.m6 * projection.m10 + view.m7 * projection.m14,
      view.m4 * projection.m3 + view.m5 * projection.m7 +
          view.m6 * projection.m11 + view.m7 * projection.m15,
      view.m8 * projection.m0 + view.m9 * projection.m4 +
          view.m10 * projection.m8 + view.m11 * projection.m12,
      view.m8 * projection.m1 + view.m9 * projection.m5 +
          view.m10 * projection.m9 + view.m11 * projection.m13,
      view.m8 * projection.m2 + view.m9 * projection.m6 +
          view.m10 * projection.m10 + view.m11 * projection.m14,
      view.m8 * projection.m3 + view.m9 * projection.m7 +
          view.m10 * projection.m11 + view.m11 * projection.m15,
      view.m12 * projection.m0 + view.m13 * projection.m4 +
          view.m14 * projection.m8 + view.m15 * projection.m12,
      view.m12 * projection.m1 + view.m13 * projection.m5 +
          view.m14 * projection.m9 + view.m15 * projection.m13,
      view.m12 * projection.m2 + view.m13 * projection.m6 +
          view.m14 * projection.m10 + view.m15 * projection.m14,
      view.m12 * projection.m3 + view.m13 * projection.m7 +
          view.m14 * projection.m11 + view.m15 * projection.m15};

  // Calculate inverted matrix -> MatrixInvert(matViewProj);
  // Cache the matrix values (speed optimization)
  float a00 = matViewProj.m0, a01 = matViewProj.m1, a02 = matViewProj.m2,
        a03 = matViewProj.m3;
  float a10 = matViewProj.m4, a11 = matViewProj.m5, a12 = matViewProj.m6,
        a13 = matViewProj.m7;
  float a20 = matViewProj.m8, a21 = matViewProj.m9, a22 = matViewProj.m10,
        a23 = matViewProj.m11;
  float a30 = matViewProj.m12, a31 = matViewProj.m13, a32 = matViewProj.m14,
        a33 = matViewProj.m15;

  float b00 = a00 * a11 - a01 * a10;
  float b01 = a00 * a12 - a02 * a10;
  float b02 = a00 * a13 - a03 * a10;
  float b03 = a01 * a12 - a02 * a11;
  float b04 = a01 * a13 - a03 * a11;
  float b05 = a02 * a13 - a03 * a12;
  float b06 = a20 * a31 - a21 * a30;
  float b07 = a20 * a32 - a22 * a30;
  float b08 = a20 * a33 - a23 * a30;
  float b09 = a21 * a32 - a22 * a31;
  float b10 = a21 * a33 - a23 * a31;
  float b11 = a22 * a33 - a23 * a32;

  // Calculate the invert determinant (inlined to avoid double-caching)
  float invDet = 1.0f / (b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 -
                         b04 * b07 + b05 * b06);

  Matrix matViewProjInv = {(a11 * b11 - a12 * b10 + a13 * b09) * invDet,
                           (-a01 * b11 + a02 * b10 - a03 * b09) * invDet,
                           (a31 * b05 - a32 * b04 + a33 * b03) * invDet,
                           (-a21 * b05 + a22 * b04 - a23 * b03) * invDet,
                           (-a10 * b11 + a12 * b08 - a13 * b07) * invDet,
                           (a00 * b11 - a02 * b08 + a03 * b07) * invDet,
                           (-a30 * b05 + a32 * b02 - a33 * b01) * invDet,
                           (a20 * b05 - a22 * b02 + a23 * b01) * invDet,
                           (a10 * b10 - a11 * b08 + a13 * b06) * invDet,
                           (-a00 * b10 + a01 * b08 - a03 * b06) * invDet,
                           (a30 * b04 - a31 * b02 + a33 * b00) * invDet,
                           (-a20 * b04 + a21 * b02 - a23 * b00) * invDet,
                           (-a10 * b09 + a11 * b07 - a12 * b06) * invDet,
                           (a00 * b09 - a01 * b07 + a02 * b06) * invDet,
                           (-a30 * b03 + a31 * b01 - a32 * b00) * invDet,
                           (a20 * b03 - a21 * b01 + a22 * b00) * invDet};

  // Create quaternion from source point
  Quaternion quat = {source.x, source.y, source.z, 1.0f};

  // Multiply quat point by unprojecte matrix
  Quaternion qtransformed = {
      // QuaternionTransform(quat, matViewProjInv)
      matViewProjInv.m0 * quat.x + matViewProjInv.m4 * quat.y +
          matViewProjInv.m8 * quat.z + matViewProjInv.m12 * quat.w,
      matViewProjInv.m1 * quat.x + matViewProjInv.m5 * quat.y +
          matViewProjInv.m9 * quat.z + matViewProjInv.m13 * quat.w,
      matViewProjInv.m2 * quat.x + matViewProjInv.m6 * quat.y +
          matViewProjInv.m10 * quat.z + matViewProjInv.m14 * quat.w,
      matViewProjInv.m3 * quat.x + matViewProjInv.m7 * quat.y +
          matViewProjInv.m11 * quat.z + matViewProjInv.m15 * quat.w};

  // Normalized world points in vectors
  result.x = qtransformed.x / qtransformed.w;
  result.y = qtransformed.y / qtransformed.w;
  result.z = qtransformed.z / qtransformed.w;

  return jaylib_wrap_vec3(result);
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

  Vector3 result = {1.0f / v.x, 1.0f / v.y, 1.0f / v.z};

  return jaylib_wrap_vec3(result);
}

static Janet cfun_Vector3Clamp(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Vector3 v = jaylib_getvec3(argv, 0);
  Vector3 min = jaylib_getvec3(argv, 1);
  Vector3 max = jaylib_getvec3(argv, 2);

  Vector3 result = {0};

  result.x = fminf(max.x, fmaxf(min.x, v.x));
  result.y = fminf(max.y, fmaxf(min.y, v.y));
  result.z = fminf(max.z, fmaxf(min.z, v.z));

  return jaylib_wrap_vec3(result);
}
static Janet cfun_Vector3ClampValue(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Vector3 v = jaylib_getvec3(argv, 0);
  float min = janet_getnumber(argv, 1);
  float max = janet_getnumber(argv, 2);

  Vector3 result = v;

  float length = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
  if (length > 0.0f) {
    length = sqrtf(length);

    if (length < min) {
      float scale = min / length;
      result.x = v.x * scale;
      result.y = v.y * scale;
      result.z = v.z * scale;
    } else if (length > max) {
      float scale = max / length;
      result.x = v.x * scale;
      result.y = v.y * scale;
      result.z = v.z * scale;
    }
  }

  return jaylib_wrap_vec3(result);
}
static Janet cfun_Vector3Equals(int32_t argc, Janet *argv) {
#if !defined(EPSILON)
#define EPSILON 0.000001f
#endif
  janet_fixarity(argc, 2);
  Vector3 p = jaylib_getvec3(argv, 0);
  Vector3 q = jaylib_getvec3(argv, 1);

  int result = ((fabsf(p.x - q.x)) <=
                (EPSILON * fmaxf(1.0f, fmaxf(fabsf(p.x), fabsf(q.x))))) &&
               ((fabsf(p.y - q.y)) <=
                (EPSILON * fmaxf(1.0f, fmaxf(fabsf(p.y), fabsf(q.y))))) &&
               ((fabsf(p.z - q.z)) <=
                (EPSILON * fmaxf(1.0f, fmaxf(fabsf(p.z), fabsf(q.z)))));

  return janet_wrap_boolean(result);
}

static Janet cfun_Vector3Refract(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Vector3 v = jaylib_getvec3(argv, 0);
  Vector3 n = jaylib_getvec3(argv, 1);
  float r = janet_getnumber(argv, 2);

  Vector3 result = {0};

  float dot = v.x * n.x + v.y * n.y + v.z * n.z;
  float d = 1.0f - r * r * (1.0f - dot * dot);

  if (d >= 0.0f) {
    d = sqrtf(d);
    v.x = r * v.x - (r * dot + d) * n.x;
    v.y = r * v.y - (r * dot + d) * n.y;
    v.z = r * v.z - (r * dot + d) * n.z;

    result = v;
  }

  return jaylib_wrap_vec3(result);
}

//----------------------------------------------------------------------------------
// Module Functions Definition - Matrix math
//----------------------------------------------------------------------------------

static Janet cfun_MatrixDeterminant(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Matrix mat = jaylib_getmatrix(argv, 0);

  float result = 0.0f;

  // Cache the matrix values (speed optimization)
  float a00 = mat.m0, a01 = mat.m1, a02 = mat.m2, a03 = mat.m3;
  float a10 = mat.m4, a11 = mat.m5, a12 = mat.m6, a13 = mat.m7;
  float a20 = mat.m8, a21 = mat.m9, a22 = mat.m10, a23 = mat.m11;
  float a30 = mat.m12, a31 = mat.m13, a32 = mat.m14, a33 = mat.m15;

  result =
      a30 * a21 * a12 * a03 - a20 * a31 * a12 * a03 - a30 * a11 * a22 * a03 +
      a10 * a31 * a22 * a03 + a20 * a11 * a32 * a03 - a10 * a21 * a32 * a03 -
      a30 * a21 * a02 * a13 + a20 * a31 * a02 * a13 + a30 * a01 * a22 * a13 -
      a00 * a31 * a22 * a13 - a20 * a01 * a32 * a13 + a00 * a21 * a32 * a13 +
      a30 * a11 * a02 * a23 - a10 * a31 * a02 * a23 - a30 * a01 * a12 * a23 +
      a00 * a31 * a12 * a23 + a10 * a01 * a32 * a23 - a00 * a11 * a32 * a23 -
      a20 * a11 * a02 * a33 + a10 * a21 * a02 * a33 + a20 * a01 * a12 * a33 -
      a00 * a21 * a12 * a33 - a10 * a01 * a22 * a33 + a00 * a11 * a22 * a33;

  return janet_wrap_number(result);
}

static Janet cfun_MatrixTrace(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Matrix mat = jaylib_getmatrix(argv, 0);

  float result = (mat.m0 + mat.m5 + mat.m10 + mat.m15);

  return janet_wrap_number(result);
}

static Janet cfun_MatrixTranspose(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Matrix mat = jaylib_getmatrix(argv, 0);

  Matrix result = {0};

  result.m0 = mat.m0;
  result.m1 = mat.m4;
  result.m2 = mat.m8;
  result.m3 = mat.m12;
  result.m4 = mat.m1;
  result.m5 = mat.m5;
  result.m6 = mat.m9;
  result.m7 = mat.m13;
  result.m8 = mat.m2;
  result.m9 = mat.m6;
  result.m10 = mat.m10;
  result.m11 = mat.m14;
  result.m12 = mat.m3;
  result.m13 = mat.m7;
  result.m14 = mat.m11;
  result.m15 = mat.m15;

  return jaylib_wrap_matrix(result);
}

static Janet cfun_MatrixInvert(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Matrix mat = jaylib_getmatrix(argv, 0);

  Matrix result = {0};

  // Cache the matrix values (speed optimization)
  float a00 = mat.m0, a01 = mat.m1, a02 = mat.m2, a03 = mat.m3;
  float a10 = mat.m4, a11 = mat.m5, a12 = mat.m6, a13 = mat.m7;
  float a20 = mat.m8, a21 = mat.m9, a22 = mat.m10, a23 = mat.m11;
  float a30 = mat.m12, a31 = mat.m13, a32 = mat.m14, a33 = mat.m15;

  float b00 = a00 * a11 - a01 * a10;
  float b01 = a00 * a12 - a02 * a10;
  float b02 = a00 * a13 - a03 * a10;
  float b03 = a01 * a12 - a02 * a11;
  float b04 = a01 * a13 - a03 * a11;
  float b05 = a02 * a13 - a03 * a12;
  float b06 = a20 * a31 - a21 * a30;
  float b07 = a20 * a32 - a22 * a30;
  float b08 = a20 * a33 - a23 * a30;
  float b09 = a21 * a32 - a22 * a31;
  float b10 = a21 * a33 - a23 * a31;
  float b11 = a22 * a33 - a23 * a32;

  // Calculate the invert determinant (inlined to avoid double-caching)
  float invDet = 1.0f / (b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 -
                         b04 * b07 + b05 * b06);

  result.m0 = (a11 * b11 - a12 * b10 + a13 * b09) * invDet;
  result.m1 = (-a01 * b11 + a02 * b10 - a03 * b09) * invDet;
  result.m2 = (a31 * b05 - a32 * b04 + a33 * b03) * invDet;
  result.m3 = (-a21 * b05 + a22 * b04 - a23 * b03) * invDet;
  result.m4 = (-a10 * b11 + a12 * b08 - a13 * b07) * invDet;
  result.m5 = (a00 * b11 - a02 * b08 + a03 * b07) * invDet;
  result.m6 = (-a30 * b05 + a32 * b02 - a33 * b01) * invDet;
  result.m7 = (a20 * b05 - a22 * b02 + a23 * b01) * invDet;
  result.m8 = (a10 * b10 - a11 * b08 + a13 * b06) * invDet;
  result.m9 = (-a00 * b10 + a01 * b08 - a03 * b06) * invDet;
  result.m10 = (a30 * b04 - a31 * b02 + a33 * b00) * invDet;
  result.m11 = (-a20 * b04 + a21 * b02 - a23 * b00) * invDet;
  result.m12 = (-a10 * b09 + a11 * b07 - a12 * b06) * invDet;
  result.m13 = (a00 * b09 - a01 * b07 + a02 * b06) * invDet;
  result.m14 = (-a30 * b03 + a31 * b01 - a32 * b00) * invDet;
  result.m15 = (a20 * b03 - a21 * b01 + a22 * b00) * invDet;

  return jaylib_wrap_matrix(result);
}

static Janet cfun_MatrixIdentity(int32_t argc, Janet *argv) {
  (void)argv;
  janet_fixarity(argc, 1);

  Matrix result = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  return jaylib_wrap_matrix(result);
}

static Janet cfun_MatrixAdd(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Matrix left = jaylib_getmatrix(argv, 0);
  Matrix right = jaylib_getmatrix(argv, 1);

  Matrix result = {0};

  result.m0 = left.m0 + right.m0;
  result.m1 = left.m1 + right.m1;
  result.m2 = left.m2 + right.m2;
  result.m3 = left.m3 + right.m3;
  result.m4 = left.m4 + right.m4;
  result.m5 = left.m5 + right.m5;
  result.m6 = left.m6 + right.m6;
  result.m7 = left.m7 + right.m7;
  result.m8 = left.m8 + right.m8;
  result.m9 = left.m9 + right.m9;
  result.m10 = left.m10 + right.m10;
  result.m11 = left.m11 + right.m11;
  result.m12 = left.m12 + right.m12;
  result.m13 = left.m13 + right.m13;
  result.m14 = left.m14 + right.m14;
  result.m15 = left.m15 + right.m15;

  return jaylib_wrap_matrix(result);
}

static Janet cfun_MatrixSubtract(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Matrix left = jaylib_getmatrix(argv, 0);
  Matrix right = jaylib_getmatrix(argv, 1);

  Matrix result = {0};

  result.m0 = left.m0 - right.m0;
  result.m1 = left.m1 - right.m1;
  result.m2 = left.m2 - right.m2;
  result.m3 = left.m3 - right.m3;
  result.m4 = left.m4 - right.m4;
  result.m5 = left.m5 - right.m5;
  result.m6 = left.m6 - right.m6;
  result.m7 = left.m7 - right.m7;
  result.m8 = left.m8 - right.m8;
  result.m9 = left.m9 - right.m9;
  result.m10 = left.m10 - right.m10;
  result.m11 = left.m11 - right.m11;
  result.m12 = left.m12 - right.m12;
  result.m13 = left.m13 - right.m13;
  result.m14 = left.m14 - right.m14;
  result.m15 = left.m15 - right.m15;

  return jaylib_wrap_matrix(result);
}

static Janet cfun_MatrixMultiply(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Matrix left = jaylib_getmatrix(argv, 0);
  Matrix right = jaylib_getmatrix(argv, 1);

  Matrix result = {0};

  result.m0 = left.m0 * right.m0 + left.m1 * right.m4 + left.m2 * right.m8 +
              left.m3 * right.m12;
  result.m1 = left.m0 * right.m1 + left.m1 * right.m5 + left.m2 * right.m9 +
              left.m3 * right.m13;
  result.m2 = left.m0 * right.m2 + left.m1 * right.m6 + left.m2 * right.m10 +
              left.m3 * right.m14;
  result.m3 = left.m0 * right.m3 + left.m1 * right.m7 + left.m2 * right.m11 +
              left.m3 * right.m15;
  result.m4 = left.m4 * right.m0 + left.m5 * right.m4 + left.m6 * right.m8 +
              left.m7 * right.m12;
  result.m5 = left.m4 * right.m1 + left.m5 * right.m5 + left.m6 * right.m9 +
              left.m7 * right.m13;
  result.m6 = left.m4 * right.m2 + left.m5 * right.m6 + left.m6 * right.m10 +
              left.m7 * right.m14;
  result.m7 = left.m4 * right.m3 + left.m5 * right.m7 + left.m6 * right.m11 +
              left.m7 * right.m15;
  result.m8 = left.m8 * right.m0 + left.m9 * right.m4 + left.m10 * right.m8 +
              left.m11 * right.m12;
  result.m9 = left.m8 * right.m1 + left.m9 * right.m5 + left.m10 * right.m9 +
              left.m11 * right.m13;
  result.m10 = left.m8 * right.m2 + left.m9 * right.m6 + left.m10 * right.m10 +
               left.m11 * right.m14;
  result.m11 = left.m8 * right.m3 + left.m9 * right.m7 + left.m10 * right.m11 +
               left.m11 * right.m15;
  result.m12 = left.m12 * right.m0 + left.m13 * right.m4 + left.m14 * right.m8 +
               left.m15 * right.m12;
  result.m13 = left.m12 * right.m1 + left.m13 * right.m5 + left.m14 * right.m9 +
               left.m15 * right.m13;
  result.m14 = left.m12 * right.m2 + left.m13 * right.m6 +
               left.m14 * right.m10 + left.m15 * right.m14;
  result.m15 = left.m12 * right.m3 + left.m13 * right.m7 +
               left.m14 * right.m11 + left.m15 * right.m15;

  return jaylib_wrap_matrix(result);
}

static Janet cfun_MatrixTranslate(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  float x = janet_getnumber(argv, 0);
  float y = janet_getnumber(argv, 1);
  float z = janet_getnumber(argv, 2);

  Matrix result = {1.0f, 0.0f, 0.0f, x, 0.0f, 1.0f, 0.0f, y,
                   0.0f, 0.0f, 1.0f, z, 0.0f, 0.0f, 0.0f, 1.0f};

  return jaylib_wrap_matrix(result);
}

static Janet cfun_MatrixRotate(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 axis = jaylib_getvec3(argv, 0);
  float angle = janet_getnumber(argv, 1);

  Matrix result = {0};

  float x = axis.x, y = axis.y, z = axis.z;

  float lengthSquared = x * x + y * y + z * z;

  if ((lengthSquared != 1.0f) && (lengthSquared != 0.0f)) {
    float ilength = 1.0f / sqrtf(lengthSquared);
    x *= ilength;
    y *= ilength;
    z *= ilength;
  }

  float sinres = sinf(angle);
  float cosres = cosf(angle);
  float t = 1.0f - cosres;

  result.m0 = x * x * t + cosres;
  result.m1 = y * x * t + z * sinres;
  result.m2 = z * x * t - y * sinres;
  result.m3 = 0.0f;

  result.m4 = x * y * t - z * sinres;
  result.m5 = y * y * t + cosres;
  result.m6 = z * y * t + x * sinres;
  result.m7 = 0.0f;

  result.m8 = x * z * t + y * sinres;
  result.m9 = y * z * t - x * sinres;
  result.m10 = z * z * t + cosres;
  result.m11 = 0.0f;

  result.m12 = 0.0f;
  result.m13 = 0.0f;
  result.m14 = 0.0f;
  result.m15 = 1.0f;

  return jaylib_wrap_matrix(result);
}
static Janet cfun_MatrixRotateX(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  float angle = janet_getnumber(argv, 0);

  Matrix result = {
      1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f}; // MatrixIdentity()

  float cosres = cosf(angle);
  float sinres = sinf(angle);

  result.m5 = cosres;
  result.m6 = sinres;
  result.m9 = -sinres;
  result.m10 = cosres;

  return jaylib_wrap_matrix(result);
}

static Janet cfun_MatrixRotateY(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  float angle = janet_getnumber(argv, 0);

  Matrix result = {
      1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f}; // MatrixIdentity()

  float cosres = cosf(angle);
  float sinres = sinf(angle);

  result.m0 = cosres;
  result.m2 = -sinres;
  result.m8 = sinres;
  result.m10 = cosres;

  return jaylib_wrap_matrix(result);
}

static Janet cfun_MatrixRotateZ(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  float angle = janet_getnumber(argv, 0);

  Matrix result = {
      1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f}; // MatrixIdentity()

  float cosres = cosf(angle);
  float sinres = sinf(angle);

  result.m0 = cosres;
  result.m1 = sinres;
  result.m4 = -sinres;
  result.m5 = cosres;

  return jaylib_wrap_matrix(result);
}

static Janet cfun_MatrixRotateXYZ(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Vector3 angle = jaylib_getvec3(argv, 0);

  Matrix result = {
      1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f}; // MatrixIdentity()

  float cosz = cosf(-angle.z);
  float sinz = sinf(-angle.z);
  float cosy = cosf(-angle.y);
  float siny = sinf(-angle.y);
  float cosx = cosf(-angle.x);
  float sinx = sinf(-angle.x);

  result.m0 = cosz * cosy;
  result.m1 = (cosz * siny * sinx) - (sinz * cosx);
  result.m2 = (cosz * siny * cosx) + (sinz * sinx);

  result.m4 = sinz * cosy;
  result.m5 = (sinz * siny * sinx) + (cosz * cosx);
  result.m6 = (sinz * siny * cosx) - (cosz * sinx);

  result.m8 = -siny;
  result.m9 = cosy * sinx;
  result.m10 = cosy * cosx;

  return jaylib_wrap_matrix(result);
}

static Janet cfun_MatrixRotateZYX(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Vector3 angle = jaylib_getvec3(argv, 0);

  Matrix result = {0};

  float cz = cosf(angle.z);
  float sz = sinf(angle.z);
  float cy = cosf(angle.y);
  float sy = sinf(angle.y);
  float cx = cosf(angle.x);
  float sx = sinf(angle.x);

  result.m0 = cz * cy;
  result.m4 = cz * sy * sx - cx * sz;
  result.m8 = sz * sx + cz * cx * sy;
  result.m12 = 0;

  result.m1 = cy * sz;
  result.m5 = cz * cx + sz * sy * sx;
  result.m9 = cx * sz * sy - cz * sx;
  result.m13 = 0;

  result.m2 = -sy;
  result.m6 = cy * sx;
  result.m10 = cy * cx;
  result.m14 = 0;

  result.m3 = 0;
  result.m7 = 0;
  result.m11 = 0;
  result.m15 = 1;

  return jaylib_wrap_matrix(result);
}

static Janet cfun_MatrixScale(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  float x = janet_getnumber(argv, 0);
  float y = janet_getnumber(argv, 1);
  float z = janet_getnumber(argv, 2);

  Matrix result = {x,    0.0f, 0.0f, 0.0f, 0.0f, y,    0.0f, 0.0f,
                   0.0f, 0.0f, z,    0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  return jaylib_wrap_matrix(result);
}

static Janet cfun_MatrixFrustum(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 6);
  double left = janet_getnumber(argv, 0);
  double right = janet_getnumber(argv, 1);
  double bottom = janet_getnumber(argv, 2);
  double top = janet_getnumber(argv, 3);
  double near = janet_getnumber(argv, 4);
  double far = janet_getnumber(argv, 5);

  Matrix result = {0};

  float rl = (float)(right - left);
  float tb = (float)(top - bottom);
  float fn = (float)(far - near);

  result.m0 = ((float)near * 2.0f) / rl;
  result.m1 = 0.0f;
  result.m2 = 0.0f;
  result.m3 = 0.0f;

  result.m4 = 0.0f;
  result.m5 = ((float)near * 2.0f) / tb;
  result.m6 = 0.0f;
  result.m7 = 0.0f;

  result.m8 = ((float)right + (float)left) / rl;
  result.m9 = ((float)top + (float)bottom) / tb;
  result.m10 = -((float)far + (float)near) / fn;
  result.m11 = -1.0f;

  result.m12 = 0.0f;
  result.m13 = 0.0f;
  result.m14 = -((float)far * (float)near * 2.0f) / fn;
  result.m15 = 0.0f;

  return jaylib_wrap_matrix(result);
}

static Janet cfun_MatrixPerspective(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 4);
  double fovY = janet_getnumber(argv, 0);
  double aspect = janet_getnumber(argv, 1);
  double nearPlane = janet_getnumber(argv, 2);
  double farPlane = janet_getnumber(argv, 3);

  Matrix result = {0};

  double top = nearPlane * tan(fovY * 0.5);
  double bottom = -top;
  double right = top * aspect;
  double left = -right;

  // MatrixFrustum(-right, right, -top, top, near, far);
  float rl = (float)(right - left);
  float tb = (float)(top - bottom);
  float fn = (float)(farPlane - nearPlane);

  result.m0 = ((float)nearPlane * 2.0f) / rl;
  result.m5 = ((float)nearPlane * 2.0f) / tb;
  result.m8 = ((float)right + (float)left) / rl;
  result.m9 = ((float)top + (float)bottom) / tb;
  result.m10 = -((float)farPlane + (float)nearPlane) / fn;
  result.m11 = -1.0f;
  result.m14 = -((float)farPlane * (float)nearPlane * 2.0f) / fn;

  return jaylib_wrap_matrix(result);
}

static Janet cfun_MatrixOrtho(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 6);
  double left = janet_getnumber(argv, 0);
  double right = janet_getnumber(argv, 1);
  double bottom = janet_getnumber(argv, 2);
  double top = janet_getnumber(argv, 3);
  double nearPlane = janet_getnumber(argv, 4);
  double farPlane = janet_getnumber(argv, 5);

  Matrix result = {0};

  float rl = (float)(right - left);
  float tb = (float)(top - bottom);
  float fn = (float)(farPlane - nearPlane);

  result.m0 = 2.0f / rl;
  result.m1 = 0.0f;
  result.m2 = 0.0f;
  result.m3 = 0.0f;
  result.m4 = 0.0f;
  result.m5 = 2.0f / tb;
  result.m6 = 0.0f;
  result.m7 = 0.0f;
  result.m8 = 0.0f;
  result.m9 = 0.0f;
  result.m10 = -2.0f / fn;
  result.m11 = 0.0f;
  result.m12 = -((float)left + (float)right) / rl;
  result.m13 = -((float)top + (float)bottom) / tb;
  result.m14 = -((float)farPlane + (float)nearPlane) / fn;
  result.m15 = 1.0f;

  return jaylib_wrap_matrix(result);
}

static Janet cfun_MatrixLookAt(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Vector3 eye = jaylib_getvec3(argv, 0);
  Vector3 target = jaylib_getvec3(argv, 1);
  Vector3 up = jaylib_getvec3(argv, 2);

  Matrix result = {0};

  float length = 0.0f;
  float ilength = 0.0f;

  // Vector3Subtract(eye, target)
  Vector3 vz = {eye.x - target.x, eye.y - target.y, eye.z - target.z};

  // Vector3Normalize(vz)
  Vector3 v = vz;
  length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
  if (length == 0.0f)
    length = 1.0f;
  ilength = 1.0f / length;
  vz.x *= ilength;
  vz.y *= ilength;
  vz.z *= ilength;

  // Vector3CrossProduct(up, vz)
  Vector3 vx = {up.y * vz.z - up.z * vz.y, up.z * vz.x - up.x * vz.z,
                up.x * vz.y - up.y * vz.x};

  // Vector3Normalize(x)
  v = vx;
  length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
  if (length == 0.0f)
    length = 1.0f;
  ilength = 1.0f / length;
  vx.x *= ilength;
  vx.y *= ilength;
  vx.z *= ilength;

  // Vector3CrossProduct(vz, vx)
  Vector3 vy = {vz.y * vx.z - vz.z * vx.y, vz.z * vx.x - vz.x * vx.z,
                vz.x * vx.y - vz.y * vx.x};

  result.m0 = vx.x;
  result.m1 = vy.x;
  result.m2 = vz.x;
  result.m3 = 0.0f;
  result.m4 = vx.y;
  result.m5 = vy.y;
  result.m6 = vz.y;
  result.m7 = 0.0f;
  result.m8 = vx.z;
  result.m9 = vy.z;
  result.m10 = vz.z;
  result.m11 = 0.0f;
  // Vector3DotProduct(vx, eye)
  result.m12 = -(vx.x * eye.x + vx.y * eye.y + vx.z * eye.z);
  // Vector3DotProduct(vy, eye)
  result.m13 = -(vy.x * eye.x + vy.y * eye.y + vy.z * eye.z);
  // Vector3DotProduct(vz, eye)
  result.m14 = -(vz.x * eye.x + vz.y * eye.y + vz.z * eye.z);
  result.m15 = 1.0f;

  return jaylib_wrap_matrix(result);
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

  Quaternion result = {q1.x + q2.x, q1.y + q2.y, q1.z + q2.z, q1.w + q2.w};

  return jaylib_wrap_vec4(result);
}

static Janet cfun_QuaternionAddValue(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Quaternion q = jaylib_getvec4(argv, 0);
  float add = janet_getnumber(argv, 1);

  Quaternion result = {q.x + add, q.y + add, q.z + add, q.w + add};

  return jaylib_wrap_vec4(result);
}

static Janet cfun_QuaternionSubtract(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Quaternion q1 = jaylib_getvec4(argv, 0);
  Quaternion q2 = jaylib_getvec4(argv, 1);

  Quaternion result = {q1.x - q2.x, q1.y - q2.y, q1.z - q2.z, q1.w - q2.w};

  return jaylib_wrap_vec4(result);
}

static Janet cfun_QuaternionSubtractValue(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Quaternion q = jaylib_getvec4(argv, 0);
  float sub = janet_getnumber(argv, 1);

  Quaternion result = {q.x - sub, q.y - sub, q.z - sub, q.w - sub};

  return jaylib_wrap_vec4(result);
}

static Janet cfun_QuaternionIdentity(int32_t argc, Janet *argv) {
  (void)argv;
  janet_fixarity(argc, 0);

  Quaternion result = {0.0f, 0.0f, 0.0f, 1.0f};

  return jaylib_wrap_vec4(result);
}

static Janet cfun_QuaternionLength(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Quaternion q = jaylib_getvec4(argv, 0);

  float result = sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);

  return janet_wrap_number(result);
}

static Janet cfun_QuaternionNormalize(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Quaternion q = jaylib_getvec4(argv, 0);

  Quaternion result = {0};

  float length = sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
  if (length == 0.0f)
    length = 1.0f;
  float ilength = 1.0f / length;

  result.x = q.x * ilength;
  result.y = q.y * ilength;
  result.z = q.z * ilength;
  result.w = q.w * ilength;

  return jaylib_wrap_vec4(result);
}

static Janet cfun_QuaternionInvert(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Quaternion q = jaylib_getvec4(argv, 0);

  Quaternion result = q;

  float lengthSq = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;

  if (lengthSq != 0.0f) {
    float invLength = 1.0f / lengthSq;

    result.x *= -invLength;
    result.y *= -invLength;
    result.z *= -invLength;
    result.w *= invLength;
  }

  return jaylib_wrap_vec4(result);
}

static Janet cfun_QuaternionMultiply(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Quaternion q1 = jaylib_getvec4(argv, 0);
  Quaternion q2 = jaylib_getvec4(argv, 1);

  Quaternion result = {0};

  float qax = q1.x, qay = q1.y, qaz = q1.z, qaw = q1.w;
  float qbx = q2.x, qby = q2.y, qbz = q2.z, qbw = q2.w;

  result.x = qax * qbw + qaw * qbx + qay * qbz - qaz * qby;
  result.y = qay * qbw + qaw * qby + qaz * qbx - qax * qbz;
  result.z = qaz * qbw + qaw * qbz + qax * qby - qay * qbx;
  result.w = qaw * qbw - qax * qbx - qay * qby - qaz * qbz;

  return jaylib_wrap_vec4(result);
}

static Janet cfun_QuaternionScale(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Quaternion q = jaylib_getvec4(argv, 0);
  float scalar = janet_getnumber(argv, 1);

  Quaternion result = {0};

  result.x = q.x * scalar;
  result.y = q.y * scalar;
  result.z = q.z * scalar;
  result.w = q.w * scalar;

  return jaylib_wrap_vec4(result);
}

static Janet cfun_QuaternionDivide(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Quaternion q1 = jaylib_getvec4(argv, 0);
  Quaternion q2 = jaylib_getvec4(argv, 1);

  Quaternion result = {q1.x / q2.x, q1.y / q2.y, q1.z / q2.z, q1.w / q2.w};

  return jaylib_wrap_vec4(result);
}

static Janet cfun_QuaternionLerp(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Quaternion q1 = jaylib_getvec4(argv, 0);
  Quaternion q2 = jaylib_getvec4(argv, 1);
  float amount = janet_getnumber(argv, 2);

  Quaternion result = {0};

  result.x = q1.x + amount * (q2.x - q1.x);
  result.y = q1.y + amount * (q2.y - q1.y);
  result.z = q1.z + amount * (q2.z - q1.z);
  result.w = q1.w + amount * (q2.w - q1.w);

  return jaylib_wrap_vec4(result);
}

static Janet cfun_QuaternionNlerp(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Quaternion q1 = jaylib_getvec4(argv, 0);
  Quaternion q2 = jaylib_getvec4(argv, 1);
  float amount = janet_getnumber(argv, 2);

  Quaternion result = {0};

  // QuaternionLerp(q1, q2, amount)
  result.x = q1.x + amount * (q2.x - q1.x);
  result.y = q1.y + amount * (q2.y - q1.y);
  result.z = q1.z + amount * (q2.z - q1.z);
  result.w = q1.w + amount * (q2.w - q1.w);

  // QuaternionNormalize(q);
  Quaternion q = result;
  float length = sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
  if (length == 0.0f)
    length = 1.0f;
  float ilength = 1.0f / length;

  result.x = q.x * ilength;
  result.y = q.y * ilength;
  result.z = q.z * ilength;
  result.w = q.w * ilength;

  return jaylib_wrap_vec4(result);
}

// NOTE: Just here to help cdun_QuaternionSlerp below
static Quaternion QuaternionNlerp(Quaternion q1, Quaternion q2, float amount) {
  Quaternion result = {0};

  // QuaternionLerp(q1, q2, amount)
  result.x = q1.x + amount * (q2.x - q1.x);
  result.y = q1.y + amount * (q2.y - q1.y);
  result.z = q1.z + amount * (q2.z - q1.z);
  result.w = q1.w + amount * (q2.w - q1.w);

  // QuaternionNormalize(q);
  Quaternion q = result;
  float length = sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
  if (length == 0.0f)
    length = 1.0f;
  float ilength = 1.0f / length;

  result.x = q.x * ilength;
  result.y = q.y * ilength;
  result.z = q.z * ilength;
  result.w = q.w * ilength;

  return result;
}

static Janet cfun_QuaternionSlerp(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 3);
  Quaternion q1 = jaylib_getvec4(argv, 0);
  Quaternion q2 = jaylib_getvec4(argv, 1);
  float amount = janet_getnumber(argv, 2);

  Quaternion result = {0};

#if !defined(EPSILON)
#define EPSILON 0.000001f
#endif

  float cosHalfTheta = q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;

  if (cosHalfTheta < 0) {
    q2.x = -q2.x;
    q2.y = -q2.y;
    q2.z = -q2.z;
    q2.w = -q2.w;
    cosHalfTheta = -cosHalfTheta;
  }

  if (fabsf(cosHalfTheta) >= 1.0f)
    result = q1;
  else if (cosHalfTheta > 0.95f)
    result = QuaternionNlerp(q1, q2, amount);
  else {
    float halfTheta = acosf(cosHalfTheta);
    float sinHalfTheta = sqrtf(1.0f - cosHalfTheta * cosHalfTheta);

    if (fabsf(sinHalfTheta) < EPSILON) {
      result.x = (q1.x * 0.5f + q2.x * 0.5f);
      result.y = (q1.y * 0.5f + q2.y * 0.5f);
      result.z = (q1.z * 0.5f + q2.z * 0.5f);
      result.w = (q1.w * 0.5f + q2.w * 0.5f);
    } else {
      float ratioA = sinf((1 - amount) * halfTheta) / sinHalfTheta;
      float ratioB = sinf(amount * halfTheta) / sinHalfTheta;

      result.x = (q1.x * ratioA + q2.x * ratioB);
      result.y = (q1.y * ratioA + q2.y * ratioB);
      result.z = (q1.z * ratioA + q2.z * ratioB);
      result.w = (q1.w * ratioA + q2.w * ratioB);
    }
  }

  return jaylib_wrap_vec4(result);
}

static Janet cfun_QuaternionFromVector3ToVector3(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 from = jaylib_getvec3(argv, 0);
  Vector3 to = jaylib_getvec3(argv, 1);

  Quaternion result = {0};

  // Vector3DotProduct(from, to)
  float cos2Theta = (from.x * to.x + from.y * to.y + from.z * to.z);
  // Vector3CrossProduct(from, to)
  Vector3 cross = {from.y * to.z - from.z * to.y, from.z * to.x - from.x * to.z,
                   from.x * to.y - from.y * to.x};

  result.x = cross.x;
  result.y = cross.y;
  result.z = cross.z;
  result.w = 1.0f + cos2Theta;

  // QuaternionNormalize(q);
  // NOTE: Normalize to essentially nlerp the original and identity to 0.5
  Quaternion q = result;
  float length = sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
  if (length == 0.0f)
    length = 1.0f;
  float ilength = 1.0f / length;

  result.x = q.x * ilength;
  result.y = q.y * ilength;
  result.z = q.z * ilength;
  result.w = q.w * ilength;

  return jaylib_wrap_vec4(result);
}

static Janet cfun_QuaternionFromMatrix(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Matrix mat = jaylib_getmatrix(argv, 0);

  Quaternion result = {0};

  float fourWSquaredMinus1 = mat.m0 + mat.m5 + mat.m10;
  float fourXSquaredMinus1 = mat.m0 - mat.m5 - mat.m10;
  float fourYSquaredMinus1 = mat.m5 - mat.m0 - mat.m10;
  float fourZSquaredMinus1 = mat.m10 - mat.m0 - mat.m5;

  int biggestIndex = 0;
  float fourBiggestSquaredMinus1 = fourWSquaredMinus1;
  if (fourXSquaredMinus1 > fourBiggestSquaredMinus1) {
    fourBiggestSquaredMinus1 = fourXSquaredMinus1;
    biggestIndex = 1;
  }

  if (fourYSquaredMinus1 > fourBiggestSquaredMinus1) {
    fourBiggestSquaredMinus1 = fourYSquaredMinus1;
    biggestIndex = 2;
  }

  if (fourZSquaredMinus1 > fourBiggestSquaredMinus1) {
    fourBiggestSquaredMinus1 = fourZSquaredMinus1;
    biggestIndex = 3;
  }

  float biggestVal = sqrtf(fourBiggestSquaredMinus1 + 1.0f) * 0.5f;
  float mult = 0.25f / biggestVal;

  switch (biggestIndex) {
  case 0:
    result.w = biggestVal;
    result.x = (mat.m6 - mat.m9) * mult;
    result.y = (mat.m8 - mat.m2) * mult;
    result.z = (mat.m1 - mat.m4) * mult;
    break;
  case 1:
    result.x = biggestVal;
    result.w = (mat.m6 - mat.m9) * mult;
    result.y = (mat.m1 + mat.m4) * mult;
    result.z = (mat.m8 + mat.m2) * mult;
    break;
  case 2:
    result.y = biggestVal;
    result.w = (mat.m8 - mat.m2) * mult;
    result.x = (mat.m1 + mat.m4) * mult;
    result.z = (mat.m6 + mat.m9) * mult;
    break;
  case 3:
    result.z = biggestVal;
    result.w = (mat.m1 - mat.m4) * mult;
    result.x = (mat.m8 + mat.m2) * mult;
    result.y = (mat.m6 + mat.m9) * mult;
    break;
  }

  return jaylib_wrap_vec4(result);
}

static Janet cfun_QuaternionToMatrix(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Quaternion q = jaylib_getvec4(argv, 0);

  Matrix result = {
      1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f}; // MatrixIdentity()

  float a2 = q.x * q.x;
  float b2 = q.y * q.y;
  float c2 = q.z * q.z;
  float ac = q.x * q.z;
  float ab = q.x * q.y;
  float bc = q.y * q.z;
  float ad = q.w * q.x;
  float bd = q.w * q.y;
  float cd = q.w * q.z;

  result.m0 = 1 - 2 * (b2 + c2);
  result.m1 = 2 * (ab + cd);
  result.m2 = 2 * (ac - bd);

  result.m4 = 2 * (ab - cd);
  result.m5 = 1 - 2 * (a2 + c2);
  result.m6 = 2 * (bc + ad);

  result.m8 = 2 * (ac + bd);
  result.m9 = 2 * (bc - ad);
  result.m10 = 1 - 2 * (a2 + b2);

  return jaylib_wrap_matrix(result);
}

static Janet cfun_QuaternionFromAxisAngle(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Vector3 axis = jaylib_getvec3(argv, 0);
  float angle = janet_getnumber(argv, 1);

  Quaternion result = {0.0f, 0.0f, 0.0f, 1.0f};

  float axisLength = sqrtf(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);

  if (axisLength != 0.0f) {
    angle *= 0.5f;

    float length = 0.0f;
    float ilength = 0.0f;

    // Vector3Normalize(axis)
    Vector3 v = axis;
    length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    if (length == 0.0f)
      length = 1.0f;
    ilength = 1.0f / length;
    axis.x *= ilength;
    axis.y *= ilength;
    axis.z *= ilength;

    float sinres = sinf(angle);
    float cosres = cosf(angle);

    result.x = axis.x * sinres;
    result.y = axis.y * sinres;
    result.z = axis.z * sinres;
    result.w = cosres;

    // QuaternionNormalize(q);
    Quaternion q = result;
    length = sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
    if (length == 0.0f)
      length = 1.0f;
    ilength = 1.0f / length;
    result.x = q.x * ilength;
    result.y = q.y * ilength;
    result.z = q.z * ilength;
    result.w = q.w * ilength;
  }

  return jaylib_wrap_vec4(result);
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

  Quaternion result = {0};

  float x0 = cosf(pitch * 0.5f);
  float x1 = sinf(pitch * 0.5f);
  float y0 = cosf(yaw * 0.5f);
  float y1 = sinf(yaw * 0.5f);
  float z0 = cosf(roll * 0.5f);
  float z1 = sinf(roll * 0.5f);

  result.x = x1 * y0 * z0 - x0 * y1 * z1;
  result.y = x0 * y1 * z0 + x1 * y0 * z1;
  result.z = x0 * y0 * z1 - x1 * y1 * z0;
  result.w = x0 * y0 * z0 + x1 * y1 * z1;

  return jaylib_wrap_vec4(result);
}

static Janet cfun_QuaternionToEuler(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Quaternion q = jaylib_getvec4(argv, 0);

  Vector3 result = {0};

  // Roll (x-axis rotation)
  float x0 = 2.0f * (q.w * q.x + q.y * q.z);
  float x1 = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
  result.x = atan2f(x0, x1);

  // Pitch (y-axis rotation)
  float y0 = 2.0f * (q.w * q.y - q.z * q.x);
  y0 = y0 > 1.0f ? 1.0f : y0;
  y0 = y0 < -1.0f ? -1.0f : y0;
  result.y = asinf(y0);

  // Yaw (z-axis rotation)
  float z0 = 2.0f * (q.w * q.z + q.x * q.y);
  float z1 = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
  result.z = atan2f(z0, z1);

  return jaylib_wrap_vec3(result);
}

static Janet cfun_QuaternionTransform(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Quaternion q = jaylib_getvec4(argv, 0);
  Matrix mat = jaylib_getmatrix(argv, 1);

  Quaternion result = {0};

  result.x = mat.m0 * q.x + mat.m4 * q.y + mat.m8 * q.z + mat.m12 * q.w;
  result.y = mat.m1 * q.x + mat.m5 * q.y + mat.m9 * q.z + mat.m13 * q.w;
  result.z = mat.m2 * q.x + mat.m6 * q.y + mat.m10 * q.z + mat.m14 * q.w;
  result.w = mat.m3 * q.x + mat.m7 * q.y + mat.m11 * q.z + mat.m15 * q.w;

  return jaylib_wrap_vec4(result);
}

static Janet cfun_QuaternionEquals(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Quaternion q = jaylib_getvec4(argv, 0);
  Quaternion p = jaylib_getvec4(argv, 1);

#if !defined(EPSILON)
#define EPSILON 0.000001f
#endif

  int result = (((fabsf(p.x - q.x)) <=
                 (EPSILON * fmaxf(1.0f, fmaxf(fabsf(p.x), fabsf(q.x))))) &&
                ((fabsf(p.y - q.y)) <=
                 (EPSILON * fmaxf(1.0f, fmaxf(fabsf(p.y), fabsf(q.y))))) &&
                ((fabsf(p.z - q.z)) <=
                 (EPSILON * fmaxf(1.0f, fmaxf(fabsf(p.z), fabsf(q.z))))) &&
                ((fabsf(p.w - q.w)) <=
                 (EPSILON * fmaxf(1.0f, fmaxf(fabsf(p.w), fabsf(q.w)))))) ||
               (((fabsf(p.x + q.x)) <=
                 (EPSILON * fmaxf(1.0f, fmaxf(fabsf(p.x), fabsf(q.x))))) &&
                ((fabsf(p.y + q.y)) <=
                 (EPSILON * fmaxf(1.0f, fmaxf(fabsf(p.y), fabsf(q.y))))) &&
                ((fabsf(p.z + q.z)) <=
                 (EPSILON * fmaxf(1.0f, fmaxf(fabsf(p.z), fabsf(q.z))))) &&
                ((fabsf(p.w + q.w)) <=
                 (EPSILON * fmaxf(1.0f, fmaxf(fabsf(p.w), fabsf(q.w))))));

  return janet_wrap_boolean(result);
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
    {"matrix-identity", cfun_MatrixInvert,
     "(matrix-invert)\n\n"
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
