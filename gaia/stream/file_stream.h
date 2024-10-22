#ifndef FILE_STREAM_H
#define FILE_STREAM_H

#include <stream/documentstream.h>
#include <fstream>

class FileStream : public DocumentStream {
public:
	FileStream(std::filesystem::path const& path);

	auto get_path() const -> std::filesystem::path override;
	auto get_line_number() const -> int override;
	auto get_column_number() const -> int override;

	auto at_end() const -> bool override;
	auto get_char() -> int override;

	auto get_current_line() -> std::string override;

private:
	std::filesystem::path m_path;
	std::ifstream m_file;
	int m_line_number = 1;
	int m_column_number = 1;
	std::string m_cache;
};

#endif // FILE_STREAM_H
