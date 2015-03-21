module Rank where
import Data.List

rank :: (Ord a) => [a] -> [(Int, a)]
rank [] = []
rank things = rankHelp (sort(things)) 1 1

rankHelp :: (Ord a) => [a] -> Int -> Int -> [(Int, a)]
rankHelp [] ranking numTied = []
rankHelp [x] ranking  numTied = [(ranking,x)]
rankHelp (x:xs) ranking numTied = (ranking,x) :
						if (x == (head(xs))) then ((rankHelp xs ranking (numTied+1))) else ((rankHelp xs (ranking+numTied) 1))
