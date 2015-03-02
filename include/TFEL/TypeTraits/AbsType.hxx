/*!
 * \file   include/TFEL/TypeTraits/AbsType.hxx
 * \brief  This file declares the AbsType traits class
 * and specialises it for standard numeric types.
 * \author Helfer Thomas
 * \date   10 Sept. 2012
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef LIB_TFEL_ABSTYPE_H_
#define LIB_TFEL_ABSTYPE_H_ 

#include"TFEL/Metaprogramming/InvalidType.hxx"
#include"TFEL/TypeTraits/RealPartType.hxx"

/*!
 * \def    TFEL_TYPETRAITS_ABSTYPE
 * \brief An helper macro to specialise AbsType for each standard
 * "real" numeric types.
 * \author Helfer Thomas
 * \date   10 Sept. 2012
 */
#define TFEL_TYPETRAITS_ABSTYPE(X)         \
    /*!                                    \
     * \brief Partial specialisation for X \
     * \see   AbsType                      \
     */                                    \
    template<>                             \
    struct AbsType< X >		           \
    {			                   \
      typedef X type;			   \
    }

/*!
 * \def    TFEL_TYPETRAITS_ABSTYPEII
 * \brief  An helper macro to specialise AbsType for each
 * standard "complex" numeric types.
 * \author Helfer Thomas
 * \date   10 Sept. 2012
 */
#define TFEL_TYPETRAITS_ABSTYPEII(X)                          \
    /*!                                                       \
     * \brief Partial specialisation for X                    \
     * \see   AbsType                                         \
     */                                                       \
    template<>                                                \
    struct AbsType<tfel::math::Complex< X > >                 \
    {				                              \
      typedef tfel::typetraits::RealPartType< X >::type type; \
    }


namespace tfel{

  namespace typetraits{

    /*!
     * \brief Traits class which associates to its argument the type
     * returned by the abs() function.
     *
     * If the argument is not complex, the result is the argument itself. 
     *
     * \param  T, type to be tested.
     * \return type, type of abs() function
     *
     * \author Helfer Thomas
     * \date   10 Sept. 2012
     */
    template<typename T>
    struct AbsType
    {
      typedef tfel::meta::InvalidType type;
    }; // end of struct AbsType

    TFEL_TYPETRAITS_ABSTYPE(float);
    TFEL_TYPETRAITS_ABSTYPE(double);
    TFEL_TYPETRAITS_ABSTYPE(long double);

    TFEL_TYPETRAITS_ABSTYPEII(float);
    TFEL_TYPETRAITS_ABSTYPEII(double);
    TFEL_TYPETRAITS_ABSTYPEII(long double);

  } // end of namespace typetraits

} // end of namespace tfel

#endif /* LIB_TFEL_ABSTYPE_H_ */

