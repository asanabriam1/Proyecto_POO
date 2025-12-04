#include <iostream>
using namespace std;

/**
 * @brief Representa un barco dentro del tablero.
 *
 * La clase Barco contiene la posición inicial (x, y),
 * el tamaño en casillas y la cantidad de impactos recibidos.
 */
class Barco {
public:
    int x;          /**< Fila donde inicia el barco */
    int y;          /**< Columna donde inicia el barco */
    int tamaño;     /**< Cuántas casillas ocupa */
    int impactos;   /**< Cuántas veces fue golpeado */

    /**
     * @brief Constructor que inicializa un barco con su posición y tamaño.
     * @param fila Coordenada de fila inicial.
     * @param columna Coordenada de columna inicial.
     * @param tam Tamaño del barco (número de casillas que ocupa).
     */
    Barco(int fila = 0, int columna = 0, int tam = 0) {
        x = fila;
        y = columna;
        tamaño = tam;
        impactos = 0;
    }
};

/**
 * @brief Representa el tablero del juego Batalla Naval.
 *
 * La clase Tablero contiene una matriz de 10x10, tres barcos
 * y los métodos necesarios para mostrar el tablero y realizar disparos.
 */
class Tablero {
public:
    int celdas[10][10];  /**< Matriz que representa el mar (0=agua, 1=barco, 2=impacto) */
    Barco barcos[3];     /**< Arreglo con los tres barcos del tablero */
    int barcosHundidos;  /**< Contador de barcos destruidos */

    /**
     * @brief Constructor que inicializa el tablero y coloca los barcos.
     */
    Tablero() {
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                celdas[i][j] = 0;

        barcosHundidos = 0;

        // Crear los tres barcos del tablero
        barcos[0] = Barco(1, 1, 2);
        barcos[1] = Barco(4, 4, 3);
        barcos[2] = Barco(7, 7, 4);

        // Colocar los barcos horizontalmente
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < barcos[i].tamaño; j++) {
                celdas[barcos[i].x][barcos[i].y + j] = 1;
            }
        }
    }

    /**
     * @brief Muestra el tablero actual con los valores de cada celda.
     */
    void mostrar() {
        cout << "\nTABLERO:\n";
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                cout << celdas[i][j] << " ";
            }
            cout << endl;
        }
    }

    /**
     * @brief Permite disparar a una posición del tablero.
     * @param fila Coordenada de fila a disparar.
     * @param columna Coordenada de columna a disparar.
     */
    void disparar(int fila, int columna) {
        if (celdas[fila][columna] == 1) {
            cout << "Barco impactado.\n";
            celdas[fila][columna] = 2;

            for (int i = 0; i < 3; i++) {
                if (fila == barcos[i].x &&
                    columna >= barcos[i].y &&
                    columna < barcos[i].y + barcos[i].tamaño) {

                    barcos[i].impactos++;
                    if (barcos[i].impactos == barcos[i].tamaño) {
                        cout << "Barco hundido.\n";
                        barcosHundidos++;
                    }
                }
            }
        }
        else if (celdas[fila][columna] == 2) {
            cout << "Ya habías disparado ahí.\n";
        }
        else {
            cout << "Agua.\n";
        }
    }

    /**
     * @brief Verifica si todos los barcos han sido destruidos.
     * @return true si todos los barcos están hundidos.
     */
    bool todosHundidos() {
        return barcosHundidos == 3;
    }
};

/**
 * @brief Controla el flujo principal del juego Batalla Naval.
 *
 * La clase Juego gestiona la interacción del usuario, mostrando el tablero
 * y permitiendo disparar hasta que todos los barcos sean destruidos.
 */
class Juego {
public:
    Tablero tablero;  /**< Objeto tablero que contiene los barcos y la lógica del juego */

    /**
     * @brief Inicia el juego e interactúa con el jugador.
     */
    void iniciar() {
        cout << "Bienvenido a Batalla Naval\n";

        while (!tablero.todosHundidos()) {
            tablero.mostrar();

            int fila, columna;
            cout << "\nIngresa fila (0-9): ";
            cin >> fila;
            cout << "Ingresa columna (0-9): ";
            cin >> columna;

            if (fila < 0 || fila > 9 || columna < 0 || columna > 9) {
                cout << "Coordenadas incorrectas.\n";
                continue;
            }

            tablero.disparar(fila, columna);
        }

        cout << "\n¡Ganaste! Hundiste todos los barcos.\n";
    }
};

/**
 * @brief Función principal que crea un objeto de tipo Juego y lo inicia.
 * @return int 0 al finalizar correctamente el programa.
 */
int main() {
    Juego juego;
    juego.iniciar();
    return 0;
}

