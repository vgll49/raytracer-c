#include "hittable.h"

#include <stdlib.h>

void hittable_set_face_normal(HitRecord *record, CRay ray, Vec3 outward_normal) {
    record->front_face = vec3_dot(ray.direction, outward_normal) < 0.0f;
    record->normal = record->front_face ? outward_normal : vec3_scale(outward_normal, -1.0f);
}

bool hittable_hit(const Hittable *object, CRay ray, float t_min, float t_max, HitRecord *record) {
    switch (object->type) {
        case HITTABLE_SPHERE: {
            Vec3 outward_normal;
            if (!sphere_hit(object->shape.sphere, ray, t_min, t_max,
                            &record->t, &record->point, &outward_normal)) {
                return false;
            }
            hittable_set_face_normal(record, ray, outward_normal);
            return true;
        }
    }
    return false;
}

void hittable_list_init(HittableList *list) {
    *list = (HittableList){0};
}

bool hittable_list_add(HittableList *list, Hittable object) {
    if (list->count == list->capacity) {
        unsigned int new_capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        Hittable *new_objects = realloc(list->objects, new_capacity * sizeof(*new_objects));
        if (new_objects == NULL) return false;
        list->objects = new_objects;
        list->capacity = new_capacity;
    }
    list->objects[list->count++] = object;
    return true;
}

bool hittable_list_hit(const HittableList *list, CRay ray, float t_min, float t_max, HitRecord *record) {
    HitRecord candidate;
    bool hit_anything = false;
    float closest_so_far = t_max;

    for (unsigned int i = 0; i < list->count; ++i) {
        if (hittable_hit(&list->objects[i], ray, t_min, closest_so_far, &candidate)) {
            hit_anything = true;
            closest_so_far = candidate.t;
            *record = candidate;
        }
    }
    return hit_anything;
}

void hittable_list_destroy(HittableList *list) {
    free(list->objects);
    *list = (HittableList){0};
}
