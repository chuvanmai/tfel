/*!
 * \file   SlipSystemsDescriptionTest.cxx
 * \brief    
 * \author Thomas Helfer
 * \date   12 juin 2017
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#include<cstdlib>
#include<iostream>

#include"TFEL/Tests/TestCase.hxx"
#include"TFEL/Tests/TestProxy.hxx"
#include"TFEL/Tests/TestManager.hxx"

#include"TFEL/FSAlgorithm/equal.hxx"
#include"TFEL/Material/SlipSystemsDescription.hxx"

struct SlipSystemsDescriptionTest final
  : public tfel::tests::TestCase
{
  SlipSystemsDescriptionTest()
    : tfel::tests::TestCase("TFEL/Material",
			    "SlipSystemsDescriptionTest")
  {} // end of SlipSystemsDescription
  virtual tfel::tests::TestResult
  execute() override
  {
    this->checkFCC();
    return this->result;
  }
  virtual ~SlipSystemsDescriptionTest() = default;
 private:

  using SlipSystemsDescription = tfel::material::SlipSystemsDescription;
  
  template<size_t N>
  static bool equal(const std::array<int,N>& v1,
		    const std::array<int,N>& v2)
  {
    return tfel::fsalgo::equal<N>::exe(v1.begin(),v2.begin());
  } // end of equal
  template<size_t N>
  static bool equal(const SlipSystemsDescription::system& g1,
		    const std::array<int,N>& p,
		    const std::array<int,N>& b)
  {
    using system_type =
      typename std::conditional<N==3,SlipSystemsDescription::system3d,
				SlipSystemsDescription::system4d>::type;
    if(!g1.template is<system_type>()){
      return false;
    }
    const auto& g1b = g1.template get<system_type>();
    return (equal(g1b.burgers,b))&&(equal(g1b.plane,p));
  } // end of equal
  template<size_t N>
  static bool contains(const std::vector<SlipSystemsDescription::system>& gs,
		       const std::array<int,N>& p,
		       const std::array<int,N>& b){
    for(const auto& g : gs){
      if(equal(g,p,b)){
	return true;
      }
    }
    return false;
  }
  //! \brief tests related to FCC systems
  void checkFCC(){
    using namespace tfel::material;
    using vec3d    = SlipSystemsDescription::vec3d;
    using system3d = SlipSystemsDescription::system3d;
    auto ssd = SlipSystemsDescription(CrystalStructure::FCC);
    auto make_vec = [](const int v0,const int v1, const int v2){
      auto v = vec3d();
      v[0]=v0;v[1]=v1;v[2]=v2;
      return v;
    };
    /* slip systems */
    ssd.addSlipSystemsFamily(make_vec(1,-1,1),make_vec(1,1,0));
    TFEL_TESTS_CHECK_EQUAL(ssd.getNumberOfSlipSystemsFamilies(),1u);
    TFEL_TESTS_CHECK_THROW(ssd.getSlipSystemFamily(1),
			   std::runtime_error);
    const auto& gsf = ssd.getSlipSystemFamily(0);
    TFEL_TESTS_ASSERT(gsf.is<system3d>());
    const auto ssf0 = gsf.get<system3d>();
    TFEL_TESTS_ASSERT(equal(ssf0.burgers,make_vec(1,1,0)));
    TFEL_TESTS_ASSERT(equal(ssf0.plane,make_vec(1,-1,1)));
    const auto gs = ssd.getSlipSystems();
    TFEL_TESTS_CHECK_EQUAL(gs.size(),1u);
    const auto& gs0 = gs[0];
    TFEL_TESTS_CHECK_EQUAL(gs0.size(),12u);
    TFEL_TESTS_ASSERT(contains(gs0,make_vec(1,1,1),make_vec(0,1,-1)));
    TFEL_TESTS_ASSERT(contains(gs0,make_vec(1,1,1),make_vec(1,0,-1)));
    TFEL_TESTS_ASSERT(contains(gs0,make_vec(1,1,1),make_vec(1,-1,0)));
    TFEL_TESTS_ASSERT(contains(gs0,make_vec(1,1,-1),make_vec(0,1,1)));
    TFEL_TESTS_ASSERT(contains(gs0,make_vec(1,1,-1),make_vec(1,0,1)));
    TFEL_TESTS_ASSERT(contains(gs0,make_vec(1,1,-1),make_vec(1,-1,0)));
    TFEL_TESTS_ASSERT(contains(gs0,make_vec(1,-1,-1),make_vec(0,1,-1)));
    TFEL_TESTS_ASSERT(contains(gs0,make_vec(1,-1,-1),make_vec(1,0,1)));
    TFEL_TESTS_ASSERT(contains(gs0,make_vec(1,-1,-1),make_vec(1,1,0)));
    TFEL_TESTS_ASSERT(contains(gs0,make_vec(1,-1,1),make_vec(0,1,1)));
    TFEL_TESTS_ASSERT(contains(gs0,make_vec(1,-1,1),make_vec(1,0,-1)));
    TFEL_TESTS_ASSERT(contains(gs0,make_vec(1,-1,1),make_vec(1,1,0)));
    /* interaction matrix */
    const auto im = ssd.getInteractionMatrixStructure();
    TFEL_TESTS_CHECK_EQUAL(im.rank(),7u);
    TFEL_TESTS_CHECK_EQUAL(im.getRank(system3d{make_vec(0,1,-1),make_vec(1,1,1)},
				      system3d{make_vec(0,1,-1),make_vec(1,1,1)}),0u);
  }
};

TFEL_TESTS_GENERATE_PROXY(SlipSystemsDescriptionTest,
			  "SlipSystemsDescriptionTest");

/* coverity [UNCAUGHT_EXCEPT]*/
int main()
{
  auto& m = tfel::tests::TestManager::getTestManager();
  m.addTestOutput(std::cout);
  m.addXMLTestOutput("SlipSystemsDescription.xml");
  return m.execute().success() ? EXIT_SUCCESS : EXIT_FAILURE;
} // end of main
