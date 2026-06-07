#include <iostream>
#include <string>
using namespace std;

/**
 * @struct Producto
 * @brief  Representa un articulo disponible en el catalogo de la tienda.
 */
struct Producto {
    int    id;       ///< Identificador unico del producto
    string nombre;   ///< Nombre descriptivo del producto
    double precio;   ///< Precio unitario en pesos mexicanos
    int    stock;    ///< Unidades disponibles en inventario
};

/**
 * @struct ItemCarrito
 * @brief  Representa un producto que el cliente agrego al carrito de compras.
 */
struct ItemCarrito {
    int    idProducto; ///< ID del producto seleccionado
    string nombre;     ///< Nombre del producto al momento de agregar
    double precio;     ///< Precio unitario al momento de agregar
    int    cantidad;   ///< Cantidad de unidades seleccionadas
};

const int MAX_PRODUCTOS = 10; ///< Capacidad maxima del catalogo
const int MAX_CARRITO   = 10; ///< Capacidad maxima del carrito

/// Catalogo global de productos disponibles
Producto catalogo[MAX_PRODUCTOS] = {
    {1, "Laptop Gamer",        18999.99, 5},
    {2, "Mouse Inalambrico",     449.00, 20},
    {3, "Teclado Mecanico",    1299.00, 12},
    {4, "Monitor 24\" FHD",   4500.00,  8},
    {5, "Audifonos Bluetooth",  899.00, 15},
};
int totalProductos = 5; ///< Numero de productos cargados en el catalogo

/// Arreglo global del carrito de compras
ItemCarrito carrito[MAX_CARRITO];
int totalCarrito = 0; ///< Numero de items actualmente en el carrito

// ─────────────────────────────────────────────────────────────
// FUNCIONES
// ─────────────────────────────────────────────────────────────

/**
 * @brief  Muestra el menu principal de la tienda en consola.
 *
 * Imprime las opciones disponibles para el usuario:
 * ver catalogo, agregar al carrito y salir.
 * No recibe parametros ni retorna valor.
 *
 * @pre    Ninguna.
 * @post   El menu es impreso en stdout. No modifica ninguna variable.
 *
 * @note   Complejidad tiempo: O(1) | Complejidad espacio: O(1)
 */
void mostrarMenu() {
    cout << "\n=== TechStore MX ===\n";
    cout << "1. Ver productos\n";
    cout << "2. Agregar al carrito\n";
    cout << "3. Ver carrito\n";
    cout << "0. Salir\n";
    cout << "Opcion: ";
}

/**
 * @brief  Recorre e imprime todos los productos del catalogo.
 *
 * Itera sobre el arreglo global 'catalogo' desde el indice 0
 * hasta 'totalProductos - 1', mostrando id, nombre, precio
 * y stock de cada producto.
 *
 * @pre    totalProductos >= 0.
 * @post   Los productos son impresos en stdout. No modifica datos.
 *
 * @note   Complejidad tiempo: O(n) donde n = totalProductos
 * @note   Complejidad espacio: O(1)
 */
void mostrarProductos() {
    cout << "\n--- Catalogo ---\n";
    for (int i = 0; i < totalProductos; i++) {
        cout << "[" << catalogo[i].id << "] "
             << catalogo[i].nombre
             << " - $" << catalogo[i].precio
             << " (Stock: " << catalogo[i].stock << ")\n";
    }
}

/**
 * @brief  Permite al usuario seleccionar un producto y agregarlo
 *         al carrito de compras.
 *
 * Flujo interno:
 *   1. Llama a mostrarProductos() para mostrar el catalogo.
 *   2. Lee el ID del producto deseado desde stdin.
 *   3. Busca linealmente el producto en 'catalogo'.
 *   4. Valida existencia y disponibilidad de stock.
 *   5. Lee la cantidad deseada y la valida contra el stock.
 *   6. Inserta el item en 'carrito' y descuenta stock.
 *
 * @pre    totalCarrito < MAX_CARRITO.
 * @post   Si exitoso: carrito[totalCarrito] queda inicializado,
 *         totalCarrito se incrementa en 1 y el stock se reduce.
 *
 * @note   Complejidad tiempo: O(n) donde n = totalProductos (busqueda lineal)
 * @note   Complejidad espacio: O(1)
 */
void agregarAlCarrito() {
    mostrarProductos();

    int id, cantidad;
    cout << "\nID del producto: ";
    cin >> id;

    // Busqueda lineal del producto por ID
    int idx = -1;
    for (int i = 0; i < totalProductos; i++) {
        if (catalogo[i].id == id) { idx = i; break; }
    }

    if (idx == -1) {
        cout << "[!] Producto no encontrado.\n";
        return;
    }
    if (catalogo[idx].stock == 0) {
        cout << "[!] Sin stock disponible.\n";
        return;
    }

    cout << "Cantidad: ";
    cin >> cantidad;

    if (cantidad <= 0 || cantidad > catalogo[idx].stock) {
        cout << "[!] Cantidad invalida.\n";
        return;
    }

    carrito[totalCarrito] = {id, catalogo[idx].nombre, catalogo[idx].precio, cantidad};
    totalCarrito++;
    catalogo[idx].stock -= cantidad;

    cout << "[OK] " << catalogo[idx].nombre << " x" << cantidad << " agregado.\n";
}

/**
 * @brief  Punto de entrada del programa.
 *
 * Ejecuta un bucle do-while que muestra el menu principal y
 * despacha la opcion elegida mediante un switch. El bucle
 * termina cuando el usuario ingresa la opcion 0 (Salir).
 *
 * @return 0 si el programa termina correctamente.
 *
 * @note   Complejidad tiempo: O(k * n) donde k = iteraciones del menu,
 *         n = totalProductos (por las funciones internas)
 * @note   Complejidad espacio: O(1)
 */
int main() {
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1: mostrarProductos(); break;
            case 2: agregarAlCarrito(); break;
            case 0: cout << "Hasta luego!\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);

    return 0;
}