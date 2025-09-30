# traffic-map-shortest-path
Interactive C++ application that visualizes a traffic map and finds the shortest path between two points using Dijkstra’s algorithm and SFML.

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

## 🚀 Future Improvements
- Add A* algorithm for pathfinding comparison.
- Integrate real traffic data or GPS coordinates.
- Export shortest path results as a route plan.

---

## 📸 Demo Screenshot (Optional)
*(Add an image of your app here if possible)*

---

## 🧑‍💻 Authors
- **Your Name** – Developer  
- **Team Members (if any)** – Collaborators
