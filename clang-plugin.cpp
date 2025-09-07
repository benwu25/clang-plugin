#include <memory>
#include <iostream>
#include <llvm/Support/Registry.h>
#include <llvm/Transforms/IPO/GlobalDCE.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/DeclGroup.h>
#include <clang/AST/Decl.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/Tooling.h>
#include <clang/Frontend/FrontendPluginRegistry.h>
#include <clang/CodeGen/ModuleBuilder.h>

// CONSUMER NOTES
// CodeGenerator is building the Module... probably can't interact with it?
//  - use debug build to check when your CodeGenerator is build  (break at CreateLLVMCodeGen to see what order and how many)
// As of late 2024, there's CIR stuff. llvm-18 didn't have that. CodeGenerator
// was the lowest Consumer available in llvm-18 headers.
class ClangPluginConsumer : public clang::CodeGenerator {

  virtual bool HandleTopLevelDecl(clang::DeclGroupRef d) override {
    llvm::Module *the_module = this->GetModule(); // built or not?
    llvm::GlobalDCEPass global_dce{};

    clang::CodeGen::CodeGenModule &cgm = this->CGM();

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
    return clang::PluginASTAction::ActionType::AddAfterMainAction;
  }
};

static clang::FrontendPluginRegistry::Add<ClangPluginAction>
    __Reg1("ClangPlugin", "");
