#ifndef FILESTREAM_H
#define FILESTREAM_H

#include <stream/documentstream.h>
#include <fstream>

class FileStream : public DocumentStream {
public:
	FileStream(std::string const& path);

	std::string get_path() const override;
	int get_line_number() const override;
	int get_column_number() const override;

	bool at_end() const override;
	int get_char() override;

	std::string get_current_line() override;

private:
	std::string m_path;
	std::ifstream m_file;
	std::size_t m_line_number = 1;
	std::size_t m_column_number = 1;
	std::string m_cache;
};

#endif // FILESTREAM_H
