#ifndef BLANKH
#define BLANKH
class blank : public transform {
public:
    blank() {}
    vec3 apply(const vec3 &v) const {
        return v;
    }
};

#endif