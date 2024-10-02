//---------------VERSIONE CLEO------------//


//-------------SUBCLASS STATEMENT----------//

int IfStmt::interpret(){
    if(condition->interpret()){
        then_stmt->interpret();
    }
    return 0;
}

int ElseStmt::interpret(){
    if(condition->interpret()){
        then_stmt->interpret();
    }
    else{
        else_stmt->interpret();
    }
    return 0;
}

