
#ifndef PRODUCTO_H
#define PRODUCTO_H

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
    // Constructores
    Producto();

    Producto(
        int _id,
        string _nombre,
        string _categoria,
        double _precio,
        int _stock);

    // Metodos de acceso
    int getId() const;
    string getNombre() const;
    string getCategoria() const;
    double getPrecio() const;
    int getStock() const;

    void setPrecio(double nuevoPrecio);
    void setStock(int nuevoStock);

    // Mostrar informacion
    void mostrar() const;
};

#endif
