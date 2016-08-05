#ifndef _FILE_SYSTEM_H_
#define _FILE_SYSTEM_H_

namespace
{
	class FileSystem
	{
		friend class DiskFileDevice;
	public:
		static struct _Mode
		{
			_Mode() :WRITE(1), READ(2), APPEND(4) {}
			int WRITE, READ, APPEND;
		}Mode;

		static struct _Device
		{
			_Device() : Disk(1) {}
			int Disk;
		}Device;

	public:
		//Opens file
		void		Open(std::string name, std::string path, int device, int mode);

		// Mounts a file device to the file system
		void		Mount(std::shared_ptr<FileDevice> device);

		// Unmounts a file device from the file system
		void		Unmount(std::shared_ptr<FileDevice> device);

		//closes any opened device
		void		Close();

	private:
		//Opens disk file device if it is mounted
		void		OpenDiskFileDevice(int device, int mode);
	private:
		std::map<int, std::shared_ptr<FileDevice> > m_devices;	//list of mounted devices
	};

	FileSystem::_Mode FileSystem::Mode;
	FileSystem::_Device FileSystem::Device;
}
#endif
