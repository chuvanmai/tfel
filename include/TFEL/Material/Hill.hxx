/*!
 * \file   include/TFEL/Material/Hill.hxx
 * \author Helfer Thomas
 * \date   26 March 2009
 * \brief  This file declares the hillTensor function.
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef LIB_TFEL_MATERIAL_HILL_H_
#define LIB_TFEL_MATERIAL_HILL_H_ 

#include"TFEL/Math/st2tost2.hxx"
#include"TFEL/Material/ModellingHypothesis.hxx"
#include"TFEL/Material/OrthotropicAxesConvention.hxx"

namespace tfel
{

  namespace material
  {

    /*!
     * \brief compute the Hill tensor.
     * \tparam    N:      space dimension
     * \tparam    stress: underlying type
     * \param[in] H_F:    orthotropic coefficient
     * \param[in] H_G:    orthotropic coefficient
     * \param[in] H_H:    orthotropic coefficient
     * \param[in] H_L:    orthotropic coefficient
     * \param[in] H_M:    orthotropic coefficient
     * \param[in] H_N:    orthotropic coefficient
     * This function builds the Hill Tensor defined by :
     * \f[\left(
     * \begin{array}{cccccc}
     * H_F+H_H & -H_F  & -H_H  & 0 & 0 & 0 \\
     * -H_F  & H_G+H_F & -H_G  & 0 & 0 & 0 \\
     * -H_H  & -H_G  & H_H+H_G & 0 & 0 & 0 \\
     * 0   & 0   & 0   & H_L & 0 & 0 \\
     * 0   & 0   & 0   & 0 & H_M & 0 \\
     * 0   & 0   & 0   & 0 & 0 & H_N \\
     * \end{array}
     * \right)
     * \f]
     * if \f$\sigma\f$ is a second order symetric tensor (stensor), 
     * \f$\sigma|H_H*\sigma\f$ computes the Hill stress :
     * \f[
     * H_F\left(\sigma_{11}-\sigma_{22}\right)^2+H_G\left(\sigma_{22}-\sigma_{33}\right)^2+H_H\left(\sigma_{33}-\sigma_{11}\right)^2
     * + 2H_L\sigma_{12}^{2} + 2H_M\sigma_{13}^{2} + 2H_N\sigma_{23}^{2}
     * \f]
     *
     * \warning This convention is given in the book of H_Lemaître et
     * Chaboche and seems to differ from the one described in most
     * other books.
     *
     * \return an object of type st2tost2
     */    
    template<unsigned short N,typename stress>
    tfel::math::st2tost2<N,stress>
    hillTensor(const stress,const stress,const stress,
	       const stress,const stress,const stress);
    /*!
     * \brief compute the Hill tensor.
     *
     * \tparam    H:      modelling hypothesis
     * \tparam    c:      orthotropic axis convention
     * \tparam    stress: stress type
     * \param[in] H_F:    orthotropic coefficient
     * \param[in] H_G:    orthotropic coefficient
     * \param[in] H_H:    orthotropic coefficient
     * \param[in] H_L:    orthotropic coefficient
     * \param[in] H_M:    orthotropic coefficient
     * \param[in] H_N:    orthotropic coefficient
     * This function builds the Hill Tensor defined by :
     * \f[\left(
     * \begin{array}{cccccc}
     * H_F+H_H & -H_F  & -H_H  & 0 & 0 & 0 \\
     * -H_F  & H_G+H_F & -H_G  & 0 & 0 & 0 \\
     * -H_H  & -H_G  & H_H+H_G & 0 & 0 & 0 \\
     * 0   & 0   & 0   & H_L & 0 & 0 \\
     * 0   & 0   & 0   & 0 & H_M & 0 \\
     * 0   & 0   & 0   & 0 & 0 & H_N \\
     * \end{array}
     * \right)
     * \f]
     * if \f$\sigma\f$ is a second order symetric tensor (stensor), 
     * \f$\sigma|H_H*\sigma\f$ computes the Hill stress :
     * \f[
     * H_F\left(\sigma_{11}-\sigma_{22}\right)^2+H_G\left(\sigma_{22}-\sigma_{33}\right)^2+H_H\left(\sigma_{33}-\sigma_{11}\right)^2
     * + 2H_L\sigma_{12}^{2} + 2H_M\sigma_{13}^{2} + 2H_N\sigma_{23}^{2}
     * \f]
     *
     * \warning This convention is given in the book of Lemaître et
     * Chaboche and seems to differ from the one described in most
     * other books.
     *
     * \return an object of type st2tost2
     */    
    template<ModellingHypothesis::Hypothesis H,
	     OrthotropicAxesConvention c,typename stress>
    tfel::math::st2tost2<ModellingHypothesisToSpaceDimension<H>::value,stress>
    computeHillTensor(const stress,const stress,const stress,
		      const stress,const stress,const stress);

    
  } // end of namespace material

} // end of namespace tfel

#include"TFEL/Material/Hill.ixx"

#endif /* LIB_TFEL_MATERIAL_HILL_H_ */
