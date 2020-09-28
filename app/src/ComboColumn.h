#include "gtkmm/treemodel.h"

class ComboColumn : public Gtk::TreeModel::ColumnRecord {
public:
    ComboColumn() {
        add(m_col_type);
    }

    Gtk::TreeModelColumn<Glib::ustring> m_col_type;
};
