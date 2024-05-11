#include <Parsers/PostgreSQL/Common/util/JSONHelpers.h>
#include <Parsers/PostgreSQL/Common/Errors.h>
#include <Common/Exception.h>

#include <Parsers/PostgreSQL/Targets/TransformTarget.h>

#include <Parsers/ASTSelectQuery.h>
#include <Parsers/ASTExpressionList.h>

namespace DB::PostgreSQL
{
    ASTPtr TransformSelectSimpleStatement(const std::shared_ptr<Node> node) 
    {
        auto ast = std::make_shared<ASTSelectQuery>();
        auto exprList = std::make_shared<ASTExpressionList>();

        auto targets = ((*node)["targetList"])->GetNodeArray();
        if (targets.size() > 1) 
        {
            throw Exception(ErrorCodes::NOT_IMPLEMENTED, "TransformSelectSimpleStatement not implemented");
        }
        auto targetAst = TransformTarget(targets[0]->GetOnlyChild());
        exprList->children.push_back(targetAst);
        ast->setExpression(ASTSelectQuery::Expression::SELECT, exprList);
        return ast;
    }
}
