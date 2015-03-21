--PROMPT:

--In Haskell, using tail recursion, write a polymorphic function
--whatIndex :: (Eq a) => a -> [a] -> Integer
--that takes an element of some Eq type, a, sought, and a finite list, lst, and returns the 0-based index of
--the first occurrence of sought in lst. However, if sought does not occur in lst, it returns -1.
--Your code must not use any library functions and must be tail recursive.

--CODE:

module WhatIndex where

whatIndex :: (Eq a) => a -> [a] -> Integer
whatIndex b [] = -1
whatIndex b (x:xs) = whatIndexHelperWrapper b (x:xs) 0

whatIndexHelperWrapper :: (Eq a) => a -> [a] -> Integer -> Integer
whatIndexHelperWrapper b [] cntr = -1
whatIndexHelperWrapper b (x:xs) cntr
	| x == b = cntr
	| x /= b = whatIndexHelperWrapper b xs (cntr+1)
