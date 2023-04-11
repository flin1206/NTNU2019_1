//#include <config.h>
#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include <stdint.h>

struct _sBmpHeader
{
    char		bm[2];
    uint32_t	size;
    uint32_t	reserve;
    uint32_t	offset;
    uint32_t	header_size;
    uint32_t	width;
    uint32_t	height;
    uint16_t	planes;
    uint16_t	bpp;
    uint32_t	compression;
    uint32_t	bitmap_size;
    uint32_t	hres;
    uint32_t	vres;
    uint32_t	used;
    uint32_t	important;
}__attribute__ ((__packed__));

typedef struct _sBmpHeader sBmpHeader;

static void
on_open_image (GtkButton* button, gpointer user_data)
{
	GtkWidget *image = GTK_WIDGET (user_data);
	GtkWidget *toplevel = gtk_widget_get_toplevel (image);
	GtkFileFilter *filter = gtk_file_filter_new ();
	GtkWidget *dialog = gtk_file_chooser_dialog_new (_("Open image"),
	                                                 GTK_WINDOW (toplevel),
	                                                 GTK_FILE_CHOOSER_ACTION_OPEN,
	                                                 GTK_STOCK_OK, GTK_RESPONSE_ACCEPT,
	                                                 GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
	                                                 NULL);

	gtk_file_filter_add_pixbuf_formats (filter);
	gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (dialog),
	                             filter);
	
	switch (gtk_dialog_run (GTK_DIALOG (dialog)))
	{
		case GTK_RESPONSE_ACCEPT:
		{
			gchar *filename = 
				gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
			//gtk_image_set_from_file (GTK_IMAGE (image), filename);
			
			/*
			GdkPixbuf *
gdk_pixbuf_new (GdkColorspace colorspace,
                gboolean has_alpha,
                int bits_per_sample,
                int width,
                int height);
            */
            
            FILE	*pFile = NULL;
            
            if( ( pFile = fopen( filename, "rb" ) ) == NULL )
            {
                printf( "File could not be opened!\n" );
                return;
            }
    
            sBmpHeader	header;
            fread( &header, 54, 1, pFile );
            
            GdkPixbuf *pBuf = gdk_pixbuf_new( GDK_COLORSPACE_RGB, 0, 8, header.width, header.height );
            
            guchar *pixels = gdk_pixbuf_get_pixels ( pBuf );
            
            size_t offset = 0;
            
            while( !feof( pFile ) )
            {
                uint8_t	original[1024] = {0};
        
                size_t count = fread( original, 1, 1024, pFile );
                
                memcpy( pixels + offset, original, count );
                
                offset += count;   
            }
			
			gtk_image_set_from_pixbuf (GTK_IMAGE (image), pBuf );
			
			
			break;
		}
		default:
			break;
	}
	gtk_widget_destroy (dialog);
}
	

static GtkWidget*
create_window (void)
{
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *image;
	GtkWidget *box;

	/* Set up the UI */
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "image-viewer-c");

	box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	button = gtk_button_new_with_label (_("Open image"));
	image = gtk_image_new ();

	gtk_box_pack_start (GTK_BOX (box), image, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (box), button, FALSE, FALSE, 0);

	gtk_container_add (GTK_CONTAINER (window), box);

	/* Connect signals */

	/* Show open dialog when opening a file */
	g_signal_connect (button, "clicked", G_CALLBACK (on_open_image), image);
	
	/* Exit when the window is closed */
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	
	return window;
}


int
main (int argc, char *argv[])
{
 	GtkWidget *window;


#ifdef ENABLE_NLS
	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
#endif

	
	gtk_init (&argc, &argv);

	window = create_window ();
	gtk_widget_show_all (window);

	gtk_main ();
	return 0;
}

