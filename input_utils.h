
#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <climits>
#include <cctype>

namespace InputUtils
{

    inline bool leerEntero(
        const std::string &mensaje,
        int &resultado)
    {
        std::string linea;
        std::cout << mensaje;

        if (!std::getline(std::cin, linea))
            return false;

        std::istringstream stream(linea);
        long long numero;
        char sobrante;

        if (!(stream >> numero) ||
            (stream >> sobrante) ||
            numero < INT_MIN ||
            numero > INT_MAX)
        {
            return false;
        }

        resultado = static_cast<int>(numero);
        return true;
    }

    inline bool leerDecimal(
        const std::string &mensaje,
        double &resultado)
    {
        std::string linea;
        std::cout << mensaje;

        if (!std::getline(std::cin, linea))
            return false;

        std::istringstream stream(linea);
        double numero;
        char sobrante;

        if (!(stream >> numero) ||
            (stream >> sobrante) ||
            !std::isfinite(numero))
        {
            return false;
        }

        resultado = numero;
        return true;
    }

    inline bool leerTextoCSV(
        const std::string &mensaje,
        std::string &resultado)
    {
        std::cout << mensaje;

        if (!std::getline(std::cin, resultado))
            return false;

        // El lector CSV del proyecto usa comas
        // como separadores y no interpreta comillas.
        if (resultado.empty() ||
            resultado.find(',') != std::string::npos ||
            resultado.find('"') != std::string::npos ||
            resultado.find('\r') != std::string::npos)
        {
            return false;
        }

        bool tieneContenido = false;

        for (unsigned char c : resultado)
        {
            if (!std::isspace(c))
            {
                tieneContenido = true;
                break;
            }
        }

        return tieneContenido;
    }

} // namespace InputUtils

#endif
