#include <stdafx.h>
#include "FileDevice.h"
#include "DiskFileDevice.h"



/*
=========================
DiskFileDevice()
=========================
*/
DiskFileDevice::DiskFileDevice():m_bRLoaded(false), m_bWLoaded(false), m_iId(0)
{

}


/*
=========================
~DiskFileDevice()
=========================
*/
DiskFileDevice::~DiskFileDevice()
{

}
/*
=========================
ROpen();
=========================
*/
std::ifstream&   DiskFileDevice::ROpen(std::string& name, std::string& path)
{
	if (!m_bRLoaded)
	{
		read.open((path + name).c_str());
		if (read.is_open())
		{
			m_bRLoaded = true;
		}
	}
	return read;
}


/*
=========================
RClose();
=========================
*/
void DiskFileDevice::RClose()
{
	if (m_bRLoaded)
	{
		m_bRLoaded = false;
		read.close();
	}
}


/*
=========================
WOpen();
=========================
*/
std::ofstream&  DiskFileDevice::WOpen(std::string& name, std::string& path)
{
	if (!m_bWLoaded)
	{
		write.open((path + name).c_str());
		if (write.is_open())
		{
			m_bWLoaded = true;
			
		}
	}
	return write;
}


/*
=========================
WClose();
=========================
*/
void DiskFileDevice::WClose()
{
	if (m_bWLoaded)
	{
		m_bWLoaded = false;
		write.close();
	}
}