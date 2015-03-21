-- $Id: InfSet.hs,v 1.1 2015/02/12 04:17:59 leavens Exp leavens $
module InfSet where
fromFunc :: (a -> Bool) -> (Set a)
unionSet :: Set a -> Set a -> Set a
intersectSet :: Set a -> Set a -> Set a
inSet :: a -> Set a -> Bool
complementSet :: Set a -> Set a

-- define the type (Set a) as one of the following and then...

data Set a = Set {charfun :: (a->Bool)}

-- Write your code below for the operations declared above...

fromFunc func = Set {charfun = func}

unionSet set1 set2 = Set {charfun = (\x -> ((charfun set1 x) || (charfun set2 x)))}

intersectSet set1 set2 = Set {charfun = (\x -> ((charfun set1 x) && (charfun set2 x)))}

inSet x set = charfun set x

complementSet set = Set {charfun = (\x -> (not (charfun set x)))}
