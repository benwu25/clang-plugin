#include <iostream>
#include "my-pass.h"

llvm::PreservedAnalyses llvm::MyPass::run(llvm::Module &M,
                                          llvm::ModuleAnalysisManager &AM) {
  // TODO: analysis/optimization on M.
  //       inspect how other Transforms do things on
  //       llvm::Function and llvm::Module. Also look
  //       at the available callbacks and places to do
  //       your pass for inspiration.
  llvm::errs() << "hi there!\n";
  llvm::errs() << M.getSourceFileName() << "\n";
  return llvm::PreservedAnalyses::all();
}
