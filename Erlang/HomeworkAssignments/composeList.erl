-module(composeList).
-compile(export_all).

composeList([]) -> fun(X) -> X end;
composeList([Func|Funcs]) -> ( fun(X) -> Func(composeList(Funcs)) end).

testFunc(PredList,Number) -> TestPred = composeList(PredList),
						 TestPred(Number).