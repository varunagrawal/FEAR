#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <glib.h>
#include <cstring>
#include <cstdlib>

#include "cv.h"
#include "fers.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

using namespace std;
using namespace cv;

GtkWidget *window, *image, *expression;
GtkWidget *vbox, *button_hbox, *image_hbox;
GtkWidget *expression_label;

char* file;


GdkPixbuf* convertOpenCVToGtk(Mat img)
{
	IplImage ipl_img = img;
	IplImage *gtk_img = &ipl_img;
	
	cvCvtColor(gtk_img, gtk_img, CV_BGR2RGB);
	
	GdkPixbuf *pix = gdk_pixbuf_new_from_data((guchar*)gtk_img->imageData, GDK_COLORSPACE_RGB, FALSE, gtk_img->depth, gtk_img->width, gtk_img->height, (gtk_img->widthStep), NULL, NULL);
	
	return pix;
	
}


char* get_file()
{
	GtkWidget *dialog = gtk_file_chooser_dialog_new("Open File", (GtkWindow *) window, GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
	
	if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
	{
		char *filename;
		
		filename = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER(dialog) );
		gtk_widget_destroy(dialog);

		return filename;
	}
	
}


void load_file(GtkWidget *widget, gpointer data)
{
	g_print("Loading file\n");
	file = get_file();
	
	Mat img = imread(file);
	//imshow("Opencv image", img);
	
	gtk_image_set_from_file(GTK_IMAGE(image), file);

	GdkPixbuf *pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(image));
	GdkPixbuf *scaled_image = gdk_pixbuf_scale_simple(pixbuf, 400, 400, GDK_INTERP_BILINEAR);

	gtk_image_set_from_pixbuf(GTK_IMAGE(image), scaled_image);	

	gtk_widget_queue_draw(image);

	gtk_label_set_text(GTK_LABEL(expression_label), "Image Loaded");
	
	g_print("File Loaded\n");
	g_print("%s\n", file);
	
	
}


void get_expression(GtkWidget *widget, gpointer data)
{
	int exp = 0;
	
	//Call recognition function here!
	//exp = predict(file);

	char* expression_image;
	
	switch(exp)
	{
	case 0:
		expression_image = "../smileys/neutral.jpg";
		
	case 1:
		expression_image = "../smileys/anger.jpg";
		
	case 2:
		expression_image = "../smileys/contempt.jpg";
		
	case 3:
		expression_image = "../smileys/disgust.jpg";
		
	case 4:
		expression_image = "../smileys/fear.jpg";
		
	case 5:
		expression_image = "../smileys/happy.jpg";
		
	case 6:
		expression_image = "../smileys/sad.jpg";
		
	case 7:
		expression_image = "../smileys/surprise.jpg";
		
	}


	gtk_image_set_from_file(GTK_IMAGE(expression), expression_image);
	
	gtk_label_set_text(GTK_LABEL(expression_label), "Expression Detected");

}


int main(int argc, char* argv[])
{
	gtk_init(&argc, &argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	
	gtk_window_set_title(GTK_WINDOW(window), "FERS");
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 500, 300);
	gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	
	vbox = gtk_vbox_new(FALSE, 5);
	
	button_hbox = gtk_hbox_new(TRUE, 3);

   	GtkWidget *load_button = gtk_button_new_with_label("Load");
	GtkWidget *run_button = gtk_button_new_with_label("Run");
	gtk_widget_set_size_request(load_button, 70, 30);
	gtk_widget_set_size_request(run_button, 70, 30);

	gtk_container_add(GTK_CONTAINER(button_hbox), load_button);
	gtk_container_add(GTK_CONTAINER(button_hbox), run_button);


	expression_label = gtk_label_new("Expression");
	
	image = gtk_image_new();
	expression = gtk_image_new();
	gtk_image_set_from_file(GTK_IMAGE(expression), "../smileys/neutral.jpg");	

	image_hbox = gtk_hbox_new(TRUE, 3);
	
	gtk_box_pack_start(GTK_BOX(image_hbox), image, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(image_hbox), expression, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), image_hbox, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), button_hbox, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), expression_label, FALSE, FALSE, 0);
	
	gtk_container_add(GTK_CONTAINER(window), vbox);

	

	int load_handler_id = g_signal_connect(G_OBJECT(load_button), "clicked", G_CALLBACK(load_file), NULL);
	
	g_signal_connect(G_OBJECT(run_button), "clicked", G_CALLBACK(get_expression), NULL);
	

	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	
	gtk_widget_show_all(window);
		
	gtk_main();

	return 0;
}


