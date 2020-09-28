#include "TagFile.h"

TagFile::TagFile(std::string filepath) : m_file(filepath.c_str()) {
    if (!m_file.isNull() && m_file.tag()
        && m_file.audioProperties())
    {
        m_tag = m_file.tag();
        m_artist = m_tag->artist().toCString();
        m_title = m_tag->title().toCString();
        m_album = m_tag->album().toCString();
        m_genre = m_tag->genre().toCString();
        // m_year = m_tag->year().toCString();
        // m_track = m_tag->track().toCString();
        m_comment = m_tag->comment().toCString();
        m_filepath = filepath;
    }
}

void TagFile::ReadDir(std::vector<TagFile>& vec, std::string dir, bool recursive) {
    DIR* dDir;
    struct dirent* ent;

    if ((dDir = opendir(dir.c_str())) != NULL && readlink(dir.c_str(), NULL, 0) == -1) {
        while ((ent = readdir(dDir)) != NULL) {
            if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, ".."))
                continue;
            std::string filepath = dir + (dir[dir.size() - 1] != '/' ? "/" : "") + ent->d_name;
            int flen = filepath.length();

            // MP3 AND RECURSIVE
            if (flen < 5 || filepath.substr(flen - 4, 4) != ".mp3") {
                if (recursive)
                    ReadDir(vec, filepath, true);
                continue;
            }

            TagLib::FileRef file(filepath.c_str());
            if (file.file()->isValid() && file.file()->audioProperties()
                && file.file()->audioProperties()->sampleRate() > 0)
                vec.push_back(TagFile(filepath));
        }
        closedir(dDir);
    }
}

bool TagFile::RewriteFile() {
    if (m_tag->artist().toCString() != m_artist)
        m_tag->setArtist(m_artist);
    if (m_tag->title().toCString() != m_title)
        m_tag->setTitle(m_title);
    if (m_tag->album().toCString() != m_album)
        m_tag->setAlbum(m_album);
    if (m_tag->genre().toCString() != m_genre)
        m_tag->setGenre(m_genre);
    if (m_tag->comment().toCString() != m_comment)
        m_tag->setComment(m_comment);
    if (m_file.save())
        return true;
    return false;
}

void TagFile::SetArtist(std::string artist) { m_artist = artist; }
void TagFile::SetTitle(std::string title) { m_title = title; }
void TagFile::SetAlbum(std::string album) { m_album = album; }
void TagFile::SetGenre(std::string genre) { m_genre = genre; }
void TagFile::SetComment(std::string comment) { m_comment = comment; }

std::string TagFile::GetFilename(void) const { return m_file.file()->name(); }
std::string TagFile::GetFilepath(void) const { return m_filepath; }
std::string TagFile::GetArtist(void) const { return m_artist; }
std::string TagFile::GetTitle(void) const { return m_title; }
std::string TagFile::GetAlbum(void) const { return m_album; }
std::string TagFile::GetGenre(void) const { return m_genre; }
std::string TagFile::GetComment(void) const { return m_comment; }
