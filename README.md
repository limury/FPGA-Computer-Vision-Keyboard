# FPGA-Computer-Vision-Keyboard
This repo was submitted as the end of year project for Imperial College London, Information Systems Engineering first year.


# Function
This program, when connected to an FPGA (implementation not included in repo) allows to draw a computer keyboard on a piece of paper and will return anything typed on it as a string. The drawn keyboard does not need to be perfect, each key can actually be any width and height.

## Restrictions:
- Each row of the keyboard must be alligned and delimited above and below by a straight line.
- The keyboard must be placed approximately perpendicular to the input camera (above 30° and vertical and horizontal lines will be confused, above 10° and functionality will be reduced.
- Each finger that you want to type with must have some green component or marked with a green marker or sticker. (To be fixed in the future)
- The keyboard MUST be contained within 4 red marks at each corner. These must be quite large for the camera to see them and distinctly tell they are red. (See img folder for reference)

# TODO
- fixKeyboard
- Implement secondary keys
- Make keyboard function without green marks on fingers
- Adjust return for getKey function
