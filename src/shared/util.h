/*Copyright (c) 2011, Edgar Solomonik, all rights reserved.*/

#ifndef __UTIL_H__
#define __UTIL_H__

#include "../interface/common.h"

volatile static int64_t int64_t_max = INT64_MAX;

#include <inttypes.h>
/*
#if (defined(__X86_64__) || defined(__IA64__) || defined(__amd64__) || \
     defined(__ppc64__) || defined(_ARCH_PPC) || defined(BGQ) || defined(BGP))
#define PRId64 "%ld"
#define PRIu64 "%lu"
#else //if (defined(__i386__))
#define PRId64 "%lld"
#define PRIu64 "%llu"
//#else
#endif
*/
#include "int_timer.h"
#include "pmpi.h"


namespace CTF_int {

  /* Force redistributions always by setting to 1 */
  #define REDIST 0
  //#define VERIFY 0
  #define VERIFY_REMAP 0
  #define FOLD_TSR 1
  #define PERFORM_DESYM 1
  #define ALLOW_NVIRT 1024
  #define DIAG_RESCALE
  #define USE_SYM_SUM
  #define HOME_CONTRACT
  #define USE_BLOCK_RESHUFFLE

  #define MAX_ORD 8
  #define LOOP_MAX_ORD(F,...) \
    F(0,__VA_ARGS__) F(1,__VA_ARGS__) F(2,__VA_ARGS__) F(3,__VA_ARGS__) \
    F(4,__VA_ARGS__) F(5,__VA_ARGS__) F(6,__VA_ARGS__) F(7,__VA_ARGS__) 

  #define ORD_CASE(ord,F,...) \
    case ord: \
      F<ord>(__VA_ARGS__); \
      break;

  #define ORD_CASE_RET(ord,R,F,...) \
    case ord: \
      R = F<ord>(__VA_ARGS__); \
      break;

  #define SWITCH_ORD_CALL(F,act_ord,...) \
    switch (act_ord){ \
      LOOP_MAX_ORD(ORD_CASE,F,__VA_ARGS__) \
      default: \
        assert(0); \
        break; \
    }

  #define SWITCH_ORD_CALL_RET(R,F,act_ord,...) \
    switch (act_ord){ \
      LOOP_MAX_ORD(ORD_CASE_RET,R,F,__VA_ARGS__) \
      default: \
        assert(0); \
        break; \
    }


  #ifndef __APPLE__
  #ifndef OMP_OFF
  #define USE_OMP
  #include "omp.h"
  #endif
  #endif

  #define CTF_COUNT_FLOPS
  #ifdef CTF_COUNT_FLOPS
  #define CTF_FLOPS_ADD(n) CTF_int::flops_add(n)
  #else
  #define CTF_FLOPS_ADD(n) 
  #endif

  //doesn't work with OpenMPI
  //volatile static int64_t mpi_int64_t = MPI_LONG_LONG_INT;
  #ifdef _SC_PHYS_PAGES
  inline
  int64_t getTotalSystemMemory()
  {
    int64_t pages = (int64_t)sysconf(_SC_PHYS_PAGES);
    int64_t page_size = (int64_t)sysconf(_SC_PAGE_SIZE);
    return pages * page_size;
  }
  #else
  inline
  int64_t getTotalSystemMemory()
  {
    //Assume system memory is 1 GB
    return ((int64_t)1)<<30;
  }
  #endif

  #include <execinfo.h>
  #include <signal.h>
  #define ABORT                                   \
    do{                                           \
    handler(); MPI_Abort(MPI_COMM_WORLD, -1); } while(0)

  //proper modulus for 'a' in the range of [-b inf]
  #ifndef WRAP
  #define WRAP(a,b)       ((a + b)%b)
  #endif

  #ifndef ALIGN_BYTES
  #define ALIGN_BYTES     16
  #endif

  #ifndef MIN
  #define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
  #endif

  #ifndef MAX
  #define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )
  #endif

  #ifndef LOC
  #define LOC \
    do { printf("debug:%s:%d ",__FILE__,__LINE__); } while(0)
  #endif

  #ifndef THROW_ERROR
  #define THROW_ERROR(...) \
  do { printf("error:%s:%d ",__FILE__,__LINE__); printf(__VA_ARGS__); printf("\n"); quit(1); } while(0)
  #endif

  #ifndef WARN
  #define WARN(...) \
  do { printf("warning: "); printf(__VA_ARGS__); printf("\n"); } while(0)
  #endif

  #if defined(VERBOSE)
    #ifndef VPRINTF
    #define VPRINTF(i,...)            \
      do { if (i<=VERBOSE) {          \
        printf("CTF: "); printf(__VA_ARGS__); } \
      } while (0)
    #endif
  #else
    #ifndef VPRINTF
    #define VPRINTF(...) do { } while (0)
    #endif
  #endif


  #ifdef DEBUG
    #ifndef DPRINTF
    #define DPRINTF(__icx,...) \
      do { if (__icx<=DEBUG) { LOC; printf(__VA_ARGS__); } } while (0)
    #endif
    #ifndef DEBUG_PRINTF
    #define DEBUG_PRINTF(...) \
      do { DPRINTF(5,__VA_ARGS__); } while(0)
    #endif
    #ifndef RANK_PRINTF
    #define RANK_PRINTF(myRank,rank,...) \
      do { if (myRank == rank) { LOC; printf("P[%d]: ",rank); printf(__VA_ARGS__); } } while(0)
    #endif
          #ifndef PRINT_INT
          #define PRINT_INT(var) \
            do {  LOC; printf(#var); printf("=%d\n",var); } while(0)
          #endif
          #ifndef PRINT_DOUBLE
          #define PRINT_DOUBLE(var) \
            do {  LOC; printf(#var); printf("=%lf\n",var); } while(0)
          #endif
  #else
    #ifndef DPRINTF
    #define DPRINTF(...) do { } while (0)
    #endif
    #ifndef DEBUG_PRINTF
    #define DEBUG_PRINTF(...) do {} while (0)
    #endif
    #ifndef RANK_PRINTF
    #define RANK_PRINTF(...) do { } while (0)

    #endif
    #ifndef PRINT_INT
    #define PRINT_INT(var)
    #endif
  #endif


  #ifdef DUMPDEBUG
    #ifndef DUMPDEBUG_PRINTF
    #define DUMPDEBUG_PRINTF(...) \
      do { LOC; printf(__VA_ARGS__); } while(0)
    #endif
  #else
    #ifndef DUMPDEBUG_PRINTF
    #define DUMPDEBUG_PRINTF(...)
    #endif
  #endif

  /*#ifdef TAU
  #include <stddef.h>
  #include <Profile/Profiler.h>
  #define TAU_FSTART(ARG)                                 \
      TAU_PROFILE_TIMER(timer##ARG, #ARG, "", TAU_USER);  \
      TAU_PROFILE_START(timer##ARG)

  #define TAU_FSTOP(ARG)                                  \
      TAU_PROFILE_STOP(timer##ARG)

  #else*/
  #ifndef TAU
  #define TAU_PROFILE(NAME,ARG,USER)
  #define TAU_PROFILE_TIMER(ARG1, ARG2, ARG3, ARG4)
  #define TAU_PROFILER_CREATE(ARG1, ARG2, ARG3, ARG4)
  #define TAU_PROFILE_STOP(ARG)
  #define TAU_PROFILE_START(ARG)
  #define TAU_PROFILE_SET_NODE(ARG)
  #define TAU_PROFILE_SET_CONTEXT(ARG)
  #define TAU_FSTART(ARG)
  #define TAU_FSTOP(ARG)
  #endif
  #define TIME(STRING) TAU_PROFILE(STRING, " ", TAU_DEFAULT)
  #define MST_ALIGN_BYTES ALIGN_BYTES

  struct mem_transfer {
    void * old_ptr;
    void * new_ptr;
  };

  std::list<mem_transfer> contract_mst();
  int untag_mem(void * ptr);
  int free_cond(void * ptr);
  void mem_create();
  void mst_create(int64_t size);
  void mem_exit(int rank);

  /**
   * \brief computes the size of a tensor in SY (NOT HOLLOW) packed symmetric layout
   * \param[in] order tensor dimension
   * \param[in] len tensor edge _elngths
   * \param[in] sym tensor symmetries
   * \return size of tensor in packed layout
   */
  int64_t sy_packed_size(int order, const int* len, const int* sym);


  /**
   * \brief computes the size of a tensor in packed symmetric (SY, SH, or AS) layout
   * \param[in] order tensor dimension
   * \param[in] len tensor edge _elngths
   * \param[in] sym tensor symmetries
   * \return size of tensor in packed layout
   */
  int64_t packed_size(int order, const int* len, const int* sym);


  /*
   * \brief calculates dimensional indices corresponding to a symmetric-packed index
   *        For each symmetric (SH or AS) group of size sg we have
   *          idx = n*(n-1)*...*(n-sg) / d*(d-1)*...
   *        therefore (idx*sg!)^(1/sg) >= n-sg
   *        or similarly in the SY case ... >= n
   *
   * \param[in] order number of dimensions in the tensor 
   * \param[in] lens edge lengths 
   * \param[in] sym symmetry
   * \param[in] idx index in the global tensor, in packed format
   * \param[out] idx_arr preallocated to size order, computed to correspond to idx
   */
  void calc_idx_arr(int         order,
                    int const * lens,
                    int const * sym,
                    int64_t     idx,
                    int *       idx_arr);

  /** \brief same as above except assumes sym only NS or SY **/
  void sy_calc_idx_arr(int         order,
                       int const * lens,
                       int const * sym,
                       int64_t     idx,
                       int *       idx_arr);

  /**
   * \brief computes the size of a tensor in packed symmetric layout
   * \param[in] n a positive number
   * \param[out] nfactor number of factors in n
   * \param[out] factor array of length nfactor, corresponding to factorization of n
   */
  void factorize(int n, int *nfactor, int **factor);

  inline
  int gcd(int a, int b){
    if (b==0) return a;
    return gcd(b, a%b);
  }

  inline
  int lcm(int a, int b){
    return a*b/gcd(a,b);
  }

  /**
   * \brief Copies submatrix to submatrix (column-major)
   * \param[in] nrow number of rows
   * \param[in] ncol number of columns
   * \param[in] lda_A lda along rows for A
   * \param[in] lda_B lda along rows for B
   * \param[in] A matrix to read from
   * \param[in,out] B matrix to write to
   */
  inline
  void lda_cpy(int          el_size,
               int          nrow,
               int          ncol,
               int          lda_A,
               int          lda_B,
               const char * A,
               char *       B){
    if (lda_A == nrow && lda_B == nrow){
      memcpy(B,A,el_size*nrow*ncol);
    } else {
      int i;
      for (i=0; i<ncol; i++){
        memcpy(B+el_size*lda_B*i,A+el_size*lda_A*i,nrow*el_size);
      }
    }
  }

  /**
   * \brief we receive a contiguous buffer kb-by-n B and (k-kb)-by-n B_aux
   * which is the block below.
   * To get a k-by-n buffer, we need to combine this buffer with our original
   * block. Since we are working with column-major ordering we need to interleave
   * the blocks. Thats what this function does.
   * \param[in] el_size element size
   * \param[in,out] B the buffer to coalesce into
   * \param[in] B_aux the second buffer to coalesce from
   * \param[in] k the total number of rows
   * \param[in] n the number of columns
   * \param[in] kb the number of rows in a B originally
   */
/*  template<typename dtype>
  void coalesce_bwd(dtype         *B,
                    dtype const   *B_aux,
                    int           k,
                    int           n,
                    int           kb){
    int i;
    for (i=n-1; i>=0; i--){
      memcpy(B+i*k+kb, B_aux+i*(k-kb), (k-kb)*sizeof(dtype));
      if (i>0) memcpy(B+i*k, B+i*kb, kb*sizeof(dtype));
    }
  }*/
  inline
  void coalesce_bwd(int           el_size,
                    char         *B,
                    char const   *B_aux,
                    int           k,
                    int           n,
                    int           kb){
    int i;
    for (i=n-1; i>=0; i--){
      memcpy(B+el_size*(i*k+kb), B_aux+el_size*(i*(k-kb)), (k-kb)*el_size);
      if (i>0){
        if (k-kb>=kb){
          memcpy(B+el_size*i*k, B+el_size*i*kb, kb*el_size);
        } else {
          for (int j=0; j<kb; j+=k-kb){
            memcpy(B+el_size*(i*k+j), B+el_size*i*(kb+j), std::min(k-kb,kb-j)*el_size);
          }
        }
      }
    }
  }
 
  /**
   * \brief permute an array
   *
   * \param order number of elements
   * \param perm permutation array
   * \param arr array to permute
   */
  void permute(int         order,
               int const * perm,
               int *       arr);

  /**
   * \brief permutes a permutation array 
   *
   * \param order number of elements in perm
   * \param order_perm number of elements in arr
   * \param perm permutation array
   * \param arr permutation array to permute
   */
  void permute_target(int         order,
                      int const * perm,
                      int *       arr);



}
#endif

