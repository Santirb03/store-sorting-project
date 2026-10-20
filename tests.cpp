#include <iostream>
#include <vector>

#include "producto.h"
#include "sorting.h"
#include "inventory.h"
#include <cassert>

using namespace std;

bool testOrdenamientoPrecio()
{
    vector<Producto> productos = {
        Producto(
            1,
            "Laptop",
            "Electronica",
            15000,
            5),

        Producto(
            2,
            "Mouse",
            "Electronica",
            500,
            20),

        Producto(
            3,
            "Monitor",
            "Electronica",
            5000,
            10)};

    mergeSort(
        productos,
        0,
        productos.size() - 1,
        1);

    return (
        productos[0].getPrecio() == 500 &&
        productos[1].getPrecio() == 5000 &&
        productos[2].getPrecio() == 15000);
}

bool testOrdenamientoStock()
{
    vector<Producto> productos = {
        Producto(
            1,
            "Laptop",
            "Electronica",
            15000,
            30),

        Producto(
            2,
            "Mouse",
            "Electronica",
            500,
            5),

        Producto(
            3,
            "Monitor",
            "Electronica",
            5000,
            15)};

    mergeSort(
        productos,
        0,
        productos.size() - 1,
        3);

    return (
        productos[0].getStock() == 5 &&
        productos[1].getStock() == 15 &&
        productos[2].getStock() == 30);
}

bool testInventario()
{
    vector<Producto> productos;

    // 1. Agregar un producto.
    Producto laptop(
        1, "Laptop", "Electronica", 15000, 5);

    assert(agregarProductoInventario(
        productos, laptop));

    assert(productos.size() == 1);

    // 2. Buscarlo por ID.
    assert(buscarProducto(productos, 1) == 0);

    // 3. Rechazar un ID duplicado.
    assert(!agregarProductoInventario(
        productos, laptop));

    assert(productos.size() == 1);

    // 4. Agregar otro producto.
    Producto mouse(
        2, "Mouse", "Electronica", 500, 20);

    assert(agregarProductoInventario(
        productos, mouse));

    // 5. Actualizar el precio y stock.
    Producto mouseActualizado(
        2, "Mouse Gamer", "Electronica", 750, 15);

    assert(actualizarProductoInventario(
        productos, mouseActualizado));

    int posicion = buscarProducto(productos, 2);

    assert(posicion != -1);
    assert(productos[posicion].getPrecio() == 750);
    assert(productos[posicion].getStock() == 15);

    // 6. Eliminar un producto.
    assert(eliminarProductoInventario(
        productos, 1));

    assert(buscarProducto(productos, 1) == -1);
    assert(productos.size() == 1);

    // 7. Rechazar la eliminacion inexistente.
    assert(!eliminarProductoInventario(
        productos, 999));

    // 8. Rechazar datos invalidos.
    Producto invalido(
        3, "Producto", "Prueba", -100, 5);

    assert(!agregarProductoInventario(
        productos, invalido));

    return true;
}

bool testMergeSortCasosLimite()
{
    // Vector vacio.
    vector<Producto> vacio;
    mergeSort(vacio, 0, -1, 1);
    assert(vacio.empty());

    // Un solo producto.
    vector<Producto> unico = {
        Producto(1, "Mouse", "Electronica", 500, 10)};

    mergeSort(unico, 0, 0, 1);
    assert(unico[0].getId() == 1);

    // Precios repetidos: comprobar estabilidad.
    vector<Producto> repetidos = {
        Producto(1, "A", "Test", 500, 3),
        Producto(2, "B", "Test", 200, 4),
        Producto(3, "C", "Test", 500, 5)};

    mergeSort(repetidos, 0, 2, 1);

    assert(repetidos[0].getId() == 2);
    assert(repetidos[1].getId() == 1);
    assert(repetidos[2].getId() == 3);

    // Ordenamiento por nombre.
    vector<Producto> nombres = {
        Producto(1, "Zebra", "Test", 100, 1),
        Producto(2, "Alpha", "Test", 200, 2)};

    mergeSort(nombres, 0, 1, 2);

    assert(nombres[0].getNombre() == "Alpha");

    // Ordenamiento por categoria.
    vector<Producto> categorias = {
        Producto(1, "A", "Ropa", 100, 1),
        Producto(2, "B", "Electronica", 200, 2)};

    mergeSort(categorias, 0, 1, 4);

    assert(categorias[0].getCategoria() == "Electronica");

    return true;
}

int main()
{
    cout << "TEST ORDENAMIENTO POR PRECIO: ";

    if (testOrdenamientoPrecio())
    {
        cout << "PASSED" << endl;
    }
    else
    {
        cout << "FAILED" << endl;
    }

    cout << "TEST ORDENAMIENTO POR STOCK: ";

    if (testOrdenamientoStock())
    {
        cout << "PASSED" << endl;
    }
    else
    {
        cout << "FAILED" << endl;
    }

    cout << "TEST INVENTARIO CRUD: ";

    if (testInventario())
        cout << "PASSED\n";
    else
        cout << "FAILED\n";

    cout << "TEST MERGE SORT CASOS LIMITE: ";

    if (testMergeSortCasosLimite())
        cout << "PASSED\n";
    else
        cout << "FAILED\n";

    return 0;
}