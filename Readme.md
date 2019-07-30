## c++ implementation of filtering using gabor kernels.
## useful to filtering out textures (repeating localized patters) in an image
## enter the path of the image to be used in command line as an argument.

Texture filtering using gabor filter: Gabor is used for feature extraction mainly texture or in other words repeating patterns in local areas(size of the kernel), it has multiple parameters however theta is an important one as it defines the angular rotation(orientation) of the filter. Since its applied as a 2D convolutional filter, it has an averaging/blurring effect on the image. Output results do indicate a blurring of continuous background ie image area having the same localized repeating patterns. <br>
Since these parameters are tuned for 1280*720 sized images, it may not yield the desired results for other sized images.
<br><br>
