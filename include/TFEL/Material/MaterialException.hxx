/*!
 * \file   include/TFEL/Material/MaterialException.hxx
 * \brief    
 * \author Helfer Thomas
 * \date   10 Aug 2006
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef LIB_TFEL_MATERIALEXCEPTION_H_
#define LIB_TFEL_MATERIALEXCEPTION_H_ 

#include<string>
#include"TFEL/Config/TFELConfig.hxx"
#include"TFEL/Exception/TFELException.hxx"

namespace tfel{
  
  namespace material {
    
    struct TFELMATERIAL_VISIBILITY_EXPORT MaterialException
      : public tfel::exception::TFELException 
    {
      MaterialException() = default;
      MaterialException(MaterialException&&)      = default;
      MaterialException(const MaterialException&) = default;
      virtual ~MaterialException() noexcept;
    };

    struct TFELMATERIAL_VISIBILITY_EXPORT DivergenceException
      : public MaterialException
    {
      DivergenceException() = default;
      DivergenceException(DivergenceException&&)      = default;
      DivergenceException(const DivergenceException&) = default;
      const char * what() const noexcept final;
      virtual ~DivergenceException() noexcept;
    };
    
    struct TFELMATERIAL_VISIBILITY_EXPORT OutOfBoundsException
      : public MaterialException
    {
      OutOfBoundsException(std::string);
      OutOfBoundsException(OutOfBoundsException&&)      = default;
      OutOfBoundsException(const OutOfBoundsException&) = default;
      const char * what() const noexcept final;
      virtual ~OutOfBoundsException() noexcept;
    private:
      std::string msg;
    };
    
  } // end of namespace material

} // end of namespace tfel


#endif /* LIB_TFEL_MATERIALEXCEPTION_H_ */

