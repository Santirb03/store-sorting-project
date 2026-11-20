
#include "inventory.h"
#include <algorithm>

IndiceProductos::IndiceProductos(const std::vector<Producto> &productos)
{
    reconstruir(productos);
}

void IndiceProductos::reconstruir(const std::vector<Producto> &productos)
{
    std::vector<Entrada> entradas;
    entradas.reserve(productos.size());

    for (std::size_t i = 0; i < productos.size(); ++i)
        entradas.push_back({productos[i].getId(), i});

    std::sort(entradas.begin(), entradas.end(),
              [](const Entrada &a, const Entrada &b) { return a.id < b.id; });

    raiz = construir(entradas, 0, entradas.size());
}

std::unique_ptr<IndiceProductos::Nodo> IndiceProductos::construir(
    const std::vector<Entrada> &entradas,
    std::size_t inicio, std::size_t fin)
{
    if (inicio == fin)
        return nullptr;

    // La mediana divide cada intervalo en dos subarboles de tamanos similares.
    const std::size_t medio = inicio + (fin - inicio) / 2;
    return std::make_unique<Nodo>(Nodo{
        entradas[medio],
        construir(entradas, inicio, medio),
        construir(entradas, medio + 1, fin)});
}

std::optional<std::size_t> IndiceProductos::buscar(int id) const
{
    const Nodo *nodo = raiz.get();

    while (nodo != nullptr)
    {
        if (id == nodo->entrada.id)
            return nodo->entrada.posicion;

        nodo = id < nodo->entrada.id ? nodo->izquierdo.get() : nodo->derecho.get();
    }

    return std::nullopt;
}

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
