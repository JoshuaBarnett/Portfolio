module Improve where
import StatementsExpressions
	  
improve :: Statement -> Statement
improve (ExpStmt e) = (ExpStmt (getExpVar e))
improve (IfStmt e stmt) = (stmt)
improve (AssignStmt string e) = (AssignStmt string e)

getExpVar :: Expression -> Expression 
getExpVar exp = case exp of
							   VarExp string 	 -> VarExp string
							   NumExp integer 	 -> NumExp integer
							   EqualsExp e1 e2 	 -> EqualsExp e1 e2
							   BeginExp [stmt] exp -> getStmtHelp [stmt]
							   BeginExp [] exp 	 -> exp

getStmtHelp :: [Statement] -> Expression
getStmtHelp (x:xs) = case x of
								(IfStmt exp stmt) -> exp
							   
