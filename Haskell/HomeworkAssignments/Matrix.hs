-- $Id: Matrix.hs,v 1.2 2015/02/12 03:40:09 leavens Exp $
module Matrix where
(Matrix, fillWith, fromRule, numRows, numColumns, 
               at, mtranspose, mmap)
-- newtype is like "data", but has some efficiency advantages
newtype Matrix a = Mat ((Int,Int),(Int,Int) -> a)

fillWith :: (Int,Int) -> a -> (Matrix a)
fillWith (x,y) e = Mat ((x,y), \(i,j)->e)
fromRule :: (Int,Int) -> ((Int,Int) -> a) -> (Matrix a)
fromRule (x,y) pred = Mat ((x,y), pred)
numRows :: (Matrix a) -> Int
numRows (Mat ((x,y),pred)) = x
numColumns :: (Matrix a) -> Int
numColumns (Mat ((x,y),pred)) = y
at :: (Matrix a) -> (Int, Int) -> a
at (Mat((x,y),pred)) (i,j) = pred (i,j)
mtranspose :: (Matrix a) -> (Matrix a)
mtranspose (Mat((x,y),pred)) = Mat ((y,x),\(i,j) -> (pred(j,i)))
mmap :: (a -> b) -> (Matrix a) -> (Matrix b)
mmap pred1 (Mat((x,y),pred2)) = Mat ((x,y), \(i,j) -> pred1(pred2((i,j))))
