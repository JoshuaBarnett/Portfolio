--hides and wraps the built in concatMap function in Haskell, using foldr.

module ConcatMap where
import Prelude hiding (concatMap)
concatMap :: (a -> [b]) -> [a] -> [b]
concatMap f ls = foldr (\l acc -> f l ++ acc) [] ls
