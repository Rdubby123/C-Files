#include <iostream>

void computeDotProduct(int x1, int y1, int z1, int x2, int y2, int z2);
void computeCrossProduct(int x1, int y1, int z1, int x2, int y2, int z2);

int main() {
    int x1, x2, y1, y2, z1, z2;
    std::cout << "Enter your vectors for cross and dot product calculations:\n";
    std::cout << "x1 = ";
    std::cin >> x1;
    std::cout << "y1 = ";
    std::cin >> y1;
    std::cout << "z1 = ";
    std::cin >> z1;
    std::cout << "x2 = ";
    std::cin >> x2;
    std::cout << "y2 = ";
    std::cin >> y2;
    std::cout << "z2 = ";
    std::cin >> z2;

    computeDotProduct(x1,y1,z1,x2,y2,z2);
    computeCrossProduct(x1,y1,z1,x2,y2,z2);

    return 0;
}

// One-Liners 
void computeDotProduct(int x1, int y1, int z1, int x2, int y2, int z2){
    std::cout << "The Dot Product is " << (x1 * x2 + y1 * y2 + z1 * z2) << "!\n"; 
}

void computeCrossProduct(int x1, int y1, int z1, int x2, int y2, int z2){
    std::cout << "The Cross Product is: (" << (y1 * z2 - z1 * y2) << ", " << (z1 * x2 - x1 * z2) << ", " << (x1 * y2 - y1 * x2) << ")\n";
}
