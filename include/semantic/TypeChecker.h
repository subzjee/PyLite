#pragma once

#include "DiagnosticsManager.h"
#include "ast/ASTVisitor.h"
#include "ast/AssignmentStatement.h"
#include "ast/VariableDefinition.h"
#include "semantic/TypeEnvironment.h"

namespace chocopy {
class TypeChecker : public ASTVisitor {
public:
  using ASTVisitor::visit;

  TypeChecker(SymbolTable& symbol_table,
              DiagnosticsManager& diagnostics_manager)
      : m_diag_manager{diagnostics_manager}, local_env(symbol_table) {};

  std::any visit(const ast::VariableDefinition& ctx) override;
  std::any visit(const ast::AssignmentStatement& ctx) override;

private:
  DiagnosticsManager& m_diag_manager;
  TypeEnvironment local_env;
};
} // namespace chocopy