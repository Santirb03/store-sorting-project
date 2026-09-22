#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <iostream>
#include <string>

using namespace std;

class Producto
{
private:
    int id;
    string nombre;
    string categoria;
    double precio;
    int stock;

public:
    Producto()
    {
        id = 0;
        nombre = "";
        categoria = "";
        precio = 0;
        stock = 0;
    }

    Producto(int _id, string _nombre, string _categoria,
             double _precio, int _stock)
    {
        id = _id;
        nombre = _nombre;
        categoria = _categoria;
        precio = _precio;
        stock = _stock;
    }

    int getId() const
    {
        return id;
    }

    string getNombre() const
    {
        return nombre;
    }

    string getCategoria() const
    {
        return categoria;
    }

    double getPrecio() const
    {
        return precio;
    }

    int getStock() const
    {
        return stock;
    }

    void mostrar() const
    {
        cout << id << " | "
             << nombre << " | "
             << categoria << " | $"
             << precio << " | Stock: "
             << stock << endl;
    }
};

#endif