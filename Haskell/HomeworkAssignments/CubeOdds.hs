--PROMPT:

-- In Haskell, write the function:
--cubeOdds :: [Integer] -> [Integer]
--that takes a list of Integers, lst, and returns a list of Integers that is just like lst, except that each odd
--element of lst is replaced by the cube of that element. In your solution, you might find it helpful to use
--the built-in predicate odd.

--CODE:

module CubeOdds where
cubeOdds :: [Integer] -> [Integer]
cubeOdds n = [ if odd x then x^3 else x | x<-n] -- list comp, if it's odd cube it if it's not leave it
