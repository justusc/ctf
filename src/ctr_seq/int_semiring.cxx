/*Copyright (c) 2014, Edgar Solomonik, all rights reserved.*/
#include "../shared/util.h"
#include "../../include/ctf.hpp"

Int_Semiring::Int_Semiring(Int_Semiring const & other){
  el_size = other.el_size;
  addid = (char*)alloc(el_size);
  memcpy(addid,other.addid,el_size);
  mulid = (char*)alloc(el_size);
  memcpy(mulid,other.mulid,el_size);
  add = other.add;
  mul = other.mul;
  gemm = other.gemm;
}

Int_Semiring::Int_Semiring(
                 int          el_size_, 
                 char const * addid_,
                 char const * mulid_,
                 MPI_Op       addmop_,
                 void (*add_)(char const * a,
                              char const * b,
                              char       * c),
                 void (*mul_)(char const * a,
                              char const * b,
                              char       * c),
                 void (*gemm_)(char         tA,
                               char         tB,
                               int          m,
                               int          n,
                               int          k,
                               char const * alpha,
                               char const * A,
                               char const * B,
                               char const * beta,
                               char *       C)){
  el_size = el_size_;
  addid = (char*)alloc(el_size);
  memcpy(addid,addid_,el_size);
  mulid = (char*)alloc(el_size);
  memcpy(mulid,mulid_,el_size);
  add = add_;
  mul = mul_;
  gemm = gemm_;
}

Int_Semiring::~Int_Semiring(){
  free(addid);
  free(mulid);
}
