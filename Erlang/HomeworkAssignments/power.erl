% PROMPT:

% In Erlang, write a stateless server in a module named power. This server
% responds to messages of the form {Pid, power, N, M}, where Pid is the sender’s process id, N and M
% are non-negative integers. When the server receives such a message, it responds by sending a message
% of the form {answer, Res} to Pid, where Res is N
% M, that is N raised to the Mth power. In your solution
% you can use the library function math:pow, which is defined so that math:pow(N,M) returns N
% M. Figure 3
% has tests for this problem. To run our tests, run power_tests:main().

% CODE:

-module(power).
-export([start/0]).

-spec start() -> pid().
start() -> spawn(fun power/0).

power() ->
	io:format("still live~n"),
	receive
		{Pid,power,N,M} ->
			io:format("PID: ~p n: ~p m: ~p ~n",[Pid,N,M]),
			Pid ! {answer,math:pow(N,M)},
			power()
	end.
	
