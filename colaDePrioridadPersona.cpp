#include "../include/colaDePrioridadPersona.h"
#include "../include/utils.h"
#include "../include/evento.h"

struct rep_colaDePrioridadPersona {
  TPersona* heap;
  TFecha* aux;
  nat size;
  nat tope;
  bool maxheap;
};

TColaDePrioridadPersona crearCP(nat N) {
  TColaDePrioridadPersona c = new rep_colaDePrioridadPersona;
  c->heap = new TPersona[N+1];
  c->aux = new TFecha[N+1];
  c->size = N;
  c->tope = 0;
  c->maxheap = false;

  for (nat i = 0; i < N+1; i++) {
    c->heap[i] = NULL;
    c->aux[i] = NULL;
  }

  return c;
}

TFecha obtenerFechaPrioridad(TPersona persona) {
  return fechaTEvento(primerEventoDeTPersona(persona));
}

// Si fecha1 es mayor que fecha2 retorna 1, si es menor retorna -1,
void filtrado_ascendenteMin(nat pos, TColaDePrioridadPersona &cp) {
  while ((pos > 1) && (compararTFechas(obtenerFechaPrioridad(cp->heap[pos]), obtenerFechaPrioridad(cp->heap[pos/2])) == -1)) {
    TPersona aux = cp->heap[pos];
    cp->heap[pos] = cp->heap[pos/2];
    cp->heap[pos/2] = aux;
    pos = pos/2;
  }
}

void filtrado_ascendenteMax(nat pos, TColaDePrioridadPersona &cp) {
  while ((pos > 1) && (compararTFechas(obtenerFechaPrioridad(cp->heap[pos]), obtenerFechaPrioridad(cp->heap[pos/2])) == 1)) {
    TPersona aux = cp->heap[pos];
    cp->heap[pos] = cp->heap[pos/2];
    cp->heap[pos/2] = aux;
    pos = pos/2;
  }
}

void filtrado_ascendente(nat pos, TColaDePrioridadPersona &cp) {
  if (cp->maxheap == false) {
    filtrado_ascendenteMin(pos, cp);
  }
  
  if (cp->maxheap == true) {
    filtrado_ascendenteMax(pos, cp);
  }
}

void filtrado_descendenteMin(nat pos, TColaDePrioridadPersona &cp) {
  while (2*pos <= cp->tope) {
    nat menor = 2*pos;

    if ((menor+1 <= cp->tope) && (compararTFechas(obtenerFechaPrioridad(cp->heap[menor]), obtenerFechaPrioridad(cp->heap[menor+1])) == 1)) {
      menor = menor+1;
    }

    if (compararTFechas(obtenerFechaPrioridad(cp->heap[pos]), obtenerFechaPrioridad(cp->heap[menor])) == 1) {
      TPersona aux = cp->heap[pos];
      cp->heap[pos] = cp->heap[menor];
      cp->heap[menor] = aux;
      pos = menor;
    } else {
      break;
    }
  }
}

void filtrado_descendenteMax(nat pos, TColaDePrioridadPersona &cp) {
  while (2*pos <= cp->tope) {
    nat menor = 2*pos;

    if ((menor+1 <= cp->tope) && (compararTFechas(obtenerFechaPrioridad(cp->heap[menor]), obtenerFechaPrioridad(cp->heap[menor+1])) == -1)) {
      menor = menor+1;
    }

    if (compararTFechas(obtenerFechaPrioridad(cp->heap[pos]), obtenerFechaPrioridad(cp->heap[menor])) == -1) {
      TPersona aux = cp->heap[pos];
      cp->heap[pos] = cp->heap[menor];
      cp->heap[menor] = aux;
      pos = menor;
    } else {
      break;
    }
  }
}

void filtrado_descendente(nat pos, TColaDePrioridadPersona &cp) {
  if (cp->maxheap == false) {
    filtrado_descendenteMin(pos, cp);
  }

  if (cp->maxheap == true) {
    filtrado_descendenteMax(pos, cp);
  }
}

void invertirPrioridad(TColaDePrioridadPersona &cp) {
  cp->maxheap = !cp->maxheap;

  for (nat i = cp->tope / 2; i >= 1; i--) {
    filtrado_descendente(i, cp);
  }
}

void liberarCP(TColaDePrioridadPersona &cp) {
  for (nat i = 1; i <= cp->tope; i++) {
    liberarTPersona(cp->heap[i]);
  }

  delete[] cp->aux;
  delete[] cp->heap;
  delete cp;
  cp = NULL;
}

void insertarEnCP(TPersona persona, TColaDePrioridadPersona &cp) {
  if (cp->tope < cp->size) {
    cp->tope++;
    cp->heap[cp->tope] = persona;
    cp->aux[idTPersona(persona)] = obtenerFechaPrioridad(persona);
    filtrado_ascendente(cp->tope, cp);
  }
}

bool estaVaciaCP(TColaDePrioridadPersona cp) {
  return (cp->tope == 0);
}

TPersona prioritaria(TColaDePrioridadPersona cp) {
  if (cp->heap[1] != NULL) {
    return cp->heap[1];
  } else {
    return NULL;
  }
} 

void eliminarPrioritaria(TColaDePrioridadPersona &cp) {
  if (!estaVaciaCP(cp)) {
    nat i = idTPersona(cp->heap[1]);
    liberarTPersona(cp->heap[1]);
    cp->aux[i] = NULL;

    cp->heap[1] = cp->heap[cp->tope];
    cp->heap[cp->tope] = NULL;
    cp->tope--;

    filtrado_descendente(1, cp);
  }
}

bool estaEnCP(nat id, TColaDePrioridadPersona cp) {
  if (id <= cp->size) {
    if (cp->aux[id] != NULL) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

TFecha prioridad(nat id, TColaDePrioridadPersona cp){
  if (estaEnCP(id, cp)) {
    return cp->aux[id];
  } else {
    return NULL;
  }
}