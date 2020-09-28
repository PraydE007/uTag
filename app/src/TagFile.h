#pragma once

#include <vector>
#include <dirent.h>
#include <unistd.h>

#include "../../3dparty/lib1/tag.h"
#include "../../3dparty/lib1/fileref.h"

class TagFile {
public:
    TagFile(std::string filepath);

    static void ReadDir(std::vector<TagFile>& vec, std::string dir, bool recursive);

    bool RewriteFile();

    void SetArtist(std::string artist);
    void SetTitle(std::string title);
    void SetAlbum(std::string album);
    void SetGenre(std::string genre);
    void SetComment(std::string comment);

    std::string GetFilename(void) const;
    std::string GetFilepath(void) const;
    std::string GetArtist(void) const;
    std::string GetTitle(void) const;
    std::string GetAlbum(void) const;
    std::string GetGenre(void) const;
    std::string GetComment(void) const;

private:
    TagLib::FileRef m_file;
    TagLib::Tag* m_tag;

    std::string m_artist;
    std::string m_title;
    std::string m_album;
    std::string m_genre;
    // std::string m_year;
    // std::string m_track;
    std::string m_comment;
    std::string m_filepath;
};
