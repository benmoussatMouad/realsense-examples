#include <librealsense2/rs.hpp>
#include "example.hpp"
#include <algorithm>

using namespace rs2;

struct state {
    double pitch, yaw, last_x, last_y;
    bool ml;
    float offset_x, offset_y;
    texture tex;
};

void register_glfw_callbacks(window& app, state& app_state);
void draw_pointcloud(window& app, state& app_state, rs2::points& points);

int main()
{
    // Create a simple OpenGL window for rendering:
    window app(1280, 720, "RealSense Pointcloud Example");
    glfw_state appState;
    // register callbacks to allow manipulation of the pointcloud
    register_glfw_callbacks(app, appState);

    pointcloud pc;
    points points;

    pipeline pipeuline;
    pipeuline.start();

    while (app) {
        frameset frames = pipeuline.wait_for_frames();
        frame color = frames.get_color_frame();
        frame depth = frames.get_depth_frame();

        pc.map_to(color);
        points = pc.calculate(depth);
        appState.tex.upload(color);
        draw_pointcloud(app.width(), app.height(), appState, points);
    }

    return 0;
}
