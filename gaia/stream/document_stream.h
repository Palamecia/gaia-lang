#ifndef DOCUMENT_STREAM_H
#define DOCUMENT_STREAM_H

#include <string>

class DocumentStream {
public:
	DocumentStream();
	DocumentStream(const DocumentStream&) = delete;
	DocumentStream(DocumentStream&&) = delete;
	virtual ~DocumentStream();

	auto operator=(const DocumentStream&) -> DocumentStream& = delete;
	auto operator=(DocumentStream&&) -> DocumentStream& = delete;

	virtual auto get_path() const -> std::filesystem::path = 0;
	virtual auto get_line_number() const -> int = 0;
	virtual auto get_column_number() const -> int = 0;

	virtual auto at_end() const -> bool = 0;
	virtual auto get_char() -> int = 0;

	virtual auto get_current_line() -> std::string = 0;
};

#endif // DOCUMENT_STREAM_H
