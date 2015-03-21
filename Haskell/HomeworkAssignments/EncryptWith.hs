--Write a higher-order function
--encryptWith :: (Int -> Int) -> [String] -> [String]
--that takes a cryptographic function, f, and a list of strings text, and returns a (poorly) encrypted version
--of each string in the list by using toCharFun f to encrypt each character.

module EncryptWith where

encryptWith :: (Int -> Int) -> [String] -> [String]
encryptWith pred [] = []
encryptWith pred (str:rest) = (encryptHelp pred str) : (encryptWith pred rest)

encryptHelp :: (Int -> Int) -> String -> String
encryptHelp pred [] = []
encryptHelp pred (x:xs) = (toEnum(pred(fromEnum(x)))) : (encryptHelp pred xs)
