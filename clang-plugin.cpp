// includes
#include <memory>
#include <iostream>
#include <llvm/Support/Registry.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/Tooling.h>
#include <clang/Frontend/FrontendPluginRegistry.h>

// does the main work?
class ClangPluginConsumer : public clang::ASTConsumer {
public:
  ClangPluginConsumer() {
    std::cout << "Building ClangPluginConsumer\n";
  }
};

class ClangPluginAction : public clang::PluginASTAction {
public:
  // ClangPluginAction() {}

  std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &CI,
                                                         clang::StringRef InFile) {
    std::cout << "In CreateASTConsumer\n";
    return std::make_unique<ClangPluginConsumer>();
  }

  bool ParseArgs(const clang::CompilerInstance& ci, const std::vector<std::string>& args) {
    std::cout << "well hi!\n";
    for (int i = 0; i < args.size(); ++i) {
        // are these compiler args?
      std::cout << "well hullo!\n";
    }
    return true;
  }

  clang::PluginASTAction::ActionType getActionType() override {
    return clang::PluginASTAction::ActionType::AddBeforeMainAction;
  }
};

static clang::FrontendPluginRegistry::Add<ClangPluginAction> __Reg1("ClangPlugin", "");
