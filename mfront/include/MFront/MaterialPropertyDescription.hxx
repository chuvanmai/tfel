/*! 
 * \file  mfront/include/MFront/MaterialPropertyDescription.hxx
 * \brief
 * \author Helfer Thomas
 * \brief 26 févr. 2014
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef LIB_MFRONT_MATERIALPROPERTYDESCRIPTION_H_
#define LIB_MFRONT_MATERIALPROPERTYDESCRIPTION_H_ 

#include<map>
#include<vector>
#include<string>

#include"MFront/LawFunction.hxx"
#include"MFront/VariableDescription.hxx"
#include"MFront/StaticVariableDescription.hxx"
#include"MFront/VariableBoundsDescription.hxx"

namespace mfront
{

  /*!
   * structure describing a material property
   */
  struct TFEL_VISIBILITY_EXPORT MaterialPropertyDescription
  {
    /*!
     * \return the external names of each input variables.
     */
    std::vector<std::string>
    getInputVariablesExternalNames(void);
    /*!
     * body of the material property
     */
    LawFunction f;
    /*!
     * list of inputs
     */
    VariableDescriptionContainer inputs;
    /*!
     * output
     */
    std::string output;
    /*!
     * law name
     */
    std::string law;
    /*!
     * material name
     */
    std::string material;
    /*!
     * library name
     */
    std::string library;
    /*!
     * class name
     */
    std::string className;
    /*!
     * included header files
     */
    std::string includes;
    /*!
     * specific sources
     */
    std::string sources;
    /*!
     * private code
     */
    std::string privateCode;
    /*!
     * class member
     */
    std::string members;
    /*!
     * bounds description
     */
    std::vector<VariableBoundsDescription> boundsDescriptions;
    /*!
     * physical bounds description
     */
    std::vector<VariableBoundsDescription> physicalBoundsDescriptions;
    /*!
     * glossary names
     */
    std::map<std::string,std::string> glossaryNames;
    /*!
     * entry names
     */
    std::map<std::string,std::string> entryNames;
    /*!
     * parameters
     */
    std::vector<std::string> parameters;
    /*!
     * parameters default value
     */
    std::map<std::string,double> parametersValues;
    /*!
     * list of material laws used
     */
    std::vector<std::string> materialLaws;
    /*!
     * static variables
     */
    StaticVariableDescriptionContainer staticVars;
  }; // end of MaterialProopertyDescription

} // end of namespace mfront

#endif /* LIB_MFRONT_MATERIALPROPERTYDESCRIPTION_H_ */

