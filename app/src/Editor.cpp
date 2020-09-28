#include "Editor.h"

Editor::Editor() : m_apply("Apply") {
    set_title("Tag Editor");
    set_position(Gtk::WindowPosition::WIN_POS_CENTER);
    set_type_hint(Gdk::WindowTypeHint::WINDOW_TYPE_HINT_DIALOG);
    set_size_request(400, 120);
    set_resizable(false);
    m_combo.set_margin_top(60);
    m_combo.set_margin_bottom(60);
    m_combo.set_margin_left(30);
    m_combo.set_margin_right(3);
    m_entry.set_margin_top(60);
    m_entry.set_margin_bottom(60);
    m_entry.set_margin_left(3);
    m_entry.set_margin_right(3);
    m_apply.set_margin_top(60);
    m_apply.set_margin_bottom(60);
    m_apply.set_margin_left(3);
    m_apply.set_margin_right(30);
    m_refTModel = Gtk::ListStore::create(m_columns);
    m_combo.set_model(m_refTModel);
    Gtk::TreeModel::Row row = *(m_refTModel->append());
    row[m_columns.m_col_type] = "Artist";
    m_combo.set_active(row);
    row = *(m_refTModel->append());
    row[m_columns.m_col_type] = "Title";
    m_combo.set_active(row);
    row = *(m_refTModel->append());
    row[m_columns.m_col_type] = "Album";
    m_combo.set_active(row);
    row = *(m_refTModel->append());
    row[m_columns.m_col_type] = "Genre";
    m_combo.set_active(row);
    row = *(m_refTModel->append());
    row[m_columns.m_col_type] = "Comment";
    m_combo.set_active(row);
    m_combo.pack_start(m_columns.m_col_type);
    m_combo.pack_start(m_cell);
    m_mainBox.add(m_combo);
    m_mainBox.pack_start(m_entry);
    m_mainBox.pack_start(m_apply);
    add(m_mainBox);
    show_all();
}

Editor::~Editor() {}
