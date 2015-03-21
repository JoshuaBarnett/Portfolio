%  PROMPT:

% In Erlang, without using the lists module or any list
% comprehensions, write a tail-recursive function
% -spec count_matching (fun((T) -> boolean()), list(T)) -> non_neg_integer().
% that takes a predicate, Pred, and a list, Lst, and returns the number of elements in Lst that satisfy Pred.
% Examples are shown in Figure 2 on page 5.
% Note that your code must use tail recursion and is not allowed to use any functions from the list module
% or list comprehensions.
% Hint: In Erlang, you can call a fuction closure, say Pred on an argument X using the syntax Pred(X).
% However, you cannot call an arbitrary function in the guard of an if expression, as the syntax only
% allows guard sequences there. See Section 8.17 and Section 8.25 of the Erlang Reference Manual User’s
% Guide for details. Instead of using an if-expression, try using a case expression instead.

% CODE:

-module(count_matching).
-export([count_matching/2]).

-spec count_matching (fun((T) -> boolean()), list(T)) -> non_neg_integer().
count_matching(Func,[]) -> 0;
count_matching(Func,[X|Xs]) -> 
	case (Func(X)) of
		true -> 1 + (count_matching(Func,Xs));
		(_) -> (count_matching(Func,Xs))
	end.
