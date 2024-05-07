
#include "image.h"
#include "kdtree.h"
#include "ray.h"
#include "raytracer.h"
#include "scene_types.h"
#include <stdio.h>

#include <glm/gtc/epsilon.hpp>

/// acne_eps is a small constant used to prevent acne when computing
/// intersection
//  or boucing (add this amount to the position before casting a new ray !
const float acne_eps = 1e-4;

bool intersectPlane(Ray *ray, Intersection *intersection, Object *obj)
{
    float dn = glm::dot(ray->dir, obj->geom.plane.normal);

    if (fabsf(dn) < 1e-5)
    {
        return false;
    }

    float t = -(glm::dot(ray->orig, obj->geom.plane.normal) + obj->geom.plane.dist) / dn;
    if ((t <= ray->tmax) && (t >= ray->tmin))
    {
        intersection->position = ray->orig + t * ray->dir;
        intersection->normal = obj->geom.plane.normal;
        intersection->mat = &(obj->mat);
        ray->tmax = t;
        return true;
    }
    return false;
}

bool intersectSphere(Ray *ray, Intersection *intersection, Object *obj)
{
    float t = 0.0;
    vec3 oc = ray->orig - obj->geom.sphere.center;

    auto a = 1.0f;
    auto b = 2.0f * glm::dot(ray->dir, oc);
    auto c = glm::dot(oc, oc) - powf(obj->geom.sphere.radius, 2);
    auto delta = powf(b, 2.0f) - 4.0f * a * c;

    if (delta > acne_eps)
    {
        /* 2 solution, plus petit t compris entre tmin tmax */
        auto t1 = (-b - sqrt(delta)) / (2.0f * a);
        auto t2 = (-b + sqrt(delta)) / (2.0f * a);

        // tmin -- t1 -- t2 -- tmax
        if ((t1 >= ray->tmin) && (t1 <= ray->tmax) && (t2 >= ray->tmin) && (t2 <= ray->tmax))
        {
            if (t1 < t2)
            {
                t = t1;
            }
            else
            {
                t = t2;
            }
            // tmin -- t1 -- tmax -- t2
        }
        else if ((t1 >= ray->tmin) && (t1 <= ray->tmax))
        {
            t = t1;
            // t1 -- tmin -- t2 -- tmax
        }
        else if ((t2 >= ray->tmin) && (t2 <= ray->tmax))
        {
            t = t2;
        }
        else
        {
            return false;
        }
    }
    // else if ( 0.0 <= fabsf(0.0 + acne_eps))
    else if ((delta >= 0.0 - acne_eps) && (delta <= 0.0 + acne_eps))
    {
        /* 1 solution */
        t = (-b) / (2.0f * a);
        if (!(t <= ray->tmax) && (t >= ray->tmin))
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    intersection->position = ray->orig + t * ray->dir;
    intersection->normal = glm::normalize(intersection->position - obj->geom.sphere.center);
    intersection->mat = &(obj->mat);
    ;
    ray->tmax = t;
    return true;
}

bool intersectScene(const Scene *scene, Ray *ray, Intersection *intersection)
{
    bool hasIntersection = false;
    size_t objectCount = scene->objects.size();

    for (size_t i = 0; i < objectCount; i++)
    {
        Object *const o = scene->objects[i];
        if (o->geom.type == SPHERE)
        {
            // be carefull with lazy evaluation
            hasIntersection = intersectSphere(ray, intersection, o) || hasIntersection;
        }
        else if (o->geom.type == PLANE)
        {
            // be carefull with lazy evaluation
            hasIntersection = intersectPlane(ray, intersection, o) || hasIntersection;
        }
    }
    return hasIntersection;
}

/* ---------------------------------------------------------------------------
 */
/*
 *	The following functions are coded from Cook-Torrance bsdf model
 *description and are suitable only
 *  for rough dielectrics material (RDM. Code has been validated with Mitsuba
 *renderer)
 */

// Shadowing and masking function. Linked with the NDF. Here, Smith function,
// suitable for Beckmann NDF
float RDM_chiplus(float c) { return (c > 0.f) ? 1.f : 0.f; }

/** Normal Distribution Function : Beckmann
 * NdotH : Norm . Half
 */
float RDM_Beckmann(float NdotH, float alpha)
{
    //! compute Beckmann normal distribution
    auto thanSquare = (1 - NdotH * NdotH) / (NdotH * NdotH);
    auto r_term = exp(-thanSquare / (alpha * alpha)) / (M_PIf32 * alpha * alpha * powf(NdotH, 4));
    return RDM_chiplus(NdotH) * r_term;
}

// Fresnel term computation. Implantation of the exact computation. we can use
// the Schlick approximation
// LdotH : Light . Half
float RDM_Fresnel(float LdotH, float extIOR, float intIOR)
{
    auto sin_theta_t = powf(extIOR / intIOR, 2) * (1 - powf(LdotH, 2));
    if (sin_theta_t > 1)
    {
        return 1.0f;
    }

    auto cosTheta_t = sqrtf(1 - sin_theta_t);

    float Rs = powf(extIOR * LdotH - intIOR * cosTheta_t, 2) / powf(extIOR * LdotH + intIOR * cosTheta_t, 2);
    float Rp = powf(extIOR * cosTheta_t - intIOR * LdotH, 2) / powf(extIOR * cosTheta_t + intIOR * LdotH, 2);
    return 0.5f * (Rs + Rp);
}

// DdotH : Dir . Half | l . h (bissec l et half_vec)
// HdotN : Half . Norm | . n (normale)
float RDM_G1(float DdotH, float DdotN, float alpha)
{

    //! compute G1 term of the Smith fonction
    float tan_theta_x = sqrtf(1 - powf(DdotH, 2)) / DdotH;
    float b = 1.0f / (alpha * tan_theta_x);
    auto k = DdotH / DdotN;
    float chi_plus = RDM_chiplus(k);
    if (b < 1.6f)
    {
        float b_s = powf(b, 2);
        return chi_plus * ((3.535f * b + 2.181f * b_s) / (1 + 2.276f * b + 2.577 * b_s));
    }
    else
    {
        return chi_plus;
    }
}

// LdotH : Light . Half
// LdotN : Light . Norm
// VdotH : View . Half
// VdotN : View . Norm
float RDM_Smith(float LdotH, float LdotN, float VdotH, float VdotN,
                float alpha)
{
    return RDM_G1(LdotH, LdotN, alpha) * RDM_G1(VdotH, VdotN, alpha);
}

// Specular term of the Cook-torrance bsdf
// LdotH : Light . Half
// NdotH : Norm . Half
// VdotH : View . Half
// LdotN : Light . Norm
// VdotN : View . Norm
color3 RDM_bsdf_s(float LdotH, float NdotH, float VdotH, float LdotN,
                  float VdotN, Material *m)
{

    //! specular term of the bsdf, using D = RDB_Beckmann, F = RDM_Fresnel, G = RDM_Smith
    float alpha = m->roughness;
    float D = RDM_Beckmann(NdotH, alpha);
    float F = RDM_Fresnel(LdotH, 1.0f, m->IOR);
    float G = RDM_Smith(LdotH, LdotN, VdotH, VdotN, alpha);
    return m->specularColor * (D * F * G) / (4 * LdotN * VdotN);
}
// diffuse term of the cook torrance bsdf
color3 RDM_bsdf_d(Material *m)
{

    //! diffuse component of the bsdf
    return m->diffuseColor / M_PIf32;
}

// The full evaluation of bsdf(wi, wo) * cos (thetai)
// LdotH : Light . Half
// NdotH : Norm . Half
// VdotH : View . Half
// LdotN : Light . Norm
// VdtoN : View . Norm
// compute bsdf * cos(Oi)
color3 RDM_bsdf(float LdotH, float NdotH, float VdotH, float LdotN, float VdotN,
                Material *m)
{
    //! compute bsdf diffuse and specular term
    return RDM_bsdf_d(m) + RDM_bsdf_s(LdotH, NdotH, VdotH, LdotN, VdotN, m);
}

color3 shade(vec3 n, vec3 v, vec3 l, color3 lc, Material *mat)
{
    color3 ret = color3(0.f);

    auto ldotn = glm::dot(l, n);
    if (ldotn > 0.0f)
    {
        auto h = normalize(v + l);
        ret = lc * RDM_bsdf(dot(l, h), dot(n, h), dot(v, h), dot(l, n), dot(v, n), mat) * ldotn;
    }
    return ret;
}

//! if tree is not null, use intersectKdTree to compute the intersection instead
//! of intersect scene
color3 trace_ray(Scene *scene, Ray *ray, KdTree *tree)
{
    if (ray->depth >= 4)
    {
        return color3(0.0f, 0.0f, 0.0f);
    }
    
    color3 color_direct = color3(0.0f, 0.0f, 0.0f);
    color3 color_reflect = color3(0.0f, 0.0f, 0.0f);
    Intersection intersection, shadow_intersec;
    Ray shadow_ray, reflect_ray;
    if (intersectScene(scene, ray, &intersection))
    {
        // ici, calcul de la couleur au point d'intersection
        // entre la rayon et l'objet de la scene
        // pour chaque source lumineuse
        size_t lightsCount = scene->lights.size();
        for (size_t i = 0; i < lightsCount; i++)
        {
            auto lPos = scene->lights[i]->position;
            auto pPos = intersection.position;
            auto l = glm::normalize(lPos - pPos);
            auto v = -ray->dir;
            // - creer un rayon d'ombre ayant pour point d'origine P+εL
            // et pour dir L, avec P point d'intersesc et ε = acne_eps
            rayInit(
                &shadow_ray,
                intersection.position + acne_eps * l,
                l,
                0.0f,
                glm::distance(lPos, pPos));
            if (!intersectScene(scene, &shadow_ray, &shadow_intersec))
            {
                // - on appelle shade() uniquement si le rayon d'ombre n'intersecte aucun objet dans la scene entre P et L
                color_direct += shade(intersection.normal, v, l, scene->lights[i]->color, intersection.mat);
            }
        }
    }
    else
    {
        return scene->skyColor;
    }

    if (color_direct.r >= 1.0f && color_direct.g >= 1.0f && color_direct.b >= 1.0f)
    {
        return color3(1.0f, 1.0f, 1.0f);
    }

    vec3 ray_reflect_dir = reflect(ray->dir, intersection.normal);
    rayInit(&reflect_ray, intersection.position + acne_eps * ray_reflect_dir, ray_reflect_dir, 0.0f, 100000.0f, ray->depth + 1);
    color_reflect = trace_ray(scene, &reflect_ray, tree);

    vec3 h = normalize(-ray->dir + reflect_ray.dir);
    return color_direct + RDM_Fresnel(dot(reflect_ray.dir, h), 1.f, intersection.mat->IOR) * color_reflect * (intersection.mat->specularColor);
}


void renderImage(Image *img, Scene *scene)
{
    //! This function is already operational, you might modify it for antialiasing
    //! and kdtree initializaion
    float aspect = 1.f / scene->cam.aspect;

    KdTree *tree = NULL;

    //! \todo initialize KdTree

    float delta_y = 1.f / (img->height * 0.5f);   //! one pixel size
    vec3 dy = delta_y * aspect * scene->cam.ydir; //! one pixel step
    vec3 ray_delta_y = (0.5f - img->height * 0.5f) / (img->height * 0.5f) *
                       aspect * scene->cam.ydir;

    float delta_x = 1.f / (img->width * 0.5f);
    vec3 dx = delta_x * scene->cam.xdir;
    vec3 ray_delta_x =
        (0.5f - img->width * 0.5f) / (img->width * 0.5f) * scene->cam.xdir;

    for (size_t j = 0; j < img->height; j++)
    {
        if (j != 0)
            printf("\033[A\r");
        float progress = (float)j / img->height * 100.f;
        printf("progress\t[");
        int cpt = 0;
        for (cpt = 0; cpt < progress; cpt += 5)
            printf(".");
        for (; cpt < 100; cpt += 5)
            printf(" ");
        printf("]\n");
#pragma omp parallel for
        for (size_t i = 0; i < img->width; i++)
        {
            color3 *ptr = getPixelPtr(img, i, j);
            vec3 ray_dir = scene->cam.center + ray_delta_x + ray_delta_y +
                           float(i) * dx + float(j) * dy;

            Ray rx;
            rayInit(&rx, scene->cam.position, normalize(ray_dir));
            *ptr = trace_ray(scene, &rx, tree);
        }
    }
}
