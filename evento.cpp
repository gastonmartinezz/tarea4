#include "../include/evento.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 3 //////
///////////////////////////////////

struct rep_evento {
    int id;
    char descripcion[MAX_DESCRIPCION];
    TFecha fecha;
};

TEvento crearTEvento(int id, const char descripcion[MAX_DESCRIPCION], TFecha fecha) {
    TEvento nuevoEvento = NULL;

    nuevoEvento = new rep_evento;

    nuevoEvento->id = id;
    nuevoEvento->fecha = fecha;
    strcpy(nuevoEvento->descripcion, descripcion);

    return nuevoEvento;
}

void imprimirTEvento(TEvento evento) {
    printf("Evento %d: %s\n", evento->id, evento->descripcion);
    printf("Fecha: ");
    imprimirTFecha(evento->fecha);
}

void liberarTEvento(TEvento &evento) {
    liberarTFecha(evento->fecha);

    delete evento;
    evento = NULL;
}

int idTEvento(TEvento evento) {
    return evento->id;
}

TFecha fechaTEvento(TEvento evento) {
    return evento->fecha;
}

void posponerTEvento(TEvento &evento, int dias) {
    aumentarTFecha(evento->fecha, dias);
}

TEvento copiarTEvento(TEvento evento) {
    TEvento newEvento = new rep_evento;

    newEvento->fecha = copiarTFecha(evento->fecha);
    newEvento->id = evento->id;
    strcpy(newEvento->descripcion, evento->descripcion);

    return newEvento;
}
