// ===========================================
// 扫地机器人 全覆盖路径规划 - C++ 详细注释版
// 功能：
// 1. 加载地图图像，转换为栅格地图 grid[row][col]
// 2. 对可通行区域进行 BFS 分区（分出多个可清扫区域）
// 3. 每个区域做 Zigzag（蛇形）遍历，生成路径
// 4. 用 A* 补全断点之间路径（自动绕障）
// 5. 可视化路径图 + 输出路径坐标
// 6. 统计覆盖率、重复率等指标
// ===========================================

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cmath>
#include <set>
#include <map>

using namespace std;

// 地图参数（来自 map.yaml）
const float resolution = 0.05f;       // 每格 0.05 米
const float origin_x = -0.37f;        // 地图起点 x
const float origin_y = -0.501f;       // 地图起点 y

// 上下左右移动方向（用于 BFS 和 zigzag）
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool inBounds(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

void bfsLabel(int sx, int sy, int label,
              const vector<vector<int>>& grid,
              vector<vector<int>>& region) {
    int rows = grid.size();
    int cols = grid[0].size();
    queue<pair<int, int>> q;
    q.push({sx, sy});
    region[sx][sy] = label;

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int k = 0; k < 4; ++k) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (inBounds(nx, ny, rows, cols) &&
                grid[nx][ny] == 0 && region[nx][ny] == -1) {
                region[nx][ny] = label;
                q.push({nx, ny});
            }
        }
    }
}

void zigzagRegion(int region_id,
                  const vector<vector<int>>& grid,
                  const vector<vector<int>>& region,
                  vector<pair<int, int>>& path) {
    int rows = grid.size();
    int cols = grid[0].size();

    for (int i = 0; i < rows; ++i) {
        if (i % 2 == 0) {
            for (int j = 0; j < cols; ++j) {
                if (region[i][j] == region_id && grid[i][j] == 0) {
                    path.emplace_back(i, j);
                }
            }
        } else {
            for (int j = cols - 1; j >= 0; --j) {
                if (region[i][j] == region_id && grid[i][j] == 0) {
                    path.emplace_back(i, j);
                }
            }
        }
    }
}

pair<float, float> gridToWorld(int row, int col) {
    float x = origin_x + col * resolution;
    float y = origin_y + row * resolution;
    return {x, y};
}

// A* 路径规划结构体
struct Node {
    int x, y;
    int g, h;
    Node* parent;
    int f() const { return g + h; }
};

struct CompareNode {
    bool operator()(Node* a, Node* b) {
        return a->f() > b->f();
    }
};

int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2); // 曼哈顿距离
}

vector<pair<int, int>> astar(const vector<vector<int>>& grid, pair<int, int> start, pair<int, int> goal) {
    int rows = grid.size();
    int cols = grid[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    priority_queue<Node*, vector<Node*>, CompareNode> open;

    Node* startNode = new Node{start.first, start.second, 0, heuristic(start.first, start.second, goal.first, goal.second), nullptr};
    open.push(startNode);

    while (!open.empty()) {
        Node* current = open.top(); open.pop();
        int x = current->x, y = current->y;
        if (visited[x][y]) continue;
        visited[x][y] = true;

        if (x == goal.first && y == goal.second) {
            vector<pair<int, int>> path;
            while (current) {
                path.push_back({current->x, current->y});
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (inBounds(nx, ny, rows, cols) && grid[nx][ny] == 0 && !visited[nx][ny]) {
                Node* neighbor = new Node{nx, ny, current->g + 1, heuristic(nx, ny, goal.first, goal.second), current};
                open.push(neighbor);
            }
        }
    }

    return {}; // 无路径
}

int main() {
    cv::Mat image = cv::imread("map2.png", cv::IMREAD_GRAYSCALE);
    if (image.empty()) {
        cerr << "地图图像读取失败！" << endl;
        return -1;
    }

    int rows = image.rows, cols = image.cols;
    vector<vector<int>> grid(rows, vector<int>(cols));

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            grid[i][j] = (image.at<uchar>(i, j) == 255) ? 0 : 1;

    vector<vector<int>> region(rows, vector<int>(cols, -1));
    int region_count = 0;

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (grid[i][j] == 0 && region[i][j] == -1)
                bfsLabel(i, j, region_count++, grid, region);

    // Step 2: zigzag 路径生成（不保证连通）
    vector<pair<int, int>> zigzag_path;
    for (int r = 0; r < region_count; ++r)
        zigzagRegion(r, grid, region, zigzag_path);

    // Step 3: 插入 A* 连通路径
    vector<pair<int, int>> full_path;
    for (int i = 0; i < zigzag_path.size(); ++i) {
        if (i == 0) {
            full_path.push_back(zigzag_path[i]);
            continue;
        }
        auto subpath = astar(grid, zigzag_path[i - 1], zigzag_path[i]);
        if (!subpath.empty()) {
            full_path.insert(full_path.end(), subpath.begin() + 1, subpath.end());
        }
    }

    // Step 4: 输出路径坐标（世界坐标）
    cout << "路径点（单位：米）：" << endl;
    for (auto& p : full_path) {
        auto [x, y] = gridToWorld(p.first, p.second);
        cout << x << ", " << y << endl;
    }

    // Step 5: 可视化路径
    cv::Mat visual(rows, cols, CV_8UC3, cv::Scalar(255,255,255));
    vector<vector<int>> visit_count(rows, vector<int>(cols, 0));
    for (auto& p : full_path) {
        visit_count[p.first][p.second]++;
        visual.at<cv::Vec3b>(p.first, p.second) = cv::Vec3b(0, 0, 255);
    }
    cv::imshow("清扫路径图", visual);
    cv::imwrite("clean_path.png", visual);
    cv::waitKey(0);

    // Step 6: 指标评估
    int total = 0, visited = 0, repeated = 0;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == 0) {
                total++;
                if (visit_count[i][j] > 0) visited++;
                if (visit_count[i][j] > 1) repeated++;
            }
        }

    float coverage = visited * 1.0f / total;
    float repeat_rate = repeated * 1.0f / full_path.size();

    cout << "覆盖率: " << coverage * 100 << "%\n";
    cout << "重复率: " << repeat_rate * 100 << "%\n";
    cout << "总步数: " << full_path.size() << endl;

    return 0;
}
