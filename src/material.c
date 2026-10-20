#include "material.h"
#include "random.h"

static float schlick_reflectance(float cosine, float eta_ratio) {
    float r0 = (1.0f - eta_ratio) / (1.0f + eta_ratio);
    r0 *= r0;
    float one_minus_cosine = 1.0f - cosine;
    return r0 + (1.0f - r0) * one_minus_cosine * one_minus_cosine *
           one_minus_cosine * one_minus_cosine * one_minus_cosine;
}

bool material_scatter(const RTMaterial *material, CRay incoming, Point3 hit_point,
                      Vec3 normal, bool front_face, CRay *scattered, Color3 *attenuation) {
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

        case MATERIAL_DIELECTRIC: {
            scattered->origin = hit_point;
            *attenuation = (Color3){1.0f, 1.0f, 1.0f};

            float eta_ratio = front_face
                ? 1.0f / material->refraction_index
                : material->refraction_index;
            Vec3 unit_direction = vec3_normalize(incoming.direction);
            float cos_theta = fminf(vec3_dot(vec3_scale(unit_direction, -1.0f), normal), 1.0f);
            float sin_theta = sqrtf(fmaxf(0.0f, 1.0f - cos_theta * cos_theta));
            bool cannot_refract = eta_ratio * sin_theta > 1.0f;

            if (cannot_refract || schlick_reflectance(cos_theta, eta_ratio) > random_double()) {
                scattered->direction = vec3_reflect(unit_direction, normal);
            } else {
                scattered->direction = vec3_refract(unit_direction, normal, eta_ratio);
            }
            return true;
        }
    }
    return false;
}
