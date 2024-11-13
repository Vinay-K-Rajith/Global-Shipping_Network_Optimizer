# Global Shipping Network Optimizer


## Abstract
The Global Shipping Network Optimizer is a C++ implementation designed to optimize maritime logistics by finding the most efficient routes between major ports worldwide. The program utilizes Dijkstra's algorithm along with the Haversine formula to calculate precise shipping distances while considering port capacities. This solution addresses the critical need in global commerce for efficient maritime route planning and logistics optimization.

## Introduction
Maritime transport forms the backbone of international trade, with over 80% of global merchandise trade by volume being carried by sea. The complexity of optimizing shipping routes between thousands of ports worldwide presents a significant challenge for logistics planners. Our project addresses this challenge by developing a sophisticated route optimization system that considers both geographical distances and port capabilities.

The system provides:
- Accurate distance calculations between ports using real geographical coordinates
- Information about port handling capacities for both cargo and containers
- Optimal route determination between any two ports in the network
- Detailed breakdown of connecting ports along the optimal route

## Problem Analysis
### Key Challenges
1. **Geographical Distance Calculation**: 
   - Need for accurate distance calculation considering Earth's curvature
   - Requirement to convert latitude/longitude coordinates into practical shipping distances

2. **Data Structure Design**:
   - Efficient storage and retrieval of port information
   - Representation of the port network for pathfinding
   - Management of multiple data types (coordinates, capacities, distances)

3. **Route Optimization**:
   - Finding the shortest path while considering real-world constraints
   - Handling large datasets of ports and routes
   - Ensuring efficient computation for real-time results

### Solution Requirements
1. **Accurate Distance Calculation**:
   - Implementation of the Haversine formula for great-circle distance calculation
   - Consideration of Earth's spherical nature

2. **Efficient Data Management**:
   - Storage of port information including names, coordinates, and capacities
   - Quick lookup capabilities for port information
   - Memory-efficient data structures

3. **Optimal Path Finding**:
   - Implementation of Dijkstra's algorithm for shortest path calculation
   - Priority queue-based optimization for improved performance

## Algorithm Applied
### 1. Haversine Formula Implementation
```cpp
double haversineDistance(const Coordinates& coord1, const Coordinates& coord2) {
    const double earthRadius = 6371.0; // Earth's radius in kilometers
    const double degToRad = M_PI / 180.0;

    double lat1 = coord1.latitude * degToRad;
    double lon1 = coord1.longitude * degToRad;
    double lat2 = coord2.latitude * degToRad;
    double lon2 = coord2.longitude * degToRad;

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = sin(dlat / 2) * sin(dlat / 2) + 
               cos(lat1) * cos(lat2) * 
               sin(dlon / 2) * sin(dlon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return earthRadius * c;
}
```

### 2. Dijkstra's Algorithm Implementation
The program implements Dijkstra's algorithm using a priority queue for efficient path finding:
1. Initialize distances to infinity except for the source port
2. Use a priority queue to process ports in order of increasing distance
3. For each port, consider all connections and update distances if a shorter path is found
4. Track the previous port in the optimal path for route reconstruction

## Output Screenshots
[Note: Please insert actual screenshots of your program's output here]

Example Output:
```
Target Port: Port of Paradip, Odisha, India

Shortest distance between Port of Shanghai, China and Port of Paradip, Odisha, India: 3756.42 kilometers

Connecting Ports:
Port of Paradip, Odisha, India (662.71 km) <- 
Port of Visakhapatnam, Andhra Pradesh, India (361.14 km) <- 
Port of Chennai, Tamil Nadu, India (786.41 km) <- 
Port of Singapore, Singapore (4314.69 km) <- 
Port of Shanghai, China

Source Port Cargo Capacity: 347.06 metric tons
Source Port Container Capacity: 43.30 TEUs
Target Port Cargo Capacity: 92.48 metric tons
Target Port Container Capacity: 18.83 TEUs
```

## Conclusion
The Global Shipping Network Optimizer successfully demonstrates the application of advanced algorithms to solve real-world maritime logistics challenges. The implementation effectively combines the Haversine formula for accurate distance calculation with Dijkstra's algorithm for optimal route finding, providing a practical tool for shipping route optimization.

Key achievements:
1. Accurate distance calculations using real geographical coordinates
2. Efficient path finding between any two ports in the network
3. Comprehensive port information including cargo and container handling capacities
4. Scalable solution capable of handling a large number of ports

Future improvements could include:
1. Integration of real-time weather data
2. Consideration of port waiting times and handling speeds
3. Multi-modal transportation options
4. Cost optimization based on fuel consumption and port fees

The project successfully meets its objectives of providing a practical tool for maritime route optimization while maintaining efficiency and accuracy in calculations.
