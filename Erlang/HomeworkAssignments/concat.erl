%PROMPT:

% In Erlang, without using any functions from Erlang’s lists module, write a
%function concat/1, whose type is given by the following.
%-spec concat(Lists :: [[T]]) -> [T].
%The function concat takes a list of lists of elements (of some type T) and returns a list of the elements
%(of type T) formed by concatenating the inner lists together in order. The following are examples written
%using the Erlang testing module. You can use the built-in ++ in your code, or any other helping
%functions. Run these tests by compiling your file and the testing file, and then running
%concat_tests:main().

%CODE:
-module(concat).
-export([concat/1]).
-spec concat(Lists :: [[T]]) -> [T].
concat([]) -> [];
concat([First|Rest]) -> First ++ (concat(Rest)).
