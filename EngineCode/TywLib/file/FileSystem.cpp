#include <stdafx.h>
#include "FileDevice.h"
#include "DiskFileDevice.h"
#include "FileSystem.h"


//Opens disk file device if it is mounted
void FileSystem::OpenDiskFileDevice(int device, int mode)
{
	if (FileSystem::Device.Disk & device)
	{
		if (FileSystem::Mode.READ & mode)
		{

		}

		if (FileSystem::Mode.WRITE & mode)
		{

		}
	}
}

//Opens specified device in specified mode.
void FileSystem::Open(std::string name, std::string path, int device, int mode)
{
	OpenDiskFileDevice(device, mode);
}


// Mounts a file device to the file system
void FileSystem::Mount(std::shared_ptr<FileDevice> device)
{
	if (device == nullptr)
	{
		return;
	}

	auto iter = m_devices.find(device->GetId());
	if (iter != m_devices.end())
	{
		m_devices.insert(std::pair<int, std::shared_ptr<FileDevice> >(device->GetId(), device));
	}
}

// Unmounts a file device from the file system
void FileSystem::Unmount(std::shared_ptr<FileDevice> device)
{
	if (device == nullptr)
	{
		return;
	}

	auto iter = m_devices.find(device->GetId());
	if (iter != m_devices.end())
	{
		m_devices.erase(iter);
	}
}

//closes any opened device
void FileSystem::Close()
{
	for (auto& iterA : m_devices)
	{
		if (iterA.second->IsROpened())
		{
			iterA.second->RClose();
		}

		if (iterA.second->IsWOpened())
		{
			iterA.second->WClose();
		}
	}
}