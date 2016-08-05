#ifndef _FILE_DEVICE_H_
#define _FILE_DEVICE_H_

/*
===========================================================

	Abstract base class, which offers functionality
	for opening and closing file

===========================================================
*/
class FileDevice
{
public:
		FileDevice() {}
		virtual ~FileDevice() {}

		//Open file for reading
		virtual std::ifstream&			ROpen(std::string& name, std::string& path) = 0;

		//close ifstream file
		virtual void					RClose() = 0;

		//Open file for writing
		virtual std::ofstream&			WOpen(std::string& name, std::string& path) = 0;

		//close ofstrema file
		virtual void					WClose() = 0;

		//return unique device id
		virtual int						GetId() const = 0;

		//returns true if ofstream is opened
		virtual bool					IsWOpened() const = 0;

		//returns true if ifstream is opened
		virtual bool					IsROpened() const = 0;

protected:
	std::ifstream read;
	std::ofstream write;
};
#endif
