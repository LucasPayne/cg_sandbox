
/*--------------------------------------------------------------------------------
    trace_line() takes a function as input, which processes each pixel in the line,
    and has access to the weight that that pixel contributes to approximate integrals
    over that line.
--------------------------------------------------------------------------------*/
struct LinePoint {
    int x;
    int y;
    float weight;
    LinePoint(int _x, int _y, float _weight) :
        x{_x}, y{_y}, weight{_weight}
    {}
};

/*--------------------------------------------------------------------------------
    Reconstructor variants
--------------------------------------------------------------------------------*/
enum ReconstructorTypes {
    CT_ART,
    CT_SART,
    NUM_RECONSTRUCTOR_TYPES
};
class Reconstructor
{
public:
    Image<float> sinogram;
    Image<float> reconstruction;

    Reconstructor(Image<float> _sinogram, int _n) :
        num_parallel_rays{_sinogram.height()},
        num_directions{_sinogram.width()},
        sinogram{_sinogram},
        n{_n},
        reconstruction(_n, _n)
    {
        reconstruction.clear(0);
    }
    Reconstructor() {}

    virtual void iterate() = 0;
    int num_parallel_rays;
    int num_directions;
    int n;
};


// ART: Algebraic Reconstruction Technique
class ARTReconstructor : public Reconstructor
{
public:
    ARTReconstructor(Image<float> _sinogram, int _n) : Reconstructor(_sinogram, _n) {
        cyclic_counter_s = 0;
        cyclic_counter_theta = 0;
        inv_num_directions = 1.f / num_directions;
        inv_num_parallel_rays_minus_one = 1.f / (num_parallel_rays - 1);

        theta = 0;
        cos_theta = 1;
        sin_theta = 0;

        w = (num_parallel_rays - 2.f) / num_parallel_rays; //weights the computed s so that no rays are tangent to the circle.
    }
    ARTReconstructor() {}
    void iterate();

    int cyclic_counter_s;
    int cyclic_counter_theta;
    float inv_num_directions;
    float inv_num_parallel_rays_minus_one;
    float theta;
    float cos_theta;
    float sin_theta;
    float w;
};


// SART: Simultaneous Algebraic Reconstruction Technique
struct SARTReconstructor : public Reconstructor
{
    Image<float> weighted_residual;
    Image<float> reconstruction_sinogram;

    Image<float> reconstruction_total_weights;

    SARTReconstructor(Image<float> _sinogram, int _n) :
        Reconstructor(_sinogram, _n),
        weighted_residual(_sinogram.width(), _sinogram.height()),
        reconstruction_sinogram(_sinogram.width(), _sinogram.height()),
        reconstruction_total_weights(_n, _n)
    {
    }
    SARTReconstructor() {}

    void iterate();
};


/*--------------------------------------------------------------------------------
    Sinograms
--------------------------------------------------------------------------------*/
void fill_sinogram(Image<float> &image, Image<float> &sinogram);
Image<float> create_sinogram(Image<float> &image, int num_parallel_rays, int num_directions);
/*--------------------------------------------------------------------------------
    Ray tracing through reconstruction images.
--------------------------------------------------------------------------------*/
void trace_line(Image<float> &image, float theta, float s, std::function<void(LinePoint)> function);
void trace_line(Image<float> &image,
                float cos_theta, float sin_theta,
                float s,
                std::function<void(LinePoint)> function);
float line_integral(Image<float> &image, float cos_theta, float sin_theta, float s);

