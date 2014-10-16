/*! 
 * \file  tests/Math/t2tost2/rightCauchyGreenTensorDerivative.cxx
 * \brief
 * \author Helfer Thomas
 * \brief 04 juin 2014
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifdef NDEBUG
#undef NDEBUG
#endif /* NDEBUG */

#include<cmath>
#include<cstdlib>
#include<cassert>

#include"TFEL/Math/stensor.hxx"
#include"TFEL/Math/tensor.hxx"
#include"TFEL/Math/t2tost2.hxx"
#include"TFEL/Utilities/ToString.hxx"

#include"TFEL/Tests/TestCase.hxx"
#include"TFEL/Tests/TestProxy.hxx"
#include"TFEL/Tests/TestManager.hxx"

template<unsigned short N>
struct RightCauchyGreenTensorDerivative
  : public tfel::tests::TestCase
{
  RightCauchyGreenTensorDerivative()
    : tfel::tests::TestCase("TFEL/Math",
			    "RightCauchyGreenTensorDerivative"+
			    tfel::utilities::ToString(N))
  {} // end of RightCauchyGreenTensorDerivative
  tfel::tests::TestResult
  execute()
  {
    using namespace std;
    using namespace tfel::math;
    const double eps  = 1.e-7;
    const double prec = 1.e-8;
    tensor<N> F;
    for(typename tensor<N>::size_type i=0;i!=F.size();++i){
      if(i<3){
	F[i] = 1+0.03*i*i;
      } else {
	F[i] = 0.03*i;
      }
    }
    stensor<N> C  = computeRightCauchyGreenTensor(F);
    t2tost2<N> dC = t2tost2<N>::dCdF(F);
    t2tost2<N> ndC;
    for(typename tensor<N>::size_type i=0;i!=F.size();++i){
      tensor<N> Fe(F);
      Fe[i] += eps;
      stensor<N> Cfe=computeRightCauchyGreenTensor(Fe);
      Fe[i] -= 2*eps;
      stensor<N> Cbe=computeRightCauchyGreenTensor(Fe);
      for(typename tensor<N>::size_type j=0;j!=C.size();++j){
	ndC(j,i) = (Cfe(j)-Cbe(j))/(2*eps);
      }
    }
    for(typename tensor<N>::size_type i=0;i!=C.size();++i){
      for(typename tensor<N>::size_type j=0;j!=F.size();++j){
	TFEL_TESTS_ASSERT(abs(ndC(i,j)-dC(i,j))<prec);
	if(abs(ndC(i,j)-dC(i,j))>prec){
	  cout << "error (" << N << "): " << i << " " << j << " " << ndC(i,j) << " " << dC(i,j) << " " << abs(ndC(i,j)-dC(i,j)) << endl;
	}
      }
    }
    return this->result;
  } // end of execute
};

typedef RightCauchyGreenTensorDerivative<1u> RightCauchyGreenTensorDerivative_1D;
typedef RightCauchyGreenTensorDerivative<2u> RightCauchyGreenTensorDerivative_2D;
typedef RightCauchyGreenTensorDerivative<3u> RightCauchyGreenTensorDerivative_3D;
TFEL_TESTS_GENERATE_PROXY(RightCauchyGreenTensorDerivative_1D,"RightCauchyGreenTensorDerivative-1D");
TFEL_TESTS_GENERATE_PROXY(RightCauchyGreenTensorDerivative_2D,"RightCauchyGreenTensorDerivative-2D");
TFEL_TESTS_GENERATE_PROXY(RightCauchyGreenTensorDerivative_3D,"RightCauchyGreenTensorDerivative-3D");

int main(void){
  using namespace std;
  using namespace std;
  using namespace tfel::tests;
  using namespace tfel::utilities;
  TestManager& manager = TestManager::getTestManager();
  manager.addTestOutput(cout);
  manager.addXMLTestOutput("RightCauchyGreenTensorDerivative.xml");
  TestResult r = manager.execute();
  if(!r.success()){
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}