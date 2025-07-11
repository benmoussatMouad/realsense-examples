#include <librealsense2/rs.hpp>
#include "example.hpp"


int main() {

    // Create a simple OpenGL window for rendering:
    window app(1280, 720, "RealSense Capture Example");

    rs2::colorizer color_map;
    rs2::rates_printer rates_printer;

    rs2::pipeline pipeuline;
    pipeuline.start();

    while (app) {
        rs2::frameset data = pipeuline.wait_for_frames()
        .apply_filter(color_map)
        .apply_filter(rates_printer);

        app.show(data);
    }

    return 0;
}