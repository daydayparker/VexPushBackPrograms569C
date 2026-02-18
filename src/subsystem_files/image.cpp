#include "main.h"
#include "liblvgl/lvgl.h"

void display_img_from_c_array(const lv_image_dsc_t image){
	// create a variable for the c array (image)
	LV_IMAGE_DECLARE(image);

	// declare and define the image object
	lv_obj_t* img = lv_image_create(lv_screen_active());

	// set the source data for the image
	lv_image_set_src(img, &image);

	//align image
	lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
}

void display_img_from_file(const void * src){

}