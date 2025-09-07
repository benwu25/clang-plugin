#ifndef LLVM_TRANSFORMS_MYPASS_H
#define LLVM_TRANSFORMS_MYPASS_H

#include <llvm/IR/PassManager.h>
#include <llvm/IR/Module.h>

namespace llvm {

class MyPass : public PassInfoMixin<MyPass> {
public:
  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM);
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_MYPASS_H
