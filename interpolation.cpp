#include "interpolation.h"
#include <algorithm>

int interpolate(double angle) {
    // Pastikan sudut berada di dalam range
    angle = std::clamp(angle, -180.0, 180.0);

    // Persamaan interpolasi linear dari range
    // [-150, 150] ke [0, 1023]
    double digital_unit = (angle + 180) * 1023.0 / 360.0;

    // Kembalikan nilai sebagai integer
    return static_cast<int>(digital_unit);
}

std::vector<int> interpolate_list(const std::vector<double>& angles) {
    std::vector<int> digital_units;
    digital_units.reserve(angles.size());
    for (double angle : angles) {
        digital_units.push_back(interpolate(angle));
    }
    return digital_units;
}
