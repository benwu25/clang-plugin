#include <iostream>
#include "my-pass.h"

llvm::PreservedAnalyses llvm::MyPass::run(llvm::Module &M,
                                          llvm::ModuleAnalysisManager &AM) {
  llvm::errs() << "hi there!\n";
  llvm::errs() << M.getSourceFileName() << "\n";
  return llvm::PreservedAnalyses::all();
}
