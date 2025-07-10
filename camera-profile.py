import cv2
import pyrealsense2 as rs
import cv2
import numpy as np

pipeline = rs.pipeline()
config = rs.config()

pipeline_wrapper = rs.pipeline_wrapper(pipeline)
pipeline_profile = config.resolve(pipeline_wrapper)
device = pipeline_profile.get_device()

config.enable_stream(rs.stream.depth, 640, 480, rs.format.z16, 30)
pipeline.start(config)
frames:rs.composite_frame = pipeline.wait_for_frames()
depth_frame:rs.depth_frame = frames.get_depth_frame()

def draw_depth_frame(height,width, depth_frame:rs.depth_frame):
    frame = np.zeros((height, width, 3), dtype=np.uint8)
    for y in range(height):
        for x in range(width):
            # Example mapping: gradient from blue to red
            r = depth_frame.get_distance(x,y)/ (2**(16-1)) * 255
            g = depth_frame.get_distance(x,y)/ (2**(16-1)) * 255
            b = depth_frame.get_distance(x,y)/ (2**(16-1)) * 255
            frame[y, x] = [b, g, r]

    cv2.imshow('depth', frame)
nparray = np.asanyarray(depth_frame.as_frame().get_data())
print(type(frames))
# pipeline.stop()
exit(0)
