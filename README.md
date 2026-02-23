# 🚉 Bridges & Stations Management System

## 📌 Overview

This project is a graph-based transportation network simulator written in C.

It models stations and their connections using adjacency lists and implements Dijkstra’s algorithm with a custom Min-Heap to compute the shortest path between two stations.

The system allows:
- Loading station data from files
- Displaying stations
- Computing optimal routes
- Managing memory dynamically

---

## 🏗️ Project Architecture

### Data Structures

- `station`
  - Name of the station
  - List of destinations (neighbors)
  - Associated line
  - Number of neighbors

- `noeud`
  - Station ID
  - Line ID
  - Distance (for Dijkstra)

- `heap`
  - Custom Min-Heap implementation
  - Used for priority queue in Dijkstra

- `etat`
  - Represents algorithm state (station, line, distance)

---

## 🧠 Algorithms

### 🔹 Dijkstra’s Algorithm
Used to compute the shortest path between two stations.

Time complexity:
- **O((V + E) log V)** using Min-Heap

### 🔹 Min-Heap Implementation
Custom implementation including:
- `push_heap`
- `pop_heap`
- `creer_heap`
- `free_heap`

---

