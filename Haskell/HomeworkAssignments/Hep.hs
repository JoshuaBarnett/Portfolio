module Hep where
hep :: [Word] -> [Word]
type Word = String
hep [] = []
hep (x:xs) = case x of 
				"you" -> "u" : (hep xs)
				"are" -> "r" : (hep xs)
				"your" -> "ur" : (hep xs)
				"boyfriend" -> "bf" : (hep xs)
				"girlfriend" -> "gf" : (hep xs)
			 	"great" -> "gr8" : (hep xs)
				"I" -> if ((head xs) == "will") then "I'll" : (hep (tail xs)) else x : (hep xs)
				"see" -> if ((head xs) == "you") then "cya" : (hep (tail xs)) else x : (hep xs)
				"be" -> if (((head xs) == "right")&&((head (tail xs)) == "back")) then "brb" : (hep (tail(tail(xs)))) else x : (hep xs)
				"by" -> if (((head xs) == "the")&&((head (tail xs)) == "way")) then "btw" : (hep (tail(tail(xs)))) else x : (hep xs)
				"for" -> if (((head xs) == "your")&&((head (tail xs)) == "information")) then "fyi" : (hep (tail(tail(xs)))) else x : (hep xs)
				"laughing" -> if (((head xs) == "out")&&((head (tail xs)) == "loud")) then "lol" : (hep (tail(tail(xs)))) else x : (hep xs)
				_ -> x : (hep xs)
