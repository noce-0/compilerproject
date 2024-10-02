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
int WhileStmt::interpret() {
    while(condition->interpret()) loop->interpret();
    return 0;
}

int DoStmt::interpret(){
    do{
        doloop->interpreter();
    }while(condition->interpret())
    return 0;
}



