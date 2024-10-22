#include "file_stream.h"

FileStream::FileStream(std::filesystem::path const& path) :
	m_path(path),
	m_file(path) {}

auto FileStream::get_path() const -> std::filesystem::path {
	return m_path;
}

auto FileStream::get_line_number() const -> int {
	return m_line_number;
}

auto FileStream::get_column_number() const -> int {
	return m_column_number;
}

auto FileStream::at_end() const -> bool {
	return m_file.eof();
}

auto FileStream::get_char() -> int {
	const auto ch = m_file.get();
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

auto FileStream::get_current_line() -> std::string {
	return m_cache;
}
