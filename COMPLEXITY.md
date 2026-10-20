# Análisis de complejidad — Sistema de Inventario

## 1. Descripción del proyecto

El proyecto implementa un sistema de administración de inventario desarrollado en C++.

Permite cargar productos desde un archivo CSV, mostrar el inventario, ordenar productos con Merge Sort, buscar productos por ID, agregar nuevos productos, actualizar información, eliminar productos y guardar los cambios en el archivo.

El objetivo de este documento es analizar las complejidades temporales y espaciales de las estructuras de datos, los algoritmos y las operaciones del sistema.

## 2. Variables utilizadas

Para analizar las complejidades se definen:

- **n:** número de productos en el inventario.
- **m:** número de caracteres procesados al leer o escribir el archivo CSV.
- **k:** número de operaciones que realiza el usuario durante una sesión.
- **L:** longitud máxima de los campos de texto de un producto.

Cuando se considera que los campos tienen una longitud acotada, las operaciones básicas por producto se consideran O(1).

## 3. Estructura de datos: std::vector

El programa utiliza `vector<Producto>` para almacenar los productos dinámicamente.

| Operación | Complejidad temporal |
|---|---|
| Acceso por índice | O(1) |
| Obtener tamaño | O(1) |
| Agregar con `push_back()` | O(1) amortizado |
| Agregar con `emplace_back()` | O(1) amortizado |
| Búsqueda secuencial | O(n) |
| Recorrido completo | O(n) |
| Eliminación con `erase()` | O(n) en el peor caso |

El vector permite almacenar productos en posiciones contiguas de memoria y facilita el recorrido necesario para Merge Sort.

**Complejidad espacial:** O(n), suponiendo un tamaño acotado por producto.

## 4. Algoritmo Merge Sort

El sistema utiliza Merge Sort para ordenar productos por precio, nombre, stock y categoría.

Merge Sort es un algoritmo de división y conquista:

1. Divide los elementos en dos mitades.
2. Ordena recursivamente cada mitad.
3. Combina las mitades mediante la operación merge.

Su recurrencia temporal es:

T(n) = 2T(n/2) + O(n)

Aplicando el teorema maestro:

T(n) = O(n log n)

| Caso | Complejidad temporal |
|---|---|
| Mejor caso | O(n log n) |
| Caso promedio | O(n log n) |
| Peor caso | O(n log n) |

La complejidad espacial auxiliar es O(n) para una implementación clásica de Merge Sort con arreglo temporal y pila recursiva de O(log n).

Estas cotas corresponden a la implementación estándar; deben contrastarse con el código de `sorting.h` y sus asignaciones temporales.

## 5. Operaciones del inventario

### Mostrar productos

La función `mostrarProductos()` recorre el vector e imprime cada producto una vez.

- Tiempo: O(n), suponiendo tamaño de campo acotado.
- Espacio auxiliar: O(1).

### Buscar producto

La función `buscarProducto()` realiza una búsqueda secuencial comparando IDs.

- Mejor caso: O(1).
- Caso promedio: O(n).
- Peor caso: O(n).
- Espacio auxiliar: O(1).

### Agregar producto

La función `agregarProducto()` primero comprueba que el ID no exista y después añade el nuevo elemento mediante `emplace_back()`.

- Búsqueda de ID duplicado: O(n).
- Inserción al final: O(1) amortizado.
- Complejidad total: O(n) en el peor caso.

### Actualizar producto

La función `actualizarProducto()` busca el producto por ID y reemplaza sus datos después de validarlos.

- Búsqueda: O(n).
- Reemplazo: O(1), con campos de texto acotados.
- Complejidad total: O(n).

### Eliminar producto

La función `eliminarProducto()` busca el producto y lo elimina mediante `vector::erase()`.

- Búsqueda: O(n).
- Desplazamiento de elementos: O(n).
- Complejidad total: O(n).

## 6. Lectura y escritura de archivos

### cargarProductos()

La función recorre el archivo CSV, procesa cada línea y agrega un objeto Producto al vector.

- Tiempo: O(m), donde m es el número de caracteres leídos.
- Espacio: O(nL), para los productos almacenados, con longitud máxima de campos L.

Si L es constante y cada producto ocupa un espacio acotado, el tiempo y espacio se simplifican a O(n).

### guardarProductos()

La función recorre todos los productos y escribe sus atributos en un CSV.

- Tiempo de serialización: O(nL).
- Espacio auxiliar para la serialización: O(1) con campos acotados, sin contar los búferes del sistema y la infraestructura del archivo.
- Tamaño del archivo generado: O(nL).

Cuando L es constante, el tiempo se simplifica a O(n).

El proceso de guardar mediante archivo temporal y respaldo también depende de las operaciones del sistema de archivos.

## 7. Validación de datos

Las funciones de `input_utils.h` permiten validar enteros, decimales y cadenas de texto.

Su complejidad depende de la longitud de la entrada recibida.

Para una entrada de longitud L:

- Tiempo: O(L).
- Espacio auxiliar: O(L), porque se almacena la línea introducida.

Con entradas de longitud acotada, se consideran operaciones O(1).

## 8. Complejidad global del programa

La complejidad del programa depende de las operaciones que realice el usuario.

### Escenario A: cargar, ordenar y mostrar

- Cargar CSV: O(n), con campos acotados.
- Ordenar mediante Merge Sort: O(n log n).
- Mostrar productos: O(n).

T(n) = O(n) + O(n log n) + O(n)

**Resultado: O(n log n).**

### Escenario B: cargar, buscar y mostrar un producto

- Cargar CSV: O(n).
- Buscar por ID: O(n).
- Mostrar un producto: O(1).

**Resultado: O(n).**

### Escenario C: cargar, modificar y guardar

- Cargar CSV: O(n).
- Buscar y modificar: O(n).
- Guardar CSV: O(n).

**Resultado: O(n)**, con campos de tamaño acotado y sin considerar el costo adicional del sistema de archivos.

### Escenario D: múltiples operaciones

Si durante una sesión se realizan k operaciones y cada una tiene un costo máximo O(n log n), puede establecerse una cota conservadora de:

**O(n + k · n log n)**

Este análisis supone que n representa una cota del tamaño del inventario durante toda la sesión.

## 9. Conclusión

El proyecto utiliza Merge Sort porque garantiza O(n log n) para ordenar productos, independientemente del orden inicial.

El uso de `std::vector` facilita el almacenamiento dinámico, acceso por índice y recorrido secuencial del inventario.

Las operaciones de búsqueda, modificación y eliminación tienen complejidad O(n) porque requieren una búsqueda lineal por ID.

La lectura y escritura CSV permiten conservar la información entre ejecuciones sin requerir una base de datos externa.

El análisis permite identificar que, a medida que aumente el inventario, la búsqueda secuencial podría optimizarse con una estructura adicional, como un árbol AVL o una tabla hash.