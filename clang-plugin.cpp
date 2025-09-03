#include <memory>
#include <iostream>
#include <llvm/Support/Registry.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/Tooling.h>
#include <clang/Frontend/FrontendPluginRegistry.h>

class ClangPluginConsumer : public clang::ASTConsumer {};

class ClangPluginAction : public clang::PluginASTAction {
public:
  std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &CI,
                                                        clang::StringRef InFile) override {
    std::cout << "In CreateASTConsumer\n";
    return std::make_unique<ClangPluginConsumer>();
  }

  bool ParseArgs(const clang::CompilerInstance& ci, const std::vector<std::string>& args) override {
    for (int i = 0; i < args.size(); ++i) {
      std::cout << "well hullo!\n";
    }
    return true;
  }

  clang::PluginASTAction::ActionType getActionType() override {
    return clang::PluginASTAction::ActionType::AddBeforeMainAction;
  }
};

static clang::FrontendPluginRegistry::Add<ClangPluginAction> __Reg1("ClangPlugin", "");
