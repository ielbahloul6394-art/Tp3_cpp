
#include <iostream>
#include <algorithm>
#include <utility>
#include <cstddef>

class Buffer {
private:
    char* data;
    std::size_t taille;

public:
    // Constructeur par defaut
    Buffer() : data(nullptr), taille(0) {
        std::cout << "Buffer vide cree" << std::endl;
    }

    // Constructeur parametre
    explicit Buffer(std::size_t t)
        : data(t > 0 ? new char[t]() : nullptr), taille(t) {
        std::cout << "Buffer de " << taille
                  << " octets cree" << std::endl;
    }

    // Constructeur de copie
    Buffer(const Buffer& other)
        : data(other.taille > 0 ? new char[other.taille] : nullptr),
          taille(other.taille) {
        if (taille > 0) {
            std::copy(other.data, other.data + taille, data);
        }
        std::cout << "Constructeur de copie du buffer" << std::endl;
    }

    // Constructeur de deplacement
    Buffer(Buffer&& other) noexcept
        : data(other.data), taille(other.taille) {
        other.data = nullptr;
        other.taille = 0;
        std::cout << "Constructeur de deplacement du buffer" << std::endl;
    }

    // Operateur d'assignation de copie
    Buffer& operator=(const Buffer& other) {
        if (this != &other) {
            char* nouveau = other.taille > 0
                ? new char[other.taille]
                : nullptr;

            if (other.taille > 0) {
                std::copy(other.data, other.data + other.taille, nouveau);
            }

            delete[] data;
            data = nouveau;
            taille = other.taille;
        }
        return *this;
    }

    // Operateur d'assignation de deplacement
    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data;

            data = other.data;
            taille = other.taille;

            other.data = nullptr;
            other.taille = 0;
        }
        return *this;
    }

    // Destructeur
    ~Buffer() {
        delete[] data;
        std::cout << "Destruction du buffer" << std::endl;
    }

    // Methodes d'acces
    char* getData() const {
        return data;
    }

    std::size_t getTaille() const {
        return taille;
    }
};

int main() {
    Buffer b1(128);             // Allocation
    Buffer b2 = b1;             // Copie
    Buffer b3 = std::move(b1);  // Deplacement

    b2 = b3;                    // Assignation de copie
    b3 = Buffer(64);            // Assignation de deplacement

    std::cout << "Taille de b2 : " << b2.getTaille() << std::endl;
    std::cout << "Taille de b3 : " << b3.getTaille() << std::endl;

    return 0;
}
