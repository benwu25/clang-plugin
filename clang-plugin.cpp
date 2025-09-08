#include <memory>
#include <iostream>
#include <llvm/Support/Registry.h>
#include <llvm/Transforms/IPO/GlobalDCE.h>
#include <llvm/Passes/PassBuilder.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/DeclGroup.h>
#include <clang/AST/Decl.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/Tooling.h>
#include <clang/Frontend/FrontendPluginRegistry.h>
#include <clang/CodeGen/ModuleBuilder.h>
#include "my-pass.h"

class ClangPluginConsumer : public clang::ASTConsumer {

  virtual bool HandleTopLevelDecl(clang::DeclGroupRef d) override {
    if (d.isSingleDecl()) {
      clang::Decl *decl = d.getSingleDecl();
      if (clang::NamedDecl *named = dynamic_cast<clang::NamedDecl *>(decl)) {
        // std::cout << "name: " << named->getDeclName().getAsString() << "\n";
      }
      clang::Stmt *body = decl->getBody();
      if (body != nullptr) {
        // body->dump();
        clang::StmtIterator it = body->child_begin();
      }
    }
    return true;
  }

};

class ClangPluginAction : public clang::PluginASTAction {
public:
  std::unique_ptr<clang::ASTConsumer>
  CreateASTConsumer(clang::CompilerInstance &CI,
                    clang::StringRef InFile) override {
    llvm::errs() << "registering MyPass...\n";
    clang::CodeGenOptions &cgo = CI.getCodeGenOpts();

    auto pipeline_start = [](llvm::ModulePassManager &MPM, llvm::OptimizationLevel Level) {
      MPM.addPass(llvm::MyPass{});
    };
    cgo.PassBuilderCallbacks.push_back(
        [=](llvm::PassBuilder &PB) {
          PB.registerPipelineStartEPCallback(pipeline_start);
        }
    );

    return std::make_unique<ClangPluginConsumer>();
  }

  bool ParseArgs(const clang::CompilerInstance &CI,
                 const std::vector<std::string> &Args) override {
    return true;
  }

  clang::PluginASTAction::ActionType getActionType() override {
    return clang::PluginASTAction::ActionType::AddBeforeMainAction;
  }
};

static clang::FrontendPluginRegistry::Add<ClangPluginAction>
    __Reg1("ClangPlugin", "");
