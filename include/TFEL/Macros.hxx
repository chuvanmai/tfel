/*! 
 * \file  include/TFEL/Macros.hxx
 * \brief  defines some usefull macros
 * \author Helfer Thomas
 * \brief 23 mai 2011
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef LIB_TFEL_MACROS_H_
#define LIB_TFEL_MACROS_H_ 

/* !
 * \def TFEL_PP_JOIN
 * \brief this macro joins joins its two arguments together.
 *
 * This macro was taken from the boost library:
 * - http://boost.org/
 * 
 * The following piece of macro magic joins the two
 * arguments together, even when one of the arguments is
 * itself a macro (see 16.3.1 in C++ standard).  The key
 * is that macro expansion of macro arguments does not
 * occur in TFEL_PP_DO_JOIN2 but does in TFEL_PP_DO_JOIN.
 *
 * \author Helfer Thomas
 * \date   28 Aug 2006
 */
#define TFEL_PP_JOIN( X, Y ) TFEL_PP_DO_JOIN( X, Y )

/*!
 * \def TFEL_PP_DO_JOIN
 * \brief An helper macro for TFEL_PP_JOIN
 * \see TFEL_PP_JOIN
 * \author Helfer Thomas
 * \date   28 Aug 2006
 */
#define TFEL_PP_DO_JOIN( X, Y ) TFEL_PP_DO_JOIN2(X,Y)

/*!
 * \def TFEL_PP_DO_JOIN2
 * \brief An helper macro for TFEL_PP_JOIN
 * \see TFEL_PP_JOIN
 * \author Helfer Thomas
 * \date   28 Aug 2006
 */
#define TFEL_PP_DO_JOIN2( X, Y ) X##Y

#endif /* LIB_TFEL_MACROS_H_ */

