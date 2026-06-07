#include <iostream>
#include <string>
using namespace std;

struct Producto {
    int    id;
    string nombre;
    double precio;
    int    stock;
};

struct ItemCarrito {
    int idProducto;
    string nombre;
    double precio;
    int cantidad;
};

const int MAX_PRODUCTOS = 10;
const int MAX_CARRITO   = 10;

Producto catalogo[MAX_PRODUCTOS] = {
    {1, "Laptop Gamer",        18999.99, 5},
    {2, "Mouse Inalambrico",     449.00, 20},
    {3, "Teclado Mecanico",    1299.00, 12},
    {4, "Monitor 24\" FHD",   4500.00,  8},
    {5, "Audifonos Bluetooth",  899.00, 15},
};
int totalProductos = 5;

ItemCarrito carrito[MAX_CARRITO];
int totalCarrito = 0;

void mostrarMenu() {
    cout << "\n=== TechStore MX ===\n";
    cout << "1. Ver productos\n";
    cout << "2. Agregar al carrito\n";
    cout << "3. Ver carrito\n";
    cout << "0. Salir\n";
    cout << "Opcion: ";
}

// ─── Función 2: mostrarProductos ──────────────────────────
void mostrarProductos() {
    cout << "\n--- Catalogo ---\n";
    for (int i = 0; i < totalProductos; i++) {
        cout << "[" << catalogo[i].id << "] "
             << catalogo[i].nombre
             << " - $" << catalogo[i].precio
             << " (Stock: " << catalogo[i].stock << ")\n";
    }
}

void agregarAlCarrito() {
    mostrarProductos();

    int id, cantidad;
    cout << "\nID del producto: ";
    cin >> id;

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

// ─── Main ──────────────────────────────────────────────────
int main() {
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1: mostrarProductos();   break;
            case 2: agregarAlCarrito();   break;
            case 0: cout << "Hasta luego!\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);

    return 0;
}