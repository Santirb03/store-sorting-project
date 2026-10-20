#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "producto.h"
#include "sorting.h"

using namespace std;

// Carga los productos desde un archivo CSV.
vector<Producto> cargarProductos(
    const string &nombreArchivo)
{
    vector<Producto> productos;

    ifstream archivo(nombreArchivo);

    if (!archivo.is_open())
    {
        cout << "Error: no se pudo abrir el archivo "
             << nombreArchivo << endl;

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

bool guardarProductos(
    const vector<Producto> &productos,
    const string &nombreArchivo)
{
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open())
    {
        cout << "Error: no se pudo abrir el archivo "
             << nombreArchivo << endl;

        return false;
    }

    // Escribir encabezados del CSV
    archivo << "id,nombre,categoria,precio,stock\n";

    // Recorrer y escribir todos los productos
    for (const Producto &producto : productos)
    {
        archivo << producto.getId() << ","
                << producto.getNombre() << ","
                << producto.getCategoria() << ","
                << producto.getPrecio() << ","
                << producto.getStock() << "\n";
    }

    archivo.close();

    if (archivo.fail())
    {
        cout << "Error al guardar los productos.\n";
        return false;
    }

    return true;
}

void mostrarProductos(
    const vector<Producto> &productos)
{
    cout << endl;

    cout << "============================================================"
         << endl;

    cout
        << "ID | Nombre | Categoria | Precio | Stock"
        << endl;

    cout << "============================================================"
         << endl;

    for (const Producto &producto : productos)
    {
        producto.mostrar();
    }

    cout << "============================================================"
         << endl;
}

// Ordena los productos usando Merge Sort.
void ordenarProductos(
    vector<Producto> &productos,
    int criterio)
{
    if (!productos.empty())
    {
        mergeSort(
            productos,
            0,
            static_cast<int>(productos.size()) - 1,
            criterio);
    }
}

int main()
{
    vector<Producto> productos =
        cargarProductos("productos.csv");

    if (productos.empty())
    {
        cout << "No se cargaron productos." << endl;
        return 1;
    }

    int opcion = 0;

    do
    {
        cout << endl;
        cout << "======================================" << endl;
        cout << "     SISTEMA DE PRODUCTOS" << endl;
        cout << "======================================" << endl;

        cout << "1. Mostrar productos" << endl;
        cout << "2. Ordenar por precio" << endl;
        cout << "3. Ordenar por nombre" << endl;
        cout << "4. Ordenar por stock" << endl;
        cout << "5. Ordenar por categoria" << endl;
        cout << "6. Guardar productos en CSV" << endl;
        cout << "7. Salir" << endl;

        cout << endl;
        cout << "Selecciona una opcion: ";

        cin >> opcion;

        switch (opcion)
        {

        case 1:
            mostrarProductos(productos);
            break;

        case 2:
            ordenarProductos(productos, 1);

            cout << endl;
            cout << "Productos ordenados por precio:"
                 << endl;

            mostrarProductos(productos);
            break;

        case 3:
            ordenarProductos(productos, 2);

            cout << endl;
            cout << "Productos ordenados por nombre:"
                 << endl;

            mostrarProductos(productos);
            break;

        case 4:
            ordenarProductos(productos, 3);

            cout << endl;
            cout << "Productos ordenados por stock:"
                 << endl;

            mostrarProductos(productos);
            break;

        case 5:
            ordenarProductos(productos, 4);

            cout << endl;
            cout << "Productos ordenados por categoria:"
                 << endl;

            mostrarProductos(productos);
            break;

        case 6:
            cout << endl;

            if (guardarProductos(productos, "productos.csv"))
            {
                cout << "Productos guardados correctamente."
                     << endl;
            }
            else
            {
                cout << "No se pudieron guardar los productos."
                     << endl;
            }

            break;

        case 7:
            cout << endl;
            cout << "Saliendo del programa..." << endl;
            break;

        default:
            cout << endl;
            cout << "Opcion invalida. Intenta nuevamente."
                 << endl;
        }

    } while (opcion != 7);

    return 0;
}