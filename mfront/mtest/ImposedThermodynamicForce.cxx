/*! 
 * \file  mfront/mtest/ImposedThermodynamicForce.cxx
 * \brief
 * \author Helfer Thomas
 * \brief 05 avril 2013
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#include"MTest/Behaviour.hxx"
#include"MTest/ImposedThermodynamicForce.hxx"

namespace mfront
{

  ImposedThermodynamicForce::ImposedThermodynamicForce(const Behaviour& b,
								 const tfel::material::ModellingHypothesis::Hypothesis h,
								 const std::string& cname,
								 const tfel::utilities::shared_ptr<Evolution> s_)
    : sev(s_)
  {
    this->c = b.getThermodynamicForceComponentPosition(h,cname);
  } // end of ImposedThermodynamicForce::ImposedThermodynamicForce

  ImposedThermodynamicForce::ImposedThermodynamicForce(const unsigned short c_,
								 const tfel::utilities::shared_ptr<Evolution> s_)
    : sev(s_),
      c(c_)
  {} // end of ImposedThermodynamicForce::ImposedThermodynamicForce

  unsigned short
  ImposedThermodynamicForce::getNumberOfLagrangeMultipliers(void) const
  {
    return 0u;
  } // end of ImposedThermodynamicForce::getNumberOfLagrangeMultipliers

  void
  ImposedThermodynamicForce::setValues(tfel::math::matrix<real>&,
					    tfel::math::vector<real>& r,
					    const tfel::math::vector<real>&,
					    const tfel::math::vector<real>&,
					    const unsigned short,
					    const unsigned short,
					    const real t,
					    const real dt,
					    const real) const
  {
    using namespace std;
    const Evolution& s = *(this->sev);
    r(this->c) -= s(t+dt);
  } // end of ImposedThermodynamicForce::setValues

  bool
  ImposedThermodynamicForce::checkConvergence(const tfel::math::vector<real>&,
						   const tfel::math::vector<real>& s,
						   const real,
						   const real seps,
						   const real t,
						   const real dt) const
  {
    using namespace std;
    const Evolution& sv = *(this->sev);
    const bool cb = abs(s(this->c)-sv(t+dt))<seps;
    return cb;
  }

   std::string
   ImposedThermodynamicForce::getFailedCriteriaDiagnostic(const tfel::math::vector<real>&,
							       const tfel::math::vector<real>& s,
							       const real,
							       const real seps,
							       const real t,
							       const real dt) const
   {
     using namespace std;
     const Evolution& sv = *(this->sev);
     ostringstream msg;
     msg << "imposed thermodynmic force not reached for component " << this->c 
	 << "(imposed value : " << sv(t+dt) << ", computed value : " 
	 << s(this->c) << ", criteria : " << seps << ")";
     return msg.str();
   }

  ImposedThermodynamicForce::~ImposedThermodynamicForce()
  {} // end of ImposedThermodynamicForce::~ImposedThermodynamicForce

} // end of namespace mfront
