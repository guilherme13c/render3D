#include "geometry.h"

void saveObj3D(const Object3D &obj, const std::string filename) {
    if (obj.points.empty()) {
        std::cerr << "ERROR: Failed to save 3D object:\tobj.points is empty"
                  << std::endl;
        exit(1);
    }

    if (filename.empty()) {
        std::cerr << "ERROR: Failed to save 3D object:\tinvalid failename"
                  << std::endl;
        exit(1);
    }

    std::ofstream fs(filename);
    if (!fs.is_open()) {
        std::cerr << "ERROR: Failed to save 3D object:\tcould not open file: "
                  << filename << std::endl;
        exit(1);
    }

    uint16_t n_points = obj.points.size();
    uint16_t n_vertices = obj.vertices.size();

    fs << n_points << " " << n_vertices << "\n";

    for (const Point3D &point : obj.points) {
        fs << point.x << " " << point.y << " " << point.z << "\n";
    }

    for (const auto &vertex : obj.vertices) {
        fs << vertex.start << " " << vertex.end << "\n";
    }

    fs.close();
}

void saveObj2D(const Object2D &obj, const std::string filename) {
    if (obj.points.empty()) {
        std::cerr << "ERROR: Failed to save 2D object:\tobj.points is empty"
                  << std::endl;
        exit(1);
    }

    if (filename.empty()) {
        std::cerr << "ERROR: Failed to save 2D object:\tinvalid filename"
                  << std::endl;
        exit(1);
    }

    std::ofstream fs(filename);
    if (!fs.is_open()) {
        std::cerr << "ERROR: Failed to save 2D object:\tcould not open file: "
                  << filename << std::endl;
        exit(1);
    }

    uint16_t n_points = obj.points.size();
    uint16_t n_vertices = obj.vertices.size();

    fs << n_points << " " << n_vertices << "\n";

    for (const auto &point : obj.points) {
        fs << point.x << " " << point.y << "\n";
    }

    for (const auto &vertex : obj.vertices) {
        fs << vertex.start << " " << vertex.end << "\n";
    }

    fs.close();
}

void loadObj3D(Object3D &obj, const std::string filename) {
    std::ifstream fs(filename);
    if (!fs.is_open()) {
        std::cerr << "ERROR: Failed to load 3D object:\tcould not open file: "
                  << filename << std::endl;
        exit(1);
    }

    uint16_t n_points, n_vertices;
    fs >> n_points >> n_vertices;

    obj.points.resize(n_points);
    obj.vertices.resize(n_vertices);

    for (auto &point : obj.points) {
        fs >> point.x >> point.y >> point.z;
    }

    for (auto &vertex : obj.vertices) {
        fs >> vertex.start >> vertex.end;
    }

    fs.close();
}

void loadObj2D(Object2D &obj, const std::string filename) {
    std::ifstream fs(filename);
    if (!fs.is_open()) {
        std::cerr << "ERROR: Failed to load 2D object:\tcould not open file: "
                  << filename << std::endl;
        exit(1);
    }

    uint16_t n_points, n_vertices;
    fs >> n_points >> n_vertices;

    obj.points.resize(n_points);
    obj.vertices.resize(n_vertices);

    for (auto &point : obj.points) {
        fs >> point.x >> point.y;
    }

    for (auto &vertex : obj.vertices) {
        fs >> vertex.start >> vertex.end;
    }

    fs.close();
}

void loadObjs(std::vector<Object2D> &objs2D, std::vector<Object3D> &objs3D,
              int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        std::string filename(argv[i]);

        size_t pos = filename.find_last_of(".");
        if (pos != std::string::npos) {
            std::string extension = filename.substr(pos + 1);
            if (extension == "o2D") {
                Object2D obj2D;
                loadObj2D(obj2D, filename);
                objs2D.push_back(obj2D);
            } else if (extension == "o3D") {
                Object3D obj3D;
                loadObj3D(obj3D, filename);
                objs3D.push_back(obj3D);
            } else {
                std::cerr << "Unsupported file format: " << filename
                          << std::endl;
            }
        } else {
            std::cerr << "Invalid file name: " << filename << std::endl;
        }
    }
}

void project3DTo2D(const Object3D &obj3D, Object2D &obj2D, float depth,
                   float centerX, float centerY, float scale) {
    for (const auto &point3D : obj3D.points) {
        float scale_factor = depth / (depth + point3D.z);
        float projected_x = centerX + point3D.x * scale_factor * scale;
        float projected_y = centerY + point3D.y * scale_factor * scale;
        obj2D.points.push_back({projected_x, projected_y});
    }

    obj2D.vertices = obj3D.vertices;
}

void rotate(Object3D &obj, const float rx, const float ry, const float rz) {
    for (Point3D &point : obj.points) {
        rotateX(point.y, point.z, rx);

        rotateY(point.x, point.z, ry);

        rotateZ(point.x, point.y, rz);
    }
}

void rotateX(float &y, float &z, float angle) {
    float tempY = y * cos(angle) - z * sin(angle);
    float tempZ = y * sin(angle) + z * cos(angle);
    y = tempY;
    z = tempZ;
};

void rotateY(float &x, float &z, float angle) {
    float tempX = x * cos(angle) + z * sin(angle);
    float tempZ = -x * sin(angle) + z * cos(angle);
    x = tempX;
    z = tempZ;
};

void rotateZ(float &x, float &y, float angle) {
    float tempX = x * cos(angle) - y * sin(angle);
    float tempY = x * sin(angle) + y * cos(angle);
    x = tempX;
    y = tempY;
};

void translate(Object3D &obj, const float dx, const float dy, const float dz) {
    for (Point3D &point : obj.points) {
        point.x += dx;
        point.y += dy;
        point.z += dz;
    }
}
