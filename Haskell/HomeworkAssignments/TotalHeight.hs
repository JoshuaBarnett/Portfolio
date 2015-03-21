module TotalHeight where
import WindowLayout

totalHeight :: WindowLayout -> Int
totalHeight window =
			case window of
			Horizontal [] -> 0
			Vertical [] -> 0
			Window {wname=_,width=_,height=x} -> x
			Vertical lst -> verticalHelper(Vertical(lst))
			Horizontal lst -> horizontalHelper(Horizontal(lst))

horizontalHelper :: WindowLayout -> Int
horizontalHelper window = 
			case window of
			Horizontal (x:xs) -> max (totalHeight(x)) (totalHeight(Horizontal (xs)))
			Vertical lst -> verticalHelper(Vertical(lst))
			otherwise -> totalHeight(window)

verticalHelper :: WindowLayout -> Int
verticalHelper window = 
			case window of
			Horizontal lst -> horizontalHelper(Horizontal(lst))
			Vertical (x:xs) -> (totalHeight(x)) + (verticalHelper(Vertical (xs)))
			otherwise -> totalHeight(window)
