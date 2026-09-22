#include <iostream>
#include <vector>

#include "producto.h"
#include "sorting.h"

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

    return 0;
}