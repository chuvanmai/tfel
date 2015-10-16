/*! 
 * \file   mfront/mtest/MTestMain.cxx
 * \brief
 * \author Helfer Thomas
 * \brief  05 avril 2013
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#include<cstdlib>
#include<vector>
#include<string>
#include<fenv.h>

#if defined _WIN32 || defined _WIN64
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include<windows.h>
#endif

#include"TFEL/Utilities/ArgumentParserBase.hxx"

#if ! (defined _WIN32 || defined _WIN64 ||defined __CYGWIN__)
#include"TFEL/System/SignalManager.hxx"
#endif

#include"MFront/MFrontLogStream.hxx"

#include"MTest/MTest.hxx"
#include"MTest/MTestParser.hxx"
#include"MTest/Constraint.hxx"
#include"MTest/Evolution.hxx"

#include"TFEL/Tests/TestManager.hxx"
#include"TFEL/Tests/XMLTestOutput.hxx"

namespace mtest
{

  struct MTestMain
    : tfel::utilities::ArgumentParserBase<MTestMain>
  {
    MTestMain(const int, 
	      const char *const *const);

    
    int execute(void);
    ~MTestMain();
  protected:
    friend struct tfel::utilities::ArgumentParserBase<MTestMain>;
    void
    treatUnknownArgument(void);
    void
    treatVerbose(void);
    void
    treatXMLOutput(void);
    void
    treatResultFileOutput(void);
    void
    treatResidualFileOutput(void);
    TFEL_NORETURN void
    treatHelpCommandsList(void);
    TFEL_NORETURN void
    treatHelpCommands(void);
    TFEL_NORETURN void
    treatHelpCommand(void);
    void
    treatEnableFloatingPointExceptions(void);
#if ! (defined _WIN32 || defined _WIN64 ||defined __CYGWIN__)
    void
    treatBacktrace();
#endif
    virtual std::string 
    getVersionDescription(void) const override;
    virtual std::string 
    getUsageDescription(void) const override;
    void 
    registerArgumentCallBacks(void);
    // input files
    std::vector<std::string> inputs;
    // xml output
    bool xml_output;
    // generate result file
    bool result_file_output;
    // generate residual file
    bool residual_file_output;
  };

  MTestMain::MTestMain(const int argc, const char *const *const argv)
    : tfel::utilities::ArgumentParserBase<MTestMain>(argc,argv),
      xml_output(false),
      result_file_output(true),
      residual_file_output(false)
  {
    using namespace std;
    this->registerArgumentCallBacks();
    this->parseArguments();
    if(this->inputs.empty()){
      string msg("MTestMain::MTestMain : ");
      msg += "no input file defined";
      throw(runtime_error(msg));
    }
  }

  void 
  MTestMain::registerArgumentCallBacks(void)
  {
    this->registerNewCallBack("--verbose",&MTestMain::treatVerbose,
			      "set verbose output",true);
    this->registerNewCallBack("--xml-output",&MTestMain::treatXMLOutput,
			      "control xml output (default no)",true);
    this->registerNewCallBack("--result-file-output",&MTestMain::treatResultFileOutput,
			      "control result output (default yes)",true);
    this->registerNewCallBack("--residual-file-output",&MTestMain::treatResidualFileOutput,
			      "control residual output (default no)",true);
    this->registerNewCallBack("--help-keywords",
			      &MTestMain::treatHelpCommands,
			      "display the help of all available commands and exit.");
    this->registerNewCallBack("--help-commands",
			      &MTestMain::treatHelpCommands,
			      "display the help of all available commands and exit."
			      "(this is equivalent to --help-keywords option).");
    this->registerNewCallBack("--help-keywords-list",
			      &MTestMain::treatHelpCommandsList,
			      "list available commands and exit.");
    this->registerNewCallBack("--help-commands-list",
			      &MTestMain::treatHelpCommandsList,
			      "list available commands and exit "
			      "(this is equivalent to --help-keywords-list option).");
    this->registerNewCallBack("--help-keyword",
			      &MTestMain::treatHelpCommand,
			      "display the help associated with a "
			      "keyword and exit.",true);
    this->registerNewCallBack("--help-command",
			      &MTestMain::treatHelpCommand,
			      "display the help associated with a "
			      "keyword and exit."
			      "(this is equivalent to "
			      "--help-keyword option).",true);
    this->registerNewCallBack("--floating-point-exceptions","-fpe",
			      &MTestMain::treatEnableFloatingPointExceptions,
			      "handle floating point exceptions through SIGFPE signals");
#if ! (defined _WIN32 || defined _WIN64 ||defined __CYGWIN__)
    this->registerNewCallBack("--backtrace","-bt",&MTestMain::treatBacktrace,
			      "print process stack when getting SIGSEGV or SIGFPE signals");
#endif
  }

  void
  MTestMain::treatEnableFloatingPointExceptions(void)
  {
    // mathematical
#if ! (defined _WIN32 || defined _WIN64 ||defined __CYGWIN__||defined __APPLE__)
#ifdef HAVE_FENV
    ::feclearexcept(FE_ALL_EXCEPT);
    ::feenableexcept(FE_DIVBYZERO); // division by zero
    ::feenableexcept(FE_INVALID);   // invalid operation
#endif /* HAVE_FENV */
#endif
  } // end of MTestMain::treatEnableFloatingPointExceptions

#if ! (defined _WIN32 || defined _WIN64 ||defined __CYGWIN__)
  void
  MTestMain::treatBacktrace(void)
  {
    using namespace tfel::system;
    // posix signals
    auto& sm = SignalManager::getSignalManager();
    // blocking all signals during treatment of signals SIGSEGV, SIGFPE
    struct sigaction action;
    sigfillset(&(action.sa_mask));
    action.sa_flags = 0;
    sm.registerHandler(SIGSEGV,sigPtrFun(SignalManager::printBackTrace),action);
    sm.registerHandler(SIGFPE,sigPtrFun(SignalManager::printBackTrace),action);
  } // end of MTestMain::treatBacktrace(void)
#endif

  void
  MTestMain::treatVerbose(void)
  {
    if(this->currentArgument->getOption().empty()){
      mfront::setVerboseMode(mfront::VERBOSE_LEVEL1);
    } else {
      const auto& option = this->currentArgument->getOption();
      if(option=="quiet"){
	mfront::setVerboseMode(mfront::VERBOSE_QUIET);
      } else if(option=="level0"){
	mfront::setVerboseMode(mfront::VERBOSE_LEVEL0);
      } else if(option=="level1"){
	mfront::setVerboseMode(mfront::VERBOSE_LEVEL1);
      } else if (option=="level2"){
	mfront::setVerboseMode(mfront::VERBOSE_LEVEL2);
      } else if (option=="level3"){
	mfront::setVerboseMode(mfront::VERBOSE_LEVEL3);
      } else if (option=="debug"){
	mfront::setVerboseMode(mfront::VERBOSE_DEBUG);
      } else if (option=="full"){
	mfront::setVerboseMode(mfront::VERBOSE_FULL);
      } else {
	throw(std::runtime_error("MTestMain::treatVerbose : "
				 "unknown option '"+option+"'"));
      }
    }
  } // end of MTestMain::treatVerbose

  void
  MTestMain::treatXMLOutput(void)
  {
    using namespace std;
    if(this->currentArgument->getOption().empty()){
      this->xml_output = true;
    } else {
      const auto& option = this->currentArgument->getOption();
      if(option=="true"){
	this->xml_output = true;
      } else if(option=="false"){
	this->xml_output = false;
      } else {
	string msg("MTestMain::treatXMLOutput : ");
	msg += "unknown option '"+option+"'";
	throw(runtime_error(msg));
      }
    }
  } // end of MTestMain::treatXMLOutput

  void
  MTestMain::treatResultFileOutput(void)
  {
    using namespace std;
    if(this->currentArgument->getOption().empty()){
      this->result_file_output = true;
    } else {
      const auto& option = this->currentArgument->getOption();
      if(option=="true"){
	this->result_file_output = true;
      } else if(option=="false"){
	this->result_file_output = false;
      } else {
	string msg("MTestMain::treatResultFileOutput : ");
	msg += "unknown option '"+option+"'";
	throw(runtime_error(msg));
      }
    }
  } // end of MTestMain::treatResultFileOutput

  void
  MTestMain::treatResidualFileOutput(void)
  {
    if(this->currentArgument->getOption().empty()){
      this->residual_file_output = true;
    } else {
      const auto& option = this->currentArgument->getOption();
      if(option=="true"){
	this->residual_file_output = true;
      } else if(option=="false"){
	this->residual_file_output = false;
      } else {
	throw(std::runtime_error("MTestMain::treatResidualFileOutput : "
				 "unknown option '"+option+"'"));
      }
    }
  } // end of MTestMain::treatResidualFileOutput

  void
  MTestMain::treatHelpCommandsList(void)
  {
    MTestParser p;
    p.displayKeyWordsList();
    ::exit(EXIT_SUCCESS);
  } // end of MTestMain::treatHelpCommandsList

  void
  MTestMain::treatHelpCommands(void)
  {
    MTestParser p;
    p.displayKeyWordsHelp();
    ::exit(EXIT_SUCCESS);
  } // end of MTestMain::treatHelpCommands
  
  void
  MTestMain::treatHelpCommand()
  {
    const auto& k = this->currentArgument->getOption();
    if(k.empty()){
      throw(std::runtime_error("MTestMain::treatHelpCommand : "
			       "no command specified"));
    }
    MTestParser p;
    p.displayKeyWordDescription(k);
    ::exit(EXIT_SUCCESS);
  }

  void
  MTestMain::treatUnknownArgument(void)
  {
    using namespace tfel::utilities;
    const auto& a = this->currentArgument->as_string();
    if(a[0]=='-'){
#if ! (defined _WIN32 || defined _WIN64 ||defined __CYGWIN__)
      ArgumentParserBase<MTestMain>::treatUnknownArgument();
#else
      std::cerr << "mtest : unsupported option '" << a << "'\n";
      exit(EXIT_FAILURE);
#endif /* __CYGWIN__ */
    }
    this->inputs.push_back(this->currentArgument->as_string());
    return;
  } // end of MTestMain::treatUnknownArgument()

  std::string 
  MTestMain::getVersionDescription(void) const
  {
    return "mtest is an behaviour testing utility";
  }

  std::string 
  MTestMain::getUsageDescription(void) const
  {
    return "Usage : mtest [options] [filesusage]";
  }

  int
  MTestMain::execute(void)
  {
    using namespace std;
    using namespace tfel::tests;
    auto& tm = TestManager::getTestManager();
    for(const auto& i : this->inputs){
      string tname;
      const auto pos = i.rfind('.');
      if(pos!=string::npos){
	tname = i.substr(0,pos);
      } else {
	tname = i;
      }
      auto t = make_shared<MTest>();
      t->readInputFile(i);
      if(this->result_file_output){
	t->setOutputFileName(tname+".res");
      }
      if(this->residual_file_output){
	t->setResidualFileName(tname+"-residual.res");
      }
      tm.addTest("MTest/"+tname,t);
      if(this->xml_output){
	shared_ptr<TestOutput> o(new XMLTestOutput(tname+".xml"));
	tm.addTestOutput("MTest/"+tname,o);
      }
      tm.addTestOutput("MTest/"+tname,cout);
    }
    const auto r = tm.execute();
    return r.success() ?  EXIT_SUCCESS : EXIT_FAILURE;
  }

  MTestMain::~MTestMain()
  {}

} // end of namespace mtest

/* coverity [UNCAUGHT_EXCEPT]*/
int main(const int argc,
	 const char * const * const argv)
{
  using namespace std;
  using namespace mtest;
  int r = EXIT_FAILURE;
#if defined _WIN32 || defined _WIN64 ||defined __CYGWIN__
  try{
#endif /* __CYGWIN__ */
    MTestMain m(argc,argv);
    r = m.execute();
#if defined _WIN32 || defined _WIN64 ||defined __CYGWIN__
  }
  catch(exception& e){
    cerr << e.what() << endl;
    return r;
  }
#endif /* __CYGWIN__ */
  return r;
} // end of main