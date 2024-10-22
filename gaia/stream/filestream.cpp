#include "filestream.h"

FileStream::FileStream(std::string const& path) :
	m_path(path),
	m_file(path) {

}

std::string FileStream::get_path() const {
	return m_path;
}

int FileStream::get_line_number() const {
	return m_line_number;
}

int FileStream::get_column_number() const {
	return m_column_number;
}

bool FileStream::at_end() const {
	return m_file.eof();
}

int FileStream::get_char() {
	int ch = m_file.get();
	if (ch == '\n') {
		m_cache.clear();
		++m_line_number;
		m_column_number = 1;
	}
	else {
		m_cache.push_back(ch);
		++m_column_number;
	}
	return ch;
}

std::string FileStream::get_current_line() {
	return m_cache;
}
