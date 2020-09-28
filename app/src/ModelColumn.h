#include "gtkmm/treemodel.h"

class ModelColumns : public Gtk::TreeModel::ColumnRecord {
public:
    ModelColumns() {
        add(m_col_id); add(m_col_artist);
        add(m_col_title); add(m_col_album);
        add(m_col_genre); add(m_col_comment);
        add(m_col_path);
    }

    Gtk::TreeModelColumn<unsigned int> m_col_id;
    Gtk::TreeModelColumn<Glib::ustring> m_col_artist;
    Gtk::TreeModelColumn<Glib::ustring> m_col_title;
    Gtk::TreeModelColumn<Glib::ustring> m_col_album;
    Gtk::TreeModelColumn<Glib::ustring> m_col_genre;
    Gtk::TreeModelColumn<Glib::ustring> m_col_comment;
    Gtk::TreeModelColumn<Glib::ustring> m_col_path;
};
