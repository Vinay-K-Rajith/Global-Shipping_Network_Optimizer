#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <string>
#include <unordered_map>
#include <cmath>
#include <iomanip>

using namespace std;

struct Port {
    int node; // Port node index
    double distance; // Distance from the source (using double for geographic distances)
    double cargo_capacity; // Annual cargo handling capacity in metric tons
    double container_capacity; // Annual container handling capacity in TEUs (Twenty-Foot Equivalent Units)
};

struct ComparePort {
    bool operator()(const Port& a, const Port& b) {
        return a.distance > b.distance;
    }
};

struct Coordinates {
    double latitude;
    double longitude;
};

// Function to calculate the Haversine distance between two coordinates
double haversineDistance(const Coordinates& coord1, const Coordinates& coord2) {
    const double earthRadius = 6371.0; // Earth's radius in kilometers
    const double degToRad = M_PI / 180.0;

    double lat1 = coord1.latitude * degToRad;
    double lon1 = coord1.longitude * degToRad;
    double lat2 = coord2.latitude * degToRad;
    double lon2 = coord2.longitude * degToRad;

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = sin(dlat / 2) * sin(dlat / 2) + cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return earthRadius * c;
}

int main() {
    // Define port names, coordinates, cargo capacity, and container capacity
    vector<string> portNames = {
        "Port of Shanghai, China", "Port of Singapore, Singapore", "Port of Rotterdam, Netherlands",
        "Port of Ningbo-Zhoushan, China", "Port of Guangzhou, China", "Port of Busan, South Korea",
        "Port of Hong Kong, Hong Kong", "Port of Qingdao, China", "Port of Tianjin, China",
        "Port of Jebel Ali, UAE", "Port of Kaohsiung, Taiwan", "Port of Antwerp, Belgium",
        "Port of Xiamen, China", "Port of Dalian, China", "Port of Los Angeles, USA",
        "Port of Long Beach, USA", "Port of Tanjung Pelepas, Malaysia", "Port of Hamburg, Germany",
        "Port of Laem Chabang, Thailand", "Port of New York and New Jersey, USA",
        "Port of Tanjung Priok, Indonesia", "Port of Tokyo, Japan", "Port of Santos, Brazil",
        "Port of Valencia, Spain", "Port of Algeciras, Spain", "Port of Felixstowe, UK",
        "Port of Piraeus, Greece", "Port of Colombo, Sri Lanka", "Port of Gioia Tauro, Italy",
        "Port of Salalah, Oman", "Port of Jeddah, Saudi Arabia", "Port of Manzanillo, Mexico",
        "Port of Vancouver, Canada", "Port of Melbourne, Australia", "Port of Durban, South Africa",
        "Port of Karachi, Pakistan", "Port of Chittagong, Bangladesh", "Port of Ho Chi Minh City, Vietnam",
        "Port of Alexandria, Egypt", "Port of Lagos, Nigeria", "Port of Maputo, Mozambique",
        "Port of Dar es Salaam, Tanzania", "Port of Luanda, Angola", "Port of Abidjan, Ivory Coast",
        "Port of Dakar, Senegal", "Port of Tema, Ghana", "Port of Mombasa, Kenya",
        "Port of Chennai, Tamil Nadu, India", "Port of Visakhapatnam, Andhra Pradesh, India",
        "Port of Paradip, Odisha, India"
    };

    vector<Coordinates> portCoordinates = {
        {31.2304, 121.4737}, {1.3521, 103.8198}, {51.9225, 4.4792},
        {29.8683, 121.5440}, {23.1291, 113.2644}, {35.1796, 129.0756},
        {22.3193, 114.1694}, {36.0671, 120.3826}, {39.3434, 117.3616},
        {25.0657, 55.1713}, {22.6273, 120.3014}, {51.2194, 4.4025},
        {24.4798, 118.0895}, {38.9140, 121.6147}, {33.7405, -118.2770},
        {33.7701, -118.1937}, {1.3667, 103.5333}, {53.5511, 9.9937},
        {13.0957, 100.8990}, {40.7128, -74.0060}, {-6.1045, 106.8804},
        {35.6528, 139.8395}, {-23.9535, -46.3349}, {39.4699, -0.3763},
        {36.1408, -5.4562}, {51.9635, 1.3511}, {37.9420, 23.6460},
        {6.9271, 79.8612}, {38.4250, 15.8986}, {17.0151, 54.0924},
        {21.4858, 39.1925}, {19.0522, -104.3188}, {49.2827, -123.1207},
        {-37.8136, 144.9631}, {-29.8587, 31.0218}, {24.8607, 67.0011},
        {22.3475, 91.8123}, {10.8231, 106.6297}, {31.2001, 29.9187},
        {6.5244, 3.3792}, {-25.9653, 32.5892}, {-6.7924, 39.2083},
        {-8.8383, 13.2344}, {5.3097, -4.0127}, {14.6928, -17.4467},
        {5.6690, 0.0177}, {-4.0435, 39.6682}, {13.0827, 80.2707},
        {17.6868, 83.2185}, {20.3167, 86.6086}
    };

    vector<double> portCargoCapacity = {
        347.06, 36.61, 14.51, 27.53, 23.28, 21.66, 19.61, 18.85, 16.75,
        14.62, 10.67, 11.10, 11.22, 10.70, 10.67, 9.69, 9.0, 8.80, 7.76,
        6.86, 7.6, 5.21, 4.25, 5.56, 4.76, 4.21, 4.95, 4.64, 3.87, 3.57,
        3.68, 3.36, 3.71, 3.14, 3.79, 2.99, 2.40, 2.01, 2.37, 1.99, 2.56,
        1.96, 2.86, 2.18, 2.24, 20.28, 75.11, 92.48
    };

    vector<double> portContainerCapacity = {
        43.30, 36.60, 14.51, 26.45, 22.24, 21.69, 20.11, 22.52, 16.55,
        18.99, 10.74, 11.05, 11.35, 10.63, 9.46, 8.11, 8.9, 8.82, 7.82,
        7.48, 8.15, 6.22, 4.37, 4.98, 4.76, 4.22, 5.40, 4.60, 3.90, 4.01,
        3.60, 3.39, 3.72, 3.00, 4.01, 2.99, 2.53, 2.11, 1.91, 1.96, 2.53,
        1.94, 2.71, 2.14, 2.21, 6.82, 12.31, 18.83
    };

    // Create a map to associate port names with node indices
    unordered_map<string, int> portNodes;
    for (size_t i = 0; i < portNames.size(); ++i) {
        portNodes[portNames[i]] = i;
    }

    // Initialize all distances to infinity
    vector<double> portDistances(portNames.size(), numeric_limits<double>::max());

    // Create a priority queue for Dijkstra's algorithm
    priority_queue<Port, vector<Port>, ComparePort> pq;

    int sourceNode, targetNode;

    cout << "List of ports:" << endl;
    for (size_t i = 0; i < portNames.size(); ++i) {
        cout << i << ": " << portNames[i] << endl;
    }

    cout << "Enter the source port index (0 to " << portNames.size() - 1 << "): ";
    cin >> sourceNode;
    cout << "Enter the target port index (0 to " << portNames.size() - 1 << "): ";
    cin >> targetNode;

    if (sourceNode == targetNode) {
        cout << "Source and target ports are the same: " << portNames[sourceNode] << endl;
        return 0;
    }

    portDistances[sourceNode] = 0;
    pq.push({sourceNode, 0.0, portCargoCapacity[sourceNode], portContainerCapacity[sourceNode]});

    // Track the path to the target port
    vector<int> prevPort(portNames.size(), -1);

    // Implement Dijkstra's algorithm
    while (!pq.empty()) {
        Port current = pq.top();
        pq.pop();

        if (current.node == targetNode) {
            break; // Found the target port
        }

        for (size_t i = 0; i < portNames.size(); ++i) {
            if (i != current.node) {
                double newDistance = current.distance + haversineDistance(portCoordinates[current.node], portCoordinates[i]);
                if (newDistance < portDistances[i]) {
                    portDistances[i] = newDistance;
                    prevPort[i] = current.node;
                    pq.push({static_cast<int>(i), newDistance, portCargoCapacity[i], portContainerCapacity[i]});
                }
            }
        }
    }

    if (portDistances[targetNode] == numeric_limits<double>::max()) {
        cout << "No path found between " << portNames[sourceNode] << " and " << portNames[targetNode] << "." << endl;
    } else {
        cout << endl; // Blank line
        cout << "Target Port: " << portNames[targetNode] << endl;
        cout << endl; // Blank line
        cout << ""
                ""
                ""
                ""
                ""
                ""
                ""
                ""
                ""
                ""
                ""
                "Shortest distance between " << portNames[sourceNode] << " and " << portNames[targetNode] << ": "
             << fixed << setprecision(2) << portDistances[targetNode] << " kilometers" << endl;

        cout << endl; // Blank line
        cout << "Connecting Ports:" << endl;
        int currentPort = targetNode;
        vector<string> connectingPorts;
        vector<double> connectingDistances;
        while (currentPort != sourceNode) {
            connectingPorts.push_back(portNames[currentPort]);
            connectingDistances.push_back(haversineDistance(portCoordinates[currentPort], portCoordinates[prevPort[currentPort]]));
            currentPort = prevPort[currentPort];
        }
        for (int i = connectingPorts.size() - 1; i >= 0; --i) {
            cout << connectingPorts[i] << " (" << fixed << setprecision(2) << connectingDistances[i] << " km) <- ";
        }
        cout << portNames[sourceNode] << endl;

        cout << endl; // Blank line
        cout << "Source Port Cargo Capacity: " << fixed << setprecision(2) << portCargoCapacity[sourceNode] << " metric tons" << endl;
        cout << "Source Port Container Capacity: " << fixed << setprecision(2) << portContainerCapacity[sourceNode] << " TEUs" << endl;
        cout << "Target Port Cargo Capacity: " << fixed << setprecision(2) << portCargoCapacity[targetNode] << " metric tons" << endl;
        cout << "Target Port Container Capacity: " << fixed << setprecision(2) << portContainerCapacity[targetNode] << " TEUs" << endl;
    }

    return 0;
}