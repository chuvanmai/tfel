/*!
 * \file   mfront/include/MFront/RungeKuttaDSLBase.hxx
 * \brief  This file declares the RungeKuttaDSLBase class
 * \author Thomas Helfer
 * \date   10 Nov 2006
 * \copyright Copyright (C) 2006-2018 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef LIB_MFRONT_RUNGEKUTTADSLBASE_HXX
#define LIB_MFRONT_RUNGEKUTTADSLBASE_HXX 

#include<string>
#include"MFront/BehaviourDSLBase.hxx"

namespace mfront{

  struct RungeKuttaDSLBase
    : public BehaviourDSLBase<RungeKuttaDSLBase>
  {
    //! return a generic description of DSL based on this class
    static std::string getDescription();
    //! constructor
    RungeKuttaDSLBase();
    //! destructor
    ~RungeKuttaDSLBase() override;

  protected:

    enum ErrorEvaluation{
      DEFAULTERROREVALUATION,
      ERRORSUMMATIONEVALUATION,
      MAXIMUMVALUEERROREVALUATION
    }; // end of ErrorEvaluation

    std::string
    computeStressVariableModifier1(const Hypothesis,
				   const std::string&,
				   const bool);

    std::string
    computeStressVariableModifier2(const Hypothesis,
				   const std::string&,
				   const bool);

    void treatUnknownVariableMethod(const Hypothesis,
				    const std::string&) override;
    //! treat the `@Epsilon` keywork
    virtual void treatEpsilon();
    //! treat the `@MinimalTimeStep` keywork
    virtual void treatMinimalTimeStep();
    //! treat the `@Algorithm` keywork
    virtual void treatAlgorithm();
    //! treat the `@ComputeStress` keywork
    virtual void treatComputeStress();
    //! treat the `@ComputeFinalStress` keywork
    virtual void treatComputeFinalStress();
    //! treat the `@UpdateAuxiliaryStateVariables` keywork
    void treatUpdateAuxiliaryStateVariables() override;
    //! treat the `@Derivative` keywork
    virtual void treatDerivative();

    virtual void setDefaultAlgorithm();
    
    void completeVariableDeclaration() override;

    void endsInputFileProcessing() override;
    
    void writeBehaviourParserSpecificIncludes(std::ostream&) const override;

    void writeBehaviourParserSpecificTypedefs(std::ostream&) const override;

    void writeBehaviourParserSpecificMembers(std::ostream&,
					     const Hypothesis) const override;

    void writeBehaviourLocalVariablesInitialisation(std::ostream&,
						    const Hypothesis) const override;
    
    virtual void writeBehaviourEulerIntegrator(std::ostream&,
					       const Hypothesis) const;

    virtual void writeBehaviourRK2Integrator(std::ostream&,
					     const Hypothesis) const;

    virtual void writeBehaviourRK4Integrator(std::ostream&,
					     const Hypothesis) const;

    virtual void writeBehaviourRK42Integrator(std::ostream&,
					      const Hypothesis) const;

    virtual void writeBehaviourRK54Integrator(std::ostream&,
					      const Hypothesis) const;

    virtual void writeBehaviourRKCastemIntegrator(std::ostream&,
						  const Hypothesis) const;

    void writeBehaviourUpdateStateVariables(std::ostream&,
					    const Hypothesis) const override;

    void writeBehaviourUpdateAuxiliaryStateVariables(std::ostream&,
						     const Hypothesis) const override;

    void writeBehaviourIntegrator(std::ostream&,
				  const Hypothesis) const override;

    friend struct BehaviourDSLBase<RungeKuttaDSLBase>;

  };

} // end of namespace mfront  

#endif /* LIB_MFRONT_RUNGEKUTTADSLBASE_HXX */

