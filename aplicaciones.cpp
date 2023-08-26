#include "../include/aplicaciones.h"
#include "colaDePrioridadPersona.h"

void listarEnOrden(TTablaPersonas t, char** nombres, nat n){
    TColaDePrioridadPersona cp = crearCP(MAX_ID);

    for (nat i = 0; i < n; i++) {
        if (perteneceATTablaPersonas(t, nombres[i])) {
            TPersona persona = obtenerPersonaDeTTablaPersonas(t, nombres[i]);
            insertarEnCP(copiarTPersona(persona), cp);
        }
    }

    while (!estaVaciaCP(cp)) {
        TPersona pri = prioritaria(cp);
        imprimirTPersona(pri);
        eliminarPrioritaria(cp);
    }

    liberarCP(cp);
}