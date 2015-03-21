--PROMPT:

--The function you are to write in Haskell is
--average3 :: (Double,Double,Double) -> Double
--which takes a triple of Doubles, (x,y,z), and returns a Double that is the average (i.e., the arithmetic
--mean) of x, y, and z. 

--CODE:

module Average3 where
average3 :: (Double,Double,Double) -> Double
average3 (a,b,c) = (a+b+c)/3
