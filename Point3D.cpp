
#include <iostream>
using namespace std;

class Point3D {
private:
    const double x;
    const double y;
    const double z;

public:
    // Constructeur avec liste d'initialisation
    Point3D(double a, double b, double c)
        : x(a), y(b), z(c) {
    }

    // Accesseurs
    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    double getZ() const {
        return z;
    }
};

int main() {
    Point3D p(1.0, 2.0, 3.0);

    cout << "Coordonnees : ("
         << p.getX() << ", "
         << p.getY() << ", "
         << p.getZ() << ")" << endl;

    return 0;
}
