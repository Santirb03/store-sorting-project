#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "producto.h"
#include "sorting.h"

using namespace std;

vector<Producto> cargarProductos(string nombreArchivo)
{

    vector<Producto> productos;

    ifstream archivo(nombreArchivo);

    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo." << endl;
        return productos;
    }

    string linea;

    getline(archivo, linea);

    while (getline(archivo, linea))
    {

        stringstream ss(linea);

        string idStr;
        string nombre;
        string categoria;
        string precioStr;
        string stockStr;

        getline(ss, idStr, ',');
        getline(ss, nombre, ',');
        getline(ss, categoria, ',');
        getline(ss, precioStr, ',');
        getline(ss, stockStr, ',');

        int id = stoi(idStr);
        double precio = stod(precioStr);
        int stock = stoi(stockStr);

        Producto producto(
            id,
            nombre,
            categoria,
            precio,
            stock);

        productos.push_back(producto);
    }

    archivo.close();

    return productos;
}

int main()
{

    // 1. Cargar productos desde el CSV
    vector<Producto> productos =
        cargarProductos("productos.csv");

    cout << "Productos cargados: "
         << productos.size() << endl;

    // 2. Mostrar productos antes de ordenar
    cout << "\nProductos originales:\n";

    for (const Producto &producto : productos)
    {
        producto.mostrar();
    }

    // 3. Ordenar los productos por precio
    mergeSort(
        productos,
        0,
        productos.size() - 1);

    // 4. Mostrar productos ya ordenados
    cout << "\nProductos ordenados por precio:\n";

    for (const Producto &producto : productos)
    {
        producto.mostrar();
    }

    return 0;
}