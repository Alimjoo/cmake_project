#include "headset_measure_3d.h"


bool read_ply_file(const std::string& file_path, PLYData& data) {
    data.vertices.clear();
    int v_count = 0;
    try {
        std::ifstream file(file_path, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open " + file_path);
            return false;
        }

        PlyFile ply_file;
        ply_file.parse_header(file);  // Parse the header to get information about the PLY file structure
        std::shared_ptr<PlyData> vertices, normals, colors, faces;

        // Request properties from the PLY file
        vertices = ply_file.request_properties_from_element("vertex", { "x", "y", "z" });

        // Read the contents into the buffers
        ply_file.read(file);

        // Fill vertices
        if (vertices) {
            const size_t vertex_count = vertices->count;  // Number of vertices (x, y, z)
            v_count = vertex_count; // Number of vertices
            const float* vertex_buffer = reinterpret_cast<float*>(vertices->buffer.get());
            for (size_t i = 0; i < vertex_count; i++) {
                ALIPoint3DF vertex = { vertex_buffer[i * 3], vertex_buffer[i * 3 + 1], vertex_buffer[i * 3 + 2] };
                data.vertices.push_back(vertex);
            }
        }
        else {
            return false;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
    data.x_range = { 100000000, -100000000 };
    data.y_range = { 100000000, -100000000 };
    data.z_range = { 100000000, -100000000 };
    for (int i = 0; i < v_count; i++) {
        auto& cur = data.vertices[i];
        if (data.x_range.min > cur.x) data.x_range.min = cur.x;
        if (data.x_range.max < cur.x) data.x_range.max = cur.x;
        if (data.y_range.min > cur.y) data.y_range.min = cur.y;
        if (data.y_range.max < cur.y) data.y_range.max = cur.y;
        if (data.z_range.min > cur.z) data.z_range.min = cur.z;
        if (data.z_range.max < cur.z) data.z_range.max = cur.z;
    }
    return true;
}


int test_analyze_depth_image(string ply_name, string gray_name, string depth_name) {
    Mat depth_image = cv::imread(depth_name, 0);
    Mat gray_image = cv::imread(gray_name, 0);
    // Mat test_im = depth_image - gray_image;
    Mat test_im =depth_image.clone();
    uchar* dp = test_im.ptr();
    int rows = depth_image.rows;
    int cols = depth_image.cols;

    int arow = rows / 2;
    vector<int> indices(cols);
    for (int i = 0; i < cols; i++) {
        indices[i] = i;
    }
    auto fig = figure();
    auto ax = fig->current_axes();
    for (int i = rows / 3*3/2; i < rows / 3 * 2; i += 50) {
        vector<float> irow_grays(cols);
        for (int j = 0; j < cols; j++) {
            irow_grays[j] = dp[i * cols + j];
            test_im.at<uchar>(i, j) = 0;
        }
        vector<float> fil_res(cols);
        ali_mid_filter(irow_grays.data(), fil_res.data(), 1, cols, 61);
        vector<float> diff_res(cols);
        ali_diff(fil_res.data(), diff_res.data(), 1, cols, 1);


        // plot(ax, indices, irow_grays)->line_width(2.0);
        // hold(on);
        // plot(ax, indices, fil_res)->line_width(2.0);
        // hold(on);
        plot(ax, indices, diff_res)->line_width(2.0);
        show();
        ax->clear();
        int iiii = 0;
    }




    return 0;
}




