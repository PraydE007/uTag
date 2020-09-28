#pragma once

#include "gtkmm/image.h"
#include "gtkmm/button.h"
#include "gtkmm/window.h"
#include "gtkmm/label.h"
#include "gtkmm/box.h"
#include "gtkmm/scrolledwindow.h"
#include "gtkmm/filechooserdialog.h"
#include "gtkmm/treeview.h"
#include "gtkmm/liststore.h"
#include "gtkmm/messagedialog.h"

#include "ModelColumn.h"
#include "Editor.h"
#include "TagFile.h"

class Form : public Gtk::Window {
public:
    Form(int argc, char *argv[]);
    virtual ~Form();

    void SetupTree();
    void SetTreeSortable();
    void OnFileChooser();
    void ConnectSignals();
    void ClearList();
    void ClearAll();
    void UpdateList();
    void EditorInFocus();
    void OnApplyButton();
    void ApplyChanges();
    static void MessageDialog(Gtk::Window& parent, std::string msg, std::string descr, Gtk::MessageType type);

    void PushSong(TagFile& song);

private:
    Editor m_edit;

    Gtk::Box m_mainBox;
    Gtk::Box m_leftBox;
    Gtk::Box m_rightBox;

    Gtk::Image m_iOpenFile;
    Gtk::Button m_bOpenFile;
    Gtk::Image m_iEditSongs;
    Gtk::Button m_bEditSongs;
    Gtk::Image m_iApplyChanges;
    Gtk::Button m_bApplyChanges;

    size_t m_size{0};
    Gtk::TreeView m_tree;
    ModelColumns m_columns;
    Gtk::ScrolledWindow m_scrolledWindow;
    Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

    std::string m_directory;
    std::vector<TagFile> m_tagFiles;
};
