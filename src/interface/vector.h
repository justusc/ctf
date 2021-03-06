#ifndef __VECTOR_H__
#define __VECTOR_H__

namespace CTF {

  /**
   * \addtogroup CTF
   * @{
   **/
  /**
   * \brief Vector class which encapsulates a 1D tensor 
   */
  template <typename dtype=double, bool is_ord=true>
  class Vector : public Tensor<dtype, is_ord> {
    public:
      int len;
      /**
       * \brief constructor for a vector
       * \param[in] len_ dimension of vector
       * \param[in] world_ CTF world where the tensor will live
       * \param[in] sr_ defines the tensor arithmetic for this tensor
       * \param[in] name_ an optionary name for the tensor
       * \param[in] profile_ set to 1 to profile contractions involving this tensor
       */ 
      Vector(int                       len,
             World &                   world,
             CTF_int::algstrct const & sr);

      /**
       * \brief constructor for a vector
       * \param[in] len_ dimension of vector
       * \param[in] world_ CTF world where the tensor will live
       * \param[in] name_ an optionary name for the tensor
       * \param[in] profile_ set to 1 to profile contractions involving this tensor
       */ 
      Vector(int                       len,
             World &                   world,
             char const *              name=NULL,
             int                       profile=0,
             CTF_int::algstrct const & sr=Ring<dtype,is_ord>());


      Vector<dtype,is_ord> & operator=(const Vector<dtype,is_ord> & A);
  /**
   * @}
   */
  };
}
#include "vector.cxx"
#endif
