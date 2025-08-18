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
  float dotProduct = (v.x * normal.x + v.y * normal.y); // Dot product
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

static const JanetReg math_cfuns[] = {
    // Utils
    {"utils/clamp", cfun_Clamp,
     "(utils/clamp x min max)\n\n"
     "Clamp x between min and max"},
    {"utils/lerp", cfun_Lerp,
     "(utils/lerp start end amount)\n\n"
     "Calculate linear interpolation between two floats"},
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
     "Check whether two given floats are almost equal"},

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
     "Get v as an array of 3 floats"},
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
};
