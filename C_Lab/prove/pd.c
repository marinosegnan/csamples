#include "a.h"

typedef struct dcomplex{int a; double d;}mia, *pdcomplex;
   
mia pp ={1,3.14};
pdcomplex pippo(int a,double d){
pp.a = a;
pp.d = d;
return &pp;
}
