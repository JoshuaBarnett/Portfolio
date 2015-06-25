-module(var).
-export([start/1,var/1]).

start(Val) -> spawn (?MODULE,var,[Val]).

var(Val) -> 
	receive
		{assign,NewVal} ->
			var(NewVal);
		{Pid,fetch} -> 
			Pid ! {value,Val},
			var(Val)
	end.