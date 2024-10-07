#include "game.h"
#include "image.h"

image sample_image;

Uint32 *screenPixels; // We store the information of RGBA in each Uint32
float rotation = 0;

void game_setup(){
    screenPixels = (Uint32*) malloc(SCREEN_WIDTH * SCREEN_HEIGHT * 4);
    load_image(&sample_image, "gameassets/meow.jpg");
}

void game_update(){
    for (int x = 0; x < SCREEN_WIDTH; x++){
        for (int y = 0; y < SCREEN_HEIGHT; y++){
            screenPixels[y*SCREEN_WIDTH + x] = 255 << 24;
        }
    }

    HMM_Mat4 trans_mat = HMM_MulM4(
        HMM_Translate((HMM_Vec3){{HALF_WIDTH, HALF_HEIGHT, 1}}),
        HMM_MulM4(
            HMM_MulM4(
                HMM_MulM4(
                HMM_Rotate_RH(rotation*3, (HMM_Vec3){0, 1, 0}),
                HMM_Rotate_RH(rotation*2, (HMM_Vec3){0, 0, 1})),
                HMM_Rotate_RH(rotation, (HMM_Vec3){1, 0, 0})),
            HMM_Translate((HMM_Vec3){-sample_image.width/2, -sample_image.height/2, 1}))
    );

    // 1. Put the rotation anchor of the image to the center of the image
    // 2. rotate the image
    // 3. Put the image at the center of the screen

    for (int x = 0; x < sample_image.width; x++){
        for (int y = 0; y < sample_image.height; y++){
            HMM_Vec4 pos_mat = (HMM_Vec4){x, y, 1, 1};
            pos_mat = HMM_MulM4V4(trans_mat, pos_mat);

            if (pos_mat.Y < 0 || pos_mat.X < 0 || pos_mat.Y >= SCREEN_HEIGHT || pos_mat.X >= SCREEN_WIDTH){
                continue;
            }
            screenPixels[(int)pos_mat.Y*SCREEN_WIDTH + (int)pos_mat.X] = get_image_pixel(&sample_image, x, y);
        }
    }
    rotation += 0.02f;
}

void game_end(){
    free(screenPixels);
}