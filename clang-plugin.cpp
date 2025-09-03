#include <memory>
#include <iostream>
#include <llvm/Support/Registry.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/DeclGroup.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/Tooling.h>
#include <clang/Frontend/FrontendPluginRegistry.h>

// what can an ASTConsumer do?
class ClangPluginConsumer : public clang::ASTConsumer {

  // Override functions to get callbacks?

  virtual bool HandleTopLevelDecl(clang::DeclGroupRef d) {
    std::cout << "toplevel decl. Is DeclGroupRef gonna allow any mutation?\n";
    if (d.isSingleDecl()) {
      clang::Decl *decl = d.getSingleDecl(); // see clang/AST/DeclBase.h for interaction
      std::cout << "got single decl\n"; // two for 2 function definitions
                                        // (foo and main)
    }
    return true;
  }
};

class ClangPluginAction : public clang::PluginASTAction {
public:
  std::unique_ptr<clang::ASTConsumer>
  CreateASTConsumer(clang::CompilerInstance &CI,
                    clang::StringRef InFile) override {
    return std::make_unique<ClangPluginConsumer>();
  }

  bool ParseArgs(const clang::CompilerInstance &ci,
                 const std::vector<std::string> &args) override {
    for (int i = 0; i < args.size(); ++i) {
      // do something
    }
    return true;
  }

  clang::PluginASTAction::ActionType getActionType() override {
    return clang::PluginASTAction::ActionType::AddBeforeMainAction;
  }
};

static clang::FrontendPluginRegistry::Add<ClangPluginAction>
    __Reg1("ClangPlugin", "");
