#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <stdlib.h>
#include <string.h>
#include "html.h"

typedef struct {
    GtkWidget *notebook;
} Browser;

void open_new_tab(Browser *browser, const char *url) {
    // Create new WebView for the tab
    WebKitWebView *web_view = WEBKIT_WEB_VIEW(webkit_web_view_new());
    webkit_web_view_load_uri(web_view, url);

    // Create a label for the tab title (simple "New Tab" for now)
    GtkWidget *label = gtk_label_new("New Tab");

    // Add the WebView inside a scrolled window (scroll support)
    GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scrolled), GTK_WIDGET(web_view));

    // Append the page to the notebook, with the label
    gint page_num = gtk_notebook_append_page(GTK_NOTEBOOK(browser->notebook), scrolled, label);

    gtk_widget_show_all(scrolled);

    // Switch to the new tab
    gtk_notebook_set_current_page(GTK_NOTEBOOK(browser->notebook), page_num);

    // Store web_view pointer in the scrolled window for easy access later (optional)
    g_object_set_data(G_OBJECT(scrolled), "web_view", web_view);
}

// Search button callback — loads search URL in the current tab's web view
void on_search_clicked(GtkButton *button, gpointer user_data) {
    Browser *browser = (Browser *)user_data;

    GtkEntry *entry = GTK_ENTRY(g_object_get_data(G_OBJECT(button), "search_entry"));
    const gchar *query = gtk_entry_get_text(entry);
    if (strlen(query) == 0) return;

    // Get current page scrolled window and its webview
    gint current_page = gtk_notebook_get_current_page(GTK_NOTEBOOK(browser->notebook));
    GtkWidget *scrolled = gtk_notebook_get_nth_page(GTK_NOTEBOOK(browser->notebook), current_page);
    WebKitWebView *web_view = WEBKIT_WEB_VIEW(g_object_get_data(G_OBJECT(scrolled), "web_view"));

    gchar *url = g_strdup_printf("https://duckduckgo.com/?q=%s", query);
    g_print("Searching: %s\n", url);

    webkit_web_view_load_uri(web_view, url);

    g_free(url);
}

// Callback to create new tab when button clicked
void on_new_tab_clicked(GtkButton *button, gpointer user_data) {
    Browser *browser = (Browser *)user_data;
    open_new_tab(browser, "https://duckduckgo.com");
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    Browser browser;

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 700);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Main vertical box container
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Horizontal box for search bar + new tab button
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    GtkWidget *search_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(search_entry), "Type your search query...");
    gtk_box_pack_start(GTK_BOX(hbox), search_entry, TRUE, TRUE, 0);

    GtkWidget *search_button = gtk_button_new_with_label("Search");
    gtk_box_pack_start(GTK_BOX(hbox), search_button, FALSE, FALSE, 0);

    GtkWidget *new_tab_button = gtk_button_new_with_label("+");
    gtk_box_pack_start(GTK_BOX(hbox), new_tab_button, FALSE, FALSE, 0);

    // Notebook for tabs
    browser.notebook = gtk_notebook_new();
    gtk_box_pack_start(GTK_BOX(vbox), browser.notebook, TRUE, TRUE, 0);

    // Connect button signals
    g_signal_connect(search_button, "clicked", G_CALLBACK(on_search_clicked), &browser);
    g_object_set_data(G_OBJECT(search_button), "search_entry", search_entry);

    g_signal_connect(new_tab_button, "clicked", G_CALLBACK(on_new_tab_clicked), &browser);

    // Open initial tab (Google or any URL)
    open_new_tab(&browser, "https://duckduckgo.com");

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
