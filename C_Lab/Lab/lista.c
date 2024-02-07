#include <lista.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * per la lista, varie possibilita':

 *
 * la lista piu' semplice e' una catena di elementi collegati da un puntatore (next)
 * in questo caso inserzione e cancellazione possono variare l'inizio della lista,
 * quindi le operazioni devono rrestituire sempre  il valore aggiornato, anche se
 * quasi sempre sara' invariato, appesantendo il codice dell'utilizzatore
 * per ovviare si puo' fare in due modi:
 * 1) aggiungere un elemento head dummy che punta al primo: in questo modo
 * inserzione e cancellazione non modificano mai head. tra l'altro, anche se
 * trascurabile, il codice risulta leggermente piu' semplice
 * 2) creare un tipo (struct) lista, che contiene come attributo il puntatore
 * al primo elemento, fungendo quindi da head. Questa soluzione rende piu' chiaro
 * la difefrenza tra lista ed elemento (pensiamo alla lista vuota!). volendo
 * si puo' aggiungere anche qui al suo interno una head per semplificare il codice
 * questa soluzione e' inoltre piu' generale in quanto permette di aggiungere altre
 * proprieta' alla lista, es dimensione etc.
 *
 * per inserire e rimuovere abbiamo implementazioni ricorsive a puro scopo dimostrativo:
 * senza HEAD sono piu' complesse, con HEAD piu' semplici, ma comunque
 * non utilizzabili per liste che non siano "giocattolo"
 *
 * proprieta' elementi della lista:
 * 1) si puo' immaginare di avere una funzione che , dati due elementi, restituisca
 * 0 se sono uguali, <0 se primo minore, >0 se primo maggiore.
 * In questo modo si possono realizzare liste ordinate:
 * l'inserimento avverra' scorrendo la lista fino a trovare il posto corretto
 * 2) duplicati o no? possiamo decidere che permettiamo elementi duplicati
 * oppure no, realizzando quello che si definisce 'insieme' (Set)
 */

void printlista(elem* e)
{
    printf("lista:\n");
    while(e != NULL) {
        printf("%p\n", e->mytype);
        e = e->next;
    }
}
