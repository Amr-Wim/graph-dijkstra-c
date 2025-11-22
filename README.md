➿ Dijkstra's Shortest Path Algorithm (C Implementation)

This project implements Dijkstra's Shortest Path Algorithm in the C programming language.
It reads a directed weighted graph from input.txt, computes the shortest paths from a chosen source node, and writes the full results to output.txt.

✨ Features

Full Dijkstra implementation (shortest path + distance table)

Graph represented with linked lists (dynamic nodes and arcs)

Custom Dijkstra data structure (distance, predecessor, visited)

Automatic file I/O (input.txt → process → output.txt)

Complete path reconstruction (source → destination)

Cross-platform (Windows / Linux / macOS)

📁 Project Structure
├── src/
│   └── dijkstra.c     # Main C program logic
├── input.txt          # Input file for the graph data
├── output.txt         # Results generated automatically after execution
└── README.md

📥 Input Format (input.txt)

The input file must contain:

The source node on the first line

A list of arcs, each defined by:

S D W

Where:
Parameter	Description

source_node	Starting node for Dijkstra’s algorithm

S	 Source node of the arc
D	 Destination node
W	 Weight (non-negative cost of the arc)


Example Input
0
0 1 4
0 2 2
1 2 5
1 3 10
2 4 3
4 3 4

📤 Output Format (output.txt)

The program outputs the distance and shortest path from the source to every reachable node:

Example Output
Chemin de 0 a 0 (distance=0) : 0
Chemin de 0 a 1 (distance=4) : 0 -> 1
Chemin de 0 a 2 (distance=2) : 0 -> 2
Chemin de 0 a 3 (distance=9) : 0 -> 2 -> 4 -> 3
Chemin de 0 a 4 (distance=5) : 0 -> 2 -> 4

🚀 Usage
🛠️ Compilation

Compile the program using GCC:

gcc src/dijkstra.c -o dijkstra

▶️ Execution

Run the program (requires input.txt to exist in the project root):

./dijkstra


The program will automatically generate output.txt.

📌 Use Cases

Data structures & algorithms coursework

Graph theory demonstrations

Pathfinding and network routing

Dijkstra implementation reference

🧑‍💻 Author

Wiame El-Amimri
Student in SDSI
FST Fès – 2025
