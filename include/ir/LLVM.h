#pragma once

#include "ast/ASTVisitor.h"
#include "ast/AssignmentStatement.h"
#include "ast/BinaryExpression.h"
#include "ast/ConstantExpression.h"
#include "ast/GroupingExpression.h"
#include "ast/Identifier.h"
#include "ast/UnaryExpression.h"
#include "semantic/SymbolTable.h"

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/Signals.h"

namespace chocopy {
class IRGen : public ASTVisitor {
public:
  using ASTVisitor::visit;

  IRGen(const llvm::StringRef module_name, SymbolTable& symbol_table)
      : m_ctx{std::make_unique<llvm::LLVMContext>()}, m_builder{*m_ctx},
        m_module{
            std::make_unique<llvm::Module>(std::move(module_name), *m_ctx)},
        m_symbol_table(symbol_table) {};

  [[nodiscard]] const llvm::Module& getModule() const { return *m_module; }

  virtual std::any visit(const ast::Program& ctx) override;
  virtual std::any visit(const ast::Literal& ctx) override;
  virtual std::any visit(const ast::VariableDefinition& ctx) override;
  virtual std::any visit(const ast::AssignmentStatement& ctx) override;
  virtual std::any
  visit(const ast::BinaryExpression<ast::Expression>& ctx) override;
  virtual std::any
  visit(const ast::BinaryExpression<ast::ConstantExpression>& ctx) override;
  virtual std::any
  visit(const ast::UnaryExpression<ast::Expression>& ctx) override;
  virtual std::any
  visit(const ast::UnaryExpression<ast::ConstantExpression>& ctx) override;
  virtual std::any visit(const ast::GroupingExpression& ctx) override;
  virtual std::any visit(const ast::Identifier& ctx) override;

private:
  void prologue();
  void epilogue();

  std::unique_ptr<llvm::LLVMContext> m_ctx;
  llvm::IRBuilder<> m_builder;
  std::unique_ptr<llvm::Module> m_module;

  SymbolTable& m_symbol_table;
  unsigned int scope = 0;

  llvm::StringMap<llvm::GlobalValue*> m_string_allocations{};
};
} // namespace chocopy