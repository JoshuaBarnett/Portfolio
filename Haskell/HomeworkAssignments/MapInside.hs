-- Using Haskell’s built-in map function, write the function
--mapInside :: (a -> b) -> [[a]] -> [[b]]
--that for some types a and b takes a function f of type a -> b, and a list of lists of type a, lls, and
--returns a list of type [[b]] that consists of applying f to each element inside each list in lls, preserving
--the structure of the lists.

module MapInside where
import Data.List

mapInside :: (a -> b) -> [[a]] -> [[b]]
mapInside pred [] = []
mapInside pred (x:rest) = (map pred x) : (mapInside pred rest)
