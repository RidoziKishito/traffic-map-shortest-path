#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <queue>
#include <limits>
#include <map>
#include <fstream>
using namespace std;

struct Point {
    float x, y;
};

vector<Point> points = {
    //{35.5 * 21.2, 11.2 * 21.2},
    //{38.3 * 21.2, 2.5 * 21.2},
    //{42.1 * 21.2, 12.7 * 21.2},
    //{30.8 * 21.2, 11.3 * 21.2},
    //{45.15 * 21.2, 15.3 * 21.2},
    //{6.5 * 21.2, 19.8 * 21.2},
    //{11.5 * 21.2, 26.65 * 21.2},
    //{22 * 21.2, 25.4 * 21.2},
    //{22.6 * 21.2, 7 * 21.2},
    //{20 * 21.2, 17.8 * 21.2},
    //{55 * 21.2, 13.3 * 21.2},
    //{60.3 * 21.2, 19 * 21.2},
    //{57.4 * 21.2, 21.8 * 21.2},
    //{42 * 21.2, 26.5 * 21.2},
    //{31 * 21.2, 23.75 * 21.2},
    //{44.2 * 21.2, 6 * 21.2},
    //{52.65 * 21.2, 2.6 * 21.2}
};

vector<pair<int, int>> edges = {
    //{1, 16}, {1, 2}, {1, 3}, {2, 3}, {2, 4}, {1,15}, {7,8}, {7,10}, {14,13}, {16,5}, {16,11},
    //{6, 4}, {2, 5}, {6, 7}, {13,12}, {9,10}, {6,9}, {10,8}, {8,15}, {10,4}, {3, 5}, {16,3},
    //{5,11}, {11, 12}, {16, 17}, {9,2}, {5,11}, {14,15}, {13,15}, {1,4}, {2,16}, {2,17},
    //{5,17}, {5,14 }, {5,15}, {5,13}, {11, 13}, {9,4}, {11,17}, {4,15}, {6,10}
};

map<pair<int, int>, float> edgeWeights;

float calculateDistance(Point p1, Point p2) {
    return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}
void readDataFromFile(const std::string& nodeFile, const std::string& edgeFile, vector<Point>& points, vector<pair<int, int>>& edges) {
    std::ifstream nodeStream(nodeFile);
    std::ifstream edgeStream(edgeFile);
    if (nodeStream.is_open() && edgeStream.is_open()) {
        float x, y;
        while (nodeStream >> x >> y) {
            points.push_back({ x, y });
        }

        int from, to;
        while (edgeStream >> from >> to) {
            edges.push_back({ from, to });
        }
    }
    else {
        std::cerr << "Failed to open files!" << std::endl;
    }
}

void writeDataToFile(const std::string& nodeFile, const std::string& edgeFile, const std::vector<Point>& points, const std::vector<std::pair<int, int>>& edges) {
    // Open files in truncate mode to delete existing data
    std::ofstream nodeStream(nodeFile, std::ios::trunc);
    std::ofstream edgeStream(edgeFile, std::ios::trunc);

    if (nodeStream.is_open() && edgeStream.is_open()) {
        // Write points to the node file
        for (const auto& point : points) {
            nodeStream << point.x << " " << point.y << std::endl;
        }

        // Write edges to the edge file
        for (const auto& edge : edges) {
            edgeStream << edge.first << " " << edge.second << std::endl;
        }
    }
    else {
        std::cerr << "Failed to open files!" << std::endl;
    }
}
void drawLine(sf::RenderWindow& window, Point start, Point end, sf::Color color = sf::Color::Blue) {
    float dx = end.x - start.x;
    float dy = end.y - start.y;
    float angle = atan2(dy, dx) * 180.f / 3.14159265f;

    sf::RectangleShape line;
    line.setSize(sf::Vector2f(calculateDistance(start, end), 5.f));
    line.setFillColor(color);
    line.setOrigin(0.f, 2.5f);
    line.setPosition(start.x, start.y);
    line.setRotation(angle);

    window.draw(line);
}

vector<int> dijkstra(int start, int end, float& totalDistance) {
    int n = points.size();
    vector<float> distances(n, numeric_limits<float>::infinity());
    vector<int> predecessors(n, -1);
    distances[start] = 0;

    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<>> pq;
    pq.push({ 0, start });

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (u == end) break;

        for (auto& edge : edges) {
            int v = (edge.first - 1 == u) ? edge.second - 1 : ((edge.second - 1 == u) ? edge.first - 1 : -1);
            if (v == -1) continue;

            float weight = edgeWeights[{min(u, v), max(u, v)}];
            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                predecessors[v] = u;
                pq.push({ distances[v], v });
            }
        }
    }

    vector<int> path;
    for (int at = end; at != -1; at = predecessors[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    totalDistance = 0.0f;
    for (size_t i = 0; i + 1 < path.size(); ++i) {
        int from = path[i];
        int to = path[i + 1];
        totalDistance += edgeWeights[{min(from, to), max(from, to)}];
    }

    return (path.size() > 1 && path[0] == start) ? path : vector<int>();
}

void initializeEdgeWeights(float scale) {
    for (auto& edge : edges) {
        int from = edge.first - 1;
        int to = edge.second - 1;
        edgeWeights[{min(from, to), max(from, to)}] = calculateDistance(points[from], points[to]) * scale;
    }
}

void handleRightClick(const sf::Vector2i& mousePos, int& selectedNode, bool& isDragging) {
    bool onExistingNode = false;
    for (size_t i = 0; i < points.size(); ++i) {
        float dx = points[i].x - mousePos.x;
        float dy = points[i].y - mousePos.y;
        if (sqrt(dx * dx + dy * dy) <= 20) {
            selectedNode = i;
            onExistingNode = true;
            isDragging = true;
            break;
        }
    }
    if (!onExistingNode) {
        points.push_back({ static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) });
        selectedNode = -1;
    }
}

void handleLeftClick(const sf::Vector2i& mousePos, int& selectedNode, int& targetNode, vector<int>& shortestPath, float& totalDistance) {
    for (size_t i = 0; i < points.size(); ++i) {
        float dx = points[i].x - mousePos.x;
        float dy = points[i].y - mousePos.y;
        if (sqrt(dx * dx + dy * dy) <= 20) {
            selectedNode = i;
            cout << "Enter the target node number (1 to " << points.size() << "): ";
            cin >> targetNode;
            targetNode -= 1;

            if (targetNode == selectedNode) {
                cout << "Selected node and target node are the same. No path needed.\n";
                shortestPath.clear();
                totalDistance = 0.0f;
            }
            else if (targetNode >= 0 && targetNode < points.size()) {
                shortestPath = dijkstra(selectedNode, targetNode, totalDistance);
                if (shortestPath.empty()) {
                    cout << "No path found between the selected node and target node.\n";
                    totalDistance = 0.0f;
                }
                else {
                    cout << "Total km: " << totalDistance << " km" << endl;
                }
            }
            else {
                cout << "Invalid target node.\n";
                shortestPath.clear();
            }
            break;
        }
    }
}
void handleMiddleClick(const sf::Vector2i& mousePos) {
    for (size_t i = 0; i < points.size(); ++i) {
        float dx = points[i].x - mousePos.x;
        float dy = points[i].y - mousePos.y;
        if (sqrt(dx * dx + dy * dy) <= 20) {  // Node selected for deletion
            points.erase(points.begin() + i);

            // Remove edges connected to the deleted node
            edges.erase(remove_if(edges.begin(), edges.end(),
                [i](pair<int, int> edge) {
                    return edge.first == i + 1 || edge.second == i + 1;
                }), edges.end());

            // Adjust edges to reflect the new node indices after deletion
            for (auto& edge : edges) {
                if (edge.first > i + 1) edge.first--;
                if (edge.second > i + 1) edge.second--;
            }
            break;
        }
    }
}
void handleMouseRelease(sf::RenderWindow& window, int selectedNode, bool& isDragging, float scale) {
    if (isDragging) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        for (size_t i = 0; i < points.size(); ++i) {
            if (i == selectedNode) continue;

            float dx = points[i].x - mousePos.x;
            float dy = points[i].y - mousePos.y;
            if (sqrt(dx * dx + dy * dy) <= 20) {
                edges.emplace_back(selectedNode + 1, i + 1);
                edgeWeights[{min<int>(selectedNode, i), max<int>(selectedNode, i)}] = calculateDistance(points[selectedNode], points[i]) * scale;
                break;
            }
        }
        isDragging = false;
    }
}

void drawEdges(sf::RenderWindow& window, const sf::Font& font, const vector<int>& shortestPath) {
    for (const auto& edge : edges) {
        int from = edge.first - 1;
        int to = edge.second - 1;
        bool isHighlighted = false;

        for (size_t i = 0; i + 1 < shortestPath.size(); ++i) {
            if ((shortestPath[i] == from && shortestPath[i + 1] == to) || (shortestPath[i] == to && shortestPath[i + 1] == from)) {
                isHighlighted = true;
                break;
            }
        }

        drawLine(window, points[from], points[to], isHighlighted ? sf::Color::Green : sf::Color::Blue);

        float distanceKm = edgeWeights[{min(from, to), max(from, to)}];
        sf::Text distanceText;
        stringstream ss;
        ss << fixed << setprecision(2) << distanceKm << " km";
        distanceText.setString(ss.str());
        distanceText.setFont(font);
        distanceText.setCharacterSize(16);
        distanceText.setFillColor(sf::Color::Black);
        distanceText.setPosition((points[from].x + points[to].x) / 2, (points[from].y + points[to].y) / 2);
        window.draw(distanceText);
    }
}

void drawNodes(sf::RenderWindow& window, const sf::Font& font) {
    for (size_t i = 0; i < points.size(); ++i) {
        sf::CircleShape shape(17);
        shape.setFillColor(sf::Color::Red);
        shape.setOutlineThickness(2);
        shape.setOutlineColor(sf::Color::Black);
        shape.setPosition(points[i].x - shape.getRadius(), points[i].y - shape.getRadius());
        window.draw(shape);

        sf::Text text;
        text.setFont(font);
        text.setString(to_string(i + 1));
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setPosition(points[i].x - 8, points[i].y - 12);
        window.draw(text);
    }
}

void drawDynamicDistance(sf::RenderWindow& window, const sf::Font& font, Point start, sf::Vector2f end, float scale) {
    float distance = calculateDistance(start, { end.x, end.y }) * scale;
    sf::Text distanceText;
    stringstream ss;
    ss << fixed << setprecision(2) << distance << " km";
    distanceText.setString(ss.str());
    distanceText.setFont(font);
    distanceText.setCharacterSize(16);
    distanceText.setFillColor(sf::Color::Black);
    distanceText.setPosition((start.x + end.x) / 2, (start.y + end.y) / 2);
    window.draw(distanceText);
}
void handleEvent(sf::RenderWindow& window, vector<int>& shortestPath, int& selectedNode, int& targetNode, bool& isDragging, sf::Vector2f& dragPosition, float scale, float& totalDistance) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (event.mouseButton.button == sf::Mouse::Right) {
                // Right-click: create or connect nodes
                handleRightClick(mousePos, selectedNode, isDragging);
            }
            else if (event.mouseButton.button == sf::Mouse::Left) {
                // Left-click: find the shortest path
                handleLeftClick(mousePos, selectedNode, targetNode, shortestPath, totalDistance);
            }
            else if (event.mouseButton.button == sf::Mouse::Middle) {
                // Middle-click: delete node
                handleMiddleClick(mousePos);
            }
        }

        if (event.type == sf::Event::MouseButtonReleased) {
            handleMouseRelease(window, selectedNode, isDragging, scale);
        }

        if (isDragging) {
            dragPosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        }
    }
}

void render(sf::RenderWindow& window, sf::Sprite& backgroundSprite, const sf::Font& font, const vector<int>& shortestPath, float scale, const sf::Vector2f& dragPosition, bool isDragging, int selectedNode) {
    window.clear();
    window.draw(backgroundSprite);
    writeDataToFile("nodes.txt", "edges.txt", points, edges);
    drawEdges(window, font, shortestPath);
    drawNodes(window, font);

    if (isDragging && selectedNode != -1) {
        drawLine(window, points[selectedNode], { dragPosition.x, dragPosition.y });
        drawDynamicDistance(window, font, points[selectedNode], dragPosition, scale);
    }

    window.display();
}

int main() {
    cout << "Use right-click to generate Node and connect to others!" << endl;
    cout << "Use left-click to find shortest path (input number in console) by Dijkstra algorithms!" << endl;
    cout << "Use middle-click to delete Node!" << endl;
    // Initialize nodes and edges from file
    readDataFromFile("nodes.txt", "edges.txt", points, edges);
    initializeEdgeWeights(0.0f); // Initialize edge weights based on the read data

    sf::RenderWindow window(sf::VideoMode(1327, 635), "Interactive Directed Graph Map with Dijkstra and Node Management");
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.png")) return -1;

    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(window.getSize().x / static_cast<float>(backgroundTexture.getSize().x),
        window.getSize().y / static_cast<float>(backgroundTexture.getSize().y));

    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) return -1;
    float referenceDistancePixels = calculateDistance(points[0], points[5]);
    float scale = 11.7f / referenceDistancePixels;
    initializeEdgeWeights(scale);

    vector<int> shortestPath;
    int selectedNode = -1, targetNode = -1;
    bool isDragging = false;
    sf::Vector2f dragPosition;
    float totalDistance = 0.0f;

    while (window.isOpen()) {
        handleEvent(window, shortestPath, selectedNode, targetNode, isDragging, dragPosition, scale, totalDistance);
        render(window, backgroundSprite, font, shortestPath, scale, dragPosition, isDragging, selectedNode);
    }

    return 0;
}