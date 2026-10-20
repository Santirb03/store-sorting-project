
#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "producto.h"

int buscarProducto(
    const std::vector<Producto> &productos,
    int id);

bool agregarProductoInventario(
    std::vector<Producto> &productos,
    const Producto &nuevo);

bool actualizarProductoInventario(
    std::vector<Producto> &productos,
    const Producto &actualizado);

bool eliminarProductoInventario(
    std::vector<Producto> &productos,
    int id);

#endif
