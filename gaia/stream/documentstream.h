#ifndef DOCUMENTSTREAM_H
#define DOCUMENTSTREAM_H

#include <string>

class DocumentStream {
public:
	DocumentStream();
	virtual ~DocumentStream();

	virtual std::string get_path() const = 0;
	virtual int get_line_number() const = 0;
	virtual int get_column_number() const = 0;

	virtual bool at_end() const = 0;
	virtual int get_char() = 0;

	virtual std::string get_current_line() = 0;
};

#endif // DOCUMENTSTREAM_H
