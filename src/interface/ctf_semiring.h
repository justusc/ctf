#ifndef __CTF_SEMIRING_H__
#define __CTF_SEMIRING_H__

/**
 * \brief semirings defined the elementwise operations computed 
 *         in each tensor contraction
 */
class CTF_Semiring {
  public: 
    int el_size;
    char * addid;
    char * mulid;
    MPI_Op addmop;
    MPI_Datatype mdtype;

    // c = a+b
    void (*add)(char const * a, 
                char const * b,
                char *       c);
    
    // c = a*b
    void (*mul)(char const * a, 
                char const * b,
                char *       c);

    // X["i"]=alpha*X["i"];
    void (*scal)(int          n,
                 char const * alpha,
                 char const * X,
                 int          incX);

    // Y["i"]+=alpha*X["i"];
    void (*axpy)(int          n,
                 char const * alpha,
                 char const * X,
                 int          incX,
                 char       * Y,
                 int          incY);

    // beta*C["ij"]=alpha*A^tA["ik"]*B^tB["kj"];
    void (*gemm)(char         tA,
                 char         tB,
                 int          m,
                 int          n,
                 int          k,
                 char const * alpha,
                 char const * A,
                 char const * B,
                 char const * beta,
                 char *       C);

  public:
    /**
     * \brief copy constructor
     * \param[in] other another semiring to copy from
     */
    CTF_Semiring(CTF_Semiring const &other);

    /**
     * \brief constructor creates semiring with all parameters
     * \param[in] el_size number of bytes in each element in the semiring set
     * \param[in] addid additive identity element 
     *              (e.g. 0.0 for the (+,*) semiring over doubles)
     * \param[in] mulid multiplicative identity element 
     *              (e.g. 1.0 for the (+,*) semiring over doubles)
     * \param[in] addmop addition operation to pass to MPI reductions
     * \param[in] add function pointer to add c=a+b on semiring
     * \param[in] mul function pointer to multiply c=a*b on semiring
     * \param[in] gemm function pointer to multiply blocks C, A, and B on semiring
     */
    CTF_Semiring(int          el_size, 
                 char const * addid,
                 char const * mulid,
                 MPI_Op       addmop,
                 void (*add )(char const * a,
                              char const * b,
                              char       * c),
                 void (*mul )(char const * a,
                              char const * b,
                              char       * c),
                 void (*gemm)(char         tA,
                              char         tB,
                              int          m,
                              int          n,
                              int          k,
                              char const * alpha,
                              char const * A,
                              char const * B,
                              char const * beta,
                              char *       C)=NULL,
                 void (*axpy)(int          n,
                              char const * alpha,
                              char const * X,
                              int          incX,
                              char       * Y,
                              int          incY)=NULL,
                 void (*scal)(int          n,
                              char const * alpha,
                              char const * X,
                              int          incX)=NULL);
    /**
     * \brief destructor frees addid and mulid
     */
    ~CTF_Semiring();
};

template <typename dtype, dtype (*func)(dtype const a, dtype const b)>
void detypedfunc(char const * a,
                 char const * b,
                 char *       c){
  dtype ans = (*func)(((dtype const *)a)[0], ((dtype const *)b)[0]);
  ((dtype *)c)[0] = ans;
}

template <typename dtype, 
          dtype (*gemm)(char,char,int,int,int,dtype,
                        dtype const*,dtype const*,dtype,dtype*)>
void detypedgemm(char         tA,
                 char         tB,
                 int          m,
                 int          n,
                 int          k,
                 char const * alpha,
                 char const * A,
                 char const * B,
                 char const * beta,
                 char *       C){
  (*gemm)(tA,tB,m,n,k,
          ((dtype const *)alpha)[0],
           (dtype const *)A,
           (dtype const *)B,
          ((dtype const *)beta)[0],
           (dtype       *)C);
}

// it seems to not be possible to initialize template argument function pointers
// to NULL, so defining this dummy_gemm function instead
template<typename dtype>
dtype dummy_gemm(char,char,int,int,int,dtype,dtype const*,dtype const*,dtype,dtype*){
  assert(0);
}


template <typename dtype, 
          dtype (*fadd)(dtype a, dtype b),
          dtype (*fmul)(dtype a, dtype b),
          dtype (*gemm)(char,char,int,int,int,dtype,dtype const*,dtype const*,dtype,dtype*)=&dummy_gemm<dtype> >
class tCTF_Semiring {
  public:
    dtype addid;
    dtype mulid;
    MPI_Op addmop;
  public:
    /**
     * \brief constructor
     */
    tCTF_Semiring(dtype  addid_,
                  dtype  mulid_,
                  MPI_Op addmop_){
      addid = addid_;
      mulid = mulid_;
      addmop = addmop_;
    }

    operator CTF_Semiring() {
      if (gemm == &dummy_gemm<dtype>){
        CTF_Semiring r(sizeof(dtype), 
                       (char const *)&addid, 
                       (char const *)&mulid, 
                       addmop, 
                       &detypedfunc<dtype,fadd>,
                       &detypedfunc<dtype,fmul>);
        return r;
      } else {
        CTF_Semiring r(sizeof(dtype), 
                       (char const *)&addid, 
                       (char const *)&mulid, 
                       addmop, 
                       &detypedfunc<dtype,fadd>,
                       &detypedfunc<dtype,fmul>,
                       &detypedgemm<dtype,gemm>);
        return r;
      }
    }
};

#endif
