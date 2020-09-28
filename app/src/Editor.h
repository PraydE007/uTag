#pragma once

#include "gtkmm/button.h"
#include "gtkmm/window.h"
#include "gtkmm/label.h"
#include "gtkmm/box.h"
#include "gtkmm/liststore.h"
#include "gtkmm/combobox.h"
#include "gtkmm/entry.h"

#include "TagFile.h"
#include "ComboColumn.h"

class Editor : public Gtk::Window {
public:
    Editor();
    virtual ~Editor();

    Gtk::Box m_mainBox;
    Gtk::Entry m_entry;
    Gtk::Button m_apply;
    Gtk::ComboBox m_combo;
    Gtk::CellRendererText m_cell;
    Glib::RefPtr<Gtk::ListStore> m_refTModel;
    ComboColumn m_columns;
};
