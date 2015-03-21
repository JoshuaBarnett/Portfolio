module ToCharFun where

toCharFun :: (Int -> Int) -> (Char -> Char)
toCharFun intFun = (\x -> (toEnum (intFun(fromEnum(x)))))
