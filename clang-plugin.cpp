#include <memory>
#include <iostream>
#include <llvm/Support/Registry.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/DeclGroup.h>
#include <clang/AST/Decl.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/Tooling.h>
#include <clang/Frontend/FrontendPluginRegistry.h>
#include <clang/CodeGen/ModuleBuilder.h>

class ClangPluginConsumer : public clang::CodeGenerator { // extend different kinds of ASTConsumer to do different things?

  virtual bool HandleTopLevelDecl(clang::DeclGroupRef d) {
    if (d.isSingleDecl()) {
      clang::Decl *decl = d.getSingleDecl();
      if (clang::NamedDecl *named = dynamic_cast<clang::NamedDecl *>(decl)) {
        std::cout << "name: " << named->getDeclName().getAsString() << "\n";
      }
      clang::Stmt *body = decl->getBody();
      if (body != nullptr) {
        body->dump();
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
    return std::make_unique<ClangPluginConsumer>();
  }

  bool ParseArgs(const clang::CompilerInstance &ci,
                 const std::vector<std::string> &args) override {
    for (auto &arg : args) {
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
