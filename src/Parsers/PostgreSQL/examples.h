struct Example{
    std::string Query, PGAST, ClickHouseAST;
};

//Examples
std::vector<Example> examples = {
    {
        "SELECT 1"
        ,
        "{\"version\":160001,\"stmts\":[{\"stmt\":{\"SelectStmt\":{\"targetList\":[{\"ResTarget\":{\"val\":{\"A_Const\":{\"ival\":{\"ival\":1},\"location\":7}},\"location\":7}}],\"limitOption\":\"LIMIT_OPTION_DEFAULT\",\"op\":\"SETOP_NONE\"}}}]}"
        ,
        "SelectWithUnionQuery (children 1) "
            "ExpressionList (children 1) "
                "SelectQuery (children 1) "
                    "ExpressionList (children 1) "
                        "Literal UInt64_1"
    },
    {
        "SELECT 1 UNION ALL SELECT 2"
        ,
        "{\"version\":160001,\"stmts\":[{\"stmt\":{\"SelectStmt\":{\"limitOption\":\"LIMIT_OPTION_DEFAULT\",\"op\":\"SETOP_UNION\",\"all\":true,\"larg\":{\"targetList\":[{\"ResTarget\":{\"val\":{\"A_Const\":{\"ival\":{\"ival\":1},\"location\":7}},\"location\":7}}],\"limitOption\":\"LIMIT_OPTION_DEFAULT\",\"op\":\"SETOP_NONE\"},\"rarg\":{\"targetList\":[{\"ResTarget\":{\"val\":{\"A_Const\":{\"ival\":{\"ival\":2},\"location\":26}},\"location\":26}}],\"limitOption\":\"LIMIT_OPTION_DEFAULT\",\"op\":\"SETOP_NONE\"}}}}]}"
        ,
        "SelectWithUnionQuery (children 1) "
            "ExpressionList (children 2) "
                "SelectQuery (children 1) "
                    "ExpressionList (children 1) "
                        "Literal UInt64_1 "
                "SelectQuery (children 1) "
                    "ExpressionList (children 1) "
                        "Literal UInt64_2"
    },
    {
        "SELECT "
        " * "
        "FROM users "
        ,
        "{\"version\":160001,\"stmts\":[{\"stmt\":{\"SelectStmt\":{\"targetList\":[{\"ResTarget\":{\"val\":{\"ColumnRef\":{\"fields\":[{\"A_Star\":{}}],\"location\":8}},\"location\":8}}],\"fromClause\":[{\"RangeVar\":{\"relname\":\"users\",\"inh\":true,\"relpersistence\":\"p\",\"location\":15}}],\"limitOption\":\"LIMIT_OPTION_DEFAULT\",\"op\":\"SETOP_NONE\"}}}]}"
        ,
        "SelectWithUnionQuery (children 1) "
            "ExpressionList (children 1) "
                "SelectQuery (children 2) "
                    "ExpressionList (children 1) "
                        "Asterisk "
                    "TablesInSelectQuery (children 1) "
                        "TablesInSelectQueryElement (children 1) "
                            "TableExpression (children 1) "
                                "TableIdentifier users "
    },
};
