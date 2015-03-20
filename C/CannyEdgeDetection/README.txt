Developed using a modification of code provided by Dr. Niels Lobo, for the Robot Vision Undergrad course at UCF.
The program (at command line) prompts the user for a "sigma" (level of Gaussian Blur) as well as a "percent" (the threshold level).
This program takes in a 256x256 PGM image file, named Garb34.pgm, and outputs three new PGM files --
CannyMagGrad.pgm: shows the Gradient of Magnitudes throughout the image
CannyPeaks.pgm: Provides a histogram of where all of the edge peaks are.
CannyFinal.pgm: Runs the CannyPeaks file through a double-threshold filter to provide a finalized edge detection image.
