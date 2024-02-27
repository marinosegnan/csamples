// int a;     // errore del linker
typedef char* pluto;       // OK reincluderlo
typedef struct aa *bb, cc; // OK reincluderlo, solo nomi

// typedef struct dd { int y;} ee;  // Eroore: ridefinizione
