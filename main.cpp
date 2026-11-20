#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <stack>
#include <queue>

#include "producto.h"
#include "sorting.h"
#include "input_utils.h"
#include "inventory.h"

using namespace std;

struct CambioPrecio
{
    int id;
    double precioAnterior;
};

struct Pedido
{
    int id;
    int cantidad;
};

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

        try
        {
            size_t finId = 0;
            size_t finPrecio = 0;
            size_t finStock = 0;

            int id = stoi(idStr, &finId);
            double precio = stod(precioStr, &finPrecio);
            int stock = stoi(stockStr, &finStock);

            // Comprobar que las conversiones fueron completas.
            if (finId != idStr.size() ||
                finPrecio != precioStr.size() ||
                finStock != stockStr.size() ||
                id <= 0 ||
                !std::isfinite(precio) ||
                precio < 0 ||
                stock < 0 ||
                nombre.empty() ||
                categoria.empty())
            {
                cerr << "Fila CSV invalida: "
                     << linea << endl;
                continue;
            }

            // Evitar productos duplicados en el CSV.
            bool duplicado = false;

            for (const Producto &existente : productos)
            {
                if (existente.getId() == id)
                {
                    duplicado = true;
                    break;
                }
            }

            if (duplicado)
            {
                cerr << "ID duplicado en CSV: "
                     << id << endl;
                continue;
            }

            productos.emplace_back(
                id, nombre, categoria, precio, stock);
        }
        catch (const std::invalid_argument &)
        {
            cerr << "Datos numericos invalidos: "
                 << linea << endl;
        }
        catch (const std::out_of_range &)
        {
            cerr << "Numero fuera de rango: "
                 << linea << endl;
        }
    }

    archivo.close();

    return productos;
}

bool guardarProductos(
    const vector<Producto> &productos,
    const string &nombreArchivo)
{
    namespace fs = std::filesystem;

    const fs::path destino(nombreArchivo);
    const fs::path temporal = destino.string() + ".tmp";
    const fs::path respaldo = destino.string() + ".bak";

    // Evitar sobreescribir archivos temporales ajenos.
    std::error_code ec;

    if (fs::exists(temporal, ec) ||
        fs::exists(respaldo, ec) || ec)
    {
        cerr << "Error: existe un archivo temporal "
             << "o de respaldo pendiente.\n";
        return false;
    }

    // 1. Escribir a un archivo temporal.
    {
        ofstream archivo(temporal);

        if (!archivo.is_open())
        {
            cerr << "No se pudo crear el temporal.\n";
            return false;
        }

        archivo << "id,nombre,categoria,precio,stock\n";
        archivo << setprecision(17);

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
            cerr << "Error al escribir el temporal.\n";
            return false;
        }
    }

    // 2. Respaldar el archivo original.
    bool habiaOriginal = fs::exists(destino, ec);

    if (ec)
        return false;

    if (habiaOriginal)
    {
        fs::rename(destino, respaldo, ec);

        if (ec)
        {
            cerr << "No se pudo respaldar el CSV.\n";
            return false;
        }
    }

    // 3. Colocar el nuevo CSV.
    fs::rename(temporal, destino, ec);

    if (ec)
    {
        cerr << "Error al instalar el nuevo CSV.\n";

        if (habiaOriginal)
        {
            std::error_code errorRestauracion;
            fs::rename(
                respaldo, destino, errorRestauracion);

            if (errorRestauracion)
                cerr << "No se pudo restaurar el "
                     << "respaldo: " << respaldo << "\n";
        }

        return false;
    }

    // 4. Borrar respaldo tras instalar el nuevo.
    if (habiaOriginal)
    {
        fs::remove(respaldo, ec);

        if (ec)
            cerr << "Aviso: el respaldo permanece "
                 << "en " << respaldo << "\n";
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
    IndiceProductos &indice,
    int criterio)
{
    if (!productos.empty())
    {
        mergeSort(
            productos,
            0,
            static_cast<int>(productos.size()) - 1,
            criterio);
        indice.reconstruir(productos);
    }
}

void agregarProducto(vector<Producto> &productos, IndiceProductos &indice)
{
    int id;
    int stock;
    double precio;
    string nombre, categoria;

    cout << "\n--- AGREGAR PRODUCTO ---\n";

    if (!InputUtils::leerEntero("ID: ", id) ||
        id <= 0)
    {
        cout << "Error: el ID debe ser positivo.\n";
        return;
    }

    if (indice.buscar(id))
    {
        cout << "Error: ese ID ya existe.\n";
        return;
    }

    if (!InputUtils::leerTextoCSV("Nombre: ", nombre) ||
        !InputUtils::leerTextoCSV("Categoria: ", categoria))
    {
        cout << "Error: nombre o categoria invalida.\n";
        return;
    }

    if (!InputUtils::leerDecimal("Precio: ", precio) ||
        precio < 0)
    {
        cout << "Error: precio invalido.\n";
        return;
    }

    if (!InputUtils::leerEntero("Stock: ", stock) ||
        stock < 0)
    {
        cout << "Error: stock invalido.\n";
        return;
    }

    Producto nuevo(id, nombre, categoria, precio, stock);

    if (!agregarProductoInventario(productos, nuevo))
    {
        cout << "No se pudo agregar el producto.\n";
        return;
    }

    indice.reconstruir(productos);
    cout << "Producto agregado correctamente.\n";
}

void actualizarProducto(vector<Producto> &productos,
                        const IndiceProductos &indice,
                        std::stack<CambioPrecio> &historial)
{
    int id;

    cout << "\n--- ACTUALIZAR PRODUCTO ---\n";

    if (!InputUtils::leerEntero(
            "ID del producto: ", id))
    {
        cout << "ID invalido.\n";
        return;
    }

    const auto posicion = indice.buscar(id);

    if (!posicion)
    {
        cout << "Producto no encontrado.\n";
        return;
    }

    cout << "Producto actual:\n";
    productos[*posicion].mostrar();

    string nombre, categoria;
    double precio;
    int stock;

    if (!InputUtils::leerTextoCSV(
            "Nuevo nombre: ", nombre) ||
        !InputUtils::leerTextoCSV(
            "Nueva categoria: ", categoria))
    {
        cout << "Nombre o categoria invalida.\n";
        return;
    }

    if (!InputUtils::leerDecimal(
            "Nuevo precio: ", precio) ||
        precio < 0)
    {
        cout << "Precio invalido.\n";
        return;
    }

    if (!InputUtils::leerEntero(
            "Nuevo stock: ", stock) ||
        stock < 0)
    {
        cout << "Stock invalido.\n";
        return;
    }

    Producto actualizado(
        id, nombre, categoria, precio, stock);

    const double precioAnterior = productos[*posicion].getPrecio();

    if (!actualizarProductoInventario(
            productos, actualizado))
    {
        cout << "No se pudo actualizar el producto.\n";
        return;
    }

    if (precio != precioAnterior)
        historial.push({id, precioAnterior});

    cout << "Producto actualizado correctamente.\n";
}

void retirarOperaciones(int id, std::stack<CambioPrecio> &historial,
                        std::queue<Pedido> &pedidos)
{
    std::stack<CambioPrecio> cambiosConservados;
    while (!historial.empty())
    {
        if (historial.top().id != id)
            cambiosConservados.push(historial.top());
        historial.pop();
    }

    // Volver a apilar los cambios conservados restablece su orden original.
    while (!cambiosConservados.empty())
    {
        historial.push(cambiosConservados.top());
        cambiosConservados.pop();
    }

    // Cada pedido pendiente se revisa una vez y los vigentes vuelven al final.
    for (auto pendientes = pedidos.size(); pendientes > 0; --pendientes)
    {
        const Pedido pedido = pedidos.front();
        if (pedido.id != id)
            pedidos.push(pedido);
        pedidos.pop();
    }
}

void eliminarProducto(vector<Producto> &productos, IndiceProductos &indice,
                      std::stack<CambioPrecio> &historial,
                      std::queue<Pedido> &pedidos)
{
    int id;

    cout << "\n--- ELIMINAR PRODUCTO ---\n";

    if (!InputUtils::leerEntero(
            "ID a eliminar: ", id))
    {
        cout << "ID invalido.\n";
        return;
    }

    const auto posicion = indice.buscar(id);

    if (!posicion)
    {
        cout << "Producto no encontrado.\n";
        return;
    }

    cout << "Producto encontrado:\n";
    productos[*posicion].mostrar();

    string respuesta;

    cout << "Confirmar eliminacion (s/n): ";

    if (!getline(cin, respuesta))
    {
        cout << "No se pudo leer la respuesta.\n";
        return;
    }

    if (respuesta != "s" && respuesta != "S")
    {
        cout << "Operacion cancelada.\n";
        return;
    }

    if (!eliminarProductoInventario(productos, id))
    {
        cout << "No se pudo eliminar el producto.\n";
        return;
    }

    indice.reconstruir(productos);
    retirarOperaciones(id, historial, pedidos);
    cout << "Producto eliminado correctamente.\n";
}

void deshacerCambioPrecio(vector<Producto> &productos,
                         const IndiceProductos &indice,
                         std::stack<CambioPrecio> &historial)
{
    if (historial.empty())
    {
        cout << "No hay cambios de precio para deshacer.\n";
        return;
    }

    const CambioPrecio cambio = historial.top();
    historial.pop();

    const auto posicion = indice.buscar(cambio.id);
    if (!posicion)
    {
        cout << "Producto no encontrado.\n";
        return;
    }

    productos[*posicion].setPrecio(cambio.precioAnterior);
    cout << "Precio restaurado para el producto " << cambio.id << ".\n";
    productos[*posicion].mostrar();
}

void registrarPedido(const IndiceProductos &indice, std::queue<Pedido> &pedidos)
{
    int id;
    int cantidad;

    if (!InputUtils::leerEntero("ID del producto: ", id) || id <= 0)
    {
        cout << "Error: el ID debe ser positivo.\n";
        return;
    }

    if (!indice.buscar(id))
    {
        cout << "Producto no encontrado.\n";
        return;
    }

    if (!InputUtils::leerEntero("Cantidad: ", cantidad) || cantidad <= 0)
    {
        cout << "Error: la cantidad debe ser positiva.\n";
        return;
    }

    pedidos.push({id, cantidad});
    cout << "Pedido registrado correctamente.\n";
}

void procesarPedido(vector<Producto> &productos, const IndiceProductos &indice,
                    std::queue<Pedido> &pedidos)
{
    if (pedidos.empty())
    {
        cout << "No hay pedidos pendientes.\n";
        return;
    }

    const Pedido pedido = pedidos.front();
    pedidos.pop();

    const auto posicion = indice.buscar(pedido.id);
    if (!posicion)
    {
        cout << "Pedido rechazado: producto no encontrado.\n";
        return;
    }

    Producto &producto = productos[*posicion];
    if (producto.getStock() < pedido.cantidad)
    {
        cout << "Pedido rechazado por stock insuficiente para el producto "
             << pedido.id << ".\n";
        return;
    }

    producto.setStock(producto.getStock() - pedido.cantidad);
    cout << "Pedido procesado para el producto " << pedido.id << ".\n";
    producto.mostrar();
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

    IndiceProductos indice(productos);
    std::stack<CambioPrecio> historial;
    std::queue<Pedido> pedidos;
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
        cout << "7. Agregar producto" << endl;
        cout << "8. Buscar producto por ID" << endl;
        cout << "9. Actualizar producto" << endl;
        cout << "10. Eliminar producto" << endl;
        cout << "11. Salir" << endl;
        cout << "12. Deshacer ultimo cambio de precio" << endl;
        cout << "13. Registrar pedido" << endl;
        cout << "14. Procesar pedido mas antiguo" << endl;

        cout << endl;
        if (!InputUtils::leerEntero(
                "Selecciona una opcion: ", opcion))
        {
            if (cin.eof())
            {
                cout << "\nFin de la entrada.\n";
                break;
            }

            cout << "Error: introduce un numero valido.\n";
            continue;
        }

        switch (opcion)
        {

        case 1:
            mostrarProductos(productos);
            break;

        case 2:
            ordenarProductos(productos, indice, 1);

            cout << endl;
            cout << "Productos ordenados por precio:"
                 << endl;

            mostrarProductos(productos);
            break;

        case 3:
            ordenarProductos(productos, indice, 2);

            cout << endl;
            cout << "Productos ordenados por nombre:"
                 << endl;

            mostrarProductos(productos);
            break;

        case 4:
            ordenarProductos(productos, indice, 3);

            cout << endl;
            cout << "Productos ordenados por stock:"
                 << endl;

            mostrarProductos(productos);
            break;

        case 5:
            ordenarProductos(productos, indice, 4);

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
            agregarProducto(productos, indice);
            break;

        case 8:
        {
            int id;

            if (!InputUtils::leerEntero(
                    "\nID del producto: ", id))
            {
                cout << "ID invalido.\n";
                break;
            }

            const auto posicion = indice.buscar(id);

            if (posicion)
            {
                cout << "Producto encontrado:\n";
                productos[*posicion].mostrar();
            }
            else
            {
                cout << "Producto no encontrado.\n";
            }

            break;
        }

        case 9:
            actualizarProducto(productos, indice, historial);
            break;

        case 10:
            eliminarProducto(productos, indice, historial, pedidos);
            break;

        case 11:
            cout << "\nSaliendo del sistema...\n";
            break;

        case 12:
            deshacerCambioPrecio(productos, indice, historial);
            break;

        case 13:
            registrarPedido(indice, pedidos);
            break;

        case 14:
            procesarPedido(productos, indice, pedidos);
            break;

        default:
            cout << endl;
            cout << "Opcion invalida. Intenta nuevamente."
                 << endl;
        }

    } while (opcion != 11);

    return 0;
}
