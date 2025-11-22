
# ➿ Dijkstra's Shortest Path Algorithm (C Implementation)

This project implements **Dijkstra's Shortest Path Algorithm** in the C programming language.  
It reads a directed weighted graph from `input.txt`, computes the shortest paths from a chosen source node, and writes the full results to `output.txt`.

## ✨ Features

- **Full Dijkstra implementation**: Calculates shortest path + distance table.
- **Dynamic Graph Structure**: Graph represented with linked lists (dynamic nodes and arcs).
- **Custom Data Structures**: optimized structures for distance, predecessor, and visited status.
- **Automatic File I/O**: Reads from `input.txt` → processes → writes to `output.txt`.
- **Path Reconstruction**: Traces the complete route from source to destination.
- **Cross-platform**: Compatible with Windows, Linux, and macOS.

## 📁 Project Structure


├── src/
│   └── dijkstra.c     # Main C program logic
├── input.txt          # Input file for the graph data
├── output.txt         # Results generated automatically after execution
└── README.md

📥 Input Format (input.txt)

The input file must be strictly formatted.
First Line: The source node for Dijkstra’s algorithm.
Subsequent Lines: A list of arcs defined by S D W.

Parameters Definition

Parameter	     Description
source_node 	Starting node for Dijkstra’s algorithm (First line only)
S	            Source node of the arc
D	            Destination node of the arc
W	            Weight (non-negative cost of the arc)

Example Input

0
0 1 4
0 2 2
1 2 5
1 3 10
2 4 3
4 3 4

📤 Output Format (output.txt)
The program outputs the distance and shortest path from the source to every reachable node.
Example Output
code
Text
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
Run the program (ensure input.txt exists in the project root):

Linux / macOS:
./dijkstra

Windows:
dijkstra.exe

The program will automatically generate or overwrite output.txt.

📌 Use Cases
🎓 Data structures & algorithms coursework
📊 Graph theory demonstrations
🌐 Pathfinding and network routing
📘 Dijkstra implementation reference

🧑‍💻 Author
Wiame El-Amimri
Student in SDSI
📍 FST Fès – 2025
