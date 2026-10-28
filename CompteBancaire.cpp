
#include <iostream>
#include <string>
#include <algorithm>
#include <utility>

class CompteBancaire {
private:
    std::string numero;
    double solde;
    std::string* historique;
    std::size_t capacite;
    std::size_t nbOps;

    void agrandirHistorique() {
        std::size_t nouvelleCap = (capacite == 0) ? 10 : capacite * 2;
        std::string* nouveau = new std::string[nouvelleCap];

        std::copy(historique, historique + nbOps, nouveau);

        delete[] historique;
        historique = nouveau;
        capacite = nouvelleCap;
    }

    void ajouterOperation(const std::string& op) {
        if (nbOps == capacite) {
            agrandirHistorique();
        }
        historique[nbOps++] = op;
    }

public:
    // Constructeur par défaut
    CompteBancaire()
        : numero("NON_DEFINI"), solde(0.0),
          historique(new std::string[10]),
          capacite(10), nbOps(0) {}

    // Constructeur paramétré
    CompteBancaire(const std::string& num, double s)
        : numero(num), solde(s),
          historique(new std::string[10]),
          capacite(10), nbOps(0) {
        ajouterOperation("Creation du compte : solde " + std::to_string(s));
    }

    // Constructeur de copie
    CompteBancaire(const CompteBancaire& other)
        : numero(other.numero), solde(other.solde),
          historique(new std::string[other.capacite]),
          capacite(other.capacite), nbOps(other.nbOps) {
        std::copy(other.historique,
                  other.historique + nbOps,
                  historique);
    }

    // Constructeur de déplacement
    CompteBancaire(CompteBancaire&& other) noexcept
        : numero(std::move(other.numero)),
          solde(other.solde),
          historique(other.historique),
          capacite(other.capacite),
          nbOps(other.nbOps) {
        other.historique = nullptr;
        other.capacite = 0;
        other.nbOps = 0;
        other.solde = 0.0;
    }

    // Destructeur
    ~CompteBancaire() {
        delete[] historique;
    }

    // Dépôt
    void deposer(double montant) {
        if (montant <= 0) {
            std::cerr << "Montant de depot invalide\n";
            return;
        }

        solde += montant;
        ajouterOperation("Depot de " + std::to_string(montant));
    }

    // Retrait
    void retirer(double montant) {
        if (montant <= 0 || montant > solde) {
            std::cerr << "Retrait impossible\n";
            return;
        }

        solde -= montant;
        ajouterOperation("Retrait de " + std::to_string(montant));
    }

    // Affichage
    void afficher() const {
        std::cout << "Compte " << numero
                  << " - Solde : " << solde << '\n';

        std::cout << "Historique des operations :\n";

        for (std::size_t i = 0; i < nbOps; ++i) {
            std::cout << "  " << historique[i] << '\n';
        }
    }
};

int main() {
    CompteBancaire c1("FR123456", 500.0);

    c1.deposer(200);
    c1.retirer(150);
    c1.afficher();

    std::cout << "\n--- Copie ---\n";
    CompteBancaire c2 = c1;
    c2.afficher();

    std::cout << "\n--- Deplacement ---\n";
    CompteBancaire c3 = std::move(c1);
    c3.afficher();

    return 0;
}
