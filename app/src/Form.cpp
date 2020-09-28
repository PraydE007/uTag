#include "Form.h"

Form::Form(int argc, char *argv[])
: m_iOpenFile("app/res/file-chooser.png"),
  m_iEditSongs("app/res/file-edit.png"),
  m_iApplyChanges("app/res/apply.png")
{
    set_title("uTag | mp3 tag changer");
    set_position(Gtk::WindowPosition::WIN_POS_CENTER);
    set_default_size(800, 600);
    set_border_width(2);

    m_bOpenFile.set_image(m_iOpenFile);
    m_bOpenFile.set_size_request(50, 50);
    m_bEditSongs.set_image(m_iEditSongs);
    m_bEditSongs.set_size_request(50, 50);
    m_bApplyChanges.set_image(m_iApplyChanges);
    m_bApplyChanges.set_size_request(50, 50);
    m_leftBox.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
    m_leftBox.add(m_bOpenFile);
    m_leftBox.add(m_bEditSongs);
    m_leftBox.add(m_bApplyChanges);
    m_refTreeModel = Gtk::ListStore::create(m_columns);
    SetupTree();
    m_scrolledWindow.set_hexpand(true);
    m_scrolledWindow.set_vexpand(true);
    m_scrolledWindow.add(m_tree);
    m_rightBox.add(m_scrolledWindow);
    m_mainBox.add(m_leftBox);
    m_mainBox.add(m_rightBox);
    ConnectSignals();
    add(m_mainBox);
    if (argc > 1) {
        TagFile::ReadDir(m_tagFiles, argv[1], false);
        UpdateList();
    }
    show_all();
    m_edit.hide();
}

Form::~Form() {}

void Form::SetupTree() {
    m_tree.set_margin_start(3);
    m_tree.set_margin_bottom(3);
    m_tree.set_margin_end(3);
    m_tree.set_margin_top(3);
    m_tree.set_model(m_refTreeModel);
    m_tree.append_column("ID", m_columns.m_col_id);
    m_tree.append_column("Artist", m_columns.m_col_artist);
    m_tree.append_column("Title", m_columns.m_col_title);
    m_tree.append_column("Album", m_columns.m_col_album);
    m_tree.append_column("Genre", m_columns.m_col_genre);
    m_tree.append_column("Comment", m_columns.m_col_comment);
    m_tree.append_column("Filepath", m_columns.m_col_path);
    auto selection = m_tree.get_selection();
    selection->set_mode(Gtk::SelectionMode::SELECTION_MULTIPLE);
    SetTreeSortable();
}

void Form::OnFileChooser() {
    Gtk::FileChooserDialog dialog("Please select a folder",
        Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
    dialog.set_transient_for(*this);
    dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("Select", Gtk::RESPONSE_OK);

    int result = dialog.run();
    if (result == Gtk::RESPONSE_OK) {
        ClearAll();
        m_directory = dialog.get_filename();
        TagFile::ReadDir(m_tagFiles, m_directory, false);
        UpdateList();
    }
}

void Form::ConnectSignals() {
    m_bOpenFile.signal_clicked().connect(sigc::mem_fun(*this, &Form::OnFileChooser));
    m_bEditSongs.signal_clicked().connect(sigc::mem_fun(*this, &Form::EditorInFocus));
    m_edit.m_apply.signal_clicked().connect(sigc::mem_fun(*this, &Form::OnApplyButton));
    m_bApplyChanges.signal_clicked().connect(sigc::mem_fun(*this, &Form::ApplyChanges));
}

void Form::SetTreeSortable() {
    auto column = m_tree.get_column(0);
    column->set_sort_column(m_columns.m_col_id);
    column = m_tree.get_column(1);
    column->set_sort_column(m_columns.m_col_artist);
    column = m_tree.get_column(2);
    column->set_sort_column(m_columns.m_col_title);
    column = m_tree.get_column(3);
    column->set_sort_column(m_columns.m_col_album);
    column = m_tree.get_column(4);
    column->set_sort_column(m_columns.m_col_genre);
    column = m_tree.get_column(5);
    column->set_sort_column(m_columns.m_col_comment);
    column = m_tree.get_column(6);
    column->set_sort_column(m_columns.m_col_path);
}

void Form::ClearList() {
    m_refTreeModel.get()->clear();
    m_size = 0;
    show_all();
}

void Form::ClearAll() {
    ClearList();
    m_tagFiles.erase(m_tagFiles.begin(), m_tagFiles.end());
    show_all();
}

void Form::UpdateList() {
    for (TagFile& file : m_tagFiles)
        PushSong(file);
    show_all();
}

void Form::PushSong(TagFile& song) {
    Gtk::TreeModel::Row row = *(m_refTreeModel->append());
    row[m_columns.m_col_id] = m_size + 1;
    row[m_columns.m_col_artist] = song.GetArtist();
    row[m_columns.m_col_title] = song.GetTitle();
    row[m_columns.m_col_album] = song.GetAlbum();
    row[m_columns.m_col_genre] = song.GetGenre();
    row[m_columns.m_col_comment] = song.GetComment();
    row[m_columns.m_col_path] = song.GetFilepath();
    m_size++;
}

void Form::EditorInFocus() {
    auto selection = m_tree.get_selection();
    int count = selection->count_selected_rows();

    if (count > 0) {
        m_edit.m_entry.set_text("");
        m_edit.set_transient_for(*this);
        m_edit.set_modal(true);
        m_edit.show();
    }
}

void Form::OnApplyButton() {
    auto selection = m_tree.get_selection();
    int count = selection->count_selected_rows();

    if (count > 0) {
        auto comboSlct = m_edit.m_combo.get_active_row_number();
        for (auto& path : selection->get_selected_rows()) {
            auto it = m_refTreeModel->get_iter(path);
            auto row = *it;
            size_t id = row->get_value(m_columns.m_col_id) - 1;
            if (comboSlct == 0)
                m_tagFiles[id].SetArtist(m_edit.m_entry.get_text());
            else if (comboSlct == 1)
                m_tagFiles[id].SetTitle(m_edit.m_entry.get_text());
            else if (comboSlct == 2)
                m_tagFiles[id].SetAlbum(m_edit.m_entry.get_text());
            else if (comboSlct == 3)
                m_tagFiles[id].SetGenre(m_edit.m_entry.get_text());
            else if (comboSlct == 4)
                m_tagFiles[id].SetComment(m_edit.m_entry.get_text());
        }
        m_edit.hide();
        ClearList();
        UpdateList();
        show_all();
    }
}

void Form::MessageDialog(Gtk::Window& parent, std::string msg, std::string descr, Gtk::MessageType type) {
    Gtk::MessageDialog dialog(parent, msg, type);

    dialog.set_secondary_text(descr);
    dialog.run();
}

void Form::ApplyChanges() {
    for (TagFile& tf : m_tagFiles) {
        if (!tf.RewriteFile()) {
            MessageDialog(
                *this,
                "Something went wrong!",
                "Data may not be compatible with ID3 type",
                Gtk::MESSAGE_ERROR
            );
            break;
        }
    }
    MessageDialog(
        *this,
        "Save success!",
        "Tags successfully saved to the files.",
        Gtk::MESSAGE_INFO
    );
}

