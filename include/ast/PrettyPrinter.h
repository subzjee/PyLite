#pragma once

#include "ast/ASTVisitor.h"
#include "ast/AssignmentStatement.h"
#include "ast/BinaryExpression.h"
#include "ast/Identifier.h"
#include "ast/VariableDefinition.h"

#include <sstream>

namespace chocopy::ast {
class PrettyPrinter : public ASTVisitor {
  using ASTVisitor::visit;

public:
  std::any visit(const Program& ctx) override;
  std::any visit(const Literal& ctx) override;
  std::any visit(const VariableDefinition& ctx) override;
  std::any visit(const AssignmentStatement& ctx) override;
  std::any visit(const Identifier& ctx) override;
  std::any visit(const ast::BinaryExpression<ast::Expression>& ctx) override;
  std::any
  visit(const ast::BinaryExpression<ast::ConstantExpression>& ctx) override;
  std::any visit(const ast::UnaryExpression<ast::Expression>& ctx) override;
  std::any
  visit(const ast::UnaryExpression<ast::ConstantExpression>& ctx) override;

private:
  std::ostringstream out;
};
} // namespace chocopy::ast