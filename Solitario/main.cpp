#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <random>
#include <algorithm>

class Carta {
private:
    std::string valor; // Valor de la carta
    std::string palo; // que tipo de carta es
    std::string color; // color de carta

// Creando constructores
public:
    Carta(std::string val, std::string pal, std::string col) : valor(val), palo(pal), color(col) {}
    Carta() : valor(""), palo(""), color("") {}

    std::string obtenerPartePosterior() const {
        return "xxxx";
    }

    std::string obtenerRepresentacion() const {
        return valor + palo + color;
    }

    std::string obtenerValor() const{
        return valor;
    }

    std::string obtenerColor() const {
        return color;
    }
};

// Creando cartas
const std::string valores[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
const std::string palos[] = {"<3R", "<>R", "E3N", "!!N"};

// Movimiento de cartas
class Baraja {
private:
    std::vector<Carta> cartas;

public:
    Baraja() {
        for (const auto& palo : palos) {
            for (const auto& valor : valores) {
                cartas.push_back(Carta(valor, palo.substr(0, 2), palo.substr(2)));
            }
        }
    }
    void mezclar() {
        std::shuffle(cartas.begin(), cartas.end(), std::mt19937(std::random_device()()));
    }
    Carta sacarCarta() {
        Carta carta = cartas.back();
        cartas.pop_back();
        return carta;
    }
    bool estaVacia() const {
        return cartas.empty();
    }
};
// Llenar cola
void llenarCola(std::queue<Carta>& cola, Baraja& baraja, int cantidad) {
    for (int i = 0; i < cantidad; ++i) {
        cola.push(baraja.sacarCarta());
    }
}
// Funcion Llenar pila
void llenarPila(std::stack<Carta>& pila, Baraja& baraja, int cantidad) {
    for (int i = 0; i < cantidad; ++i) {
        pila.push(baraja.sacarCarta());
    }
}
// Funcion Lista de las cartas volteadas
void mostrarPartePosterior(const std::queue<Carta>& cola) {
    std::cout << "\nColacarta: ";
    for (int i = 0; i < static_cast<int>(cola.size()); ++i) {
        std::cout << "xxxx ";
    }
    std::cout << std::endl;
}
// Funcion Revelar cartas
void mostrarcartas(const std::vector<std::stack<Carta>>& columnas) {
    // Mostrar las columnas con la carta superior revelada
    for (int i = 0; i < 7; ++i) {
        std::cout << "Columna " << i + 1 << ": ";
        // Crear una copia de la pila actual para evitar modificar la original
        std::stack<Carta> pila_temp = columnas[i];
        // Verificar si la pila de la columna actual está vacia
        if (pila_temp.empty()) {
            std::cout << "xxxx ";
        } else {
            // Cartas ocultas
            for (int j = 0; j < i; ++j)
                std::cout << "xxxx ";
            // Carta revelada *********************************************************************
            std::cout << pila_temp.top().obtenerRepresentacion() << " ";
            pila_temp.pop();
        }
        // Cartas ocultas restantes
        for (int j = i + 1; j < 7; ++j)
            std::cout << "     ";
        std::cout << std::endl;
    }
}
// Funcion buscar cartas
void buscarCarta(std::queue<Carta>& cola, std::vector<Carta>& cartasReveladas) {
    if (!cola.empty()) {
        Carta carta = cola.front();
        cola.pop();
        cartasReveladas.push_back(carta);
        std::cout << " \n\t Carta Encontrada: " << carta.obtenerRepresentacion() << " ";
    }
}
//Funcion revelar las cartas
void mostrarCartasReveladas(const std::vector<Carta>& cartasReveladas) {
    std::cout << "Cartas reveladas: ";
    for (const auto& carta : cartasReveladas) {
        std::cout << carta.obtenerRepresentacion() << " ";
    }
    std::cout << std::endl;
}
// Funcion para mover las cartas en las columnas
void moverCartaEntreColumnas(std::vector<std::stack<Carta>>& columnas) {
    int origen, destino;
    std::cout << "Seleccione la columna de origen (1-7): ";
    std::cin >> origen;
    std::cout << "Seleccione la columna de destino (1-7): ";
    std::cin >> destino;
    origen--; // Ajustar al indice del vector (0-6)
    destino--;
    // Verificar si las columnas seleccionadas son validas
    if (origen < 0 || origen >= 7 || destino < 0 || destino >= 7) {
        std::cout << "Columnas seleccionadas no validas. Intente de nuevo." << std::endl;
        return;
    }
    // Verificar si la columna de origen está vacia
    if (columnas[origen].empty()) {
        std::cout << "La columna de origen esta vacia." << std::endl;
        return;
    }
    // Obtener la carta de origen
    Carta cartaOrigen = columnas[origen].top();

    // Verificar si la columna de destino esta vacia o si el movimiento es valido
    if (columnas[destino].empty() || (columnas[destino].top().obtenerValor() == "K" && cartaOrigen.obtenerValor() == "Q")
        || (columnas[destino].top().obtenerValor() == "Q" && cartaOrigen.obtenerValor() == "J") || (columnas[destino].top().obtenerValor() == "J" && cartaOrigen.obtenerValor() == "10")
        || (columnas[destino].top().obtenerValor() == "10" && cartaOrigen.obtenerValor() == "9") || (columnas[destino].top().obtenerValor() == "9" && cartaOrigen.obtenerValor() == "8")
        || (columnas[destino].top().obtenerValor() == "8" && cartaOrigen.obtenerValor() == "7") || (columnas[destino].top().obtenerValor() == "7" && cartaOrigen.obtenerValor() == "6")
        || (columnas[destino].top().obtenerValor() == "6" && cartaOrigen.obtenerValor() == "5") || (columnas[destino].top().obtenerValor() == "5" && cartaOrigen.obtenerValor() == "4")
        || (columnas[destino].top().obtenerValor() == "4" && cartaOrigen.obtenerValor() == "3") || (columnas[destino].top().obtenerValor() == "3" && cartaOrigen.obtenerValor() == "2")
        || (columnas[destino].top().obtenerValor() == "2" && cartaOrigen.obtenerValor() == "A")) {
        // Mover la carta de la columna de origen a la de destino
        std::cout << " \n\t**** Movimiento Exitoso ****\n" << std::endl;
        columnas[destino].push(cartaOrigen);
        columnas[origen].pop();
    } else {
        std::cout << "\n\t ----Movimiento no valido----\n" << std::endl;
    }
}

int main() {
    std::queue<Carta> cola;
    std::vector<std::stack<Carta>> columnas(7);
    std::vector<std::vector<Carta>> guardarcartas;
    Baraja baraja;
    char opcion;
    std::vector<Carta> cartasReveladas;
    int cartasBuscadas = 0;

    do {
        if (cartasBuscadas >= 24) {
            std::cout << "Ya has encontrado todas las cartas.\n";
            std::cout << "Deseas repetir la busqueda (r)";
            std::cin >> opcion;
            if (opcion == 'r') {
                if (!cartasReveladas.empty()) {
                    cola = std::queue<Carta>(); // Reiniciar la cola
                    for (const auto& carta : cartasReveladas) {
                        cola.push(carta); // Llenar la cola con las cartas encontradas
                        cartasReveladas.clear(); // vacia las cartas reveladas
                    }
                    cartasBuscadas = 0; // Reiniciar el contador de cartas encontradas
                } else {
                    std::cout << "No hay cartas reveladas para repetir la busqueda.\n";
                }
            } else if (opcion == 'q') {
                std::cout << "--GRACIAS POR JUGAR--\n";
                return 0;
            } else {
                std::cout << "Opcion no valida. Intente de nuevo.\n";
            }
        }
        if (cola.empty()) {
            baraja.mezclar();
            llenarCola(cola, baraja, 24);
            for (int i = 0; i < 7; ++i) {
                llenarPila(columnas[i], baraja, 7 - i);
            }
        }
        mostrarPartePosterior(cola);
        mostrarCartasReveladas(cartasReveladas);
        std::cout << "-----------------------------------------------------------------------------------------------------------------\n";
        mostrarcartas(columnas);

        std::cout << "Opciones:\n";
        std::cout << "  b - Buscar carta\n";
        std::cout << "  m - Mover carta entre columnas\n";
        std::cout << "  q - Salir\n";
        std::cout << "Ingrese su opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 'b':
                if (cartasBuscadas < 24) {
                    buscarCarta(cola, cartasReveladas);
                    std::cout << std::endl;
                    cartasBuscadas++;
                } else {
                    std::cout << "Ya has encontrado todas las cartas.\n";
                }
                break;
            case 'm':
                moverCartaEntreColumnas(columnas);
                //mostrarcartas(columnas);
                break;
            case 'q':
                std::cout << "--GRACIAS POR JUGAR--\n";
                return 0;
            default:
                std::cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 'q');

    return 0;
}