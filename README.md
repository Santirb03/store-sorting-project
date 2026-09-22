# store-sorting-project
C++ inventory management project using sorting algorithms.


# Sistema de Administración de Productos

## Descripción

Este proyecto consiste en un sistema de administración de productos
desarrollado en C++.

El objetivo del programa es cargar información de productos desde un
archivo CSV y permitir al usuario ordenar los datos utilizando
diferentes atributos.

Cada producto contiene:

- ID
- Nombre
- Categoría
- Precio
- Stock

El programa permite ordenar la información utilizando el algoritmo
Merge Sort.

---

## Funcionalidades

El programa permite:

- Cargar productos desde un archivo CSV.
- Mostrar todos los productos.
- Ordenar productos por precio.
- Ordenar productos por nombre.
- Ordenar productos por stock.
- Ordenar productos por categoría.
- Utilizar un menú interactivo para seleccionar las operaciones.

---

## Archivos

- `main.cpp`: contiene el programa principal y el menú.
- `Producto.h`: contiene la clase Producto.
- `sorting.h`: contiene la implementación de Merge Sort.
- `productos.csv`: contiene los datos utilizados por el programa.
- `tests.cpp`: contiene pruebas del algoritmo.

---

## Compilación

Para compilar el programa:

```bash
g++ main.cpp -o main