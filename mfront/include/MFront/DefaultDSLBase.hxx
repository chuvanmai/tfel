/*!
 * \file   mfront/include/MFront/DefaultDSLBase.hxx
 * \brief  
 * \author Helfer Thomas
 * \date   08 nov 2006
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef LIB_MFRONT_MFRONTPARSERBASE_HXX_
#define LIB_MFRONT_MFRONTPARSERBASE_HXX_ 

#include"MFront/BehaviourDSLBase.hxx"

namespace mfront{

  struct DefaultDSLBase
    : public BehaviourDSLBase<DefaultDSLBase>
  {

    DefaultDSLBase();

    ~DefaultDSLBase();

  protected:

    virtual void
    writeBehaviourParserSpecificIncludes(void);
    
    virtual void
    treatProvidesTangentOperator(void);

    virtual void
    treatProvidesSymmetricTangentOperator(void);

  }; // end of struct DefaultDSLBase

} // end of namespace mfront  

#endif /* LIB_MFRONT_MFRONTPARSERBASE_HXX_ */

