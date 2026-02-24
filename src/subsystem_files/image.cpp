#include "main.h"
#include "liblvgl/lvgl.h"

//THANK YOU VALOR
//https://www.youtube.com/@valor2393S

void display_img_from_c_array(){
	// create a variable for the c array (image)
	LV_IMAGE_DECLARE(daniel_skill_issue_image);

	// declare and define the image object
	lv_obj_t* img = lv_image_create(lv_screen_active());

	// set the source data for the image
	lv_image_set_src(img, &daniel_skill_issue_image);

	//align image
	lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
}

void display_img_from_file(const void * src){

}