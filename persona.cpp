#include "../include/persona.h"

struct rep_persona {
    int id;
    nat edad;
    char nombre[100];
    TAgendaLS agenda;
};

TPersona crearTPersona(nat id, nat edad, const char nombre[100], TAgendaLS agenda) {
    TPersona person = new rep_persona;

    person->id = id;
    person->edad = edad;
    strcpy(person->nombre, nombre);
    person->agenda = agenda;

    return person;
}

void liberarTPersona(TPersona &persona) {
    liberarAgendaLS(persona->agenda);
    delete persona;
    persona = NULL;
}

//Imprime a la persona utilizando printf e imprimeAgendaLS
void imprimirTPersona(TPersona persona) {
    printf("Persona %d: %s, %d años\n", persona->id, persona->nombre, persona->edad);
    imprimirAgendaLS(persona->agenda);
}

nat idTPersona(TPersona persona) {
    return persona->id;
}

nat edadTPersona(TPersona persona) {
    return persona->edad;
}

char* nombreTPersona(TPersona persona) {
    return persona->nombre;
}

TAgendaLS agendaTPersona(TPersona persona) {
    return persona->agenda;
}

void agregarEventoATPersona(TPersona &persona, TEvento evento) {
    agregarEnAgendaLS(persona->agenda, evento);
}

void posponerEventoEnTPersona(TPersona &persona, int id, nat n) {
    posponerEnAgendaLS(persona->agenda, id, n);
}

void removerEventoDeTPersona(TPersona &persona, int id) {
    removerDeAgendaLS(persona->agenda, id);
}

bool estaEnAgendaDeTPersona(TPersona persona, int id) {
    return estaEnAgendaLS(persona->agenda, id);
}

TEvento obtenerDeAgendaDeTPersona(TPersona persona, int id) {
    return obtenerDeAgendaLS(persona->agenda, id);
}

TPersona copiarTPersona(TPersona persona) {
    TPersona newPerson = new rep_persona;

    newPerson->id = persona->id;
    newPerson->edad = persona->edad;
    newPerson->agenda = copiarAgendaLS(persona->agenda);
    strcpy(newPerson->nombre, persona->nombre);
    
    return newPerson;
}

TEvento primerEventoDeTPersona(TPersona persona){
    if (agendaTPersona(persona) == NULL) {
        return NULL;
    } else {
        return primerEventoAgendaLS(persona->agenda);
    }
}