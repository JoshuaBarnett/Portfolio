-module(logger).
-export([start/0,logger/1]).

start() -> spawn(?MODULE,logger,[[]]).

logger(Entries) ->
	receive
		{Pid, log, Entry} -> 
			Pid ! {self(), logged},
			logger(Entries++[Entry]);
		{Pid, fetch} ->
			Pid ! {self(), log_is, Entries},
			logger(Entries)
	end.