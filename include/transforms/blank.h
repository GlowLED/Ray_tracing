#ifndef BLANKH
#define BLANKH
class blank : public transform {
public:
    blank() {}
    virtual vec3 world_to_object(const vec3 &v) const {
        return v;
    }
    virtual vec3 object_to_world(const vec3 &v) const {
        return v;
    }
};

#endif