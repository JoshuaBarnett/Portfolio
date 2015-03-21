--PROMPT:

--This problem will have you write a solution in 2 ways. The problem is to write a function
--that takes a list of Integers and returns a list that is just like the argument but in which every element is
--10 greater than the corresponding element in the argument list.
--(a) (5 points) Write the function
--add10_list_comp :: [Integer] -> [Integer]
--that solves the above problem by using a list comprehension.
--(b) (5 points) Write the function
--add10_list_rec :: [Integer] -> [Integer]
--that solves the above problem by writing out the recursion yourself; that is, without using a list
--comprehension and without using map or any other higher-order library function.

--CODE:


module Add10List where

add10_list_comp :: [Integer] -> [Integer]
add10_list_comp n = [x+10 | x <- n] -- with a list comprehension

add10_list_rec :: [Integer] -> [Integer]
add10_list_rec [] = [] --base case!
add10_list_rec (n:ns) = (n+10):add10_list_rec ns --add 10 to current node, recurse through tail
