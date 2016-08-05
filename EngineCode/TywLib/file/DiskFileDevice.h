#ifndef _DISK_FILE_DEVICE_H_
#define _DISK_FILE_DEVICE_H_



class DiskFileDevice: public FileDevice
{
public:
	DiskFileDevice();
	~DiskFileDevice();

	//Open file for reading
	virtual std::ifstream&				ROpen(std::string& name, std::string& path);

	//close ifstream file
	virtual void						RClose();

	//Open file for writing
	virtual  std::ofstream&				WOpen(std::string& name, std::string& path);

	//close ofstrema file
	virtual void						WClose();

	//return unique device id
	virtual int							GetId() const { return m_iId; }

	//returns true if ofstream is opened
	virtual bool						IsWOpened() const { return  m_bWLoaded; }

	//returns true if ifstream is opened
	virtual bool						IsROpened() const { return m_bRLoaded; }
private:
	bool		m_bRLoaded;		//File for reading boolean
	bool		m_bWLoaded;		//File for writing boolean

private:
	int	m_iId;
};
#endif