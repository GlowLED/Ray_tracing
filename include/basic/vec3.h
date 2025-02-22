#ifndef VEC3H
#define VEC3H
#include <cmath>
class vec3 {
public:
    vec3() {}
    vec3(float x, float y, float z) {e[0] = x; e[1] = y; e[2] = z;}
    float x() const {return e[0];}
    float y() const {return e[1];}
    float z() const {return e[2];}

    vec3 operator+() const {return *this;}
    vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);}

    float operator[](int i) const {return e[i];}
    float& operator[](int i) {return e[i];}

    float length() const {
        return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    }
    float squared_length() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    vec3 operator+=(const vec3 &v2) {
        e[0] += v2[0];
        e[1] += v2[1];
        e[2] += v2[2];
        return *this;
    }
    vec3 operator-=(const vec3 &v2) {
        e[0] -= v2[0];
        e[1] -= v2[1];
        e[2] -= v2[2];
        return *this;
    }
    vec3 operator*=(const vec3 &v2) {
        e[0] *= v2[0];
        e[1] *= v2[1];
        e[2] *= v2[2];
        return *this;
    }
    vec3 operator/=(const vec3 &v2) {
        e[0] /= v2[0];
        e[1] /= v2[1];
        e[2] /= v2[2];
        return *this;
    }
    vec3 operator*=(const float t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }
    vec3 operator/=(const float t) {
        e[0] /= t;
        e[1] /= t;
        e[2] /= t;
        return *this;
    }

private:
    float e[3];
};
vec3 operator+(const vec3 &v1, const vec3 &v2) {
    return vec3(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}
vec3 operator-(const vec3 &v1, const vec3 &v2) {
    return vec3(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}
vec3 operator*(const vec3 &v1, const vec3 &v2) {
    return vec3(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}
vec3 operator*(float t, const vec3 &v) {
    return vec3(t * v[0], t * v[1], t * v[2]);
}
vec3 operator*(const vec3 &v, float t) {
    return t * v;
}
vec3 operator/(const vec3 &v1, const vec3 &v2) {
    return vec3(v1[0] / v2[0], v1[1] / v2[1], v1[2] / v2[2]);
}
vec3 operator/(vec3 v, float t) {
    return (1 / t) * v;
}
vec3 operator/(float t, vec3 v) {
    return (1 / t) * v;
}
float dot(const vec3 &v1, const vec3 &v2) {
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}
vec3 cross(const vec3 &v1, const vec3 &v2) {
    return vec3(v1[1] * v2[2] - v1[2] * v2[1],
                v1[2] * v2[0] - v1[0] * v2[2],
                v1[0] * v2[1] - v1[1] * v2[0]);
}
vec3 unit_vector(vec3 v) {
    return v / v.length();
}
#endif