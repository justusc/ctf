/*Copyright (c) 2014, Edgar Solomonik, all rights reserved.*/
#include "../shared/util.h"
#include "../shared/blas_symbs.h"
#include "untyped_tensor.h"
#include "algstrct.h"

namespace CTF_int {

  void sgemm(char           tA,
             char           tB,
             int            m,
             int            n,
             int            k,
             float          alpha,
             float  const * A,
             float  const * B,
             float          beta,
             float  *       C){
    int lda_A, lda_B, lda_C;
    lda_C = m;
    if (tA == 'n' || tA == 'N'){
      lda_A = m;
    } else {
      lda_A = k;
    }
    if (tB == 'n' || tB == 'N'){
      lda_B = k;
    } else {
      lda_B = n;
    }
    CTF_BLAS::SGEMM(&tA,&tB,&m,&n,&k,&alpha,A,&lda_A,B,&lda_B,&beta,C,&lda_C);
  }


  void cidgemm(char           tA,
               char           tB,
               int            m,
               int            n,
               int            k,
               double         alpha,
               double const * A,
               double const * B,
               double         beta,
               double *       C){
    int lda_A, lda_B, lda_C;
    lda_C = m;
    if (tA == 'n' || tA == 'N'){
      lda_A = m;
    } else {
      lda_A = k;
    }
    if (tB == 'n' || tB == 'N'){
      lda_B = k;
    } else {
      lda_B = n;
    }
    CTF_BLAS::DGEMM(&tA,&tB,&m,&n,&k,&alpha,A,&lda_A,B,&lda_B,&beta,C,&lda_C);
  }

  void cgemm(char                        tA,
             char                        tB,
             int                         m,
             int                         n,
             int                         k,
             std::complex<float>         alpha,
             std::complex<float> const * A,
             std::complex<float> const * B,
             std::complex<float>         beta,
             std::complex<float> *       C){
    int lda_A, lda_B, lda_C;
    lda_C = m;
    if (tA == 'n' || tA == 'N'){
      lda_A = m;
    } else {
      lda_A = k;
    }
    if (tB == 'n' || tB == 'N'){
      lda_B = k;
    } else {
      lda_B = n;
    }
    CTF_BLAS::CGEMM(&tA,&tB,&m,&n,&k,&alpha,A,&lda_A,B,&lda_B,&beta,C,&lda_C);
  }


  void zgemm(char                         tA,
             char                         tB,
             int                          m,
             int                          n,
             int                          k,
             std::complex<double>         alpha,
             std::complex<double> const * A,
             std::complex<double> const * B,
             std::complex<double>         beta,
             std::complex<double> *       C){
    int lda_A, lda_B, lda_C;
    lda_C = m;
    if (tA == 'n' || tA == 'N'){
      lda_A = m;
    } else {
      lda_A = k;
    }
    if (tB == 'n' || tB == 'N'){
      lda_B = k;
    } else {
      lda_B = n;
    }
    CTF_BLAS::ZGEMM(&tA,&tB,&m,&n,&k,&alpha,A,&lda_A,B,&lda_B,&beta,C,&lda_C);
  }
  algstrct::algstrct(int el_size_){
    el_size = el_size_;
  }

  MPI_Op algstrct::addmop() const {
    printf("CTF ERROR: no addition MPI_Op present for this algebraic structure\n");
    ASSERT(0);
    return MPI_SUM;
  }

  MPI_Datatype algstrct::mdtype() const {
    printf("CTF ERROR: no MPI_Datatype present for this algebraic structure\n");
    ASSERT(0);
    return MPI_CHAR;
  }

  char const * algstrct::addid() const {
    return NULL;
  }

  char const * algstrct::mulid() const {
    return NULL;
  }

  void algstrct::addinv(char const * a, char * b) const {
    printf("CTF ERROR: no additive inverse present for this algebraic structure\n");
    ASSERT(0);
  }

  void algstrct::add(char const * a, char const * b, char * c) const {
    printf("CTF ERROR: addition operation present for this algebraic structure\n");
    ASSERT(0);
  }

  void algstrct::mul(char const * a, char const * b, char * c) const {
    printf("CTF ERROR: multiplication operation present for this algebraic structure\n");
    ASSERT(0);
  }

  void algstrct::min(char const * a, char const * b, char * c) const {
    printf("CTF ERROR: min operation present for this algebraic structure\n");
    ASSERT(0);
  }

  void algstrct::max(char const * a, char const * b, char * c) const {
    printf("CTF ERROR: max operation present for this algebraic structure\n");
    ASSERT(0);
  }

  void algstrct::cast_int(int64_t i, char * c) const {
    printf("CTF ERROR: integer scaling not possible for this algebraic structure\n");
    ASSERT(0);
  }

  void algstrct::cast_double(double d, char * c) const {
    printf("CTF ERROR: double scaling not possible for this algebraic structure\n");
    ASSERT(0);
  }

  double algstrct::cast_to_double(char const * c) const {
    printf("CTF ERROR: double cast not possible for this algebraic structure\n");
    ASSERT(0);
    return 0.0;
  }

  int64_t algstrct::cast_to_int(char const * c) const {
    printf("CTF ERROR: int cast not possible for this algebraic structure\n");
    ASSERT(0);
    return 0;
  }

  void algstrct::print(char const * a, FILE * fp) const {
    for (int i=0; i<el_size; i++){
      fprintf(fp,"%x",a[i]);
    }
  }

  void algstrct::min(char * c) const {
    printf("CTF ERROR: min limit not present for this algebraic structure\n");
    ASSERT(0);
  }

  void algstrct::max(char * c) const {
    printf("CTF ERROR: max limit not present for this algebraic structure\n");
    ASSERT(0);
  }

  void algstrct::scal(int          n,
                      char const * alpha,
                      char       * X,
                      int          incX)  const {
    printf("CTF ERROR: scal not present for this algebraic structure\n");
    ASSERT(0);
  }

  void algstrct::axpy(int          n,
                      char const * alpha,
                      char const * X,
                      int          incX,
                      char       * Y,
                      int          incY)  const {
    printf("CTF ERROR: axpy not present for this algebraic structure\n");
    ASSERT(0);
  }

   void algstrct::gemm(char         tA,
                       char         tB,
                       int          m,
                       int          n,
                       int          k,
                       char const * alpha,
                       char const * A,
                       char const * B,
                       char const * beta,
                       char *       C)  const {
    printf("CTF ERROR: gemm not present for this algebraic structure\n");
    ASSERT(0);
  }
 
  bool algstrct::isequal(char const * a, char const * b) const {
    if (a == NULL && b == NULL) return true;
    bool iseq = true;
    for (int i=0; i<el_size; i++) {
      if (a[i] != b[i]) iseq = false;
    }
    return iseq;
  }
      
  void algstrct::acc(char * b, char const * beta, char const * a, char const * alpha) const {
    char tmp[el_size];
    mul(b, beta, tmp);
    mul(a, alpha, b);
    add(b, tmp, b);
  }

  void algstrct::copy(char * a, char const * b) const {
    memcpy(a, b, el_size);
  }
  
  void algstrct::copy_pair(char * a, char const * b) const {
    memcpy(a, b, pair_size());
  }
      
  void algstrct::copy(char * a, char const * b, int64_t n) const {
    memcpy(a, b, el_size*n);
  }
  
  void algstrct::copy_pairs(char * a, char const * b, int64_t n) const {
    memcpy(a, b, pair_size()*n);
  }


  void algstrct::copy(int n, char const * a, int inc_a, char * b, int inc_b) const {
    switch (el_size) {
      case 4:
        CTF_BLAS::SCOPY(&n, (float const*)a, &inc_a, (float*)b, &inc_b);
        break;
      case 8:
        CTF_BLAS::DCOPY(&n, (double const*)a, &inc_a, (double*)b, &inc_b);
        break;
      case 16:
        CTF_BLAS::ZCOPY(&n, (std::complex<double> const*)a, &inc_a, (std::complex<double>*)b, &inc_b);
        break;
      default:
#ifdef USE_OMP
        #pragma omp parallel for
#endif
        for (int i=0; i<n; i++){
          copy(b+el_size*inc_b*i, a+el_size*inc_a*i);
        }
        break;
    }
  }

  void algstrct::copy(int64_t      m,
                      int64_t      n,
                      char const * a,
                      int64_t      lda_a,
                      char *       b,
                      int64_t      lda_b) const {
    if (lda_a == m && lda_b == n){
      memcpy(b,a,el_size*m*n);
    } else {
      for (int i=0; i<n; i++){
        memcpy(b+el_size*lda_b*i,a+el_size*lda_a*i,m*el_size);
      }
    }
  }
 
  void algstrct::copy(int64_t      m,
                      int64_t      n,
                      char const * a,
                      int64_t      lda_a,
                      char const * alpha,
                      char *       b,
                      int64_t      lda_b,
                      char const * beta) const {
    if (!isequal(beta, mulid())){
      if (isequal(beta, addid())){
        if (lda_b == 1)
          set(b, addid(), m*n);
        else {
          for (int i=0; i<n; i++){
            set(b+i*lda_b*el_size, addid(), m);
          }
        }
      } else {
        if (lda_b == m)
          scal(m*n, beta, b, 1);
        else {
          for (int i=0; i<n; i++){
            scal(m, beta, b+i*lda_b*el_size, 1);
          }
        }
      }
    }
    if (lda_a == m && lda_b == m){
      axpy(m*n, alpha, a, 1, b, 1);
    } else {
      for (int i=0; i<n; i++){
        axpy(m, alpha, a+el_size*lda_a*i, 1, b+el_size*lda_b*i, 1);
      }
    }
  }           

  void algstrct::set(char * a, char const * b, int64_t n) const {
    switch (el_size) {
      case 4: {
          float * ia = (float*)a;
          float ib = *((float*)b);
          std::fill(ia, ia+n, ib);
        }
        break;
      case 8: {
          double * ia = (double*)a;
          double ib = *((double*)b);
          std::fill(ia, ia+n, ib);
        }
        break;
      case 16: {
          std::complex<double> * ia = (std::complex<double>*)a;
          std::complex<double> ib = *((std::complex<double>*)b);
          std::fill(ia, ia+n, ib);
        }
        break;
      default: {
          for (int i=0; i<n; i++) {
            memcpy(a+i*el_size, b, el_size);
          }
        }
        break;
    }
  }

  void algstrct::set_pair(char * a, int64_t key, char const * vb) const {
    memcpy(a, &key, sizeof(int64_t));
    memcpy(a+sizeof(int64_t), vb, el_size);
  }

  void algstrct::set_pairs(char * a, char const * b, int64_t n) const {
    for (int i=0; i<n; i++) {
      memcpy(a + i*(sizeof(int64_t)+el_size), b, (sizeof(int64_t)+el_size));
    }
  }
 
  int64_t algstrct::get_key(char const * a) const {
    return (int64_t)*a;
  }
     
  char const * algstrct::get_value(char const * a) const {
    return a+sizeof(int64_t);
  }
      
  ConstPairIterator::ConstPairIterator(PairIterator const & pi){
    sr=pi.sr; ptr=pi.ptr; 
  }

  ConstPairIterator::ConstPairIterator(algstrct const * sr_, char const * ptr_){ 
    sr=sr_; ptr=ptr_; 
  }

  ConstPairIterator ConstPairIterator::operator[](int n) const { 
    return ConstPairIterator(sr,ptr+(sr->el_size+sizeof(int64_t))*n);
  }

  int64_t ConstPairIterator::k() const {
    return ((int64_t*)ptr)[0];
  }

  char const * ConstPairIterator::d() const {
    return ptr+sizeof(int64_t);
  }

  void ConstPairIterator::read(char * buf, int64_t n) const {
    memcpy(buf, ptr, (sizeof(int64_t)+sr->el_size)*n);
  }
  
  void ConstPairIterator::read_val(char * buf) const {
    memcpy(buf, ptr+sizeof(int64_t), sr->el_size);
  }
  
  PairIterator::PairIterator(algstrct const * sr_, char * ptr_){
    sr=sr_;
    ptr=ptr_;
  }

  PairIterator PairIterator::operator[](int n) const { 
    return PairIterator(sr,ptr+(sr->el_size+sizeof(int64_t))*n);
  }

  int64_t PairIterator::k() const {
    return ((int64_t*)ptr)[0];
  }

  char const * PairIterator::d() const {
    return ptr+sizeof(int64_t);
  }

  void PairIterator::read(char * buf, int64_t n) const {
    memcpy(buf, ptr, (sizeof(int64_t)+sr->el_size)*n);
  }
  
  void PairIterator::read_val(char * buf) const {
    memcpy(buf, ptr+sizeof(int64_t), sr->el_size);
  }

  void PairIterator::write(char const * buf, int64_t n){
    memcpy(ptr, buf, (sizeof(int64_t)+sr->el_size)*n);
  }

  void PairIterator::write(PairIterator const iter, int64_t n){
    memcpy(ptr, iter.ptr, (sizeof(int64_t)+sr->el_size)*n);
  }

  void PairIterator::write(ConstPairIterator const iter, int64_t n){
    memcpy(ptr, iter.ptr, (sizeof(int64_t)+sr->el_size)*n);
  }

  void PairIterator::write_val(char const * buf){
    memcpy(ptr+sizeof(int64_t), buf, sr->el_size);
  }

  void PairIterator::write_key(int64_t key){
    ((int64_t*)ptr)[0] = key;
  }

  template<int l>
  struct CompPair{
    int64_t key;
    char data[l];
    bool operator < (const CompPair& other) const {
      return (key < other.key);
    }
  };
  template struct CompPair<1>;
  template struct CompPair<2>;
  template struct CompPair<4>;
  template struct CompPair<8>;
  template struct CompPair<12>;
  template struct CompPair<16>;
  template struct CompPair<20>;
  template struct CompPair<24>;
  template struct CompPair<28>;
  template struct CompPair<32>;
  
  struct CompPtrPair{
    int64_t key;
    int64_t idx;
    bool operator < (const CompPtrPair& other) const {
      return (key < other.key);
    }
  };

  void PairIterator::sort(int64_t n){
    switch (sr->el_size){
      case 1:
        std::sort((CompPair<1>*)ptr,((CompPair<1>*)ptr)+n);
        break;
      case 2:
        std::sort((CompPair<2>*)ptr,((CompPair<2>*)ptr)+n);
        break;
      case 4:
        std::sort((CompPair<4>*)ptr,((CompPair<4>*)ptr)+n);
        break;
      case 8:
        std::sort((CompPair<8>*)ptr,((CompPair<8>*)ptr)+n);
        break;
      case 12:
        std::sort((CompPair<12>*)ptr,((CompPair<12>*)ptr)+n);
        break;
      case 16:
        std::sort((CompPair<16>*)ptr,((CompPair<16>*)ptr)+n);
        break;
      case 20:
        std::sort((CompPair<20>*)ptr,((CompPair<20>*)ptr)+n);
        break;
      case 24:
        std::sort((CompPair<24>*)ptr,((CompPair<24>*)ptr)+n);
        break;
      case 28:
        std::sort((CompPair<28>*)ptr,((CompPair<28>*)ptr)+n);
        break;
      case 32:
        std::sort((CompPair<32>*)ptr,((CompPair<32>*)ptr)+n);
        break;
      default:
        //Causes a bogus uninitialized variable warning with GNU
        CompPtrPair ptr_pairs[n];
#ifdef USE_OMP
        #pragma omp parallel for
#endif
        for (int64_t i=0; i<n; i++){
          ptr_pairs[i].key = *(int64_t*)(ptr+i*(sizeof(int64_t)+sr->el_size));
          ptr_pairs[i].idx = i;
        }
        //FIXME :(
        char swap_buffer[(sizeof(int64_t)+sr->el_size)*n];
    
        memcpy(swap_buffer, ptr, (sizeof(int64_t)+sr->el_size)*n);
        
#ifdef USE_OMP
        #pragma omp parallel for
#endif
        for (int64_t i=0; i<n; i++){
          memcpy(ptr+i*(sizeof(int64_t)+sr->el_size), 
                 swap_buffer+ptr_pairs[i].idx*(sizeof(int64_t)+sr->el_size),
                 sizeof(int64_t)+sr->el_size);
        }
        break;
    }
  }

  int64_t PairIterator::lower_bound(int64_t n, ConstPairIterator op){
    switch (sr->el_size){
      case 1:
        return std::lower_bound((CompPair<1>*)ptr,((CompPair<1>*)ptr)+n, ((CompPair<1>*)op.ptr)[0]) - (CompPair<1>*)ptr;
        break;
      case 2:
        return std::lower_bound((CompPair<2>*)ptr,((CompPair<2>*)ptr)+n, ((CompPair<2>*)op.ptr)[0]) - (CompPair<2>*)ptr;
        break;
      case 4:
        return std::lower_bound((CompPair<4>*)ptr,((CompPair<4>*)ptr)+n, ((CompPair<4>*)op.ptr)[0]) - (CompPair<4>*)ptr;
        break;
      case 8:
        return std::lower_bound((CompPair<8>*)ptr,((CompPair<8>*)ptr)+n, ((CompPair<8>*)op.ptr)[0]) - (CompPair<8>*)ptr;
        break;
      case 12:
        return std::lower_bound((CompPair<12>*)ptr,((CompPair<12>*)ptr)+n, ((CompPair<12>*)op.ptr)[0]) - (CompPair<12>*)ptr;
        break;
      case 16:
        return std::lower_bound((CompPair<16>*)ptr,((CompPair<16>*)ptr)+n, ((CompPair<16>*)op.ptr)[0]) - (CompPair<16>*)ptr;
        break;
      case 20:
        return std::lower_bound((CompPair<20>*)ptr,((CompPair<20>*)ptr)+n, ((CompPair<20>*)op.ptr)[0]) - (CompPair<20>*)ptr;
        break;
      case 24:
        return std::lower_bound((CompPair<24>*)ptr,((CompPair<24>*)ptr)+n, ((CompPair<24>*)op.ptr)[0]) - (CompPair<24>*)ptr;
        break;
      case 28:
        return std::lower_bound((CompPair<28>*)ptr,((CompPair<28>*)ptr)+n, ((CompPair<28>*)op.ptr)[0]) - (CompPair<28>*)ptr;
        break;
      case 32:
        return std::lower_bound((CompPair<32>*)ptr,((CompPair<32>*)ptr)+n, ((CompPair<32>*)op.ptr)[0]) - (CompPair<32>*)ptr;
        break;
      default: {
        int64_t keys[n];
#ifdef USE_OMP
        #pragma omp parallel for
#endif
        for (int64_t i=0; i<n; i++){
          keys[i] = (*this)[i].k();
        }
        return std::lower_bound(keys, keys+n, op.k())-keys;
        } break;
    }
  }

}

