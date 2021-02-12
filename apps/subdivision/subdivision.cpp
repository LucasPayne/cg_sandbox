#include <time.h>
#include "cg_sandbox.h"
#include "opengl_utilities/gl.h"
#include "utils/check_quit_key.cpp"
#include "objects/mesh_object.cpp"
#include "objects/cameraman.cpp"
#include "behaviours/Trackball.cpp"
#include "mesh_processing/mesh_processing.h"
#include "world/graphics/image.h"

Aspect<Camera> main_camera;

struct TrianglePatch : public IBehaviour {
    vec3 points[6];
    SurfaceGeometry geom;
    bool active;
    bool subdiv_central;

    vec3 point(int i, int j, int k) {
        assert(i + j + k == 2);
        if (i == 2) return points[0];
        if (j == 2) return points[1];
        if (k == 2) return points[2];
        if (k == 0) return points[3];
        if (i == 0) return points[4];
        if (j == 0) return points[5];
        assert(0);
    }
    // cycle = 0,1,2
    // This version cycles the indices i,j,k so that it is easy to do something symmetrically for each vertex of the triangle.
    vec3 point(int i, int j, int k, int cycle) {
        switch (cycle) {
            case 0: return point(i,j,k);
            case 1: return point(j,k,i);
            case 2: return point(k,i,j);
        }
        assert(0);
    }

    TrianglePatch() {}
    TrianglePatch(std::vector<vec3> &_points, bool _subdiv_central = true) : active{true}, subdiv_central{_subdiv_central} {
        assert(_points.size() == 6);
        Vertex vertices[6];
        for (int i = 0; i < 6; i++) {
            points[i] = _points[i];
            vertices[i] = geom.add_vertex(_points[i]);
        }
        geom.add_triangle(vertices[0], vertices[3], vertices[5]);
        geom.add_triangle(vertices[1], vertices[4], vertices[3]);
        geom.add_triangle(vertices[2], vertices[5], vertices[4]);
        geom.add_triangle(vertices[3], vertices[4], vertices[5]);
    }

    void update() {
        if (active) world->graphics.paint.wireframe(geom, mat4x4::identity(), 0.001);
    }

    void keyboard_handler(KeyboardEvent e) {
        if (active && e.action == KEYBOARD_PRESS) {
            if (e.key.code == KEY_T) subdivide();
        }
    }

    void subdivide() {
        if (subdiv_central) {
            for (int cyc = 0; cyc <= 2; cyc++) {
                std::vector<vec3> ps = {
                    point(2,0,0,cyc),
                    0.5*(point(1,1,0,cyc) + 0.5*(point(2,0,0,cyc) + point(0,2,0,cyc))),
                    0.5*(point(1,0,1,cyc) + 0.5*(point(2,0,0,cyc) + point(0,0,2,cyc))),
                    0.5*(point(2,0,0,cyc) + point(1,1,0,cyc)),
                    0.25*(point(2,0,0,cyc) + point(1,1,0,cyc) + point(1,0,1,cyc) + point(0,1,1,cyc)),
                    0.5*(point(2,0,0,cyc) + point(1,0,1,cyc))
                };
                world->add<TrianglePatch>(entity, ps);
            }
            std::vector<vec3> ps;
	    for (int cyc = 0; cyc <= 2; cyc++)
                ps.push_back(0.5*(point(1,1,0,cyc) + 0.5*(point(2,0,0,cyc) + point(0,2,0,cyc))));
	    for (int cyc = 0; cyc <= 2; cyc++) 
	        ps.push_back(0.25*(point(2,0,0,cyc) + point(1,1,0,cyc) + point(1,0,1,cyc) + point(0,1,1,cyc)));
            world->add<TrianglePatch>(entity, ps);
        } else {
            std::vector<vec3> ps = {
	        point(2,0,0),
	        0.5*(point(1,1,0) + 0.5*(point(2,0,0) + point(0,2,0))),
                0.5*(point(1,0,1) + 0.5*(point(2,0,0) + point(0,0,2))),
                0.5*(point(2,0,0) + point(1,1,0)),
                0.25*(point(2,0,0) + point(1,1,0) + point(1,0,1) + point(0,1,1)),
                0.5*(point(2,0,0) + point(1,0,1))
            };
            world->add<TrianglePatch>(entity, ps);

            ps = {
                0.25*point(0,2,0) + 0.5*point(1,1,0) + 0.25*point(2,0,0),
            
                point(0,0,2),

                0.25*point(0,0,2) + 0.5*point(1,0,1) + 0.25*point(2,0,0),

                0.5*point(0,1,1) + 0.5*point(1,0,1),

                0.5*point(0,0,2) + 0.5*point(1,0,1),

                0.25*(point(0,1,1) + point(1,0,1) + point(1,1,0) + point(2,0,0)),
            };
            world->add<TrianglePatch>(entity, ps);

            ps = {
                0.25*point(0,2,0) + 0.5*point(1,1,0) + 0.25*point(2,0,0),
                point(0,2,0),
                point(0,0,2),
                0.5*(point(0,2,0) + point(1,1,0)),
                point(0,1,1),
                0.5*(point(0,1,1) + point(1,0,1)),
            };
            world->add<TrianglePatch>(entity, ps);
        }

        active = false;
    }
};



struct SubdivisionCurve : public IBehaviour {
    std::vector<std::vector<vec3>> components;

    SubdivisionCurve() {}
    SubdivisionCurve(std::vector<vec3> _points) {
        components.push_back(_points);
    }

    void update() {
        static vec4 colors[4] = {vec4(1,0,0,1), vec4(0,1,0,1), vec4(0,0,1,1), vec4(0,0,0,1)};

        int c = 0;
        for (auto points : components) {
            for (int i = 0; i < points.size()-1; i++) {
                world->graphics.paint.line(points[i], points[i+1], 10, colors[c%4]);
            }
            c += 1;
        }
    }

    void keyboard_handler(KeyboardEvent e) {
        if (e.action == KEYBOARD_PRESS) {
            if (e.key.code == KEY_T) {
                subdivide();
            }
        }
    }

    void subdivide() {
        std::vector<std::vector<vec3>> new_components;
        for (auto points : components) {
            for (int segment = 0; segment <= 1; segment++) {
                auto point = [&](int index) {
                    if (segment == 0) return points[index];
                    return points[5-1-index];
                };
                auto comp = std::vector<vec3>();
                comp.push_back(point(0));
                comp.push_back(0.5*point(0) + 0.5*point(1));
                comp.push_back(0.25*point(0) + 0.5*point(1) + 0.25*point(2));
                comp.push_back((1.f/8)*point(0) + (3.f/8)*point(1) + (3.f/8)*point(2) + (1.f/8)*point(3));
                comp.push_back(1.f/16 * point(0) + 4.f/16 * point(1) + 6.f/16 * point(2) + 4.f/16 * point(3) + 1.f/16 * point(4));
                new_components.push_back(comp);
            }
        }
        components = new_components;
    }
};



int factorial(int n)
{
    if (n <= 1) return 1;
    int f = n;
    for (int i = 1; i < n-1; i++) {
        f *= n-i;
    }
    return f;
}
int binomial_coefficient(int n, int k)
{
    if (k == 0) {
        return 1;
    }
    int c = n;
    for (int i = 1; i < k; i++) {
        c *= n-i;
    }
    return c / factorial(k);
}


struct SplineCurve : public IBehaviour {
#define DEGREE 2
#define DEBOOR_WIDTH (DEGREE+1)
    std::vector<vec3> points;

    SplineCurve() {}
    SplineCurve(std::vector<vec3> _points) {
        points = _points;
        show_de_boor = true;
        show_bezier = true;
    }

    bool show_de_boor;
    bool show_bezier;

    void render_bezier_curve(int degree, vec3 *ps, float width, vec4 color, int tess=10) {
        float w = 1.f / tess;
        std::vector<vec3> chain(tess+1);
        for (int i = 0; i <= tess; i++) {
            float t = i*w;
            vec3 p = vec3::zero();
            for (int j = 0; j <= degree; j++) {
                float coeff = 1;
                for (int k = 0; k < j; k++) {
                    coeff *= 1-t;
                }
                for (int k = 0; k < degree-j; k++) {
                    coeff *= t;
                }
                coeff *= binomial_coefficient(degree, j);
                p += coeff * ps[j];
            }
            chain[i] = p;
        }
        world->graphics.paint.chain(chain, width, color);
    }

    void update() {
        static vec4 colors[4] = {vec4(1,0,0,1), vec4(0,1,0,1), vec4(0,0,1,1)};
        if (show_de_boor) {
            for (int i = 0; i <= points.size()-2; i++) {
	        world->graphics.paint.line(points[i], points[i+1], 3, vec4(0,0,0,1));
            }
        }

        #if DEGREE == 2
        float weights[DEBOOR_WIDTH * DEBOOR_WIDTH] = {
            0.5, 0.5, 0,
            0, 1, 0,
            0, 0.5, 0.5
        };
        #elif DEGREE == 3
        float weights[DEBOOR_WIDTH * DEBOOR_WIDTH] = {
            1.f/6,   2.f/3,   1.f/6,   0,
            0,       2.f/3,   1.f/3,   0,
            0,       1.f/3,   2.f/3,   0,
            0,       1.f/6,   2.f/3,   1.f/6,
        };
        #elif DEGREE == 4
        float weights[DEBOOR_WIDTH * DEBOOR_WIDTH] = {
            1.f/24,   11.f/24,   11.f/24,   1.f/24,    0,
            0,      1.f/3,     7.f/12,    1.f/12,    0,
            0,      1.f/6,     2.f/3,     1.f/6,     0,
            0,      1.f/12,    7.f/12,    1.f/3,     0,
            0,      1.f/24,    11.f/24,   11.f/24,   1.f/24,
        };
        #elif DEGREE == 5
        float weights[DEBOOR_WIDTH * DEBOOR_WIDTH] = {
            1.f/120,   13.f/60,   11.f/20,   13.f/60,   1.f/120,   0,
            0,       2.f/15,    11.f/20,   3.f/10,    1.f/60,    0,
            0,       1.f/15,    1.f/2,     2.f/5,     1.f/30,    0,
            0,       1.f/30,    2.f/5,     1.f/2,     1.f/15,    0,
            0,       1.f/60,    3.f/10,    11.f/20,   2.f/15,    0,
            0,       1.f/120,   13.f/60,   11.f/20,   13.f/60,   1.f/120,
        };
        #elif DEGREE == 6
        float weights[DEBOOR_WIDTH * DEBOOR_WIDTH] = {
            1.f/720,   19.f/240,   151.f/360,   151.f/360,   19.f/240,    1.f/720,    0,
            0,       2.f/45,     131.f/360,   19.f/40,     41.f/360,    1.f/360,    0,
            0,       1.f/45,     53.f/180,    31.f/60,     29.f/180,    1.f/180,    0,
            0,       1.f/90,     2.f/9,       8.f/15,      2.f/9,       1.f/90,     0,
            0,       1.f/180,    29.f/180,    31.f/60,     53.f/180,    1.f/45,     0,
            0,       1.f/360,    41.f/360,    19.f/40,     131.f/360,   2.f/45,     0,
            0,       1.f/720,    19.f/240,    151.f/360,   151.f/360,   19.f/240,   1.f/720,
        };
        #endif

        for (int i = 0; i <= points.size()-DEBOOR_WIDTH; i++) {
            vec3 deboor[DEBOOR_WIDTH];
            for (int j = 0; j < DEBOOR_WIDTH; j++) deboor[j] = points[i+j];

            vec3 bezier[DEBOOR_WIDTH];
            for (int j = 0; j < DEBOOR_WIDTH; j++) bezier[j] = vec3::zero();
            
            for (int b = 0; b < DEBOOR_WIDTH; b++) {
                for (int bb = 0; bb <= DEBOOR_WIDTH; bb++) {
                    bezier[b] += weights[DEBOOR_WIDTH*b + bb] * deboor[bb];
                }
            }
            #if DEGREE == 2 // test degree evaluation 2->4

	    vec3 bezier_elevated[5];
            static float elevation_weights[5*3] = {
                1.f,     0,     0,
                1.f/2,   1.f/2,   0,
                1.f/6,   2.f/3,   1.f/6,
                0,     1.f/2,   1.f/2,
                0,     0,     1,
            };
            for (int i = 0; i < 5; i++) {
                bezier_elevated[i] = vec3::zero();
                for (int j = 0; j < 3; j++) {
                    bezier_elevated[i] += bezier[j]*elevation_weights[3*i + j];
                }
            }
            if (show_bezier) {
                for (int j = 0; j < 4; j++) {
                    world->graphics.paint.line(bezier_elevated[j], bezier_elevated[j+1], 1.5, colors[i%4]);
                }
            }
            render_bezier_curve(4, bezier_elevated, 5, colors[i%4]);
            #else
            if (show_bezier) {
                for (int j = 0; j < DEBOOR_WIDTH-1; j++) {
                    world->graphics.paint.line(bezier[j], bezier[j+1], 1.5, colors[i%4]);
                }
            }
            render_bezier_curve(DEBOOR_WIDTH-1, bezier, 5, colors[i%4]);
            #endif
        }
    }

    void keyboard_handler(KeyboardEvent e) {
        if (e.action == KEYBOARD_PRESS) {
            if (e.key.code == KEY_T) show_de_boor = !show_de_boor;
            if (e.key.code == KEY_Y) show_bezier = !show_bezier;
        }
    }
};
#undef DEGREE
#undef DEBOOR_WIDTH


/*
    Gives the ordered sums that have a given number of terms, that sum to n.
    This is returned in a flat array, where each sequence of 'terms' members is a sum.
*/
std::vector<int> ordered_sums(int terms, int n)
{
    if (terms == 1) {
        return { n };
    }
    auto sums = std::vector<int>(0);
    for (int i = 0; i < n+1; i++) {
        auto trailing = ordered_sums(terms-1, n-i);
        int num_trailing = trailing.size() / (terms-1);
        for (int j = 0; j < num_trailing; j++) {
            sums.push_back(i);
            for (int k = 0; k < terms-1; k++) sums.push_back(trailing[j*(terms-1)+k]);
        }
    }
    return sums;
}


struct TriangleNetIndex {
    TriangleNetIndex() {}
    TriangleNetIndex(int i, int j, int k)
    {
        indices[0] = i;
        indices[1] = j;
        indices[2] = k;
    }
    int indices[3];

    bool operator==(const TriangleNetIndex &other) {
        return indices[0] == other.indices[0] &&
               indices[1] == other.indices[1] && 
               indices[2] == other.indices[2];
    }

    int operator[](int index) {
        return indices[index];
    }

    TriangleNetIndex relative(int di, int dj, int dk) {
        assert(di + dj + dk == 0);
        return TriangleNetIndex(indices[0]+di, indices[1]+dj, indices[2]+dk);
    }
};

std::vector<TriangleNetIndex> triangle_net_indices(int width)
{
    // width here means the number of points at the bottom of the triangle.
    int n = width*(width+1)/2;
    auto indices = std::vector<TriangleNetIndex>(n);
    auto sums = ordered_sums(3, width-1);
    for (int i = 0; i < n; i++) indices[i] = TriangleNetIndex(sums[3*i+0], sums[3*i+1], sums[3*i+2]);
    return indices;
}

int triangle_net_index_to_flat_index(int width, TriangleNetIndex index)
{
    int i = 0;
    for (auto other_index : triangle_net_indices(width)) {
        if (other_index == index) return i;
        i ++;
    }
    assert(0);
}

// # ordered_sums(3, 5) will give all triples of sums 0+0+5, 0+1+4, ..., 3+1+1, etc., that add to 5.
// def ordered_sums(terms, n):
//     if terms == 1:
//         yield tuple([n])
//         return
//     for i in range(0, n+1):
//         for trailing in ordered_sums(terms-1, n-i):
//             yield tuple([i]) + trailing




struct TriangularSplineSurface : public IBehaviour {
    std::vector<vec3> points;
    int de_boor_net_width;

    bool show_de_boor;
    bool show_bezier;


    int to_flat_index(TriangleNetIndex index) const {
        int i = 0;
        for (auto other_index : indices()) {
            if (index == other_index) return i;
            i++;
        }
        assert(0);
    }


    void render_de_boor_net(int width, vec3 *points, float line_width, vec4 color)
    {
        for (auto index : triangle_net_indices(width)) {
	    vec3 a = points[triangle_net_index_to_flat_index(width, index)];
            if (index[0] > 0) {
                vec3 b = points[triangle_net_index_to_flat_index(width, index.relative(-1, 1, 0))];
                world->graphics.paint.line(a, b, line_width, color);
            }
            if (index[1] > 0) {
                vec3 b = points[triangle_net_index_to_flat_index(width, index.relative(0, -1, 1))];
                world->graphics.paint.line(a, b, line_width, color);
            }
            if (index[2] > 0) {
                vec3 b = points[triangle_net_index_to_flat_index(width, index.relative(1, 0, -1))];
                world->graphics.paint.line(a, b, line_width, color);
            }
        }
    }
    void render_de_boor_net(int width, std::vector<vec3> &points, float line_width, vec4 color)
    {
        render_de_boor_net(width, &points[0], line_width, color);
    }

    TriangularSplineSurface() {}
    TriangularSplineSurface(int _de_boor_net_width, std::vector<vec3> _points) {
        de_boor_net_width = _de_boor_net_width;

        assert(_points.size() == de_boor_net_width*(de_boor_net_width+1)/2);

        points = _points;
        show_de_boor = true;
        show_bezier = true;
    }


    std::vector<TriangleNetIndex> indices() const {
        auto sums = ordered_sums(3, de_boor_net_width-1);
        auto index_list = std::vector<TriangleNetIndex>(de_boor_net_width*(de_boor_net_width+1)/2);
        for (int i = 0; i < sums.size()/3; i++) {
            index_list[i] = TriangleNetIndex(sums[3*i+0], sums[3*i+1], sums[3*i+2]);
        }
        return index_list;
    }

    vec3 point(TriangleNetIndex index) const {
        return points[to_flat_index(index)];
    }
    vec3 &point(TriangleNetIndex index){
        return points[to_flat_index(index)];
    }


    void update() {
        static vec4 colors[4] = {vec4(1,0,0,1), vec4(0,1,0,1), vec4(0,0,1,1)};
        if (show_de_boor) {
            render_de_boor_net(de_boor_net_width, points, 1.5f, vec4(0,0,0,1));
        }
        
        static float weights[(5*(5+1))/2 * (5*(5+1))/2] = {
            0, 1.f/12.f, 1.f/12.f, 0, 0, 1.f/12.f, 1.f/2.f, 1.f/12.f, 0, 1.f/12.f, 1.f/12.f, 0, 0, 0, 0, 
            0, 1.f/24.f, 1.f/8.f, 0, 0, 0, 1.f/2.f, 1.f/6.f, 0, 1.f/24.f, 1.f/8.f, 0, 0, 0, 0, 
            0, 0, 1.f/6.f, 0, 0, 0, 1.f/3.f, 1.f/3.f, 0, 0, 1.f/6.f, 0, 0, 0, 0, 
            0, 0, 1.f/8.f, 1.f/24.f, 0, 0, 1.f/6.f, 1.f/2.f, 0, 0, 1.f/8.f, 1.f/24.f, 0, 0, 0, 
            0, 0, 1.f/12.f, 1.f/12.f, 0, 0, 1.f/12.f, 1.f/2.f, 1.f/12.f, 0, 1.f/12.f, 1.f/12.f, 0, 0, 0, 
            0, 0, 1.f/24.f, 0, 0, 1.f/24.f, 1.f/2.f, 1.f/8.f, 0, 1.f/8.f, 1.f/6.f, 0, 0, 0, 0, 
            0, 0, 1.f/24.f, 0, 0, 0, 5.f/12.f, 1.f/4.f, 0, 1.f/24.f, 1.f/4.f, 0, 0, 0, 0, 
            0, 0, 1.f/24.f, 0, 0, 0, 1.f/4.f, 5.f/12.f, 0, 0, 1.f/4.f, 1.f/24.f, 0, 0, 0, 
            0, 0, 1.f/24.f, 0, 0, 0, 1.f/8.f, 1.f/2.f, 1.f/24.f, 0, 1.f/6.f, 1.f/8.f, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 1.f/3.f, 1.f/6.f, 0, 1.f/6.f, 1.f/3.f, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 1.f/4.f, 1.f/4.f, 0, 1.f/24.f, 5.f/12.f, 1.f/24.f, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 1.f/6.f, 1.f/3.f, 0, 0, 1.f/3.f, 1.f/6.f, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 1.f/6.f, 1.f/8.f, 0, 1.f/8.f, 1.f/2.f, 1.f/24.f, 1.f/24.f, 0, 0, 
            0, 0, 0, 0, 0, 0, 1.f/8.f, 1.f/6.f, 0, 1.f/24.f, 1.f/2.f, 1.f/8.f, 0, 1.f/24.f, 0, 
            0, 0, 0, 0, 0, 0, 1.f/12.f, 1.f/12.f, 0, 1.f/12.f, 1.f/2.f, 1.f/12.f, 1.f/12.f, 1.f/12.f, 0, 
        };

        int bezier_patch_number = 0;
        #define window_width 4
        #define window_size (((window_width+1)*(window_width+2))/2)
        #define patch_degree 4
        #define num_bezier_points (((patch_degree+1)*(patch_degree+2))/2)

        for (auto index : indices()) {
            if (index[0] < window_width) continue;
            vec3 window[window_size];
            TriangleNetIndex corner_indices[3] = { index.relative( 0, 0, 0),
                                                   index.relative(-window_width, window_width, 0),
                                                   index.relative(-window_width, 0, window_width) };
            vec3 corners[3];
            for (int i = 0; i < 3; i++) corners[i] = vec3(corner_indices[i].indices[0],
                                                          corner_indices[i].indices[1],
                                                          corner_indices[i].indices[2]);
            int i = 0;
            for (auto window_index : triangle_net_indices(window_width+1)) {
                vec3 barycentric_index = vec3(window_index.indices[0] * (1.f / window_width),
                                              window_index.indices[1] * (1.f / window_width),
                                              window_index.indices[2] * (1.f / window_width));
                vec3 p_index_floats = corners[0]*barycentric_index[0] +
                                      corners[1]*barycentric_index[1] +
                                      corners[2]*barycentric_index[2];
                auto p_index = TriangleNetIndex(std::round(p_index_floats.x()),
                                                std::round(p_index_floats.y()),
                                                std::round(p_index_floats.z()));
                window[i] = point(p_index);
                i++;
            }
            // std::cout << "window: ";
            // for (auto w : window) std::cout << w << ", ";
            // std::cout << "\n";

            vec3 bezier_points[num_bezier_points];
            for (int i = 0; i < num_bezier_points; i++) {
                bezier_points[i] = vec3::zero();
                for (int j = 0; j < window_size; j++) {
                    bezier_points[i] += weights[window_size*i + j]*window[j];
                }
            }

            render_de_boor_net(window_width+1, bezier_points, 1, colors[bezier_patch_number % 3]);
            bezier_patch_number ++;
        }
    }

    void keyboard_handler(KeyboardEvent e) {
        if (e.action == KEYBOARD_PRESS) {
            if (e.key.code == KEY_T) show_de_boor = !show_de_boor;
            if (e.key.code == KEY_Y) show_bezier = !show_bezier;
        }
    }
};

class App : public IGC::Callbacks {
public:
    World &world;
    App(World &world);

    void close();
    void loop();
    void keyboard_handler(KeyboardEvent e);
    void mouse_handler(MouseEvent e);
    void window_handler(WindowEvent e);
};


App::App(World &_world) : world{_world}
{
    Entity cameraman = create_cameraman(world);
    cameraman.get<Transform>()->position = vec3(0,0,2);
    main_camera = cameraman.get<Camera>();

    if (0) {
        // Triangle subdiv testing
        Entity e = world.entities.add();
        vec3 a = vec3(2,0,0);
        vec3 b = vec3(0,2,0);
        vec3 c = vec3(0,0,2);
        vec3 ab = 0.5*(a + b) + vec3::random(-2,2);
        vec3 bc = 0.5*(b + c) + vec3::random(-2,2);
        vec3 ca = 0.5*(c + a) + vec3::random(-2,2);
        // vec3 a = vec3(-2,0,0);
        // vec3 b = vec3(2,0,0);
        // vec3 c = vec3(0,2,0);
        // vec3 ab = 0.5*(a + b);
        // vec3 bc = 0.5*(b + c);
        // vec3 ca = 0.5*(c + a);
        std::vector<vec3> points = {
            a, b, c, ab, bc, ca
        };
        world.add<TrianglePatch>(e, points, false);
    }

    if (0) {
        // Curve subdiv testing
        Entity e = world.entities.add();
        auto points = std::vector<vec3>(5);
        for (int i = 0; i < points.size(); i++) {
            points[i] = vec3::random(-1,1);
        }
        world.add<SubdivisionCurve>(e, points);
    }

    
    if (0) {
        // Spline curve testing
        Entity e = world.entities.add();
        auto points = std::vector<vec3>(20);
        points[0] = vec3::zero();
        for (int i = 1; i < points.size(); i++) {
            points[i] = points[i-1] + vec3::random(-1,1);
        }
        world.add<SplineCurve>(e, points);
    }

    if (1) {
        // Triangular spline surface testing
        Entity e = world.entities.add();
        int n = 10;
        auto points = std::vector<vec3>(n*(n+1)/2);

        vec3 basis[3] = {vec3(0,0,0),
                         vec3(0,0,1),
                         vec3(sin(M_PI/3), 0, cos(M_PI/3))};
        auto spline = world.add<TriangularSplineSurface>(e, n, points);
        for (auto index : spline->indices()) {
            spline->point(index) = basis[0] * (index.indices[0] - (n-1)/3.f) +
                                   basis[1] * (index.indices[1] - (n-1)/3.f) +
                                   basis[2] * (index.indices[2] - (n-1)/3.f);
            spline->point(index) += vec3::random(-0.5, 0.5);
        }
    }
}


void App::close()
{
}

void App::loop()
{
}

void App::window_handler(WindowEvent e)
{
}
void App::keyboard_handler(KeyboardEvent e)
{
    check_quit_key(e, KEY_Q);

    if (e.action == KEYBOARD_PRESS) {
        // if (e.key.code == KEY_R) world.graphics.compile_shaders();
    }
}

void App::mouse_handler(MouseEvent e)
{
}

int main(int argc, char *argv[])
{
    srand(time(0));

    printf("[main] Creating context...\n");
    IGC::Context context("A world");
    printf("[main] Creating world...\n");
    World world(context);
    printf("[main] Adding world callbacks...\n");

    printf("[main] Creating app...\n");
    App app(world);
    printf("[main] Adding app callbacks...\n");
    context.add_callbacks(&app);

    context.enable_raw_mouse();

    printf("[main] Entering loop...\n");
    context.enter_loop();
    context.close();
}
