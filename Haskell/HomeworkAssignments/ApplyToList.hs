module ApplyToList where
import BinaryRelation
import Relations

applyRel :: (Eq k) => k -> (BinaryRelation k v) -> [v]
applyRel a t = [x | (b,x)<-t, a == b] 
--use (b,x) to split t, allowing access to both parts of the binary relation. Include the second half if a == b (k alone == k from k v)

applyToList :: (Eq k) => [k] -> (BinaryRelation k v) -> [v]
applyToList [] t = [] --recursive base case 
applyToList (key:keys) t = (applyRel key t) ++ (applyToList keys t) --apply rel from the first of the keys, then concatenate recursively thru the list
