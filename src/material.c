#include "material.h"

bool material_scatter(const RTMaterial *material, CRay incoming, Point3 hit_point,
                      Vec3 normal, CRay *scattered, Color3 *attenuation) {
    (void)incoming;

    switch (material->type) {
        case MATERIAL_DIFFUSE:
            scattered->origin = hit_point;
            scattered->direction = vec3_add(normal, vec3_random_unit_vector());
            // The two vectors can nearly cancel; keep the ray direction valid in that case.
            if (vec3_length_sq(scattered->direction) <= EPS) {
                scattered->direction = normal;
            }
            *attenuation = material->albedo;
            return true;

        case MATERIAL_METAL:
            scattered->origin = hit_point;
            Vec3 reflected = vec3_normalize(vec3_reflect(incoming.direction, normal));
            Vec3 fuzz_offset = vec3_scale(vec3_random_unit_vector(), material->fuzz);
            scattered->direction = vec3_add(reflected, fuzz_offset);
            *attenuation = material->albedo;
            return !vec3_near_zero(scattered->direction) &&
                   vec3_dot(scattered->direction, normal) > 0.0f;
    }
    return false;
}
