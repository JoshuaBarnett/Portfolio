-module(barrier).
-export([start/1,barrier/2]).

start(NumProc) -> spawn(?MODULE,barrier,[NumProc,[]]).


barrier(NumProc,Pids) ->
		receive
			{Pid, done} ->
						Pid ! {self(), ok},
						case NumProc of
							1 ->
								[X ! {self(), continue}|| X <- ([Pid]++Pids)],
								barrier(NumProc-1,[]);
							(_) -> barrier(NumProc-1,[Pid|Pids])
						end;
			{Pid, how_many_running} ->
				Pid ! {self(), number_running_is, NumProc},
				barrier(NumProc,Pids)
		end.
