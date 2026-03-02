# Route Planner Project for CSC 122 (Spring 2025)

## Overview

This program computes the longest feasible route through a network of cities given a starting city, budget, and time limit. It reads a CSV file containing city costs, travel connections, total budget, time limit, and the starting city.

The program ensures that:

- Cities are visited at most once per route (except the starting city, which is not revisited).
- Travel and accommodation costs stay within budget.
- Total travel time does not exceed the time limit.

## Input File Format

1. First line: TimeLimit,Budget,StartingCity
2. City Costs: CityName,Cost
3. Connections: CityA,CityB,TravelTime (hours)

Example:

```
5,1500,NewYork
Boston,120
Chicago,100
NewYork,Boston,4
Boston,Chicago,6
```

## How It Works

1. The program reads the file using FileReader and organizes the data.
2. routeFinder recursively explores all feasible routes using DFS with backtracking:
    - Only adds cities if budget, time, and uniqueness constraints are satisfied.
    - Backtracks when no further cities can be added.
    - Records routes that reach dead-ends (fully utilize available resources).
3. Output identifies the longest route and displays a detailed itinerary with travel times, accommodation costs, and total days.

## Usage

1. Compile all source files together (main.cpp, FileReader.cpp, routeFinder.cpp, Output.cpp).
2. Run the program and enter the input file name when prompted.
3. The program outputs the longest feasible route with a step-by-step summary and total costs.

## Potential Improvements

- More detailed output criteria
- User constraint adjustment
- Improve comment descriptiveness for readability
- Move data organization logic to FileReader.cpp
- Add unit testing and exception handling
- Implement Dijkstra's Algorithm instead of recursive DFS?
