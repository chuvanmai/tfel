include_directories(
  "${CASTEMHOME}/include"
  "${PROJECT_SOURCE_DIR}/include"
  "${PROJECT_SOURCE_DIR}/mfront/include"
  "${CMAKE_CURRENT_BINARY_DIR}/include")
link_directories("${PROJECT_BINARY_DIR}/mfront/src"
                 "${PROJECT_BINARY_DIR}/src/Material"
                 "${PROJECT_BINARY_DIR}/src/Math"
                 "${PROJECT_BINARY_DIR}/src/Utilities"
                 "${PROJECT_BINARY_DIR}/src/Exception")

configure_file("${PROJECT_SOURCE_DIR}/mfront/tests/behaviours/references/PolyCrystalsAngles.txt"
    PolyCrystalsAngles.txt @ONLY)

macro(test_crossed2deltabis test_arg)
  if(CMAKE_CONFIGURATION_TYPES)
    foreach(conf ${CMAKE_CONFIGURATION_TYPES})
      set(file "crossed2deltabis${test_arg}-${conf}.mtest")
      get_property(MFrontCastemBehavioursBuildPath TARGET MFrontCastemBehaviours PROPERTY LOCATION_${conf})
      get_property(MFrontMaterialPropertiesCastemBuildPath TARGET MFrontMaterialProperties-castem PROPERTY LOCATION_${conf})
      configure_file(crossed2deltabis${test_arg}.mtest.in
	${file} @ONLY)
      add_test(NAME crossed2deltabis${test_arg}_${conf}_mtest
	CONFIGURATIONS ${conf}
	COMMAND mtest --verbose=level0 --xml-output=true --result-file-output=false ${file})
      set_tests_properties(crossed2deltabis${test_arg}_${conf}_mtest
	PROPERTIES DEPENDS MFrontCastemBehaviours)
      set_tests_properties(crossed2deltabis${test_arg}_${conf}_mtest
	PROPERTIES DEPENDS MFrontMaterialProperties-castem)
      set_tests_properties(crossed2deltabis${test_arg}_${conf}_mtest
	PROPERTIES DEPENDS mtest)
      install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${file}
	DESTINATION "share/mfront/tests/behaviours/crossed2deltabis"
	COMPONENT mtest)
    endforeach(conf ${CMAKE_CONFIGURATION_TYPES})
  else(CMAKE_CONFIGURATION_TYPES)
    get_property(MFrontCastemBehavioursBuildPath TARGET MFrontCastemBehaviours PROPERTY LOCATION_${conf})
    configure_file(crossed2deltabis${test_arg}.mtest.in
      crossed2deltabis${test_arg}.mtest @ONLY)
    add_test(NAME crossed2deltabis${test_arg}_mtest
      COMMAND mtest --verbose=level0 --xml-output=true --result-file-output=false crossed2deltabis${test_arg}.mtest)
    set_tests_properties(crossed2deltabis${test_arg}_mtest
      PROPERTIES DEPENDS MFrontCastemBehaviours)
    set_tests_properties(crossed2deltabis${test_arg}_mtest
      PROPERTIES DEPENDS MFrontMaterialProperties-castem)
    set_tests_properties(crossed2deltabis${test_arg}_mtest
      PROPERTIES DEPENDS mtest)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/crossed2deltabis${test_arg}.mtest
      DESTINATION "share/mfront/tests/behaviours/crossed2deltabis"
      COMPONENT mtest)
  endif(CMAKE_CONFIGURATION_TYPES)
endmacro(test_crossed2deltabis)

test_crossed2deltabis(ddif2-2)
test_crossed2deltabis(ddif2-3)
test_crossed2deltabis(ddif2-4)
test_crossed2deltabis(ddif2)
test_crossed2deltabis(druckerprager)
test_crossed2deltabis(ellipticcreep)
test_crossed2deltabis(finitestrainsinglecrystal-001)
test_crossed2deltabis(finitestrainsinglecrystal-012-2)
test_crossed2deltabis(finitestrainsinglecrystal-012)
test_crossed2deltabis(finitestrainsinglecrystal-159)
test_crossed2deltabis(finitestrainsinglecrystal2-001)
test_crossed2deltabis(finitestrainsinglecrystal_numericaljacobian-001)
test_crossed2deltabis(finitestrainsinglecrystal_numericaljacobian-012-2)
test_crossed2deltabis(finitestrainsinglecrystal_numericaljacobian-012)
test_crossed2deltabis(finitestrainsinglecrystal_numericaljacobian-159)
test_crossed2deltabis(hayhurst)
test_crossed2deltabis(implicithayhurst)
test_crossed2deltabis(implicitmonocrystal)
test_crossed2deltabis(implicitnorton3)
test_crossed2deltabis(implicitnorton-planestress2)
test_crossed2deltabis(lorentz)
test_crossed2deltabis(monocrystal_dd_cc_irradiation)
test_crossed2deltabis(monocrystal_dd_cc_irradiation_numericaljacobian)
test_crossed2deltabis(monocrystal_dd_cfc_irradiation)
test_crossed2deltabis(monocrystal_dd_cfc)
test_crossed2deltabis(monocrystal_dd_cfc_numericaljacobian)
test_crossed2deltabis(monocrystal)
test_crossed2deltabis(norton2)
test_crossed2deltabis(norton-euler)
test_crossed2deltabis(norton)
test_crossed2deltabis(norton-rk2)
test_crossed2deltabis(nortonrk2)
test_crossed2deltabis(nortonrk3)
test_crossed2deltabis(norton-rk4)
test_crossed2deltabis(nortonrk4)
test_crossed2deltabis(plasisocin)
test_crossed2deltabis(plasticity)
test_crossed2deltabis(strainhardeningcreep)
test_crossed2deltabis(stressrelaxation)
test_crossed2deltabis(T91-satohtest)
test_crossed2deltabis(T91-viscositytest)
test_crossed2deltabis(viscoplasisocin)

# test_crossed2deltabis(mieheapellambrechtlogarithmicstrainnortoncreep-uniaxialloading-3-3D)
# test_crossed2deltabis(monocrystal_dd_cc)
# test_crossed2deltabis(monocrystal_dd_cc_numericaljacobian)