#include "../s21_3d_viewer.h"
#include <wand/MagickWand.h>

int GenerateAnimatedGif(char *image_path, char *filename)
{
    MagickWand *mw = NULL;
    MagickBooleanType status;
    MagickWandGenesis();
    mw = NewMagickWand();
 
    /* Read all the images from the directory */
    status = MagickReadImages(mw, image_path, &exception);
    if (status == MagickFalse) {
        CatchException(&exception);
        return 1;
    }
 
    /* Set the GIF animation delay */
    status = MagickSetOption(mw, "delay", "10");
    if (status == MagickFalse) {
        CatchException(&exception);
        return 1;
    }
 
    /* Write the animation to a file */
    status = MagickWriteImages(mw, filename, MagickTrue, &exception);
    if (status == MagickFalse) {
        CatchException(&exception);
        exit(1);
    }

    /* Clean up */
    mw = DestroyMagickWand(mw);
    MagickWandTerminus();
    return 0;
}