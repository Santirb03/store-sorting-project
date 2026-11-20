
#ifndef INVENTORY_H
#define INVENTORY_H

#include <cstddef>
#include <memory>
#include <optional>
#include <vector>
#include "producto.h"

class IndiceProductos
{
public:
    explicit IndiceProductos(const std::vector<Producto> &productos);
    void reconstruir(const std::vector<Producto> &productos);
    std::optional<std::size_t> buscar(int id) const;

private:
    struct Entrada
    {
        int id;
        std::size_t posicion;
    };

    struct Nodo
    {
        Entrada entrada;
        std::unique_ptr<Nodo> izquierdo;
        std::unique_ptr<Nodo> derecho;
    };

    static std::unique_ptr<Nodo> construir(
        const std::vector<Entrada> &entradas,
        std::size_t inicio, std::size_t fin);

    std::unique_ptr<Nodo> raiz;
};

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
