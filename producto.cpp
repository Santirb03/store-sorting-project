
#include "producto.h"
#include <iostream>

using namespace std;

// Constructor por defecto
Producto::Producto()
{
    id = 0;
    nombre = "";
    categoria = "";
    precio = 0.0;
    stock = 0;
}

// Constructor con parametros
Producto::Producto(
    int _id,
    string _nombre,
    string _categoria,
    double _precio,
    int _stock)
{
    id = _id;
    nombre = _nombre;
    categoria = _categoria;
    precio = _precio;
    stock = _stock;
}

// Obtener ID
int Producto::getId() const
{
    return id;
}

// Obtener nombre
string Producto::getNombre() const
{
    return nombre;
}

// Obtener categoria
string Producto::getCategoria() const
{
    return categoria;
}

// Obtener precio
double Producto::getPrecio() const
{
    return precio;
}

// Obtener stock
int Producto::getStock() const
{
    return stock;
}

// Mostrar informacion del producto
void Producto::mostrar() const
{
    cout
        << id << " | "
        << nombre << " | "
        << categoria << " | $"
        << precio << " | Stock: "
        << stock << endl;
}
