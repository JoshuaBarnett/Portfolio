%PROMPT:

%This problem is about “sales data records.” There are two record types that are
%involved in the type salesdata(), which are defined in the file salesdata.hrl (note that file extension
%carefully, it’s hrl with an “h”) shown below and included with the testing files.
% $Id: salesdata.hrl,v 1.1 2013/04/11 02:24:12 leavens Exp $
% Record definitions for the salesdata() type.
%-record(store, {address :: string(), amounts :: [integer()]}).
%-record(group, {gname :: string(), members :: [salesdata:salesdata()]}).
%The type salesdata() itself is defined by the following, which says that a sales data values is either a
%store record or a group record.
% $Id: salesdata.erl,v 1.4 2015/03/12 12:15:20 leavens Exp $
%-module(salesdata).
%-include("salesdata.hrl").
%-export_type([salesdata/0]).
%-type salesdata() :: #store{} | #group{}.
%Your task is to write, in Erlang, a function
%-spec substaddr(salesdata:salesdata(), string(), string()) -> salesdata:salesdata().
%that takes a sales data record SD, two strings New and Old, and returns a sales data record that is just like
%SD except that all store records in SD whose address field’s value is Old in SD are changed to New in the
%result.
%Your solution must follow the grammar; we will take points off for not following the grammar! In
%particular, you should never call substaddr with a list argument; be sure to use a helping function for
%lists instead.
%Figure 1 on the following page has tests for this problem. To run our tests, run
%substaddr_tests:main(). Note how the testing file does -include("salesdata.hrl"); your solution
%file (substaddr.erl) must also include this directive if you want to use the Erlang record syntax.
%To be clear, your solution should go in a file substaddr.erl, as the tests import substaddr/3 from that
%file. Thus to use the record syntax and typing, your solution file substaddr.erl should start out as
%follows. (Note that you cannot import the type salesdata/0 from salesdata.erl, as Erlang does not
%currently permit type imports.)

%CODE

-module(substaddr).
-include("salesdata.hrl").
-export([substaddr/3]).

%-spec substaddr(salesdata:salesdata(), string(), string()) -> salesdata:salesdata().
substaddr(#store{address = Name, amounts = Amts},New,Old) ->
	if
		(Name == Old) -> #store{address = New,amounts = Amts};
		true -> #store{address = Name,amounts = Amts}
	end;
substaddr(#group{gname = Gname, members = Memberlist},New,Old) -> #group{gname = Gname,members = [substaddr(X,New,Old) || X<- Memberlist]}.


