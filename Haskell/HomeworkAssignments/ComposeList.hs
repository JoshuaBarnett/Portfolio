-- Write a function
--composeList :: [(a -> a)] -> (a -> a)
--that takes a list of functions, and returns a function which is their composition.

module ComposeList where

composeList :: [(a -> a)] -> (a -> a)
composeList [] = (\x -> x)
composeList (pred:rest) = (\x -> pred (composeList (rest) x))
