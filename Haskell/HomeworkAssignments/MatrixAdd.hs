-- $Id: MatrixAdd.hs,v 1.1 2013/09/24 14:54:21 leavens Exp $
module MatrixAdd where
import Matrix
import MatrixInstances

sameShape :: (Matrix a) -> (Matrix a) -> Bool
pointwiseApply :: (a -> a -> b) -> (Matrix a) -> (Matrix a) -> (Matrix b)
add :: (Num a) => (Matrix a) -> (Matrix a) -> (Matrix a)
sub :: (Num a) => (Matrix a) -> (Matrix a) -> (Matrix a)
-- without changing the above, implement the declared functions.

sameShape (Mat((x1,y1),pred1)) (Mat((x2,y2),pred2)) = if ((x1==x2)&&(y1==y2)) then True else False

pointwiseApply func (Mat((x1,y1),pred1)) (Mat((x2,y2),pred2)) = if (sameShape (Mat((x1,y1),pred1)) (Mat((x2,y2),pred2))) 
																then (Mat((x1,y1),\(i,j) -> ((pred1(i,j)) `func` (pred2(i,j)))) )
																else error "Matrix shapes mismatched"

add (Mat((x1,y1),pred1)) (Mat((x2,y2),pred2)) = pointwiseApply (+) (Mat((x1,y1),pred1)) (Mat((x2,y2),pred2))

sub (Mat((x1,y1),pred1)) (Mat((x2,y2),pred2)) = pointwiseApply (-) (Mat((x1,y1),pred1)) (Mat((x2,y2),pred2))
