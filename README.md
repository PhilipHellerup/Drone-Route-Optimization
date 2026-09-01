# Drone Route Optimization
A route optimization program written in C that uses the Branch and Bound algorithm to solve the Traveling Salesman Problem (TSP) for drone-based medical deliveries.

Developed as a first-semester Software Engineering project at Aalborg University.

## Overview
The project investigates how software can optimize drone routes for delivering medical supplies to rural and remote areas.

Delivery locations are represented as coordinates in a complete weighted graph. The program calculates the Euclidean distance between each location and uses Branch and Bound to determine the shortest route that visits every delivery point exactly once before returning to the starting point.

## Features
- Reads delivery locations from coordinate data.
- Calculates Euclidean distances between locations.
- Represents routes using a weighted adjacency matrix.
- Solves the Traveling Salesman Problem using Branch and Bound.
- Prunes suboptimal routes during the search.
- Outputs the optimal route and total distance.

## Technologies & Concepts

**Technologies:**\
C, CMake, Git, GitHub, CLion.

**Concepts:**\
Traveling Salesman Problem, Branch and Bound, Graph Theory, Adjacency Matrices, Euclidean Distance, Recursion, Backtracking.

## Contributors
Developed as a group project by:
- Anders Mathias Larsen
- Daniel Sloth
- Jacob Christian Larsen
- Lena Hayes
- Philip Vestergaard Hellerup Jørgensen
- Philippe Christian Frøkjær Bourrachot
- Viktor Alexander Parkhøi

## Project Report
The accompanying report, **Pathfinding Algorithm for Drone Delivery Using Branch and Bound Method**, covers the problem analysis, theoretical foundation, algorithm design, implementation, and evaluation of the solution.

*1st Semester Software Engineering Project - Aalborg University - 2024*
