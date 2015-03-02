/*! 
 * \file  TinyVectorFromTinyVectorViewIO.hxx
 * \brief
 * \author Helfer Thomas
 * \date   24 janv. 2015
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef LIB_TFEL_MATH_TINYVECTORFROMTINYVECTORVIEWIO_H_
#define LIB_TFEL_MATH_TINYVECTORFROMTINYVECTORVIEWIO_H_ 

#include<ostream>
#include"TFEL/Math/Vector/TinyVectorFromTinyVectorView.hxx"

namespace tfel{
  
  namespace math {

    // Serialisation operator
    template<unsigned short N, unsigned short Mn,
	     unsigned short In,typename T,bool b>
    std::ostream&
    operator << (std::ostream &,
		 const Expr<tvector<N,T>,TinyVectorFromTinyVectorViewExpr<N,Mn,In,T,b> >&);


    template<unsigned short N, unsigned short Mn,
	     unsigned short In,typename T,bool b>
    std::ostream&
    operator << (std::ostream & os,
		 const Expr<tvector<N,T>,TinyVectorFromTinyVectorViewExpr<N,Mn,In,T,b> >& s)
    {
      os << "[ ";
      for(unsigned short i=0;i<N;++i){
	os << s(i) << " ";
      }
      os << "]";
      return os;
    } // end of operator << 

  } // end of namespace typetraits

} // end of namespace tfel

#endif /* LIB_TFEL_MATH_TINYVECTORFROMTINYVECTORVIEWIO_H_ */

