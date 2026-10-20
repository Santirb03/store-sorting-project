# Decisiones tecnológicas — Sistema de Inventario

## 1. Objetivo del proyecto

El proyecto consiste en desarrollar un sistema de administración de inventario que permita registrar, consultar, ordenar, modificar y eliminar productos.

Se busca aplicar los conocimientos de estructuras de datos y algoritmos mediante una solución funcional desarrollada en C++.

Las tecnologías y estructuras utilizadas se seleccionaron considerando la complejidad algorítmica, facilidad de implementación, mantenimiento y necesidades actuales del sistema.

## 2. Selección de C++

**Decisión:** utilizar C++ como lenguaje de programación.

C++ permite implementar algoritmos y estructuras de datos directamente, trabajar con memoria dinámica y utilizar bibliotecas estándar como STL.

Para este proyecto resulta adecuado porque permite comprender el funcionamiento de algoritmos de ordenamiento como Merge Sort y analizar su complejidad temporal y espacial.

**Ventajas:**
- Permite trabajar directamente con estructuras de datos.
- Cuenta con bibliotecas estándar para administrar colecciones y archivos.
- Ofrece buen rendimiento.
- Facilita aplicar programación orientada a objetos.

**Limitaciones:**
- Requiere mayor atención a la memoria y a los tipos de datos.
- Es necesario compilar el programa.
- El manejo de errores requiere una implementación cuidadosa.

## 3. Selección de std::vector

**Decisión:** almacenar los productos utilizando `std::vector<Producto>`.

El vector permite mantener una colección dinámica de productos y acceder directamente a ellos mediante índices.

Se seleccionó porque el sistema necesita recorrer el inventario para mostrar información, ordenar productos y guardar los datos.

**Ventajas:**
- Acceso por índice en O(1).
- Inserción al final en O(1) amortizado.
- Almacenamiento contiguo de elementos.
- Integración sencilla con Merge Sort.

**Limitaciones:**
- Buscar un ID mediante recorrido secuencial requiere O(n).
- Eliminar un elemento puede requerir desplazar otros productos, con costo O(n).

**Alternativa considerada:** `std::list`.

Aunque una lista enlazada permite eliminar nodos de manera eficiente cuando se conoce su posición, no proporciona acceso directo por índice. El vector resulta más conveniente para el algoritmo de ordenamiento implementado.

## 4. Selección de Merge Sort

**Decisión:** implementar Merge Sort para ordenar los productos.

Merge Sort utiliza la técnica de división y conquista. Divide la colección en partes, ordena cada mitad y combina los resultados.

Se seleccionó porque garantiza una complejidad temporal de O(n log n) en el mejor caso, caso promedio y peor caso.

**Ventajas:**
- Complejidad temporal O(n log n).
- Comportamiento predecible.
- Permite ordenar por distintos atributos mediante una función de comparación.
- Puede conservar el orden relativo de elementos equivalentes si la combinación se implementa de forma estable.

**Limitaciones:**
- Requiere memoria auxiliar adicional O(n) en la implementación utilizada.
- Para colecciones pequeñas, algoritmos más sencillos pueden tener menor sobrecarga.

**Alternativa considerada:** Quick Sort.

Quick Sort suele tener un buen rendimiento práctico, pero su implementación clásica tiene una complejidad O(n²) en el peor caso.

Merge Sort se consideró adecuado porque ofrece una garantía de tiempo O(n log n).

## 5. Selección de archivos CSV

**Decisión:** almacenar el inventario en un archivo CSV.

El archivo utiliza columnas para representar los atributos de cada producto:

`id,nombre,categoria,precio,stock`

Este mecanismo permite guardar y recuperar información entre ejecuciones.

**Ventajas:**
- Es un formato sencillo y legible.
- Puede abrirse en programas de hojas de cálculo.
- No requiere instalar un gestor de bases de datos.
- Facilita realizar pruebas con conjuntos de datos pequeños.

**Limitaciones:**
- No tiene las garantías de concurrencia de una base de datos.
- Es necesario implementar validaciones.
- El formato CSV simple utilizado no admite todos los caracteres especiales dentro de los campos.
- Guardar el inventario implica recorrer y escribir los productos.

**Alternativa considerada:** SQLite.

SQLite sería apropiado si el sistema creciera y necesitara consultas más complejas, transacciones e índices.

Para el alcance actual del proyecto, CSV es suficiente.

## 6. Programación orientada a objetos

**Decisión:** representar cada producto mediante una clase `Producto`.

Esta clase contiene los atributos:

- ID.
- Nombre.
- Categoría.
- Precio.
- Stock.

Los atributos son privados y se consultan mediante métodos públicos.

Se utiliza encapsulamiento para organizar el código y controlar la forma en que otras partes del programa acceden a la información.

La implementación se separó en:

- `producto.h`: declaración de la clase.
- `producto.cpp`: implementación de los métodos.

Esta separación mejora la organización y facilita el mantenimiento del proyecto.

## 7. Organización modular del proyecto

El programa está dividido en componentes con responsabilidades diferentes.

| Archivo | Responsabilidad |
|---|---|
| `main.cpp` | Control del menú y administración del inventario |
| `producto.h` | Declaración de la clase Producto |
| `producto.cpp` | Implementación de Producto |
| `sorting.h` | Algoritmo de ordenamiento Merge Sort |
| `input_utils.h` | Validación de entradas |
| `productos.csv` | Almacenamiento de información |
| `tests.cpp` | Pruebas del programa |
| `COMPLEXITY.md` | Análisis de complejidades |

Esta organización permite identificar responsabilidades y realizar modificaciones sin alterar innecesariamente otros componentes.

## 8. Posibles mejoras futuras

El proyecto podría ampliarse con:

- Árboles AVL para realizar búsquedas por ID en O(log n).
- Tablas hash para búsquedas promedio cercanas a O(1).
- SQLite para manejar información persistente de mayor tamaño.
- Una interfaz gráfica.
- Pruebas automatizadas más completas.

Estas alternativas no se implementaron inicialmente porque la prioridad del proyecto es comprender y aplicar las estructuras y algoritmos actuales.

## 9. Conclusión

Las tecnologías seleccionadas responden al alcance de un sistema de inventario académico.

C++ permite implementar y analizar directamente los algoritmos; `std::vector` facilita el almacenamiento dinámico; Merge Sort ofrece un ordenamiento eficiente y predecible; y CSV proporciona persistencia sin dependencias externas.

Las decisiones consideran tanto las ventajas de cada componente como sus limitaciones y posibles alternativas.