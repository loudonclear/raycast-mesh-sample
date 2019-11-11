#include "tracer.h"

#include <iostream>

#include <util/common.h>

Tracer::Tracer(int width, int height)
    : m_width(width), m_height(height)
{
}

void Tracer::traceScene(const Mesh& mesh, const std::vector<BasicCamera> &cams, std::vector<glm::vec3> &hits)
{
    for (const BasicCamera &cam : cams) {
	glm::mat4x4 invViewMat = glm::inverse(cam.getScaleMatrix() * cam.getViewMatrix());

	for(int y = 0; y < m_height; ++y) {
	    //#pragma omp parallel for
 	    for(int x = 0; x < m_width; ++x) {
		tracePixel(x, y, mesh, invViewMat, hits);
	    }
	}
    }
}

glm::vec3 Tracer::tracePixel(int x, int y, const Mesh& mesh, const glm::mat4x4 &invViewMatrix, std::vector<glm::vec3> &hits)
{
    glm::vec3 p(0, 0, 0);
    glm::vec3 d((2.f * x / m_width) - 1, 1 - (2.f * y / m_height), -1);
    d = glm::normalize(d);

    Ray r(p, d);
    r = r.transform(invViewMatrix);
    return traceRay(r, mesh, hits);
}

glm::vec3 Tracer::traceRay(const Ray& r, const Mesh& mesh, std::vector<glm::vec3> &hits)
{
    IntersectionInfo i;
    Ray ray(r);
    if(mesh.getIntersection(ray, &i)) {
        glm::vec3 v = ray.o + i.t * ray.d;
        hits.push_back(v);
    }
}
