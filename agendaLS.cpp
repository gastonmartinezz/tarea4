#include "../include/agendaLS.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 3 //////
///////////////////////////////////

struct rep_agendaLS {
    TEvento evento;
    TAgendaLS sig;
};

TAgendaLS crearAgendaLS() {
    TAgendaLS p = NULL;
    return p;
}

void agregarEnAgendaLS(TAgendaLS &agenda, TEvento evento) {

    TAgendaLS r = new rep_agendaLS;
    r->evento = evento;

    if (agenda == NULL) {
        r->sig = NULL;
        agenda = r;
        
    } else if (compararTFechas(fechaTEvento(agenda->evento), fechaTEvento(r->evento)) == 1) {
        r->sig = agenda;
        agenda = r;

    } else {
        TAgendaLS q = agenda;

        while (q->sig != NULL && compararTFechas(fechaTEvento(r->evento), fechaTEvento(q->sig->evento)) == 1) {
            q = q->sig;
        }

        while (q->sig != NULL && compararTFechas(fechaTEvento(r->evento), fechaTEvento(q->sig->evento)) == 0 && idTEvento(q->sig->evento) > idTEvento(r->evento)) {
            q = q->sig;
        }
        r->sig = q->sig;
        q->sig = r;
    }
}

void imprimirAgendaLS(TAgendaLS agenda) {
    while (agenda != NULL) {
        imprimirTEvento(agenda->evento);
        agenda = agenda->sig;
    }
}

void liberarAgendaLS(TAgendaLS &agenda) {
    TAgendaLS p;

    while (agenda != NULL) {
        p = agenda;
        agenda = agenda->sig;
        liberarTEvento(p->evento);
        delete p;
    }
    
    delete agenda;
    agenda = NULL;
}

bool esVaciaAgendaLS(TAgendaLS agenda){
    return (agenda==NULL);
}

TAgendaLS copiarAgendaLS(TAgendaLS agenda){
    TAgendaLS copy, result;

    if (agenda == NULL) {
        result = NULL;
    } else {
        TAgendaLS last = NULL;
        while (agenda != NULL) {
            copy = new rep_agendaLS;
            copy->evento = copiarTEvento(agenda->evento);
            copy->sig = NULL;

            if (last == NULL) {
                result = last = copy;
            } else {
                last->sig = copy;
                last = copy;
            }
            agenda = agenda->sig;
        }
    }
    return result;
}

bool estaEnAgendaLS(TAgendaLS agenda, int id) {
    bool result = false;
    if (agenda == NULL) {
        result = false;
    } else {
        while (agenda != NULL) {
            if (idTEvento(agenda->evento) == id) {
                result = true;
                break;
        } else {
            agenda = agenda->sig;
        }
        }
    }
    return result;
}

TEvento obtenerDeAgendaLS(TAgendaLS agenda, int id) {
    TEvento result = NULL;

    if (agenda == NULL) {
        result = NULL;
    } else {
        while (agenda != NULL) {
            if (idTEvento(agenda->evento) == id) {
                result = agenda->evento;
            }
        agenda = agenda->sig;
        }
    }
    return result;
}

void posponerEnAgendaLS(TAgendaLS &agenda, int id, nat n) {

    if (idTEvento(agenda->evento) == id) {
        posponerTEvento(agenda->evento, n);

        TAgendaLS eveAPos = agenda;
        
        agenda = agenda->sig;
        TAgendaLS q = agenda;

        while (q->sig != NULL && compararTFechas(fechaTEvento(eveAPos->evento), fechaTEvento(q->sig->evento)) == 1) {
            q = q->sig;
        }

        eveAPos->sig = q->sig; 
        q->sig = eveAPos;

    } else {
        TAgendaLS q = agenda;

        while (q->sig != NULL && idTEvento(q->sig->evento) != id) {
            q = q->sig;
        }

        TAgendaLS etp = q->sig;
        posponerTEvento(etp->evento, n);

        q->sig = etp->sig;

        while (q->sig != NULL && compararTFechas(fechaTEvento(etp->evento), fechaTEvento(q->sig->evento)) == 1) {
            q = q->sig;
        }

        etp->sig = q->sig;
        q->sig = etp;
    }
}

void imprimirEventosFechaLS(TAgendaLS agenda, TFecha fecha) {
    while (agenda != NULL) {
        if (compararTFechas(fechaTEvento(agenda->evento), fecha) == 0) {
            imprimirTEvento(agenda->evento);
        }
        agenda = agenda->sig;
    }
}

bool hayEventosFechaLS(TAgendaLS agenda, TFecha fecha) {
    bool result = false;

    if (agenda == NULL) {
        result = false;
    } else {
        while (agenda != NULL) {
            if (compararTFechas(fechaTEvento(agenda->evento), fecha) == 0) {
                result = true;
        }
        agenda = agenda->sig;
        }
    }
    return result;
}

void removerDeAgendaLS(TAgendaLS &agenda, int id) {
    TAgendaLS toRemove;

    //Caso base: elimina el primer nodo
    if (idTEvento(agenda->evento) == id) {

        toRemove = agenda;
        agenda = agenda->sig;
        liberarTEvento(toRemove->evento);
        delete toRemove;

    } else {
        //Caso intermedio: hay que remover un nodo dentro de la lista
        TAgendaLS iter = agenda;

        while (iter->sig != NULL && idTEvento(iter->sig->evento) != id) {
            iter = iter->sig;
        }

        toRemove = iter->sig;
        iter->sig = toRemove->sig;
        liberarTEvento(toRemove->evento);
        delete toRemove;
    }
}

TEvento primerEventoAgendaLS(TAgendaLS agenda){
    if (agenda == NULL) {
        return NULL;
    } else {
        return agenda->evento;
    }
}