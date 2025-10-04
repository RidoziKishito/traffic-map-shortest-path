# Traffic Map Visualization and Shortest Path Search (C++)

**Duration:** Sep 2024 – Nov 2024  
**Technologies:** C++, SFML, Dijkstra’s Algorithm

## 📌 Project Overview
An interactive C++ application that visualizes a traffic map and calculates the shortest path between two points using Dijkstra’s algorithm. Users can dynamically add and connect locations (nodes) and visualize the shortest route in real-time. The interface is built with **SFML** for 2D map rendering, node interaction, and distance calculation in kilometers.

---

## 🧠 Project Description

### 1. Problem Statement
Implement a program that represents a traffic map and finds the shortest path between two points.

### 2. Objectives
- Build an interactive tool that simulates a traffic map.
- Allow users to add and connect nodes (locations) on a map.
- Use Dijkstra’s algorithm to compute the shortest path and display total distance in kilometers.

### 3. Scope
This project is designed for college students and demonstrates how graph algorithms can be applied to real-world scenarios like traffic navigation.

---

## ⚙️ Theoretical Background

### Tools & Libraries
- **C++**: Core programming language for performance and memory efficiency.
- **SFML (Simple and Fast Multimedia Library)**: Used for creating the 2D graphical interface, handling user input, and rendering map elements.

### Methods & Techniques
- **Dijkstra’s Algorithm**: Finds the shortest path in a weighted graph.
- **Euclidean Distance**: Used as edge weights between nodes.
- **Interactive Features**: Users can create, move, and connect nodes via mouse clicks.

---

## 🧮 Implementation

- **Add Nodes:** Right-click to add or move nodes on the map.
- **Connect Nodes:** Right-click and drag from one node to another to create an edge.
- **Shortest Path Search:** Left-click to select a start node and enter the target node to calculate the shortest path.
- **Visualization:** The computed path is highlighted in green and distances are displayed in kilometers.

---

## 🖼️ Design & Features

- **2D Graphics:** Nodes displayed as red circles; edges as lines.
- **Interactive Input:** Real-time creation and connection of nodes.
- **Distance Labels:** Dynamic distance display while dragging.
- **Console Guidance:** Console messages guide user interactions.
- **Cross-Platform:** Runs on any OS with SFML installed.

---

## ⚙️ Installation & Setup

To build and run this project locally:

1.  **Clone** the repository:
    ```bash
    git clone https://github.com/RidoziKishito/traffic-map-shortest-path.git
    cd traffic-map-shortest-path
    ```

2.  **SFML is already included**

    ✅ The project already contains SFML configured and ready to use — no extra installation is required.

    (You don’t need to download or link SFML manually.)

4.  **Build the project**
    Using a C++ compiler (e.g., g++):
    ```bash
    g++ main.cpp -o TrafficMap -lsfml-graphics -lsfml-window -lsfml-system
    ```
    Or open the .sln / .cbp project file in your IDE and click **Build**.
5.  **Run the program**
    ```bash
    ./TrafficMap
    ```

---
## 🚀 Future Development Ideas
- Add A* algorithm for pathfinding comparison.
- Integrate real traffic data or GPS coordinates.
- Export shortest path results as a route plan.

---

## 📸 Demo Screenshot
<img width="938" height="471" alt="image" src="https://github.com/user-attachments/assets/551890d4-3ab7-4c0d-8219-e18d76522916" />

## 📄 License

This project is open source and available under the **MIT License**.

## 🤝 Contact & Support

If you encounter any issues or have questions about this project, feel free to reach out:
* 📧 Email: huytranquoc24@gmail.com
* 🌐 Facebook: https://www.facebook.com/huy.tranquoc.129357/
* 💼 LinkedIn: https://www.linkedin.com/in/tran-quoc-huy-0612-ai/

---

## 🧑‍💻 Authors
- **Tran Quoc Huy - 23110026** – Developer  
- **Le Vu Khang - 23110029** – Collaborators
