# Municipal Incident Response System

## Overview

A C++ console application that simulates a municipal incident response system across selected locations in Gauteng, South Africa. The system manages reported incidents, tracks response teams, prioritises open incidents by severity, and calculates shortest travel routes between locations.

## Features

- Manages 10 Gauteng locations, including Pretoria, Johannesburg, Soweto, and Vereeniging.
- Models road connections using a weighted travel-time matrix and a road-name matrix.
- Generates 10 simulated incidents with random locations, categories, and severity levels.
- Generates 6 response teams with different capabilities, locations, and availability statuses.
- Displays incident information, locations, roads, and response teams.
- Prioritises open incidents according to severity: High, Medium, then Low.
- Identifies available response teams capable of handling a particular incident category.
- Assigns suitable teams to incidents based on capability, availability, and shortest travel time.
- Uses Dijkstra's algorithm to calculate the shortest travel route between locations.
- Supports incident assignment, resolution, and response team availability updates.
- Uses a fixed random seed to make the generated starting data reproducible.

## Incident Categories

- Water
- Electricity
- Roads
- Sanitation
- Public Facilities

## Incident Severity and Status

**Severity levels:** Low, Medium, High

**Incident statuses:** Open, Assigned, Resolved

## Technologies and Concepts

- C++
- Classes and structures
- Arrays and two-dimensional matrices
- Functions and modular programming
- Random number generation
- Severity-based selection sorting
- Weighted graphs
- Dijkstra's shortest-path algorithm
- Menu-driven console applications

## How to Compile and Run

Compile using GCC:

```bash
g++ municipal_incident_response.cpp -o municipal_incident_response
```

Run on Linux or Ubuntu:

```bash
./municipal_incident_response
```

On Windows, run the generated `municipal_incident_response.exe` executable.

## Learning Objectives

This project demonstrates how data structures, graph algorithms, and selection logic can be combined to model an incident management process. It explores shortest-path routing, response team allocation, incident prioritisation, and state changes within a simulated municipal service environment.

## Project Context

Developed as an academic C++ programming project focused on graph algorithms, data management, and municipal incident response simulation.
