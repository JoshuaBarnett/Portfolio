-module(electionserver).
-compile(export_all).

-spec start() -> pid().
start() -> spawn(?MODULE,electionserver,[[],[]]).

electionserver(VoteList,CandList) ->
	receive
		{Pid, vote, Candidate} ->
			Pid ! ok,
			lists:member(Candidate,CandList) of
				true -> electionserver(addvote(VoteList,Candidate),CandList);
				(_) -> electionserver([{Candidate,1}|VoteList],[Candidate|CandList])
			end;
		{Pid, get_res} ->
			Pid ! {self(),result, lists:sort(VoteList)},
			electionserver(VoteList,CandList)
	end.

-spec vote(ES::pid(), Candidate::atom()) -> ok.
vote(SPid,Candidate) -> SPid ! {self(), vote, Candidate},
	receive ok -> ok end.

-spec results(ES::pid()) -> [{atom(), non_neg_integer()}].
results(SPid) -> SPid ! {self(), get_res},
	receive {Spid, result, ResList} -> ResList end. 
	
addvote(VoteList,Candidate) -> [case (Candidate) of 
								CandName -> {CandName,VoteCount+1};
								(_) -> {CandName,VoteCount} end || {CandName,VoteCount} <- VoteList].