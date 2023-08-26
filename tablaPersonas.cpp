#include "../include/tablaPersonas.h"

struct rep_tablaPersonas {
    TPersonasLDE* map;
    int size;
    int cant;
};

nat funcionDeDispersion(const char nombre[100]){
    nat res = 0;
    int i = 0;
    while(i< 100 && nombre[i] != '\0'){
        res += int(nombre[i]);
        i++;
    }
    return res;
}

TTablaPersonas crearTTablaPersonas(int max){
    TTablaPersonas t = new rep_tablaPersonas;
    t->map = new TPersonasLDE[max];
    t->size = max;
    t->cant = 0;
    
    for (int i = 0; i < max; i++) {
        t->map[i] = crearTPersonasLDE();
    }

    return t;
}

void insertarPersonaEnTabla(TTablaPersonas &tabla, TPersona persona){
    nat pos = funcionDeDispersion(nombreTPersona(persona)) % tabla->size;
    TPersonasLDE list = tabla->map[pos];
    insertarTPersonasLDE(list, persona, 1);
}


void eliminarPersonaDeTTablaPersonas(TTablaPersonas &tabla, const char nombre[100]){
    nat pos = funcionDeDispersion(nombre) % tabla->size;
    TPersonasLDE list = tabla->map[pos];
    eliminarPersonaConNombreTPersonasLDE(list, nombre);
}

bool perteneceATTablaPersonas(TTablaPersonas tabla, const char nombre[100]){
    nat pos = funcionDeDispersion(nombre) % tabla->size;
    TPersonasLDE list = tabla->map[pos];

    return estaPersonaConNombreEnTPersonasLDE(list, nombre);
}

TPersona obtenerPersonaDeTTablaPersonas(TTablaPersonas tabla, const char nombre[100]){
    nat pos = funcionDeDispersion(nombre) % tabla->size;
    TPersonasLDE list = tabla->map[pos];

    if (perteneceATTablaPersonas(tabla, nombre)) {
        return obtenerPersonaConNombreTPersonasLDE(list, nombre);
    } else {
        return NULL;
    }
}

void liberarTTablaPersonas(TTablaPersonas &tabla){
    for (int i = 0; i < tabla->size; i++) {
        liberarTPersonasLDE(tabla->map[i]);
    }
    
    delete[] tabla->map;
    delete tabla;
    tabla = NULL;
}

void imprimirTTablaPersonas(TTablaPersonas tabla){
    for (int i = 0; i < tabla->size; i++) {
        imprimirTPersonasLDE(tabla->map[i]);
    }
}