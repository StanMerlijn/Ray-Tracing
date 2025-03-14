#include "header/common.hpp"
#include "header/color.hpp"
#include "header/ray.hpp"

double hit_sphere(const dpoint3 &center, double radius, const ray &r)
{
    dvec3 oc = center - r.origin();
    auto a = glm::dot(r.direction(), r.direction());
    auto h = glm::dot(r.direction(), oc);
    auto c = glm::dot(oc, oc) - radius * radius;
    auto discriminant = h * h - a * c;

    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (h - std::sqrt(discriminant)) / a;
    }
}

color rayColor(const ray &r)
{
    auto t = hit_sphere(dpoint3(0, 0, -1), 0.5, r);
    if (t > 0.0)
    {
        dvec3 N = glm::normalize(r.at(t) - dvec3(0, 0, -1));
        return 0.5 * color(N.x + 1, N.y + 1, N.z + 1);
    }

    dvec3 unitDirection = glm::normalize(r.direction());
    auto a = 0.5 * (unitDirection.y + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main()
{
    // Image 16:9 aspect ratio
    // Can do some math bullshit to make it 16:9 but just make it 1920x1080
    double aspectRatio = 16.0 / 9.0;
    int imageWidth = 1920;
    int imageHeight = 1080;

    // Viewport
    auto focalLength = 1.0;
    double viewportHeight = 2.0;
    double viewportWidth = viewportHeight * (double(imageWidth) / double(imageHeight));
    auto camera_center = dpoint3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewportU = dvec3(viewportWidth, 0, 0);
    auto viewportV = dvec3(0, -viewportHeight, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixelDeltaU = viewportU / double(imageWidth);
    auto pixelDeltaV = viewportV / double(imageHeight);

    // Calculate the location of the upper left pixel.
    auto viewportUpperLeft = camera_center - dvec3(0, 0, focalLength) - viewportU / 2.0 - viewportV / 2.0;
    auto pixel00Loc = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

    // Render
    std::cout << "P3\n"
              << imageWidth << ' ' << imageHeight << "\n255\n";

    // Timing the render
    auto start = std::chrono::high_resolution_clock::now();

    // TODO: Parallelize this
    // #pragma omp parallel for
    for (int j = 0; j < imageHeight; j++)
    {
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
        for (int i = 0; i < imageWidth; i++)
        {
            auto pixel_center = pixel00Loc + (double(i) * pixelDeltaU) + (double(j) * pixelDeltaV);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = rayColor(r);
            writeColor(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";

    // End of the timer
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::clog << "Render time: " << duration.count() << " miliseconds\n";
}