#include <stdio.h>
#include <wand/magick_wand.h>

int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s: infile outfile\n", argv[0]);
    return 1;
  }

  const char *infile = argv[1];
  const char *outfile = argv[2];

  // initialize GraphicsMagick API
  InitializeMagick(NULL);

  // allocate Wand handle
  MagickWand *magick_wand = NewMagickWand();

  // read input image file
  MagickPassFail status = MagickReadImage(magick_wand, infile);

  // rotate image clockwise 30 degrees with black background
  if (status == MagickPass) {
    PixelWand *background = NewPixelWand();
    status = PixelSetColor(background, "#000000");
    status |= MagickRotateImage(magick_wand, background, 30);
    DestroyPixelWand(background);
  }

  // write output file
  if (status == MagickPass) {
    status = MagickWriteImage(magick_wand, outfile);
  }

  // release Wand handle
  status |= DestroyMagickWand(magick_wand);

  // diagnose any error
  if (status != MagickPass) {
    ExceptionType severity;
    char *description = MagickGetException(magick_wand, &severity);
    fprintf(stderr, "%.1024s (severity %d)\n", description, severity);
  }

  // destroy GraphicsMagick API
  DestroyMagick();

  return (status == MagickPass ? 0 : 1);
}
