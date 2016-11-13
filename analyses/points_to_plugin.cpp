#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include "instr_plugin.hpp"
#include "llvm/analysis/PointsTo/PointsTo.h"
#include "analysis/PointsTo/PointsToFlowInsensitive.h"

using dg::analysis::pta::PSNode;
class PointsToPlugin : public InstrPlugin
{
 private:
  std::unique_ptr<dg::LLVMPointerAnalysis> PTA;

 public:
  bool isNull(llvm::Value* a){
	  //TODO

	  return false;
  }

  bool isEqual(llvm::Value* a, llvm::Value* b){
	  if(PTA){
		  PSNode *psnode = PTA->getPointsTo(a);
		  for (auto& ptr : psnode->pointsTo) {
			  llvm::Value *llvmVal = ptr.target->getUserData<llvm::Value>();
			  if(llvmVal == b) return true;
		  }
	  }
	  else{
		  return true; // a may point to b
	  }

	  return false;
  }

  bool isNotEqual(llvm::Value* a, llvm::Value* b){
	  if(PTA){
		  PSNode *psnode = PTA->getPointsTo(a);
		  for (auto& ptr : psnode->pointsTo) {
			  llvm::Value *llvmVal = ptr.target->getUserData<llvm::Value>();
			  if(llvmVal == b) return false;
		  }
	  }
	  else{
		  return true; // we do not know whether a points to b
	  }

	  return true;
  }

  bool greaterThan(llvm::Value* a, llvm::Value* b){
	  if(PTA){
		  //TODO
	  }
	  return true;
  }

  bool lessThan(llvm::Value* a, llvm::Value* b){
	  if(PTA){
		  //TODO
	  }
	  return true;
  }

  bool lessOrEqual(llvm::Value* a, llvm::Value* b){
	  if(PTA){
		  //TODO
	  }
	  return true;
  }

  bool greaterOrEqual(llvm::Value* a, llvm::Value* b){
	  if(PTA){
		  //TODO
	  }
	  return true;
  }

  PointsToPlugin(llvm::Module* module) {
      llvm::errs() << "Running points-to analysis...\n";
	  PTA = std::unique_ptr<dg::LLVMPointerAnalysis>(new dg::LLVMPointerAnalysis(module));
	  PTA->run<dg::analysis::pta::PointsToFlowInsensitive>();
  }
};

extern "C" InstrPlugin* create_object(llvm::Module* module){
    return new PointsToPlugin(module);
}
