--PROMPT:

-- Write the function
--deleteNth :: (Eq a) => Int -> a -> [a] -> [a]
--that takes a positive Int, n, an element, toDelete, of some equality type a, and a list, as, of type [a],
--and returns a list that is just like as, but which does not contain the nth occurrence (in as) of the element
--toDelete. Your solution must not use any Haskell library functions. You may assume that n is strictly greater than 0.

--CODE:

module DeleteNth where
deleteNth :: (Eq a) => Int -> a -> [a] -> [a]
deleteNth n b [] = [] --recursive base case!
deleteNth n b (a:lst) 
	| n == 1 && a == b = deleteNth 0 b lst --if n is down to one and a = b, then skip this node and move on
	| a == b && n /= 1 = a:deleteNth (n-1) b lst --if a = b and n isn't equal to one, decrement and move on in recursion
	| otherwise = a:deleteNth n b lst --any other case (a/=b) then we add the node and keep going
