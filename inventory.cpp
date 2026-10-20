
#include "inventory.h"

int buscarProducto(
    const std::vector<Producto> &productos,
    int id)
{
    for (int i = 0;
         i < static_cast<int>(productos.size()); ++i)
    {
        if (productos[i].getId() == id)
            return i;
    }
    return -1;
}

bool agregarProductoInventario(
    std::vector<Producto> &productos,
    const Producto &nuevo)
{
    if (nuevo.getId() <= 0 ||
        nuevo.getNombre().empty() ||
        nuevo.getCategoria().empty() ||
        nuevo.getPrecio() < 0 ||
        nuevo.getStock() < 0 ||
        buscarProducto(productos, nuevo.getId()) != -1)
        return false;

    productos.push_back(nuevo);
    return true;
}

bool actualizarProductoInventario(
    std::vector<Producto> &productos,
    const Producto &actualizado)
{
    int posicion = buscarProducto(
        productos, actualizado.getId());

    if (posicion == -1 ||
        actualizado.getNombre().empty() ||
        actualizado.getCategoria().empty() ||
        actualizado.getPrecio() < 0 ||
        actualizado.getStock() < 0)
        return false;

    productos[posicion] = actualizado;
    return true;
}

bool eliminarProductoInventario(
    std::vector<Producto> &productos,
    int id)
{
    int posicion = buscarProducto(productos, id);

    if (posicion == -1)
        return false;

    productos.erase(productos.begin() + posicion);
    return true;
}
