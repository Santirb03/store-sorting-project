#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include "producto.h"

using namespace std;

bool comparar(
    const Producto &a,
    const Producto &b,
    int criterio)
{
    if (criterio == 1)
    {
        return a.getPrecio() <= b.getPrecio();
    }

    if (criterio == 2)
    {
        return a.getNombre() <= b.getNombre();
    }

    if (criterio == 3)
    {
        return a.getStock() <= b.getStock();
    }

    if (criterio == 4)
    {
        return a.getCategoria() <= b.getCategoria();
    }

    return false;
}

void merge(
    vector<Producto> &productos,
    int izquierda,
    int medio,
    int derecha,
    int criterio)
{
    vector<Producto> mitadIzquierda;
    vector<Producto> mitadDerecha;

    for (int i = izquierda; i <= medio; i++)
    {
        mitadIzquierda.push_back(productos[i]);
    }

    for (int i = medio + 1; i <= derecha; i++)
    {
        mitadDerecha.push_back(productos[i]);
    }

    int i = 0;
    int j = 0;
    int k = izquierda;

    while (
        i < static_cast<int>(mitadIzquierda.size()) &&
        j < static_cast<int>(mitadDerecha.size()))
    {
        if (
            comparar(
                mitadIzquierda[i],
                mitadDerecha[j],
                criterio))
        {
            productos[k] = mitadIzquierda[i];
            i++;
        }
        else
        {
            productos[k] = mitadDerecha[j];
            j++;
        }

        k++;
    }

    while (i < static_cast<int>(mitadIzquierda.size()))
    {
        productos[k] = mitadIzquierda[i];
        i++;
        k++;
    }

    while (j < static_cast<int>(mitadDerecha.size()))
    {
        productos[k] = mitadDerecha[j];
        j++;
        k++;
    }
}

void mergeSort(
    vector<Producto> &productos,
    int izquierda,
    int derecha,
    int criterio)
{
    if (izquierda >= derecha)
    {
        return;
    }

    int medio =
        izquierda + (derecha - izquierda) / 2;

    mergeSort(
        productos,
        izquierda,
        medio,
        criterio);

    mergeSort(
        productos,
        medio + 1,
        derecha,
        criterio);

    merge(
        productos,
        izquierda,
        medio,
        derecha,
        criterio);
}

#endif