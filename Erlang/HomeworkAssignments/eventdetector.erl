-module(eventdetector).
-compile(export_all).

start(InitialState,TransitionFun) -> spawn(?MODULE,eventdetector,[InitialState,TransitionFun,[]]).

eventdetector(State,TFun,Observers) ->
	receive
		{Pid, add_me} -> Pid ! {added}, eventdetector(State,TFun,[Pid|Observers]);
		{Pid, add_yourself_to, EDPid} -> EDPid ! {self(), add_me}, 
										 receive {added} -> Pid ! {added} end,
										eventdetector(State,TFun,Observers);
		{Pid, state_value} -> Pid ! {value_is, State}, eventdetector(State,TFun,Observers);
		Other -> {NewState, Event} = TFun(State,Other),
				 case Event of
					none -> eventdetector(NewState,TFun,Observers);
					(_) -> [X ! Event|| X <- Observers], eventdetector(NewState,TFun,Observers)
				end
	end.