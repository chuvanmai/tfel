/*!
 * \file   CrystalStructure.hxx
 * \brief    
 * \author THOMAS HELFER
 * \date   09 juin 2017
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef LIB_TFEL_MATERIAL_CRYSTALSTRUCTURE_HXX
#define LIB_TFEL_MATERIAL_CRYSTALSTRUCTURE_HXX

namespace tfel{

  namespace material{

    //! \brief list of supported crystal structures
    enum struct CrystalStructure{
      Cubic, //!< cubic structure
      FCC,   //!< face centered cubic structure
      HCP    //!< hexagonal closed-packed structures
    }; // end of enum struct CrystalStructure
    
  } // end of namespace material

} // end of namespace tfel

#endif /* LIB_TFEL_MATERIAL_CRYSTALSTRUCTURE_HXX */
