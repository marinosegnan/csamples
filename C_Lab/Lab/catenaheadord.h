#ifndef _RICLISTAELH_H_
#define _RICLISTAELH_H_
#include <elements.h>

elem* inserth(elem* start, void* nuovo);
elem* removeh(elem* start, void* target);
void removehnr(elem* start, void* nuovo);
void inserthnr(elem* start, void* nuovo);

#endif