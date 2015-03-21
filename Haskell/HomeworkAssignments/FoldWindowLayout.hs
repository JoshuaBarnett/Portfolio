-- In this problem you will write a function
--foldWindowLayout :: ((String,Int,Int) -> r) -> ([r] -> r) -> ([r] -> r)
---> WindowLayout -> r
--that abstracts from all the WindowLayout examples we have seen (such as those earlier in this homework
--and on the course examples page). For each type r, the function foldWindowLayout takes 3 functions:
--wf, hf, and vf, which correspond to the three variants in the grammar for WindowLayout. In more detail:
--• wf, operates on a tuple of the information from a Window variant and returns a value of type r,
--• hf, takes a list of the results of mapping (foldWindowLayout wf hf vf) over the list in a
--Horizontal variant, and
--• vf, takes a list of the results of mapping (foldWindowLayout wf hf vf) over the list in a
--Vertical variant.

module FoldWindowLayout where
import WindowLayout

foldWindowLayout :: ((String, Int, Int) -> r) -> ([r] -> r) -> ([r] -> r) -> WindowLayout -> r
foldWindowLayout wf hf vf (Horizontal lst) = hf (map (foldWindowLayout wf hf vf) lst)
foldWindowLayout wf hf vf (Vertical lst) = vf (map (foldWindowLayout wf hf vf) lst)
foldWindowLayout wf hf vf (Window {wname = x, width = y, height = z}) = wf (x, y, z)
