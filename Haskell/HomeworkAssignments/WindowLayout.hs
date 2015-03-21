-- This is a support file for several of the modules, called WindowLayout. This is used in SplitScreen, TotalHeight, and FoldWindowLayout

-- $Id: WindowLayout.hs,v 1.1 2015/02/12 04:23:12 leavens Exp leavens $
module WindowLayout where
data WindowLayout = Window {wname :: String, width :: Int, height :: Int}
                  | Horizontal [WindowLayout]
                  | Vertical [WindowLayout]
                  deriving (Show, Eq)
