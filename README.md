# Sistema de administración de productos

Proyecto de C++17 para administrar un inventario en `productos.csv`. Cada producto tiene ID, nombre, categoría, precio y stock.

- Merge Sort ordena el inventario por precio, nombre, stock o categoría.
- Un árbol binario de búsqueda balanceado guarda el ID y la posición de cada producto en el vector. Se reconstruye al ordenar, agregar o eliminar. La opción 8 consulta el árbol en O(log n) y lee los datos actuales del vector.
- Una pila `std::stack` registra el ID y el precio anterior cuando la opción 9 cambia el precio. La opción 12 restaura los precios del más reciente al más antiguo y conserva los demás datos del producto.
- Una cola `std::queue` guarda los pedidos en orden de llegada. Al procesar un pedido se consulta el stock actual y se retira el pedido de la cola, incluso si se rechaza por falta de unidades.

Eliminar un producto retira sus cambios de precio y cancela sus pedidos pendientes. La pila y la cola se vacían al salir. La opción 6 guarda el inventario en el CSV.

## Compilación y pruebas

Desde la raíz del repositorio, usa `g++` con soporte para C++17. Los comandos de PowerShell compilan y ejecutan las pruebas en una carpeta temporal y abren el menú con una copia del CSV.

```powershell
$demo = Join-Path ([System.IO.Path]::GetTempPath()) ('store-sorting-' + [guid]::NewGuid())
New-Item -ItemType Directory -Path $demo | Out-Null
g++ -std=c++17 main.cpp producto.cpp inventory.cpp -o (Join-Path $demo 'main.exe')
g++ -std=c++17 tests.cpp producto.cpp inventory.cpp -o (Join-Path $demo 'tests.exe')
& (Join-Path $demo 'tests.exe')
Copy-Item -LiteralPath productos.csv -Destination $demo
Push-Location $demo
.\main.exe
Pop-Location
```

En Bash, ejecuta desde la misma raíz.

```bash
demo=$(mktemp -d)
g++ -std=c++17 main.cpp producto.cpp inventory.cpp -o "$demo/main"
g++ -std=c++17 tests.cpp producto.cpp inventory.cpp -o "$demo/tests"
"$demo/tests"
cp productos.csv "$demo/"
(cd "$demo" && ./main)
```

## Opciones del menú

| Opción | Operación |
| --- | --- |
| 1 | Mostrar todos los productos |
| 2 | Ordenar por precio |
| 3 | Ordenar por nombre |
| 4 | Ordenar por stock |
| 5 | Ordenar por categoría |
| 6 | Guardar los productos en `productos.csv` |
| 7 | Agregar un producto |
| 8 | Buscar un producto por ID en el árbol |
| 9 | Actualizar nombre, categoría, precio y stock |
| 10 | Eliminar un producto, su historial de precios y sus pedidos |
| 11 | Salir |
| 12 | Deshacer el último cambio de precio |
| 13 | Registrar un pedido por ID con una cantidad entera positiva |
| 14 | Procesar el pedido más antiguo |

## Demo del árbol, la pila y la cola

Inicia el menú con una copia nueva del CSV del repositorio. Introduce cada valor de la secuencia en una línea.

| Secuencia | Resultado esperado |
| --- | --- |
| `8 → 2` | El árbol encuentra Mouse Logitech con precio 599 y stock 25. |
| `9 → 2 → Mouse Logitech → Electronica → 650 → 25` | La pila guarda el precio 599. |
| `9 → 2 → Mouse Demo → Accesorios → 700 → 25` | La pila guarda el precio 650. |
| `2`, luego `8 → 2` | Merge Sort ordena por precio y el árbol encuentra el ID 2 con precio 700. |
| `13 → 2 → 3`, luego `13 → 2 → 23` | La cola registra primero 3 unidades y después 23. |
| `14`, luego `14` | El primer pedido se procesa y deja 22 unidades. El segundo se rechaza por stock insuficiente y sale de la cola. |
| `12`, luego `12` | El precio vuelve primero a 650 y después a 599. El producto conserva Mouse Demo, Accesorios y el stock de 22. |
| `8 → 2`, luego `14` | El árbol muestra los datos actuales y la cola indica que está vacía. |
| `6`, luego `11` | El programa guarda los cambios en la copia del CSV y sale. |

Consulta el [análisis de complejidad](COMPLEXITY.md) y las [decisiones de diseño](DESIGN_DECISIONS.md) de la implementación inicial.
