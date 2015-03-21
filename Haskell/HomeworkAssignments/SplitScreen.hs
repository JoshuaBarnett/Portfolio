module SplitScreen where
import WindowLayout

splitScreen :: String -> WindowLayout -> WindowLayout
splitScreen name w1 =
			case w1 of
			Window {wname=z,width=x,height=y} -> if (z == name)
												then Horizontal [(Window {wname = name,width = ((x) `div` 2),height = y}),(Window {wname = name,width = ((x) `div` 2),height = y})]
												else (Window {wname = z,width = x,height = y})
			Horizontal lst -> Horizontal (horizontalHelper name lst)
			Vertical lst -> Vertical (verticalHelper name lst)

horizontalHelper :: String -> [WindowLayout] -> [WindowLayout]
horizontalHelper name window = 
			case window of
			[] -> window
			(x:xs) -> (splitScreen name x) : horizontalHelper name xs

verticalHelper :: String -> [WindowLayout] -> [WindowLayout]
verticalHelper name window = 
			case window of
			[] -> window
			(x:xs) -> (splitScreen name x) : verticalHelper name xs
