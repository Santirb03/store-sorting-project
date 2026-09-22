#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include "producto.h"

using namespace std;

void merge(
    vector<Producto> &productos,
    int izquierda,
    int medio,
    int derecha)
{

    vector<Producto> izquierdaVector;
    vector<Producto> derechaVector;

    for (int i = izquierda; i <= medio; i++)
    {
        izquierdaVector.push_back(productos[i]);
    }

    for (int i = medio + 1; i <= derecha; i++)
    {
        derechaVector.push_back(productos[i]);
    }

    int i = 0;
    int j = 0;
    int k = izquierda;

    while (
        i < izquierdaVector.size() &&
        j < derechaVector.size())
    {

        if (
            izquierdaVector[i].getPrecio() <=
            derechaVector[j].getPrecio())
        {
            productos[k] = izquierdaVector[i];
            i++;
        }
        else
        {
            productos[k] = derechaVector[j];
            j++;
        }

        k++;
    }

    while (i < izquierdaVector.size())
    {
        productos[k] = izquierdaVector[i];
        i++;
        k++;
    }

    while (j < derechaVector.size())
    {
        productos[k] = derechaVector[j];
        j++;
        k++;
    }
}

void mergeSort(
    vector<Producto> &productos,
    int izquierda,
    int derecha)
{

    if (izquierda >= derecha)
    {
        return;
    }

    int medio = izquierda + (derecha - izquierda) / 2;

    mergeSort(productos, izquierda, medio);
    mergeSort(productos, medio + 1, derecha);

    merge(productos, izquierda, medio, derecha);
}

#endif